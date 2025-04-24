#include "IG1App.h"

#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"
#include "Scene8.h"
#include "Scene9.h"
#include "Scene10.h"

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

			mScenes[mCurrentScene]->update();

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

	// VIEWPORTS ----------------------------------------------------
	Viewport* mainViewPort = new Viewport(mWinW, mWinH);
	mViewPort = mainViewPort;
	mViewPorts.push_back(mainViewPort);

	Viewport* lerftViewPort = new Viewport(mWinW / 2, mWinH);
	lerftViewPort->setPos(0, 0);
	mViewPorts.push_back(lerftViewPort);

	Viewport* rightViewPort = new Viewport(mWinW / 2, mWinH);
	rightViewPort->setPos(mWinW / 2, 0);
	mViewPorts.push_back(rightViewPort);

	// CAMARAS ------------------------------------------------------
	Camera* mainCamera = new Camera(mainViewPort);
	mCamera = mainCamera;
	mCameras.push_back(mainCamera);

	Camera* leftCamera = new Camera(lerftViewPort);
	leftCamera->setSize(lerftViewPort->width(), lerftViewPort->height());
	leftCamera->set3D();
	mCameras.push_back(leftCamera);

	Camera* rightCamera = new Camera(rightViewPort);
	rightCamera->setSize(rightViewPort->width(), rightViewPort->height());
	rightCamera->set2D();
	mCameras.push_back(rightCamera);


	// SCENES -------------------------------------------------------
	mScenes.push_back(new Scene7); // 0
	mScenes.push_back(new Scene1); // 1
	mScenes.push_back(new Scene2); // 2
	mScenes.push_back(new Scene3); // 3
	mScenes.push_back(new Scene4); // 4
	mScenes.push_back(new Scene7); // 5
	mScenes.push_back(new Scene8); // 6
	mScenes.push_back(new Scene9); // 7
	mScenes.push_back(new Scene10);// 8

	// For two different scenes displaying
	multipleScenes.push_back(0); // index Scene6 de mScenes
	multipleScenes.push_back(2); // index Scene2 de mScenes

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

	// Callbacks mouse
	glfwSetMouseButtonCallback(mWindow, s_mouse);
	glfwSetCursorPosCallback(mWindow, s_motion);
	glfwSetScrollCallback(mWindow, s_mouseWheel);

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

	for (auto& vp : mViewPorts)
		delete vp;

	mViewPorts.clear();

	for (auto& cam : mCameras)
		delete cam;

	mCameras.clear();

	//delete mCamera;
	//mCamera = nullptr;
	//delete mViewPort;
	//mViewPort = nullptr;

	glfwTerminate();
}

void
IG1App::display()
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	if (m2Vistas)
		display2V();
	else if (isMultipleScenes)
		display2Scenes();
	else
		mScenes[mCurrentScene]->render(*mCameras[mCurrentCamera]); // uploads the viewport and camera to the GPU


	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}

void
IG1App::display2V() const
{
	//// Para renderizar las vistas utilizamos una cámara auxiliar:
	//Camera auxCam = *mCamera; // copiando mCamera

	//// El puerto de vista queda compartido (se copia el puntero)
	//Viewport auxVP = *mViewPort;
	//
	//// El tamaño de los 2 puertos de vista es el mismo
	//mViewPort->setSize(mWinW / 2, mWinH);

	//// Para que no cambie la escala, tenemos que cambiar el tamaño de la ventana de vista de la cámara
	//auxCam.setSize(mViewPort->width(), mViewPort->height());

	//// Vista ortogonal
	//mViewPort->setPos(0, 0);
	//auxCam.set2D();
	//mScenes[mCurrentScene]->render(auxCam);

	//// Vista perspectiva
	//mViewPort->setPos(mWinW / 2, 0);
	//auxCam.set3D();
	//mScenes[mCurrentScene]->render(auxCam);

	//// Resetear el viewport a como estaba
	//*mViewPort = auxVP;

	////////////////////////////////////////////////////////
	// CON ARRAY DE CAMARAS (NO HACE FALTA CAMARA AUXILIAR) <-------
	// 
	// Render scene with left camera
	mScenes[mCurrentScene]->render(*mCameras[1]);

	// Render scene with right camera
	mScenes[mCurrentScene]->render(*mCameras[2]);

}

