/*
* Quad class. Draws a yellowish colour quad.
*/

#include "Renderable.h"

using namespace std;

// setup the static variables
GLfloat Quad::material[4] = {1.f, 1.f, 1.f, 1.f};
GLfloat Quad::shininess = 120.f;


/// Default Constructor. Initialises defaults.
Quad::Quad() : Renderable()
{
	show_percent();
}


/// Default destructor.
Quad::~Quad()
{
	cout << "++ Destructing quad\n";
}


/// Draws the quad
void Quad::_draw(void)
{
	// set up the material properties (only front needs to be set)
	glMaterialfv(GL_FRONT, GL_AMBIENT, material);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	// enable texturing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, FLOOR_TEXTURE);

	// set up texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor3f(0.9f, 0.6f, 0.0f);
	glFrontFace(GL_CCW);
	glBegin(GL_QUADS);
		glNormal3f(0.f, 0.f, 1.f);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(-0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(0.5f,  -0.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
