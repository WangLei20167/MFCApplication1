
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "OpenGL.h";
#include "afxwin.h"
#include "ToolUtils.h"


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialog
{
public:
	CMenu m_Menu;
	OpenGL openGL;
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnSize(UINT nType, int cx, int cy); 
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
	afx_msg void OnStnDblclickPctrl();

	//对话框功能  
private:
	BOOL bFullScreen;
	CRect rectFullScreen;
	WINDOWPLACEMENT m_struOldWndpl;//结构中包含了有关窗口在屏幕上位置的信息  
	WINDOWPLACEMENT m_struOldWndpPic;//PICTURE控件在屏幕上位置的信息  
	
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void On32772();
	afx_msg void OnBnClickedSavebt();
	CStatic m_Picture;
	afx_msg void OnBnClickedOpenimg();
	afx_msg void OnBnClickedGetposbt();
	afx_msg void OnBnClickedEnlargebt();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedMinbt();
	afx_msg void OnBnClickedButton3();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedShowlabbt();
	afx_msg void OnBnClickedChangeposbt();
};
