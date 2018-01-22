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
	// openGL�ĳ�ʼ������
	//���ñ�����ɫ
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	//glViewport(0, 0, 200, 200);  
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	//glOrtho(-1, 1, (GLfloat)width / (GLfloat)height *(-10), (GLfloat)width / (GLfloat)height *10, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//���������
	
}

bool OpenGL::SetupPixelFormat(HDC hDC0) {
	int nPixelFormat;                 // ���ص��ʽ  
	hDC = hDC0;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С  
		1,                                // �汾��  
		PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ  
		PFD_SUPPORT_OPENGL |              // ֧��OpenGL  
		PFD_DOUBLEBUFFER,                 // ˫����ģʽ  
		PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ  
		24,                               // 24 λ��ɫ���  
		0, 0, 0, 0, 0, 0,                 // ������ɫλ  
		0,                                // û�з�͸���Ȼ���  
		0,                                // ������λλ  
		0,                                // ���ۼӻ���  
		0, 0, 0, 0,                       // �����ۼ�λ  
		32,                               // 32 λ��Ȼ���     
		0,                                // ��ģ�建��  
		0,                                // �޸�������  
		PFD_MAIN_PLANE,                   // ����  
		0,                                // ����  
		0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ  
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
	//ʹ��3�������͵�����������Ⱦ��ɫΪ��ɫ
	glColor3f(1.0, 0.0, 0.0);

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.2, 0.0);
	glVertex3f(-0.2, -0.2, 0.0);
	glVertex3f(0.2, -0.2, 0.0);
	glEnd();

	//�ı��ߵĿ��
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
	//���š�ƽ�ơ���ת�ȱ任   
	glShadeModel(GL_SMOOTH);
	//glViewport(0, 0, 200, 200);  
	glMatrixMode(GL_PROJECTION);


	//glScalef(......);
	//glRotatef(......);
	//glTranslatef(......);
	//�任Ҫ��ͼ�������˳��һ������������ת�����������   
	glGetIntegerv(GL_VIEWPORT, viewport); // �õ��������һ�������ӿڵĲ���   
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glPopMatrix();

	winX = x;
	winY = viewport[3] - (float)y;
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
}
