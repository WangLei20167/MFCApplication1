#include "stdafx.h"
#include "ToolUtils.h"


ToolUtils::ToolUtils()
{
}


ToolUtils::~ToolUtils()
{
}

string ToolUtils::getTime() {
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
							 //格式化输出本地时间
							 //2018-01-15 17:36:12
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H-%M-%S", &t);
	return tmp;
}

/*
获取当前工作路径
*/
string ToolUtils::getCurrentPath() {
	CString  strPathName;
	GetModuleFileName(NULL, strPathName.GetBuffer(256), 256);
	strPathName.ReleaseBuffer(256);
	int nPos = strPathName.ReverseFind('\\');
	strPathName = strPathName.Left(nPos + 1);
	//CString转string
	string path = strPathName.GetBuffer();
	strPathName.ReleaseBuffer();
	return path;
}

//创建目录
void ToolUtils::newFolder(const string folderPath) {
	//检查路径是否存在，不存在则创建
	if (!PathIsDirectory(folderPath.c_str()))
	{
		::CreateDirectory(folderPath.c_str(), 0);
	}
}