void IG1App::display2Scenes()
{
	//// Para renderizar las vistas utilizamos una cámara auxiliar:
	//Camera auxCam = *mCamera; // copiando mCamera

	//// El puerto de vista queda compartido (se copia el puntero)
	//Viewport auxVP = *mViewPort;

	//// El tamaño de los 2 puertos de vista es el mismo
	//mViewPort->setSize(mWinW / 2, mWinH);

	//// Para que no cambie la escala, tenemos que cambiar el tamaño de la ventana de vista de la cámara
	//auxCam.setSize(mViewPort->width(), mViewPort->height());

	//// Vista ortogonal
	//mViewPort->setPos(0, 0);
	//auxCam.set2D();

	//// Resetear el viewport a como estaba
	//*mViewPort = auxVP;

	// Se guarda la escena y camara actual, porque el evento de ratón es antes y no actualiza la escena correcta para el update
	size_t previousScene = mCurrentScene;
	size_t previousCamera = mCurrentCamera;

	changeScene(multipleScenes[0]);
	changeCamera(1); // Cambia mCurrentCamera a la cámara izquierda [1]
	mScenes[mCurrentScene]->render(*mCameras[mCurrentCamera]);

	changeScene(multipleScenes[1]);
	changeCamera(2); // Cambia mCurrentCamera a la cámara derecha [2]
	mScenes[mCurrentScene]->render(*mCameras[mCurrentCamera]);

	// Vuelve a la escena que estaba el ratón
	changeScene(previousScene);
	changeCamera(previousCamera); // Cambia a la cámara principal [0]
}

void
IG1App::resize(int newWidth, int newHeight) // UPDATE ALL VIEW PORTS AND CAMERAS
{
	// Update window size variables
	mWinW = newWidth;
	mWinH = newHeight;

	//// Resize Viewport to the new window size
	//mViewPort->setSize(newWidth, newHeight);
	mViewPorts[0]->setSize(mWinW, mWinH); // MAIN viewport (full screen)
	mViewPorts[1]->setSize(mWinW / 2, mWinH); // LEFT viewport
	mViewPorts[2]->setSize(mWinW / 2, mWinH); // RIGHT viewport
	mViewPorts[2]->setPos(mWinW / 2, 0); // Set the position of the right viewport

	// Resize Scene Visible Area such that the scale is not modified
	//mCamera->setSize(mViewPort->width(), mViewPort->height());
	mCameras[0]->setSize(mViewPorts[0]->width(), mViewPorts[0]->height()); // MAIN camera (full screen)
	mCameras[1]->setSize(mViewPorts[1]->width(), mViewPorts[1]->height()); // LEFT camera
	mCameras[2]->setSize(mViewPorts[2]->width(), mViewPorts[2]->height()); // RIGHT camera
}

void IG1App::mouse(int button, int action, int mods)
{
	mMouseButt = GLFW_MOUSE_BUTTON_LAST; // Undefined mouse button

	if (action == GLFW_RELEASE) return; // We only want to update when pressing, we do nothing whith releasing

	mMouseButt = button;

	double xpos, ypos;
	glfwGetCursorPos(mWindow, &xpos, &ypos);
	mMouseCoord = { xpos, ypos };
}

void IG1App::motion(double x, double y)
{
	glm::dvec2 mp = mMouseCoord - glm::dvec2(x, y); // Set the vector from the new origin to the old point (Screen coodrs)

	mMouseCoord = { x, y };

	// Para controlar la cámara que toca IZQ / DER
	if (isMultipleScenes || m2Vistas) {
		if (x < mWinW / 2) {
			// To move the camera in focus: mCameras[1] left
			changeCamera(1); // Cambia a la cámara izquierda [1]
			if (isMultipleScenes) {
				changeScene(multipleScenes[0]);
			}
		}
		else {
			// mCameras[2] right
			changeCamera(2); // Cambia a la cámara derecha [2]
			if (isMultipleScenes) {
				changeScene(multipleScenes[1]);
			}
		}
	}


	if (mMouseButt == GLFW_MOUSE_BUTTON_RIGHT)
	{
		mCameras[mCurrentCamera]->moveUD(-mp.y); // Y is in screen coords and we want to invert the direction
		mCameras[mCurrentCamera]->moveLR(mp.x);

		mNeedsRedisplay = true; // Important to update the Camera!!!
	}
	else if (mMouseButt == GLFW_MOUSE_BUTTON_LEFT)
	{
		mCameras[mCurrentCamera]->orbit(mp.x, 0);

		mNeedsRedisplay = true; // Important to update the Camera!!!
	}
}

