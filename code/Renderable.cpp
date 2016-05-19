/*
* Renderable Class. This is an abstract class that all of the objects that
* are attached to the scene inherit from. It provides basic functionality
* for moving/rotating/scaling objects as well as defining a pure virtual
* function '_draw()' that must be difined by its children classes which 
* actually does the drawing of any specific object.
*/

#include "Renderable.h"

// create the static parts of all objects
unsigned int Renderable::textures[2];
GLUquadricObj *Renderable::quadric = gluNewQuadric();


/// Default Constructor. Initialises the position to zero.
/// The rotation around the Y axis is picked randomly to allow random
/// spinning of objects. Display lists are off by default
Renderable::Renderable()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	
	this->rx = 0.0f;
	this->ry = getRand(0.0f, 360.0f);
	this->rz = 0.0f;

	this->sx = 1.0f;
	this->sy = 1.0f;
	this->sz = 1.0f;

	isList = false;
}


/// Default Destructor. Does nothing.
Renderable::~Renderable()
{
	// Nothing needs to be done here
}


/// Builds a display list of this object.
void Renderable::build(GLuint &dlist)
{
	dlist = glGenLists(1);
	if (!glIsList(dlist)) {
		isList = false;
		return;
	}
	isList = true;

	glPushMatrix();
	glNewList(dlist, GL_COMPILE);
		_draw();
	glEndList();
	glPopMatrix();
}


/// Moves the object
/*
* This method moves the object coordinates to the specified position along
* the x, y and z axes.
*/
void Renderable::move(GLfloat x, GLfloat y, GLfloat z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


/// Rotates an object
/*
* This method rotates the object coordinates a specified number of degrees
* around each of the x, y and z axes. All of the rotations are
* performed around the point (1.0f, 1.0f, 1.0f) and happen in
* the following manner: x-rot, y-rot, z-rot
*/
void Renderable::rotate(GLfloat x, GLfloat y, GLfloat z)
{
	this->rx = x;
	this->ry = y;
	this->rz = z;
}


/// Scales the object
void Renderable::scale(GLfloat x, GLfloat y, GLfloat z)
{
	this->sx = x;
	this->sy = y;
	this->sz = z;
}


/// Draws the object
/*
* This method sets up the object ready for drawing by a concrete
* class. Firstly all of the rotations are performed on the object,
* then the translation is done, finally the _draw() method is
* called to actually draw the object. Upon exit, the MODELVIEW
* matrix is restored.
*
* If a display list has been built for this object, then it is
* draw instead of re-drawing the object.
*/
void Renderable::draw(void)
{
	glPushMatrix();

	glTranslatef(this->x, this->y, this->z);

	glRotatef(this->rx, 1.0f, 0.0f, 0.0f);
	glRotatef(this->ry, 0.0f, 1.0f, 0.0f);
	glRotatef(this->rz, 0.0f, 0.0f, 1.0f);

	glScalef(sx, sy, sz);

	// if the object is flagged as a display list object, then call the
	// display list drawing function of the object, otherwise just call
	// the normal draw function of the object
	if (this->isList)
		_draw_dlist();
	else
		_draw();

	glPopMatrix();
}


/// Generates a random value to use
GLfloat Renderable::getRand(GLfloat minimum, GLfloat range)
{
	return (((GLfloat)rand() / (GLfloat)RAND_MAX) * range) + minimum;
}

void  show_percent() {
	obj=obj+1;
 int curr_status = ((obj/status)*50);
     int dashes = 2*(width * curr_status)/status;

     std::cout << '|' << std::left << std::setw(width) << std::string(dashes, '-') << '|' << std::setw(3) << curr_status << "%";
        std::cout << std::string(width+6, '\b');
}

void getn1(int n)
{
	status= n*7;
}
