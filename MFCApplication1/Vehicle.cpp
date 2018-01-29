#include "stdafx.h"
#include "Vehicle.h"


Vehicle::Vehicle()
{
	xPos = 35.0;
	yPos = -11.2;
}


Vehicle::~Vehicle()
{
}

void Vehicle::draw() {
	glPointSize(15.0);
	//À¶É«»­µã
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);

	glVertex2f(xPos, yPos);
	//glVertex2f(1.0, 2.0);
	glEnd();
}

void Vehicle::changePos(GLfloat x, GLfloat y) {
	if (xPos == 35.0) {
		xPos = 38.0;
	}
	else {
		xPos = 35.0;
	}
	
	yPos = -11.2;
}
