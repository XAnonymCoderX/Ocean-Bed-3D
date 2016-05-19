/*
* Main file that contains the main() method. Takes care of
* instantiating the Scene class.
*/

#include <GLUT/glut.h>
#include <iostream>

#include "Scene.h"
#include "Renderable.h"
#include "Textures.h"

#define OBJ_CRAB 0
#define OBJ_OCTOPUS 1
#define OBJ_STARFISH 2
#define OBJ_FISH 3
#define OBJ_PLANT 4

static Scene *scene;	/// the scene we render
static bool wireMode = false;	/// wireframe mode on / off
static bool flatShading = false;	/// flat shading on / off

static bool init(int argc, char *argv[]);	/// initialises the application
static void setupGL(void);	/// initialises OpenGL
static void animator(int type);	/// animates the aquarium
static void resizeWindow(int w, int h);	/// resizes the window
static void keyboardInput(unsigned char key, int x, int y);	/// handles keyboard input
static void keyboardInput(int key, int x, int y);	/// handles keyboard input (special)
static void drawScene(void);	/// draws the scene
static void addObject(int type);	/// adds an object to the scene
static void setupViewVolume(void);	/// sets up the viewing volume
static void getTextures(void);	/// initiates all textures
static void getSandTexture(void);	/// loads the sand texture
static void getFishTexture(void);	/// loads the fish texture
void create_menu(void);
void mouse(int button, int state, int x, int y);

using namespace std;

/// Program starts here
int main(int argc, char *argv[])
{
	int n1=rand()%50;
	getn1(n1);
	cout << "-- Program starting\n";

	srand(time(NULL));
	init(argc, argv);

	// register our call-back functions
	cout << "-- Registering callbacks\n";
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboardInput);
	glutSpecialFunc(keyboardInput);
	create_menu();
	glutMouseFunc(mouse);
	

	// generate/load textures
	cout << "-- Generating/Loading Textures\n";
	getTextures();

	// create the scene and set perspective projection as default
	scene = new Scene();
	scene->perspectiveMode = true;

	// create all quads for the floor of the aquarium
	Quad *quad;
	for (GLfloat i = -9.5; i <= 9.5; i++)
	{
		for (GLfloat j = -9.5; j <= 9.5; j++)
		{
			quad = new Quad();
			quad->ry = 0.0f;	// we don't want random rotation
			quad->rx = 90.0f;
			quad->x = 3.5f * i;
			quad->z = 3.5f * j;
			quad->scale(3.5f, 3.5f, 1.0f);
			scene->add(quad);
		}
	}

	// 'fake' keys being pressed to enable the state to
	// setup lighting and fog
	keyboardInput((unsigned char)'L', 0, 0);
	keyboardInput((unsigned char)'0', 0, 0);
	keyboardInput((unsigned char)'1', 0, 0);
	keyboardInput((unsigned char)'F', 0, 0);

	// add some stuff to the scene
	cout << "-- Adding Crab, Starfish, Fish, Octopus, Plant\n";
	for (int o = 0; o < n1; o++)
	{
		addObject(OBJ_CRAB);
		addObject(OBJ_STARFISH);
		addObject(OBJ_FISH);
		addObject(OBJ_FISH);
		addObject(OBJ_FISH);
		addObject(OBJ_OCTOPUS);
		addObject(OBJ_PLANT);
	}
	cout << endl;

	// start the timer and enter the mail GLUT loop
	glutTimerFunc(60, animator, 0);
	glutMainLoop();
	
	return 0;
}


/// Animates the aquarium. This function just renders the scene every
/// 25 milliseconds. A timer is used to give smooth animation at the
/// same rate on differnt computers. idle function draws the scenes
/// at way too different speeds on different computers
void animator(int type)
{
	glutPostRedisplay();
	glutTimerFunc(20, animator, 0);
}


/// Resizes the current viewport to the full window size
void resizeWindow(int w, int h)
{
	glViewport(0, 0, w, h);

	// update the width and height we are using
	scene->width = w;
	scene->height = h;

	setupViewVolume();
}


/// Handles keyboard input for normal keys
void keyboardInput(unsigned char key, int x, int y)
{
	switch(key) {
	case 27:	// ESC key (Quits)
		exit(0);
		break;

	case ' ':	// SPACE key (Toggle flat/smooth shading)
		flatShading = !flatShading;
		if (flatShading) glShadeModel(GL_FLAT);
		else glShadeModel(GL_SMOOTH);
		break;

	case 'A':
	case 'a':
		scene->camera.tiltdown();
		break;

	case 'Z':
	case 'z':
		scene->camera.tiltup();
		break;

	case 'W':
	case 'w':	// toggles wireframe mode on/off
		wireMode = !wireMode;
		if (!wireMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDisable(GL_BLEND);
			glDisable(GL_LINE_SMOOTH);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
		}
		break;

	case 'P':
	case 'p':	// toglles between perspective/orthographic projections
		scene->perspectiveMode = !scene->perspectiveMode;
		setupViewVolume();
		break;

	case 'f':
	case 'F':	// toggles fog on/off
		scene->fogMode = !scene->fogMode;
		if (scene->fogMode) glEnable(GL_FOG);
		else glDisable(GL_FOG);
		break;

	case 'l':
	case 'L':	// toggles lighting calculations on/off
		scene->lightMode = !scene->lightMode;
		if (scene->lightMode) glEnable(GL_LIGHTING);
		else glDisable(GL_LIGHTING);
		break;

	case '0':	// toggles light 0 on / off
		scene->light0On = ! scene->light0On;
		if (scene->light0On) glEnable(GL_LIGHT0);
		else glDisable(GL_LIGHT0);
		break;

	case '1':	// toggles light 1 on / off
		scene->light1On = ! scene->light1On;
		if (scene->light1On) glEnable(GL_LIGHT1);
		else glDisable(GL_LIGHT1);
		break;
	}
}


