/*
* Plant class. Draws a plant.
*/

#include "Renderable.h"

using namespace std;

// setup the static variables
GLfloat Plant::material1[4] = {0.1f, 0.3f, 0.15f, 1.f};
GLfloat Plant::material2[4] = {0.6f, 1.f, 0.8f, 1.f};
GLfloat Plant::shininess = 100.f;


/// Default Constructor. Initialises defaults.
Plant::Plant() : Renderable()
{
	show_percent();
	build(dlist);
}


/// Default destructor.
Plant::~Plant()
{
	cout << "++ Destructing Plant\n";
}


/// Draws the Plant
void Plant::_draw(void)
{
	/*
	* The materials are set in _draw_dlist() since that function
	* is called eacht time to draw the display list version of the
	* plant, this functin only gets used to build the display list
	*/

	// in the start we generate a plant with AT LEAST one branch
	// so that we never get a situation where a plant is created
	// with 0 branches
	generate(0, Renderable::getRand(1, 6));
}


// Generates the plan. This really draws it, but the draw commands
// are saved into the display list
void Plant::generate(int level, int number)
{
	// if we reached 5 levels of recursion, exit
	// remember we start at level 0
	if (level == 5) return;

	// each branch is abuout 3/4 of the size of the previous
	GLfloat height = 3.0f / (0.75 * (level + 1.f));	
	GLfloat bottom = 0.75f / pow(2, level);
	GLfloat top = 0.75f / pow(2, (GLfloat)level + 1.f);
	
	for (int i = 0; i < number; i++)
	{
		
		GLfloat horzAngle = Renderable::getRand(0, 180);
		GLfloat vertAngle = Renderable::getRand(0, 180);
		int numChildren = Renderable::getRand(0, 6);

		glPushMatrix();
		glRotatef(horzAngle, 0.0f, 1.0f, 0.0f);
		glRotatef(vertAngle, 1.0f, 0.0f, 0.0f);

		// cap the bottom
		glFrontFace(GL_CW);
		gluDisk(quadric, 0.0f, bottom, 8 - level, 1);
		glFrontFace(GL_CCW);

		// draw branch
		gluCylinder(quadric, bottom, top, height, 8 - level, 1);
		
		// cap top
		glTranslatef(0.0f, 0.0f, height);
		gluDisk(quadric, 0.0f, top, 8 - level, 1);

		// call this function again to generate more branches
		// rotate back to 'normal' position first i.e. facing up
		// this avoids branches looking down and going through
		// the floor
		glRotatef(-vertAngle, 1.0f, 0.0f, 0.0f);
		generate(level + 1, numChildren);
		glPopMatrix();
	}
}


/// Draws the display list for the plant object
void Plant::_draw_dlist(void)
{
	// set up the material properties (only front needs to be set)
	glMaterialfv(GL_FRONT, GL_AMBIENT, material1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material2);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColor4fv(material1);

	glCallList(this->dlist);
}
