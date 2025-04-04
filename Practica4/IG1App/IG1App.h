#ifndef _H_IG1App_H_
#define _H_IG1App_H_

#include <GL/glew.h>     // OpenGL Extension Wrangler
#include <GLFW/glfw3.h>  // OpenGL Library
#include <glm/glm.hpp>   // OpenGL Mathematics
#include <unordered_map>

#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"

class IG1App
{
public:
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const& J) = delete;         // no copy constructor
	void operator=(IG1App const& J) = delete; // no copy assignment

	// Viewport position and size
	Viewport const& viewPort() { return *mViewPort; };
	// Camera position, view volume and projection
	Camera const& camera() { return *mCamera; };
	// Graphics objects of the scene
	Scene const& scene() { return *mScenes[mCurrentScene]; };

	// Change to the given scene
	bool changeScene(size_t sceneNr);
	void changeCamera(size_t camNr);

	void run();   // the main event processing loop
	void close(); // the application

protected:
	IG1App() = default;
	~IG1App() { close(); };

	void init();
	void iniWinOpenGL();
	void destroy();

	void display();                      // the scene
	void display2V() const;                      // the scene
	void display2Scenes();                      // the scene
	void resize(int newWidth, int newHeight);  // the viewport (without changing the scale)
	void key(unsigned int codepoint); // keypress event
	void specialkey(int key, int scancode, int action, int mods); // special keypress event
	void mouse(int button, int action, int mods);
	void motion(double x, double y);
	void mouseWheel(double dx, double dy);

	// static callbacks
	static void s_display(GLFWwindow*) { s_ig1app.display(); };
	static void s_resize(GLFWwindow*, int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(GLFWwindow* win, unsigned int codepoint) { s_ig1app.key(codepoint); };
	static void s_specialkey(GLFWwindow* win, int key, int scancode, int action, int mods) { s_ig1app.specialkey(key, scancode, action, mods); };
	static void s_mouse(GLFWwindow* win, int button, int action, int mods) { s_ig1app.mouse(button, action, mods); };
	static void s_motion(GLFWwindow* win, double x, double y) { s_ig1app.motion(x, y); };
	static void s_mouseWheel(GLFWwindow* win, double dx, double dy) { s_ig1app.mouseWheel(dx, dy); };

	// Viewport position and size
	Viewport* mViewPort = nullptr;
	std::vector<Viewport*> mViewPorts;
	size_t mCurrentViewPort = 0;

	// Camera position, view volume and projection
	Camera* mCamera = nullptr;
	std::vector<Camera*> mCameras;
	size_t mCurrentCamera = 0;

	// Graphics objects are in the scenes
	std::vector<Scene*> mScenes;
	size_t mCurrentScene = 0;

	bool mNeedsRedisplay = true;  // main event processing loop
	GLFWwindow* mWindow = nullptr; // window's handle
	int mWinW = 800;               // window's width
	int mWinH = 600;               // window's height

	const double FRAME_DURATION = 0.03; // 30FPS
	bool mUpdateEnable = true;
	double mNextUpdate = 0;

	glm::dvec2 mMouseCoord = { 0, 0 };
	int mMouseButt = GLFW_MOUSE_BUTTON_LAST; // By default is is undefined
	int mMouseMod = 0x0000;

	bool m2Vistas = false;
	bool isMultipleScenes = false;
	std::vector<size_t> multipleScenes;
};

#endif //_H_IG1App_H_
