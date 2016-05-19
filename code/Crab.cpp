/*
* Crab class. Draws a pinky colour crab.
*/

#include "Renderable.h"

using namespace std;

// setup the static variables
GLfloat Crab::material[4] = {0.5f, 0.5f, 0.5f, 1.f};
GLfloat Crab::shininess = 50.f;


/// Default Constructor. Builds the display list for the crab.
Crab::Crab() : Renderable()
{
	show_percent();
	sy = sx = sz = 2.f; // make crab twice as big
	build(dlist);
}


/// Default destructor.
Crab::~Crab()
{
	cout << "++ Destructing crab\n";
}


/// Draws the crab
void Crab::_draw(void)
{
	/*
	* The materials are set in _draw_dlist() since that function
	* is called eacht time to draw the display list version of the
	* crab, this functin only gets used to build the display list
	*/

	// get our red colour
	glColor3f(1.0f, 0.45f, 0.45f);

	// draw crab body (squashed along Y axis
	glPushMatrix();
	glScalef(1.0f, 0.5f, 1.0f);
	gluSphere(quadric, 0.3f, 16, 16);
	glPopMatrix();

	// draw all of the legs
	glPushMatrix();
	drawLegs();
	glScalef(-1.f, 1.f, 1.f);
	glFrontFace(GL_CW);
	drawLegs();
	glFrontFace(GL_CCW);
	glPopMatrix();

	// set to use our black colour
	glColor3f(0.0f, 0.0f, 0.0f);

	// draw left crab eye
	glTranslatef(-0.06f, 0.0f, 0.3f);
	glutSolidSphere(0.05f, 12, 8);

	// draw right crab eye
	glTranslatef(0.12f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 12, 8);
}


/// Draws the display list for the crab object
void Crab::_draw_dlist(void)
{
	// set up the material properties (only front needs to be set)
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glCallList(this->dlist);

	// turn of colour material tracking
	glDisable(GL_COLOR_MATERIAL);
}


/// Draws a leg using an angle between the two bones
void Crab::drawLeg(GLfloat jointAngle, GLfloat jointOffset)
{
	// draw first part of a leg
	glPushMatrix();
	glTranslatef(-0.38f, 0.0f, 0.0f);
	glScalef(3.0f, 1.0f, 1.0f);
	glutSolidCube(0.06f);
	glPopMatrix();

	// draw second part of a leg
	glPushMatrix();
	glTranslatef(-0.53f, jointOffset, 0.0f);
	glRotatef(jointAngle, 0.0f, 0.0f, 1.0f);
	glScalef(4.0f, 1.0f, 1.0f);
	glutSolidCube(0.06f);
	glPopMatrix();
}


/// Draws one leg
void Crab::drawLeg()
{
	drawLeg(-45.0f, 0.075f);
}


/// Draws complete set of legs (side legs)
void Crab::drawLegs()
{
	// set a darker pinky colour for legs
	glColor3f(1.0f, 0.55f, 0.55f);

	// draw three side legs
	for (GLfloat i = -15.0f; i <= 15.0f; i += 15.0f)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -0.025f);
		glRotatef(i, 0.0f, 1.0f, 0.0f);
		drawLeg();
		glPopMatrix();
	}

	// draw fourth leg (the straight and bent downwards leg)
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.00f);
	glRotatef(-65.0f, -0.2f, 1.0f, 0.0f);
	drawLeg(0.0f, 0.0f);
	glPopMatrix();

	// set a light pinky colour for front legs
	glColor3f(1.0f, 0.65f, 0.65f);

	// front leg (arm)
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(55.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg();
	glPopMatrix();

	// front clippers on the front leg (arm)
	glPushMatrix();
	glTranslatef(0.24f, 0.0f, 0.725f);
	glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawLeg(-60.0f, 0.1f);
	glPopMatrix();
}