void IG1App::mouseWheel(double dx, double dy)
{
	if (mMouseMod == GLFW_MOD_CONTROL)
	{
		mCameras[mCurrentCamera]->setScale(glm::sign(dy) * 0.01);
	}
	else
	{
		mCameras[mCurrentCamera]->moveFB(glm::sign(dy) * 4);
	}

	mNeedsRedisplay = true; // Important to update the Camera!!!
}

void
IG1App::key(unsigned int key)
{
	bool need_redisplay = true;

	switch (key) {
	case '+':
		mCameras[mCurrentCamera]->setScale(+0.01); // zoom in  (increases the scale)
		break;
	case '-':
		mCameras[mCurrentCamera]->setScale(-0.01); // zoom out (decreases the scale)
		break;
	case 'l':
		mCameras[mCurrentCamera]->set3D();
		break;
	case 'o':
		mCameras[mCurrentCamera]->set2D();
		break;
	case 'p':
		mCameras[mCurrentCamera]->changePrj();
		break;
	case 'a':
		mCameras[mCurrentCamera]->moveLR(-3.0); // Hacia la izquierda
		break;
	case 'd':
		mCameras[mCurrentCamera]->moveLR(3.0); // Hacia la derecha
		break;
	case 'w':
		mCameras[mCurrentCamera]->moveUD(3.0); // Hacia arriba
		break;
	case 's':
		mCameras[mCurrentCamera]->moveUD(-3.0); // Hacia abajo
		break;
	case 'W':
		mCameras[mCurrentCamera]->moveFB(3.0); // Hacia adelante
		break;
	case 'S':
		mCameras[mCurrentCamera]->moveFB(-3.0); // Hacia atr�s
		break;
	case 'O':
		mCameras[mCurrentCamera]->orbit(.8, .3);
		break;
	case 'k':
		m2Vistas = !m2Vistas;
		if (!m2Vistas) {
			changeCamera(0); // main camera
		}
		else {
			mCameras[1]->set3D();
			mCameras[2]->set2D();
			mCameras[2]->setCenital();
		}
		break;
	case 'm':
		isMultipleScenes = !isMultipleScenes;
		if (!isMultipleScenes) {
			changeCamera(0); // main camera
			changeScene(0); // main scene6
		}
		else {
			mCameras[1]->set3D();
			mCameras[2]->set2D();
		}
		break;
	case 'n':
		mScenes[mCurrentScene]->showNormals();
		break;
	case 'u':
		mUpdateEnable = !mUpdateEnable;
		break;
	case 'f':
		mScenes[mCurrentScene]->rotate();
		//mScenes[mCurrentScene]->printscreen();
		break;
	case 'g':
		mScenes[mCurrentScene]->orbit();
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
	mMouseMod = 0x0000; // Undefined control

	// Only interested in press events
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;
	mMouseMod = mods;

	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
	case GLFW_KEY_ESCAPE:                     // Escape key
		glfwSetWindowShouldClose(mWindow, true); // stops main loop
		break;
	case GLFW_KEY_RIGHT:
		if (mods == GLFW_MOD_CONTROL)
			mCameras[mCurrentCamera]->rollReal(-1); // rotates -1 on the Z axis of the camera
		else
			mCameras[mCurrentCamera]->yawReal(-1); // rotates 1 on the Y axis of the camera

		break;
	case GLFW_KEY_LEFT:
		if (mods == GLFW_MOD_CONTROL)
			mCameras[mCurrentCamera]->rollReal(1); // rotates 1 on the Z axis of the camera
		else
			mCameras[mCurrentCamera]->yawReal(1); // rotate -1 on the Y axis of the camera
		break;
	case GLFW_KEY_UP:
		mCameras[mCurrentCamera]->pitchReal(1); // rotates 1 on the X axis of the camera
		break;
	case GLFW_KEY_DOWN:
		mCameras[mCurrentCamera]->pitchReal(-1); // rotates -1 on the X axis of the camera
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

void IG1App::changeCamera(size_t camNr)
{
	// Change only if a different camera
	if (camNr != mCurrentCamera) {
		mCurrentCamera = camNr;
	}
}
