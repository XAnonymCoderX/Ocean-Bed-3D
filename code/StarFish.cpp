/*
* StarFish class. Draws a yellowish colour StarFish.
*/

#include "Renderable.h"

using namespace std;

// setup the static variables
GLfloat StarFish::material[4] = {0.3f, 0.3f, 0.3f, 1.f};
GLfloat StarFish::shininess = 32.f;


/// Default Constructor. Initialises defaults.
StarFish::StarFish() : Renderable()
{
	show_percent();
}


/// Default destructor.
StarFish::~StarFish()
{
	cout << "++ Destructing StarFish\n";
}


/// Draws the StarFish
void StarFish::_draw(void)
{
	// set up the material properties (only front needs to be set)
	glMaterialfv(GL_FRONT, GL_SPECULAR, material);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// set up vertex arrays
	glVertexPointer(3, GL_FLOAT, 0, vertex);
	glNormalPointer(GL_FLOAT, 0, normal);
	glColorPointer(3, GL_FLOAT, 0, colours);

	// enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// draw all legs
	GLfloat step = 360.0f / 5;
	for (int i = 0; i < 5;  i++)
	{
		glPushMatrix();
		glRotatef(i * step, 0.0f, 1.0f, 0.0f);
		glDrawArrays(GL_QUADS, 0, 4 * 5);
		glPopMatrix();
	}

	// disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	// turn of colour material tracking
	glDisable(GL_COLOR_MATERIAL);
}


/*
* ========================================
* ====== VERTEX ARRAYS FOLLOW BELOW ======
* ========================================
*
* StarFish is divided into sections like this (only one leg is defined):
*
* Leg Top:			Leg Bottom:
*  _				 _
* |  - _			|  - _
* |      -			|      -
* |  1     -		|  3     -
* 0---------|X		0---------|X
* |  2     -		|  4     -
* |     _ -			|     _ -
* | _ -				| _ - 
*
* X: This is the end point of a leg
*      /\
*    /    \
*    \    /
*      \/
*/

GLfloat StarFish::vertex[] =
{
	//3					|					|					|
    0.0f, 0.2f, 0.0f,	0.0f, 0.0f, 0.6f,	1.5f, 0.0f, 0.3f,	1.5f, 0.2f, 0.0f,
    //4					|					|					|
	0.0f, 0.0f, -0.6f,	0.0f, 0.2f, 0.0f,	1.5f, 0.2f, 0.0f,	1.5f, 0.0f, -0.3f,
    //1					|					|					|
	0.0f, -0.2f, 0.0f,	1.5f, -0.2f, 0.0f,	1.5f, 0.0f, 0.3f,	0.0f, 0.0f, 0.6f,		
	//2					|					|					|
    0.0f, 0.0f, -0.6f,	1.5f, 0.0f, -0.3f,	1.5f, -0.2f, 0.0f,	0.0f, -0.2f, 0.0f,		
	//X					|					|					|
	1.5f, 0.2f, 0.0f,	1.5f, 0.0f, 0.3f,	1.5f, -0.2f, 0.0f,	1.5f, 0.0f, -0.3f
};

GLfloat StarFish::normal[] =
{
    //3					|					|					|
	0.f, 0.71f, -0.71f,	0.f, 1.f, 0.0f,		0.f, 1.0f, 0.f,		0.f, 0.71f, -0.71f,
    //4					|					|					|
	0.f, 1.0f, 0.f,		0.0f, 0.71f, 0.71f,	0.f, 0.71f, 0.71f,	0.0f, 1.f, 0.f,
	//1					|					|					|
	0.f, -0.71f, -0.71f,0.f, -1.f, 0.0f,	0.f, -1.0f, 0.f,	0.f, -0.71f, -0.71f,
	//2					|					|					|
    0.f, -1.0f, 0.f,	0.0f, -0.71f, 0.71f,0.f, -0.71f, 0.71f,	0.0f, -1.f, 0.f,
	//X					|					|					|
	1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f

};

GLfloat StarFish::colours[] =
{
    //3					|					|					|
	0.1f, 0.0f, 0.0f,	0.9f, 0.4f, 0.0f,	0.9f, 0.4f, 0.0f,	0.1f, 0.0f, 0.0f,
    //4					|					|					|
	0.9f, 0.4f, 0.0f,	0.1f, 0.0f, 0.0f,	0.1f, 0.0f, 0.0f,	0.9f, 0.4f, 0.0f,
    //1					|					|					|
	0.85f, 0.5f, 0.0f,	0.1f, 0.0f, 0.0f,	0.1f, 0.0f, 0.0f,	0.85f, 0.5f, 0.0f,
    //2					|					|					|
	0.9f, 0.4f, 0.0f,	0.1f, 0.0f, 0.0f,	0.1f, 0.0f, 0.0f,	0.9f, 0.4f, 0.0f,
	//X					|					|					|
	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f

};
