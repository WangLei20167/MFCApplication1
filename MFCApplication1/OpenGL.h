#pragma once
//#include <gl/GL.h>  
//#include <gl/GLU.h>  
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Vehicle.h"

class OpenGL
{
public:
	//用来移动的参数
	//左右 移动的单位值
	//左负右正  X轴
	GLfloat LRMove = 0;
	//上正下负  Y轴
	GLfloat UDMove = 0;
	//放大缩小的倍数
	GLfloat enlarge = 1;

	GLboolean showLable = false;
	Vehicle vehicle;
public:
	OpenGL();
	~OpenGL();
	HDC hDC;
	HGLRC hRC;
	
public:
	/************************************************************************/
	/*    对OpenGL的一些初始化工作，width和height表示窗口的宽和高                                                                  */
	/************************************************************************/
	void Init(int width, int height);

	/************************************************************************/
	/* 设置像素格式                                                                     */
	/************************************************************************/
	bool SetupPixelFormat(HDC hDC0);

	/************************************************************************/
	/* 窗口大小改变时的回调函数                                                                     */
	/************************************************************************/
	void Reshap(int width, int height);

	/************************************************************************/
	/*  具体的渲染操作，窗口中显示的内容是在这个函数中完成的                                                                    */
	/************************************************************************/
	void Render();

};