/// Processes special keyboard keys like F1, F2, etc
void keyboardInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		scene->showMenu = !scene->showMenu;
		break;

	case GLUT_KEY_F2:
		addObject(OBJ_CRAB);
		break;

	case GLUT_KEY_F3:
		addObject(OBJ_OCTOPUS);
		break;

	case GLUT_KEY_F4:
		addObject(OBJ_STARFISH);
		break;

	case GLUT_KEY_F5:
		addObject(OBJ_FISH);
		break;

	case GLUT_KEY_F6:
		addObject(OBJ_PLANT);
		break;

	case GLUT_KEY_LEFT:
		scene->camera.anticlockwise();
		break;

	case GLUT_KEY_RIGHT:
		scene->camera.clockwise();
		break;

	case GLUT_KEY_UP:
		scene->camera.inc();
		break;

	case GLUT_KEY_DOWN:
		scene->camera.dec();
		break;
	}
}

/* Called when a menu option has been selected. Translates the menu item
   identifier into a keystroke, then call's the keyboard function. */
void menu(int val)
{
  unsigned char key;

  switch (val) {
  case 1:
	keyboardInput(GLUT_KEY_F1, 0, 0);
    break;
  case 2:
    	keyboardInput(GLUT_KEY_F2, 0, 0);
    break;
  case 3:
    	keyboardInput(GLUT_KEY_F3, 0, 0);
    break;
  case 4:
    	keyboardInput(GLUT_KEY_F4, 0, 0);
    break;
  case 5:
    	keyboardInput(GLUT_KEY_F5, 0, 0);
    break;
  case 6:
    	keyboardInput(GLUT_KEY_F6, 0, 0);
    break;
  case 7:
    	keyboardInput((unsigned char)'F', 0, 0);
    break;
  case 8:
    	keyboardInput((unsigned char)'W', 0, 0);
    break;
  case 9:
	keyboardInput((unsigned char)'L', 0, 0);
    break;
  case 10:
    	keyboardInput((unsigned char)'1', 0, 0);
    break;
  case 11:
    	keyboardInput((unsigned char)'A', 0, 0);
    break;
  case 12:
    	keyboardInput((unsigned char)'Z', 0, 0);
    break;
  case 13:
    	keyboardInput(GLUT_KEY_UP, 0, 0);
    break;
  case 14:
    	keyboardInput(GLUT_KEY_DOWN, 0, 0);
    break;
  case 15:
    	keyboardInput(GLUT_KEY_LEFT, 0, 0);
    break;
  case 16:
    	keyboardInput(GLUT_KEY_RIGHT, 0, 0);
    break;
  case 17:
    	exit(0);
    break;
  default:
    return;
  }
  keyboardInput(key, 0, 0);
}

void create_menu(void)
{
  glutCreateMenu(menu);
//  glutAttachMenu(GLUT_LEFT_BUTTON);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutAddMenuEntry("F1	  - Toggle Help Screen", 1);
  glutAddMenuEntry("F2	  - Add a crab", 2);
  glutAddMenuEntry("F3	  - Add an octopus", 3);
  glutAddMenuEntry("F4	  - Add a starfish", 4);
  glutAddMenuEntry("F5    - Add a fish", 5);
  glutAddMenuEntry("F6    - Add a plant", 6);
  glutAddMenuEntry("F/f   - Toggle fog on/off", 7);
  glutAddMenuEntry("W/w   - Toggle wireframe on/off", 8);
  glutAddMenuEntry("L/l   - Toggle lighting on/off", 9);
  glutAddMenuEntry("1/0   - Toggle light 1/0 on/off", 10);
  glutAddMenuEntry("A	  - Inc elevation angle", 11);
  glutAddMenuEntry("Z 	  - Dec elevation angle", 12);
  glutAddMenuEntry("UP    - Dec distance from center", 13);
  glutAddMenuEntry("DOWN  - Inc distance to origin", 14);
  glutAddMenuEntry("LEFT  - Rotate clockwise", 15);
  glutAddMenuEntry("RIGHT - Rotate anticlockwise", 16);
  glutAddMenuEntry("ESC   - Exit", 17);
}

