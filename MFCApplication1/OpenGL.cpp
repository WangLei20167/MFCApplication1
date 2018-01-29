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
	//着色模式
	glShadeModel(GL_SMOOTH);
	glViewport(0, 0, (GLfloat)width, (GLfloat)height);
	//glOrtho(-1, 1, -1, 1, -1,1);
	glMatrixMode(GL_PROJECTION);  //投影
	
	//62.4度是一个相对合理值   
	//沿Z轴负方向移动的距离  等于 X轴正负范围
	gluPerspective(60.5, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	
	//得到视觉坐标系
	glMatrixMode(GL_MODELVIEW);   //模型视图
	glLoadIdentity();             //功能是重置当前指定的矩阵为单位矩阵

	//抗锯齿设定 
	//一次设定，整体有效
	glEnable(GL_BLEND);             //启用混合功能，将图形颜色同周围颜色相混合    
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_POLYGON_SMOOTH);     //多边形抗锯齿    
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);        //线抗锯齿    
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POINT_SMOOTH);       //点抗锯齿    
	glHint(GL_POINT_SMOOTH, GL_NICEST);
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
	//如果是因为图片全屏后需要重绘，应该是按照窗口长宽与原窗口长宽比进行缩放
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

//这里的代码是在不停执行的
//绘图主函数
void OpenGL::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	//使用3个浮点型的数字设置渲染颜色为红色
	glColor3f(1.0, 0.0, 0.0);
	glLoadIdentity();
	//平移
	//沿Z轴负方向平移10个单位长度
	//此处平移决定了X坐标轴的范围(-10,10)
	//Y轴根据窗口的宽高比  确定
	//把坐标轴移动到左侧中央
	glTranslatef(-50.0 + LRMove, 0.0 + UDMove, -50.0);
	//设置显示比例
	glScalef(enlarge, enlarge, 1);
	//尝试使用顶点数组
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
	// 启用顶点数组
	//glEnableClientState(GL_VERTEX_ARRAY);
	//// 好用  
	////第一个参数的每个顶点的坐标个数 几纬
	//glVertexPointer(2, GL_FLOAT, 0, vertices);
	////
	////后两个参数
	////first，从数组缓存中的哪一位开始绘制，一般为0。
	////count，数组中顶点的数量。
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//// 禁用顶点数组  
	//glDisableClientState(GL_VERTEX_ARRAY);
	//每使用一次操作一次   
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//放大
	//glScalef(2.0, 2.0, 1.0);

	//改变线的宽度
	float width = 3.0;
	glLineWidth(width);
	//黑色画线
	glColor3f(0.0, 0.0, 0.0);

	GLfloat ver = 10.0;
	//上线
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
	// 好用  
	//第一个参数的每个顶点的坐标个数 几纬坐标
	glVertexPointer(2, GL_FLOAT, 0, vertices0);
	//上线
	glDrawArrays(GL_LINE_STRIP, 0, 8);
	glPushMatrix();
	//坐标轴下移1.5个单位   相当于图形上移   
	GLfloat down = -3.0;
	glTranslatef(0.0, -3, 0.0);
	// 禁用顶点数组  
	//下线
	glDrawArrays(GL_LINE_STRIP, 0, 8);
	glPopMatrix();

	//画中间虚线
	glColor3f(1.0, 0.0, 0.0);
	//为什么线宽等于2  虚线闪烁
	//等于1时，不会闪烁
	glLineWidth(1);
	glPushMatrix();
	//坐标轴下移1.5个单位   相当于图形上移   

	glTranslatef(0.0, down/2, 0.0);
	// 禁用顶点数组  
	//下线

	//启用虚线
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(5, 0x27FF);

	glDrawArrays(GL_LINE_STRIP, 0, 8);

	glDisable(GL_LINE_STIPPLE);
	
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	
	if (showLable) {
		vehicle.draw();
	}
	
	//在这里面使用for 循环维护一个渲染表
	//设置点的像素值
	//glPointSize(20.0);
	////蓝色画点
	//glColor3f(0.0, 0.0, 1.0);
	//glBegin(GL_POINTS);
	//
	//glVertex2f(35.0,-11.2);
	////glVertex2f(1.0, 2.0);
	//glEnd();
	glLoadIdentity();
	SwapBuffers(hDC);
}



//没用到
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
