#pragma once
//ʹ�õĹ��߷���
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

