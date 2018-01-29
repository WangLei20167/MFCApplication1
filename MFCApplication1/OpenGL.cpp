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
	//��ɫģʽ
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, (GLfloat)width, (GLfloat)height);
	//glOrtho(-1, 1, -1, 1, -1,1);
	glMatrixMode(GL_PROJECTION);  //ͶӰ
	
	//62.4����һ����Ժ���ֵ   
	//��Z�Ḻ�����ƶ��ľ���  ���� X��������Χ
	gluPerspective(60.5, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	
	//�õ��Ӿ�����ϵ
	glMatrixMode(GL_MODELVIEW);   //ģ����ͼ
	glLoadIdentity();             //���������õ�ǰָ���ľ���Ϊ��λ����

	//������趨 
	//һ���趨��������Ч
	glEnable(GL_BLEND);             //���û�Ϲ��ܣ���ͼ����ɫͬ��Χ��ɫ����    
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_POLYGON_SMOOTH);     //����ο����    
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);        //�߿����    
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POINT_SMOOTH);       //�㿹���    
	glHint(GL_POINT_SMOOTH, GL_NICEST);
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
	//�������ΪͼƬȫ������Ҫ�ػ棬Ӧ���ǰ��մ��ڳ�����ԭ���ڳ���Ƚ�������
	glViewport(0, 0, width, height);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective
	(60.5,
		(GLfloat)width / (GLfloat)height,
		0.1f,
		100.0f
	);
	//gluLookAt(10,5,10,0,0,0,0,1,0);  
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();
}

//����Ĵ������ڲ�ִͣ�е�
//��ͼ������
void OpenGL::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	//ʹ��3�������͵�����������Ⱦ��ɫΪ��ɫ
	glColor3f(1.0, 0.0, 0.0);
	glLoadIdentity();
	//ƽ��
	//��Z�Ḻ����ƽ��10����λ����
	//�˴�ƽ�ƾ�����X������ķ�Χ(-10,10)
	//Y����ݴ��ڵĿ�߱�  ȷ��
	//���������ƶ����������
	glTranslatef(-50.0 + LRMove, 0.0 + UDMove, -50.0);
	//������ʾ����
	glScalef(enlarge, enlarge, 1);
	//����ʹ�ö�������
	/*GLfloat vertices[] = {
		0.0, 0.2, 0.0,
		-0.2, -0.2, 0.0,
		0.2, -0.2, 0.0
	};*/
	
	/*GLfloat vertices[] = {
		0.0, 0.2,
		-0.2, -0.2,
		0.2, -0.2
	};*/
	// ���ö�������
	//glEnableClientState(GL_VERTEX_ARRAY);
	//// ����  
	////��һ��������ÿ�������������� ��γ
	//glVertexPointer(2, GL_FLOAT, 0, vertices);
	////
	////����������
	////first�������黺���е���һλ��ʼ���ƣ�һ��Ϊ0��
	////count�������ж����������
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//// ���ö�������  
	//glDisableClientState(GL_VERTEX_ARRAY);
	//ÿʹ��һ�β���һ��   
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//�Ŵ�
	//glScalef(2.0, 2.0, 1.0);

	//�ı��ߵĿ��
	float width = 3.0;
	glLineWidth(width);
	//��ɫ����
	glColor3f(0.0, 0.0, 0.0);

	GLfloat ver = 10.0;
	//����
	/*GLfloat vertices0[] = {
		2 * ver, 1.0,
		0.0, 1.0,
		-1.0, 0.0,
		-2 * ver, 0.0,
	};*/

	GLfloat vertices0[] = {
		0,0,
		7.81,-4.17,
		23.43,-7.81, 
		31.3,-10.41,
		40.63,-10.41,
		53.13,-7.9,
		93.75,-6.25,
		100,-3.125,
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	// ����  
	//��һ��������ÿ�������������� ��γ����
	glVertexPointer(2, GL_FLOAT, 0, vertices0);
	//����
	glDrawArrays(GL_LINE_STRIP, 0, 8);
	glPushMatrix();
	//����������1.5����λ   �൱��ͼ������   
	GLfloat down = -3.0;
	glTranslatef(0.0, -3, 0.0);
	// ���ö�������  
	//����
	glDrawArrays(GL_LINE_STRIP, 0, 8);
	glPopMatrix();

	//���м�����
	glColor3f(1.0, 0.0, 0.0);
	//Ϊʲô�߿����2  ������˸
	//����1ʱ��������˸
	glLineWidth(1);
	glPushMatrix();
	//����������1.5����λ   �൱��ͼ������   

	glTranslatef(0.0, down/2, 0.0);
	// ���ö�������  
	//����

	//��������
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(5, 0x27FF);

	glDrawArrays(GL_LINE_STRIP, 0, 8);

	glDisable(GL_LINE_STIPPLE);
	
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	
	if (showLable) {
		vehicle.draw();
	}
	
	//��������ʹ��for ѭ��ά��һ����Ⱦ��
	//���õ������ֵ
	//glPointSize(20.0);
	////��ɫ����
	//glColor3f(0.0, 0.0, 1.0);
	//glBegin(GL_POINTS);
	//
	//glVertex2f(35.0,-11.2);
	////glVertex2f(1.0, 2.0);
	//glEnd();
	glLoadIdentity();
	SwapBuffers(hDC);
}



//û�õ�
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
