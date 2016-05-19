/*
* Camera class. This class is responsible for positioninig the
* camera at the right place. It also takes care of adjusting the
* camera position/angle.
*/

#include "Camera.h"

using namespace std;

/// Default Constructor. Initialises defaults.
Camera::Camera()
{
	cout << "-- Creating camera\n";
	reset();
}


/// Default destructor.
Camera::~Camera()
{
	cout << "++ Destructing camera\n";
}


/// Resets the camera position to default position and tilt
void Camera::reset(void)
{
	this->distance = -50.0f;
	this->verticalTilt = -30.0f;
	this->horizontalAngle = 90.0f;
}


/// Positions the camera at the required place and rotation
/// Zoom and spin is done by translate/rotate
void Camera::position(void)
{
	glTranslatef(0.0f, 0.0f, this->distance);
	glRotatef(this->verticalTilt, 1.0f, 0.0f, 0.0f);
	glRotatef(this->horizontalAngle, 0.0f, 1.0f, 0.0f); 
}


/// Decrements the distance to origin (zoom in)
void Camera::dec(void)
{
		this->distance--;
}


/// Incrementes the distance to origin (zoom out)
void Camera::inc(void)
{
	this->distance++;
}


/// Adjusts the camera rotation around the Y axis
void Camera::clockwise(void)
{
	this->horizontalAngle++;
}


/// Adjusts the camera rotation around the Y axis
void Camera::anticlockwise(void)
{
	this->horizontalAngle--;
}


/// Adjusts the camera rotation around the X axis
/// the angle is locked if it gets above 0 degrees
void Camera::tiltup(void)
{
	if (this->verticalTilt < 0)
		this->verticalTilt++;
}


/// Adjusts the camera rotation around the X axis
/// The angle is locked if it gets greate than 90 degrees
void Camera::tiltdown(void)
{
	if (this->verticalTilt > -90)
		this->verticalTilt--;
}
