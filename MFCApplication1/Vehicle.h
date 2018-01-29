#pragma once
#include "Lable.h"
class Vehicle :
	public Lable
{
public:
	Vehicle();
	~Vehicle();
	void draw();
	virtual void changePos(GLfloat x, GLfloat y);
};

