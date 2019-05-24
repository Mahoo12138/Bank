#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <string.h>
#include <regex>

using namespace std;

//获取系统时间，创建账户名
string Time() {
	//声明变量
	SYSTEMTIME sys_time;

	//将变量值设置为本地时间
	GetLocalTime(&sys_time);
	long long year = sys_time.wYear;
	int month = sys_time.wMonth;
	int day = sys_time.wDay;
	int hour = sys_time.wHour;
	int minute = sys_time.wMinute;
	long long time = (year * 100000000) + (month * 1000000) + (day * 10000) + (hour * 100) + minute;
	string t = to_string(time);
	return t;
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
	string name;
	string phonenum;
	int money;
	string password;
	string account;
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
	void Setaccount(string str) {
		this->account = str;
	}	
	void Setpassword(string pass) {
		this->password = pass;
	}
	string Getaccount() {
		return account;
	}
	string Getname() {
		return name;
	}
	string Getphonenum() {
		return phonenum;
	}
	int Getmoney() {
		return money;
	}
	string Getpassword() {
		return password;
	}

	void Transfer() {

	}
	void Deposit() {

	}
};

//主类
class Bank {
private:
	string account = "admin";
	string password = "admin";
	
public:
	User user;

	//注册方法
	void SignUp(User user) {
		string name;
		string phonenum;
		int money;
		string password;

		RefreshPage();

		ofstream fout("SignUp.txt", ios::app);

		
		user.Setaccount();
		fout << user.Getaccount();
		fout << ":\n";

		GotoPosXY(9, 32);
		cout << "注册中：设置手机号码" ;
		GotoPosXY(11, 32);
		cout << "                                   ";
		GotoPosXY(11, 32);
		cout << "请输入手机号码：";
		GotoPosXY(10, 45);
		cout << "   ┍━━━━━━━━━━━━━┑";
		GotoPosXY(11, 48);
		cout << "│             │";
		GotoPosXY(12, 45);
		cout << "   ┕━━━━━━━━━━━━━┙";
		
		GotoPosXY(11, 50);
		cin >> phonenum;

		regex pn("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");		//定义十一位合法手机号正则表达式规则
		regex pw("\\d{6}$");											//定义六位合法格式密码正则表达式规则

		while (1) {
			
			if (!regex_match(phonenum, pn)) {
				GotoPosXY(19, 16);
				cout << "请输入正确手机号！";
				Sleep(1800);
				GotoPosXY(19, 16);
				cout << "                         ";
				GotoPosXY(11, 50);
				cout << "            ";
				GotoPosXY(11, 50);
				cin >> phonenum;
			}
			else 
				break;
		}
		fout << phonenum + '\n';
		user.Setname(phonenum);

		GotoPosXY(9, 40);
		cout << "             ";
		GotoPosXY(9, 40);
		cout << "设置姓名";

		GotoPosXY(10, 45);
		cout << "                    ";
		GotoPosXY(11, 48);
		cout << "                 ";
		GotoPosXY(12, 45);
		cout << "                    ";

		GotoPosXY(11, 32);
		cout << "请输入您的姓名：";
		
		GotoPosXY(10, 45);
		cout << "   ┍━━━━━━━━━━━┑";
		GotoPosXY(11, 48);
		cout << "│           │";
		GotoPosXY(12, 45);
		cout << "   ┕━━━━━━━━━━━┙";

		GotoPosXY(11, 50);
		cin >> name;
		
		user.Setname(name);

		GotoPosXY(9, 40);
		cout << "设置密码   ";
		GotoPosXY(11, 32);
		cout << "请设置六位的数字密码：";
		GotoPosXY(10, 45);
		cout << "         ┍━━━━━━━━┑";
		GotoPosXY(11, 54);
		cout << "│        │  ";
		GotoPosXY(12, 45);
		cout << "         ┕━━━━━━━━┙";
		GotoPosXY(11, 56);
		cin >> password;

		while (1) {

			if (!regex_match(password, pw)) {
				GotoPosXY(19, 16);
				cout << "请输入格式正确的密码！";
				Sleep(1800);
				GotoPosXY(19, 16);
				cout << "                         ";
				GotoPosXY(11, 54);
				cout << "            ";
				GotoPosXY(11, 54);
				cin >> password;
			}
			else
				break;
		}

		user.Setpassword(password);
		fout << password;
		fout << "\n";

		
		while (1) {
			GotoPosXY(10, 45);
			cout << "                      ";
			GotoPosXY(11, 54);
			cout << "            ";
			GotoPosXY(12, 45);
			cout << "                      ";
			GotoPosXY(9, 40);
			cout << "存入金额          ";
			GotoPosXY(11, 32);
			cout << "请输入存入金额：    ";
			GotoPosXY(10, 39);
			cout << "         ┍━━━━━━━━┑";
			GotoPosXY(11, 48);
			cout << "│        │  ";
			GotoPosXY(12, 39);
			cout << "         ┕━━━━━━━━┙";
			GotoPosXY(11, 50);
			cin >> money;
			if (money < 0) {
				GotoPosXY(19, 16);
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
		fout << name + '\n';
		fout.close();
	}

	//登录方法
	void LogIn(User user) {
		string name,phonenum,tempStr,password;
		char tempstr[256],key;
		int money;
		string account;

		fstream check("SignUp.txt");
		if (check.fail()) {
			check.close();
			GotoPosXY(19, 16);
			cout << "当前无注册用户，请注册！";
			Sleep(1500);
			GotoPosXY(19, 16);
			cout << "                         ";
			SignUp(user);
			GotoPosXY(19, 16);
			cout << "您已成功注册，正在载入登录界面！";
			Sleep(800);
		}
		else {
			key = check.get();	//试图去读一个字符

			if (check.eof()) {	//一个字符都未读到，表示文件为空
				GotoPosXY(19, 16);
				cout << "当前无注册用户，请注册！";
				Sleep(1500);
				GotoPosXY(19, 16);
				cout << "                         ";
				SignUp(user);
				GotoPosXY(19, 16);
				cout << "您已成功注册，正在载入登录界面！";
				Sleep(800);
			}
		}
		check.close();
		RefreshPage();
		GotoPosXY(9, 32);
		cout << "登录中：输入手机号";

		GotoPosXY(11, 32);
		cout << "请输入手机号码：";
		GotoPosXY(10, 45);
		cout << "   ┍━━━━━━━━━━━━━┑";
		GotoPosXY(11, 48);
		cout << "│             │";
		GotoPosXY(12, 45);
		cout << "   ┕━━━━━━━━━━━━━┙";

		GotoPosXY(11, 50);
		cin >> phonenum;

		regex p("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");	//定义正则表达式规则

		while (1) {

			if (!regex_match(phonenum, p)) {
				GotoPosXY(19, 16);
				cout << "请输入正确手机号！";
				Sleep(1800);
				GotoPosXY(19, 16);
				cout << "                         ";
				GotoPosXY(11, 50);
				cout << "            ";
				GotoPosXY(11, 50);
				cin >> phonenum;
			}
			else
				break;
		}
		fstream file("SignUp.txt");
		file.seekg(0, ios::beg);		//让文件指针回到开始位置，以免影响登录检索
		while (!file.eof()) {
			cout << "开始检索";
			file.getline(tempstr,256,'\n');
			cout << tempstr;
			tempStr = string(tempstr);
			if (phonenum == tempStr) {
				cout << "找到了";
				user.Setnum(phonenum);
				file.seekg(-28, ios::cur);	//让文件指针从当前位置向文件开始方向移动个字节 
				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				int index = tempStr.find(":");
				string account = tempStr.substr(0, index);
				user.Setaccount(account);
				file.seekg(13, ios::cur);
				file.getline(tempstr, 256, '\n');

				tempStr = string(tempstr);
		
				user.Setpassword(tempStr);

				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				money = atoi(tempStr.c_str());
				user.Setmoney(money);

				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				user.Setname(tempStr);
				break;
			}
			 
		}
		file.close();
		GotoPosXY(9, 40);
		cout << "输入密码   ";
		GotoPosXY(11, 32);
		cout << "请输入六位的数字密码：";
		GotoPosXY(10, 45);
		cout << "         ┍━━━━━━━━┑";
		GotoPosXY(11, 54);
		cout << "│        │  ";
		GotoPosXY(12, 45);
		cout << "         ┕━━━━━━━━┙";
		
		tempStr = user.Getpassword();
		while (1) {
			GotoPosXY(11, 56);
			cin >> password;
			if (password == tempStr) {
				GotoPosXY(19, 16);
				cout << "登录成功！正在跳转界面……";
				Sleep(800);
				break;
			}
			else {
				GotoPosXY(19, 16);
				cout << "密码输入错误！请重新输入！";
				Sleep(200);
				GotoPosXY(11, 56);
				cout << "      ";
				continue;
			}
		}
		RefreshPage();
		UserPage();
	}

	//主界面实现
	void MainPage(User user) {
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
			SignUp(user);
		}
		else if (x == '2') {
			LogIn(user);
		}
		else {
			exit(0);
		}

	}

	//用户界面实现
	void UserPage() {
		char x;
		GotoPosXY(8, 31);
		cout << "请根据需要输入序号：";
		GotoPosXY(10, 32);
		cout << "1>  存款";
		GotoPosXY(10, 44);
		cout << "2>  取款";
		GotoPosXY(12, 32);
		cout << "3>  转账";
		GotoPosXY(12, 44);
		cout << "4>  退出";
		GotoPosXY(19, 16);
		cout << "密码输入错误！请重新输入！";
		GotoPosXY(19, 36);
		cin >> x;
		

	}

	//刷新界面
	void RefreshPage() {
        system("cls");
		cout << "\n\n\n\n\t\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※             欢迎使用老黄银行管理系统             ※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※    客服电话：15507462014，如有紧急情况请拨110    ※\n"
			<< "\t\t※                                                  ※\n"
			<< "\t\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
			<< endl;
	}
};
