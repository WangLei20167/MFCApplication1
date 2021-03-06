
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PCtrl, m_Picture);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CMFCApplication1Dlg::On32771)
	ON_STN_DBLCLK(IDC_PCtrl, &CMFCApplication1Dlg::OnStnDblclickPctrl)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_32772, &CMFCApplication1Dlg::On32772)
	ON_BN_CLICKED(IDC_SAVEBT, &CMFCApplication1Dlg::OnBnClickedSavebt)
	ON_BN_CLICKED(IDC_OPENIMG, &CMFCApplication1Dlg::OnBnClickedOpenimg)
	ON_BN_CLICKED(IDC_GETPOSBT, &CMFCApplication1Dlg::OnBnClickedGetposbt)
	ON_BN_CLICKED(IDC_ENLARGEBT, &CMFCApplication1Dlg::OnBnClickedEnlargebt)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_MinBt, &CMFCApplication1Dlg::OnBnClickedMinbt)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_SHOWLABBT, &CMFCApplication1Dlg::OnBnClickedShowlabbt)
	ON_BN_CLICKED(IDC_CHANGEPOSBT, &CMFCApplication1Dlg::OnBnClickedChangeposbt)
END_MESSAGE_MAP()

void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{

	CDialog::OnSize(nType, cx, cy);
	//openGL.Reshap(cx, cy);
	/*switch (nType)
	{
	case SIZE_RESTORED:
		MessageBox("捕获到窗口还原消息");
		break;
	case SIZE_MINIMIZED:
		MessageBox("捕获到窗口最小化消息");
		break;
	case SIZE_MAXIMIZED:
		MessageBox("捕获到窗口最大化消息");
		break;
	}*/
}



// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//最大化显示
	//SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);

	//CRect rcWorkArea;
	//// 获取工作区的大小
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	//MoveWindow(&rcWorkArea);
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	/************************************************************************/
	/*  传递给SetupPixelFormat的参数是要绘图的对象的DC，可以是窗口中的某一个控件
	这里使用的是窗口的DC，即在窗口中绘图，而不是在窗口的某个控件中绘图*/
	/************************************************************************/
	//在整个窗口中显示
	//openGL.SetupPixelFormat(::GetDC(m_hWnd));
	//在picture控件中显示
	CDC* pDC = GetDlgItem(IDC_PCtrl)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	openGL.SetupPixelFormat(hDC);
	//得到绘图区域对应的长方形  
	CRect rect;

	CWnd *pWnd = GetDlgItem(IDC_PCtrl);//IDC_picture为picture控件ID
	//GetDlgItem(IDC_PCtrl)->GetClientRect(&rect);
	//GetClientRect(&rect);
	pWnd->GetClientRect(&rect);
	//设置绘图区域的宽和高  
	openGL.Init(rect.right, rect.bottom);
	SetTimer(1, 10, 0);

	//添加菜单项
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值  
	openGL.Render();
	CDialog::OnTimer(nIDEvent);
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	//解决了窗口大小发生改变后，OpenGL图形不会重绘的问题
	//重绘
	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_PCtrl);//IDC_picture为picture控件ID										  
	pWnd->GetClientRect(&rect);
	//设置绘图区域的宽和高  
	openGL.Reshap(rect.right, rect.bottom);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::On32771()
{
	// TODO: Add your command handler code here
	MessageBox(_T("this is a test"));
}

