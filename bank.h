#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string.h>

using namespace std;

//获取系统时间，创建账户名
long long Time() {
	//声明变量
	SYSTEMTIME sys_time;

	//将变量值设置为本地时间
	GetLocalTime(&sys_time);
	long long year = sys_time.wYear;
	int month = sys_time.wMonth;
	int day = sys_time.wDay;
	int hour = sys_time.wHour;
	int minute = sys_time.wMinute;
	return year * 100000000 + month * 1000000 + day * 10000 + hour * 100 + minute;
	//输出时间
	/*  sys_time.wYear,
		sys_time.wMonth,
		sys_time.wDay,
		sys_time.wHour,
		sys_time.wMinute,
		sys_time.wSecond,
		sys_time.wMilliseconds,
		sys_time.wDayOfWeek
	*/
}	

//指定位置输出
void GotoPosXY(int y, int x) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)	//设置控制台光标输出的位置
								/*获取标准输出的句柄*/, pos);		

	/*
	COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标。其定义为：
		typedef struct _COORD {
		SHORT X; // horizontal coordinate
		SHORT Y; // vertical coordinate
	} COORD;
	*/
}

//用户类，处理数据
class User {
private:
	long long account;
	string name;
	string phonenum;
	int money = 0;
	int password = 0;
public:
	void Setname(string name) {
		this->name = name;
	}
	void Setnum(string num) {
		this->phonenum = num;
	}
	void Setmoney(int mon) {
		this->money = mon;
	}
	void Setaccount() {
		this->account = Time();
	}
	void Setpassword(int pass) {
		this->password = pass;
	}
	long long Getaccount() {
		return account;
	}
};

//银行类，处理用户
class Bank {

public:
	//注册方法
	void SignUp() {
		string name;
		string phonenum;
		int money;
		int password;

		SignUpPage();

		ofstream fout("SignUp.txt", ios::app);

		User user;
		user.Setaccount();
		fout << user.Getaccount();
		fout << ":\n";
		GotoPosXY(11, 32);
		cout << "请输入的姓名:";
		GotoPosXY(10, 45);
		cout << "┍━━━━━━━━━━━┑\n";
		GotoPosXY(11, 45);
		cout << "│           │\n";
		GotoPosXY(12, 45);
		cout << "┕━━━━━━━━━━━┙";
		
		GotoPosXY(11, 47);
		cin >> name;
		fout << name + '\n';
		user.Setname(name);
		
		GotoPosXY(11, 32);
		cout << "请输入手机号码：";
		GotoPosXY(10, 45);
		cout << "┍━━━━━━━━━━━┑\n";
		GotoPosXY(11, 45);
		cout << "│           │\n";
		GotoPosXY(12, 45);
		cout << "┕━━━━━━━━━━━┙";
		cin >> phonenum;
		fout << phonenum + '\n';
		user.Setname(phonenum);
		while (1) {
			GotoPosXY(11, 32);
			cout << "请设置六位的数字密码：";
			cin >> password;
			if (password < 100000 || password > 999999) {
				cout << "密码输入有误，请重新输入！";
				continue;
			}
			else {
				user.Setpassword(password);
				fout << password;
				fout << "\n";
			}
			break;
				
		}
		while (1) {
			cout << "请输入存入金额：";
			cin >> money;
			if (money < 0) {
				cout << "金额输入有误，请重新输入！";
				continue;
			}
			else {
				user.Setmoney(money);
				fout << money ;
				fout << "\n";  
			}
			break;
		}
		fout << "\n";
		fout.close();
	}

	//登录方法
	void LogIn() {
		cout << "已登录" << endl;
		system("cls");
		MainPage();
	}

	//主界面实现
	void MainPage() {
		char x;    
		system("cls"); 
		cout << "123456789012345678901234567890123456789012345678901234567890" << endl;
		cout << "\n\n\n\t\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n" 
			<< "\t\t※                                                  ※\n" 
			<< "\t\t※             欢迎使用老黄银行管理系统             ※\n" 
			<< "\t\t※                                                  ※\n" 
			<< "\t\t※                                                  ※\n" 
			<< "\t\t※             请选择：                             ※\n" 
			<< "\t\t※                   1>   注册                      ※\n" 
			<< "\t\t※                   2>   登录                      ※\n" 
			<< "\t\t※             ·>其他任意键退出系统<·             ※\n" 
			<< "\t\t※                                                  ※\n" 
			<< "\t\t※    客服电话：15507462014，如有紧急情况请拨110    ※\n" 
			<< "\t\t※                                                  ※\n" 
			<< "\t\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
			<< endl;         
		cout << "\n\t\t请选择操作方式： ";         
		cin >> x;
        if (x == '1') { 
			GotoPosXY(9, 32);
			cout << "注册中：设置姓名"<< endl;
			SignUp();
		}
		else if (x == '2') {
			GotoPosXY(9, 32);
			cout << "登陆中" << endl;
			LogIn();
		}
		else {
			exit(0); 
		}         

	}

	//登陆界面初始化
	void LogInPage() {

	}

	//注册界面初始化
	void SignUpPage() {
		
		GotoPosXY(10, 32);
		cout << "                     ";
		GotoPosXY(11, 32);
		cout << "                     ";
		GotoPosXY(12, 32);
		cout << "                         ";
		GotoPosXY(19, 16);
		cout << "                         ";
	}
};