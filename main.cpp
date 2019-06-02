#include "bank.h"	//程序核心头文件	
#include <io.h>		//C运行库创建文件夹头文件
#include <direct.h>	//检测文件是否存在头文件
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "WINMM.LIB")

using namespace std;

int main()
{
	//创建一个日志文件夹
	string LogName = ".\\Log";
	//检查是否已存在，否则创建
	if (_access(LogName.c_str(), 0) == -1) {
		int key = _mkdir(LogName.c_str());
	}
	mciSendString(TEXT("open bgm.wma alias bgm"), NULL, 0, NULL);	//将bgm文件命名为bgm
	mciSendString(TEXT("play bgm"), NULL, 0, NULL);	//播放bgm

	//声明银行类，调用主界面
	Bank admin;
    admin.MainPage(); 
	return 0;
}