//双击全屏功能
void CMFCApplication1Dlg::OnStnDblclickPctrl()
{
	// TODO: Add your control notification handler code here
	//MessageBox(_T("this is a test"));
	if (!bFullScreen)
	{
		bFullScreen = true;
		//获取系统屏幕宽高  
		int g_iCurScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int g_iCurScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		//用m_struOldWndpl得到当前窗口的显示状态和窗体位置，以供退出全屏后使用  
		GetWindowPlacement(&m_struOldWndpl);
		GetDlgItem(IDC_PCtrl)->GetWindowPlacement(&m_struOldWndpPic);

		//计算出窗口全屏显示客户端所应该设置的窗口大小，主要为了将不需要显示的窗体边框等部分排除在屏幕外  
		CRect rectWholeDlg;
		CRect rectClient;
		GetWindowRect(&rectWholeDlg);//得到当前窗体的总的相对于屏幕的坐标  
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rectClient);//得到客户区窗口坐标  
		ClientToScreen(&rectClient);//将客户区相对窗体的坐标转为相对屏幕坐标  
									//GetDlgItem(IDC_STATIC_PICSHOW)->GetWindowRect(rectClient);//得到PICTURE控件坐标  

		rectFullScreen.left = rectWholeDlg.left - rectClient.left;
		rectFullScreen.top = rectWholeDlg.top - rectClient.top;
		rectFullScreen.right = rectWholeDlg.right + g_iCurScreenWidth - rectClient.right;
		rectFullScreen.bottom = rectWholeDlg.bottom + g_iCurScreenHeight - rectClient.bottom;

		//设置窗口对象参数，为全屏做好准备并进入全屏状态  
		WINDOWPLACEMENT struWndpl;
		struWndpl.length = sizeof(WINDOWPLACEMENT);
		struWndpl.flags = 0;
		struWndpl.showCmd = SW_SHOWNORMAL;
		struWndpl.rcNormalPosition = rectFullScreen;
		SetWindowPlacement(&struWndpl);//该函数设置指定窗口的显示状态和显示大小位置等，是我们该程序最为重要的函数  
									   //将PICTURE控件的坐标设为全屏大小  
		GetDlgItem(IDC_PCtrl)->MoveWindow(CRect(0, 0, g_iCurScreenWidth, g_iCurScreenHeight));
	}
	else
	{
		//退出全屏
		GetDlgItem(IDC_PCtrl)->SetWindowPlacement(&m_struOldWndpPic);
		SetWindowPlacement(&m_struOldWndpl);
		bFullScreen = false;
	}

}




void CMFCApplication1Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default
	//if (bFullScreen)
	//{
	//	/*lpMMI->ptMaxSize.x = rectFullScreen.Width();
	//	lpMMI->ptMaxSize.y = rectFullScreen.Height();
	//	lpMMI->ptMaxPosition.x = rectFullScreen.left;
	//	lpMMI->ptMaxPosition.y = rectFullScreen.top;
	//	lpMMI->ptMaxTrackSize.x = rectFullScreen.Width();
	//	lpMMI->ptMaxTrackSize.y = rectFullScreen.Height();*/
	//}
	//为什么使用后窗口下端与任务栏还有间隙？？？  加20覆盖间隙   20是一个合理值？？？
	//每个前面加上(float)   或  后面 +20
	lpMMI->ptMaxSize.y = GetSystemMetrics(SM_CYFULLSCREEN) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME);

	CDialog::OnGetMinMaxInfo(lpMMI);
}


void CMFCApplication1Dlg::On32772()
{
	// TODO: Add your command handler code here
	//exit(0);
	PostQuitMessage(0);//最常用
}

//保存场景
void CMFCApplication1Dlg::OnBnClickedSavebt()
{
	// TODO: Add your control notification handler code here
	CDC *pdc = m_Picture.GetDC();
	CImage imag;
	CRect rcClient;
	m_Picture.GetWindowRect(&rcClient);
	imag.Create(rcClient.Width(), rcClient.Height(), 32);
	::BitBlt(imag.GetDC(), 0, 0, rcClient.Width(), rcClient.Height(), pdc->m_hDC, 0, 0, SRCCOPY);
	string path = ToolUtils::getCurrentPath() + "\\images\\";
	ToolUtils::newFolder(path);
	//用当前时间为图片命名
	string fileName = ToolUtils::getTime() + ".bmp";
	imag.Save((path + fileName).c_str()); // 改成 imag.Save(_T("f:\\2.bmp"));
	ReleaseDC(pdc);
	imag.ReleaseDC();
	AfxMessageBox(_T("保存成功!"));
}

//打开文件夹
void CMFCApplication1Dlg::OnBnClickedOpenimg()
{
	// TODO: Add your control notification handler code here
	/*CString cstr;
	cstr.LoadString(IDS_IMAGEFOLDER);
	MessageBox(cstr);*/
	string path = ToolUtils::getCurrentPath() + "\\images\\";
	//使用上一次文件位置和大小显示
	ShellExecute(NULL, "open", NULL, NULL, path.c_str(), SW_SHOWNORMAL);
}

