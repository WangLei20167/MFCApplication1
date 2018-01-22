#include "stdafx.h"
#include "ToolUtils.h"


ToolUtils::ToolUtils()
{
}


ToolUtils::~ToolUtils()
{
}

string ToolUtils::getTime() {
	struct tm t;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);   //��ȡ�������ں�ʱ��
							 //��ʽ���������ʱ��
							 //2018-01-15 17:36:12
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H-%M-%S", &t);
	return tmp;
}

/*
��ȡ��ǰ����·��
*/
string ToolUtils::getCurrentPath() {
	CString  strPathName;
	GetModuleFileName(NULL, strPathName.GetBuffer(256), 256);
	strPathName.ReleaseBuffer(256);
	int nPos = strPathName.ReverseFind('\\');
	strPathName = strPathName.Left(nPos + 1);
	//CStringתstring
	string path = strPathName.GetBuffer();
	strPathName.ReleaseBuffer();
	return path;
}

//����Ŀ¼
void ToolUtils::newFolder(const string folderPath) {
	//���·���Ƿ���ڣ��������򴴽�
	if (!PathIsDirectory(folderPath.c_str()))
	{
		::CreateDirectory(folderPath.c_str(), 0);
	}
}
