#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
class Lable
{
public:
	//Œª÷√
	GLfloat xPos;
	GLfloat yPos;
public:
	Lable();
	~Lable();
	virtual void changePos(GLfloat x,GLfloat y);
};

