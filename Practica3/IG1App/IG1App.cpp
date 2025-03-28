#include "IG1App.h"

#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"

#include <iostream>

using namespace std;

// static single instance (singleton pattern)
IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

// Print OpenGL errors and warnings
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const GLchar* message, const void* userParam)
{
	const char* prefix = (type == GL_DEBUG_TYPE_ERROR)
		? "\x1b[31m[ERROR]\x1b[0m "
		: "\x1b[33m[WARNING]\x1b[0m ";
	cout << prefix << message << endl;
}

void
IG1App::close()
{
	cout << "Closing GLFW...\n";
	glfwSetWindowShouldClose(mWindow, true); // stops main loop
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWindow == 0) // if not intilialized
		init();

	// IG1App main loop
	while (!glfwWindowShouldClose(mWindow)) {

		mNextUpdate = glfwGetTime() + FRAME_DURATION;

		// Redisplay the window if needed
		if (mNeedsRedisplay) {
			display();
			mNeedsRedisplay = false;
		}

		if (mUpdateEnable && mNextUpdate > glfwGetTime()) {
			
			mScenes[mCurrentScene]->update
			();
			mNeedsRedisplay = true;

			mNextUpdate = glfwGetTime() + FRAME_DURATION;

			glfwWaitEventsTimeout(mNextUpdate - glfwGetTime());
		}
		else glfwWaitEvents();

	}

	destroy();
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH);
	mCamera = new Camera(mViewPort);
	mScenes.push_back(new Scene6);
	mScenes.push_back(new Scene1);
	mScenes.push_back(new Scene2);
	mScenes.push_back(new Scene3);
	mScenes.push_back(new Scene4);
	mScenes.push_back(new Scene5);
	mScenes.push_back(new Scene6);

	mCamera->set2D();

	for (auto& s : mScenes)
		s->init();

	mScenes[0]->load();
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting GLFW...\n";
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // enable on macOS

	// Create window with its associated OpenGL context, return window's pointer
	mWindow = glfwCreateWindow(mWinW, mWinH, "IG1App", nullptr, nullptr);

	if (mWindow == nullptr) {
		glfwTerminate();
		throw std::logic_error("cannot create GLFW window");
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize OpenGL extension library
	if (GLenum err = glewInit(); err != GLEW_OK) {
		glfwTerminate();
		throw std::logic_error("Error while loading extensions: "s +
		                       reinterpret_cast<const char*>(glewGetErrorString(err)));
	}

	// Callback registration
	glfwSetWindowSizeCallback(mWindow, s_resize);
	glfwSetCharCallback(mWindow, s_key);
	glfwSetKeyCallback(mWindow, s_specialkey);
	glfwSetWindowRefreshCallback(mWindow, s_display);

	// Error message callback (all messages)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0u, 0, GL_TRUE);
	glDebugMessageCallback(debugCallback, nullptr);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::destroy()
{ // release memory and resources
	for (Scene* scene : mScenes)
		delete scene;
	mScenes.clear();

	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;

	glfwTerminate();
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	mScenes[mCurrentScene]->render(*mCamera); // uploads the viewport and camera to the GPU

	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned int key)
{
	bool need_redisplay = true;

	switch (key) {
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		case 'p':
			mCamera->changePrj();
			break;
		case 'a':
			mCamera->moveLR(-3.0); // Hacia la izquierda
			break;
		case 'd':
			mCamera->moveLR(3.0); // Hacia la derecha
			break;
		case 'w':
			mCamera->moveUD(3.0); // Hacia arriba
			break;
		case 's':
			mCamera->moveUD(-3.0); // Hacia abajo
			break;
		case 'W':
			mCamera->moveFB(3.0); // Hacia adelante
			break;
		case 'S':
			mCamera->moveFB(-3.0); // Hacia atr�s
			break;
		case 'O':
			mCamera->orbit(.8, .3);
			break;
		case 'k':
			mCamera->setCenital();
			break;
		case 'u':
			mUpdateEnable = !mUpdateEnable;
			break;
		case 'f':
			mScenes[mCurrentScene]->printscreen();
			break;
		default:
			if (key >= '0' && key <= '9') {
				if (!changeScene(key - '0')) {
					cout << "[NOTE] There is no scene " << char(key) << ".\n";
					need_redisplay = false;
				}
			}
			else
				need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

void
IG1App::specialkey(int key, int scancode, int action, int mods)
{
	// Only interested in press events
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;

	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(-1); // rotates -1 on the Z axis of the camera
			else
				mCamera->yawReal(-1); // rotates 1 on the Y axis of the camera

			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(1); // rotates 1 on the Z axis of the camera
			else
				mCamera->yawReal(1); // rotate -1 on the Y axis of the camera
			break;
		case GLFW_KEY_UP:
			mCamera->pitchReal(1); // rotates 1 on the X axis of the camera
			break;
		case GLFW_KEY_DOWN:
			mCamera->pitchReal(-1); // rotates -1 on the X axis of the camera
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

bool
IG1App::changeScene(size_t sceneNr)
{
	// Check whether the scene exists
	if (sceneNr >= mScenes.size())
		return false;

	// Change only if a different scene
	if (sceneNr != mCurrentScene) {
		mScenes[mCurrentScene]->unload();
		mCurrentScene = sceneNr;
		mScenes[mCurrentScene]->load();
	}

	return true;
}
