#include "stdafx.h"
#include "OpenGL.h"


OpenGL::OpenGL()
{
}


OpenGL::~OpenGL()
{
	wglMakeCurrent(hDC, NULL);
	wglDeleteContext(hRC);
}


void OpenGL::Init(int width, int height) {
	// openGL的初始化设置
	//设置背景颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	//glViewport(0, 0, 200, 200);  
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	//glOrtho(-1, 1, (GLfloat)width / (GLfloat)height *(-10), (GLfloat)width / (GLfloat)height *10, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//添加坐标轴
	
}

bool OpenGL::SetupPixelFormat(HDC hDC0) {
	int nPixelFormat;                 // 象素点格式  
	hDC = hDC0;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小  
		1,                                // 版本号  
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图  
		PFD_SUPPORT_OPENGL |              // 支持OpenGL  
		PFD_DOUBLEBUFFER,                 // 双缓存模式  
		PFD_TYPE_RGBA,                    // RGBA 颜色模式  
		24,                               // 24 位颜色深度  
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位  
		0,                                // 没有非透明度缓存  
		0,                                // 忽略移位位  
		0,                                // 无累加缓存  
		0, 0, 0, 0,                       // 忽略累加位  
		32,                               // 32 位深度缓存     
		0,                                // 无模板缓存  
		0,                                // 无辅助缓存  
		PFD_MAIN_PLANE,                   // 主层  
		0,                                // 保留  
		0, 0, 0                           // 忽略层,可见性和损毁掩模  
	};
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(NULL, "can not find proper mode", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	SetPixelFormat(hDC, nPixelFormat, &pfd);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	return TRUE;
}
void OpenGL::Reshap(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective
	(60.0f,
		(GLfloat)width / (GLfloat)height,
		0.1f,
		100.0f
	);
	//gluLookAt(10,5,10,0,0,0,0,1,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void OpenGL::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	//使用3个浮点型的数字设置渲染颜色为红色
	glColor3f(1.0, 0.0, 0.0);

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.2, 0.0);
	glVertex3f(-0.2, -0.2, 0.0);
	glVertex3f(0.2, -0.2, 0.0);
	glEnd();

	//改变线的宽度
	float width = 3.0;
	glLineWidth(width);
	glBegin(GL_LINE_STRIP);

	glVertex3f(5.5, -0.5, 0.0);
	glVertex3f(0.0, -0.5, 0.0);

	glVertex3f(-1.0, -1.5, 0.0);
	glVertex3f(-5.5, -1.5, 0.0);
	//glVertex3f(5.5, -1.0, 0.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(5.5, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(-5.5, 0.0, 0.0);
	//glVertex3f(5.5, -1.0, 0.0);
	glEnd();

	SwapBuffers(hDC);
}

void win2global(int x, int y) {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glPushMatrix();
	//缩放、平移、旋转等变换   
	glShadeModel(GL_SMOOTH);
	//glViewport(0, 0, 200, 200);  
	glMatrixMode(GL_PROJECTION);


	//glScalef(......);
	//glRotatef(......);
	//glTranslatef(......);
	//变换要绘图函数里的顺序一样，否则坐标转换会产生错误   
	glGetIntegerv(GL_VIEWPORT, viewport); // 得到的是最后一个设置视口的参数   
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glPopMatrix();

	winX = x;
	winY = viewport[3] - (float)y;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
}