//
void CMFCApplication1Dlg::OnBnClickedGetposbt()
{
	// TODO: Add your control notification handler code here
	CRect rect;

	GetDlgItem(IDC_GETPOSBT)->GetWindowRect(&rect);//获取控件的屏幕坐标
	ScreenToClient(&rect);//转换为对话框上的客户坐标
	CString right;
	right.Format(_T("%d"), rect.right);
	CString bottom;
	bottom.Format(_T("%d"), rect.bottom);
	CString cstr = right + ", " + bottom;
	//MessageBox(cstr);


	CRect rect1;

	GetDlgItem(IDC_OPENIMG)->GetWindowRect(&rect1);//获取控件的屏幕坐标
	ScreenToClient(&rect1);//转换为对话框上的客户坐标
	CString right1;
	right1.Format(_T("%d"), rect1.right);
	CString bottom1;
	bottom1.Format(_T("%d"), rect1.bottom);
	CString cstr1 = right1 + ", " + bottom1;
	//MessageBox(cstr1);

	CRect rect2;
	//IDC_SAVEBT
	GetDlgItem(IDC_PCtrl)->GetWindowRect(&rect2);//获取控件的屏幕坐标
	ScreenToClient(&rect2);//转换为对话框上的客户坐标
	CString right2;
	right2.Format(_T("%d"), rect2.right);
	CString bottom2;
	bottom2.Format(_T("%d"), rect2.bottom);
	CString cstr2 = right2 + ", " + bottom2;
	//MessageBox(cstr2);

	CString sss = cstr + "\r\n" + cstr1 + "\r\n" + cstr2;
	MessageBox(sss);
}

//放大
void CMFCApplication1Dlg::OnBnClickedEnlargebt()
{
	// TODO: Add your control notification handler code here
	openGL.enlarge += 0.5;
	/*if (openGL.enlarge == 1) {
		openGL.enlarge = 2;
		SetDlgItemText(IDC_ENLARGEBT, "还原");
	}
	else {
		SetDlgItemText(IDC_ENLARGEBT, "放大");
		openGL.enlarge = 1;
	}*/
}


//鼠标移动
void CMFCApplication1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ClientToScreen(&point);
	CRect rect;
	GetDlgItem(IDC_PCtrl)->GetClientRect(rect);
	GetDlgItem(IDC_PCtrl)->ClientToScreen(rect);
	if (rect.PtInRect(point))   //鼠标是否在控件范围之内
	{
		MessageBox("鼠标在Picture Control控件内");
	}
	CDialog::OnMouseMove(nFlags, point);
}

//按键处理方法
BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
		case 'W': //Esc按键事件  
			openGL.UDMove += 0.5;
			return true;
		case VK_DOWN:
		case 'S':
			//Ctrl + S 组合键
			if (::GetKeyState(VK_CONTROL) < 0) {
				OnBnClickedSavebt();
				return true;
			}
			openGL.UDMove -= 0.5;
			return true;
		case VK_LEFT:
		case 'A': //Esc按键事件  
			openGL.LRMove -= 0.5;
			return true;
		case VK_RIGHT:
		case 'D': //Esc按键事件  
			openGL.LRMove += 0.5;
			return true;
		case VK_ESCAPE: //Enter按键事件 
			//退出全屏
			if (bFullScreen) {
				OnStnDblclickPctrl();
			}
			return true;
			//Ctrl + S 组合键

		default:
			;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//缩小
void CMFCApplication1Dlg::OnBnClickedMinbt()
{
	// TODO: Add your control notification handler code here
	if (openGL.enlarge <= 0.5) {
		return;
	}
	openGL.enlarge -= 0.2;
	/*CString cstr;
	cstr.Format(_T("%f"), openGL.enlarge);
	MessageBox("当前倍数" + cstr);*/
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	openGL.enlarge = 1;
	openGL.LRMove = 0;
	openGL.UDMove = 0;
}

//响应鼠标滚轮
BOOL CMFCApplication1Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	float size = openGL.enlarge + 0.1*zDelta / 120;
	if (size > 0.5) {
		openGL.enlarge += 0.1*zDelta / 120;
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

//显示标签
void CMFCApplication1Dlg::OnBnClickedShowlabbt()
{
	// TODO: Add your control notification handler code here
	if (openGL.showLable) {
		openGL.showLable = false;
		SetDlgItemText(IDC_SHOWLABBT, "显示标签");
	}
	else {
		openGL.showLable = true;
		SetDlgItemText(IDC_SHOWLABBT, "清除标签");
	}
}

//改变位置
void CMFCApplication1Dlg::OnBnClickedChangeposbt()
{
	// TODO: Add your control notification handler code here
	openGL.vehicle.changePos(1, 1);
}