void mouse(int button, int state, int x, int y){
	switch(button){
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN)		
			keyboardInput(GLUT_KEY_LEFT, 0, 0);
	break;

   // Wheel reports as button 3(scroll up) and button 4(scroll down)
   if (button == 3) // It's a wheel event
   {
       // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
       keyboardInput(GLUT_KEY_UP, 0, 0);
   }
	if (button == 4) // It's a wheel event
   {
       // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
       keyboardInput(GLUT_KEY_DOWN, 0, 0);
   }
	}
}


/// Draws the scene to the window
/*
* This function calls the render method of the current scene
* to render the contents of the scene onto the window created.
*/
void drawScene()
{
	scene->render();
}


/// Adds an object to the scene
void addObject(int type)
{
	/*
	* we know our floor is drawn square at the origin, so we base
	* our random positions to lie within the the ocean floor. additionally
	* we extend the height of the volume by 10 units.
	*/

	// first pick the x and z locations
	GLfloat x = Renderable::getRand(-25.0f, 50.0f);
	GLfloat z = Renderable::getRand(-25.0f, 50.0f);

	// the height is a bit different, differnt objects need a different
	// offset above the sea floor
	GLfloat y;

	Renderable *object;

	switch (type)
	{
	case OBJ_STARFISH:
		y = -0.3f;
		object = new StarFish();
		break;
	case OBJ_CRAB:
		y = -0.4f;
		object = new Crab();
		break;
	case OBJ_FISH:
		y = Renderable::getRand(-26.0f, 25.0f);
		object = new Fish();
		break;
	case OBJ_OCTOPUS:
		y = Renderable::getRand(-27.0f, 25.0f);
		object = new Octopus();
		break;
	case OBJ_PLANT:
		y = 0.0f;
		object = new Plant();
		object->ry = 0.0f;
		break;
	}

	object->move(x, y, z);	// set objects new position
	scene->add(object);	// adds object to rendering queue
	scene->objects[type]++;	// increments the count of this type of object
}


/// Sets up the viewing volume to be used
void setupViewVolume(void)
{
	// work out the aspect ratio for width and height
	GLfloat aspect = (GLfloat)scene->width / (GLfloat)scene->height;
	GLfloat iaspect = (GLfloat)scene->height / (GLfloat)scene->width;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// setup new viewing volume based on the aspect ratio and projection type
	if (scene->perspectiveMode == true)
		gluPerspective(-45.0f, aspect, 1.0f, 250.0f);
	else {
		// orthographic mode correction depends on whether the ratio is greater
		// or less than 1.0 as the viewport must be scaled in different
		// directions to look right
		if (aspect >= 1.0f)
			glOrtho(-40.0f * aspect, 40.0f * aspect, -40.0f, 40.0f, 1.0f, 250.0f);
		else 
			glOrtho(-40.0f, 40.0f, -40.0f * iaspect, 40.0f * iaspect, 1.0f, 250.0f);
	}

	glMatrixMode(GL_MODELVIEW);
}


/// Initiates all textures
void getTextures(void)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(2, Renderable::textures);

	getSandTexture();
	getFishTexture();
}


/// Loads the sand texture
void getSandTexture(void)
{
	glBindTexture(GL_TEXTURE_2D, Renderable::textures[0]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 64, 64, GL_RGB, GL_UNSIGNED_BYTE, sand_image.pixel_data);
}


/// Loads the fish texture
void getFishTexture(void)
{
	glBindTexture(GL_TEXTURE_2D, Renderable::textures[1]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 128, 128, GL_RGB, GL_UNSIGNED_BYTE, fish_image.pixel_data);
}


/// Init GLUT and OpenGL
/*
* Creates a window that is half the size of the screen
* and then calls setupGL() to setup the initial OpenGL
* environment.
*/
bool init(int argc, char *argv[])
{
	// initialise glut
	cout << "-- Initialising GLUT\n";
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// setup our widnow now
	cout << "-- Creating window\n";
    glutCreateWindow("Ocean Sea bed Scene 3D");
	glutFullScreen();

	// initialise opengl initial state
	setupGL();

	return true;
}


/// Sets up the OpenGL state machine environment
/// All hints, culling, fog, light models, depth testing, polygon model
/// and blending are set up here
void setupGL(void)
{
	cout << "-- Setting up OpenGL state\n";

	// blue green background colour
	glClearColor(0.0, 0.5, 0.55, 1.0);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// depth testing used on with less than testing
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	// setup  fog, but disable for now
	glDisable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP);
	GLfloat fogColor[4] = {0.0f, 0.5f, 0.55f, 1.0f};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.0075);
	glHint(GL_FOG_HINT, GL_NICEST);
	
	// enable normalising of normals after scaling
	glEnable(GL_NORMALIZE);

	// setup lighting, but disable for nwo
	glDisable(GL_LIGHTING);
	GLfloat ambient[] = {0.1f, 0.1f, 0.1f, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	/*
	* The actual lights are defined in the Scene class
	*/

	// set up line antialiasing
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// setup backface culling
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// choose nices perspective correction for textures
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
