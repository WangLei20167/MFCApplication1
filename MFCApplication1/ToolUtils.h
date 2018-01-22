#pragma once
//使用的工具方法
#include <string>
#include <time.h>
using namespace std;
class ToolUtils
{
public:
	ToolUtils();
	~ToolUtils();
	static string getTime();
	static string getCurrentPath();
	static void newFolder(const string folder);
};

