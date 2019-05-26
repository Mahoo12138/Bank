 #include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <string.h>
#include <regex>

using namespace std;

int a = 1, b = 2, c = 3;		//CheckInput()函数辅助变量
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

//检测输入合法
int CheckInput(int key,string str) {
	regex pn("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");		//定义十一位合法手机号正则表达式规则
	regex pw("\\d{6}$");											//定义六位合法格式密码正则表达式规则
	regex mo("^\\d{1,}$");											//定义合法金额正则表达式规则
	
	if (key == 1) {
		return regex_match(str, pw);
	}
	else if (key == 2) {
		return regex_match(str, pn);
	}
	else{
		return regex_match(str, mo);
	}
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
	void Resetting() {
		name = "";
		phonenum = "";
		money = 0;
		password = "";
		account = "";
	}
};

//主类
class Bank {
	// 
//                                  _oo8oo_
//                                 o8888888o
//                                 88" . "88
//                                 (| -_- |)
//                                 0\  =  /0
//                               ___/'==='\___
//                             .' \\|     |// '.
//                            / \\|||  :  |||// \
//                           / _||||| -:- |||||_ \
//                          |   | \\\  -  /// |   |
//                          | \_|  ''\---/''  |_/ |
//                          \  .-\__  '-'  __/-.  /
//                        ___'. .'  /--.--\  '. .'___
//                     ."" '<  '.___\_<|>_/___.'  >' "".
//                    | | :  `- \`.:`\ _ /`:.`/ -`  : | |
//                    \  \ `-.   \_ __\ /__ _/   .-` /  /
//                =====`-.____`.___ \_____/ ___.`____.-`=====
//                                  `=---=`
// 
// 
//               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//                          佛祖保佑       永无bug
private:
	string admin_account = "admin";
	string admin_password = "admin";
	
public:
	User Yuser,Wuser;

	//注册方法
	void SignUp() {
		string name;
		string phonenum;
		int money;
		string password;

		RefreshPage();

		ofstream fout("SignUp.txt", ios::app);

		
		Yuser.Setaccount();
		fout << Yuser.Getaccount();
		fout << "\n";

		GotoPosXY(9, 26);cout << "注册中：设置手机号码" ;
		GotoPosXY(11, 26);cout << "                              ";
		GotoPosXY(11, 26);cout << "请输入手机号码：";
		GotoPosXY(10, 39);cout << "   ┍━━━━━━━━━━━━━┑";
		GotoPosXY(11, 42);cout << "│             │";
		GotoPosXY(12, 39);cout << "   ┕━━━━━━━━━━━━━┙";
		
		GotoPosXY(11, 44);
		cin >> phonenum;

		while (1) {
			
			if (!CheckInput(b,phonenum)){
				GotoPosXY(19, 10);cout << "请输入正确手机号！";
				Sleep(1800);
				GotoPosXY(19, 10);cout << "                         ";
				GotoPosXY(11, 44);cout << "            ";
				GotoPosXY(11, 44);cin >> phonenum;
			}
			else 
				break;
		}
		fout << phonenum + '\n';
		Yuser.Setname(phonenum);

		GotoPosXY(9, 34);cout << "             ";
		GotoPosXY(9, 34);cout << "设置姓名";

		GotoPosXY(10, 39);cout << "                    ";
		GotoPosXY(11, 42);cout << "                 ";
		GotoPosXY(12, 39);cout << "                    ";

		GotoPosXY(11, 26);cout << "请输入您的姓名：";
		
		GotoPosXY(10, 39);cout << "   ┍━━━━━━━━━━━┑";
		GotoPosXY(11, 42);cout << "│           │";
		GotoPosXY(12, 39);cout << "   ┕━━━━━━━━━━━┙";

		GotoPosXY(11, 44);cin >> name;
		
		Yuser.Setname(name);

		GotoPosXY(9, 34);cout << "设置密码   ";
		GotoPosXY(11, 26);cout << "请设置六位的数字密码：";
		GotoPosXY(10, 39);cout << "         ┍━━━━━━━━┑";
		GotoPosXY(11, 48);cout << "│        │  ";
		GotoPosXY(12, 39);cout << "         ┕━━━━━━━━┙";
		GotoPosXY(11, 50);cin >> password;

		while (1) {

			if (!CheckInput(a,password)) {
				GotoPosXY(19, 10);cout << "请输入格式正确的密码！";
				Sleep(1800);
				GotoPosXY(19, 10);cout << "                         ";
				GotoPosXY(11, 48);cout << "        ";
				GotoPosXY(11, 48);cin >> password;
			}
			else
				break;
		}

		Yuser.Setpassword(password);
		fout << password;
		fout << "\n";

		
		while (1) {
			GotoPosXY(10, 36);cout << "                   ";
			GotoPosXY(11, 48);cout << "            ";
			GotoPosXY(12, 36);cout << "                      ";
			GotoPosXY(9, 34);cout << "存入金额          ";
			GotoPosXY(11, 26);cout << "请输入存入金额：    ";
			GotoPosXY(10, 33);cout << "         ┍━━━━━━━━┑        ";
			GotoPosXY(11, 42);cout << "│        │  ";
			GotoPosXY(12, 33);cout << "         ┕━━━━━━━━┙";
			GotoPosXY(11, 44);cin >> money;
			if (money < 0) {
				GotoPosXY(19, 10);cout << "金额输入有误，请重新输入！";
				continue;
			}
			else {
				Yuser.Setmoney(money);
				fout << money ;
				fout << "\n";
			}
			break;
		}
		fout << name + '\n';
		fout.close();
		RefreshPage();
		UserPage();
	}

	//登录方法
	void LogIn() {
		string name,phonenum,tempStr,password;
		char tempstr[256],key;
		int money;
		string account;

		fstream check("SignUp.txt");
		if (check.fail()) {
			check.close();
			GotoPosXY(19, 12);cout << "当前无注册用户，请注册！";
			Sleep(1500);
			GotoPosXY(19, 12);cout << "                         ";
			SignUp();
			GotoPosXY(19, 12);cout << "您已成功注册，正在载入登录界面！";
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
				SignUp();
				GotoPosXY(19, 16);
				cout << "您已成功注册，正在载入登录界面！";
				Sleep(800);
			}
		}
		check.close();
		RefreshPage();
		GotoPosXY(9, 26);cout << "登录中：输入手机号";
		GotoPosXY(11, 26);cout << "请输入手机号码：";
		GotoPosXY(10, 39);cout << "   ┍━━━━━━━━━━━━━┑";
		GotoPosXY(11, 42);cout << "│             │";
		GotoPosXY(12, 39);cout << "   ┕━━━━━━━━━━━━━┙";

		GotoPosXY(11, 44);
		cin >> phonenum;
		if (phonenum == admin_account) {
			AdminPage();
		}
		while (1) {
			if (!CheckInput(b,phonenum)) {
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
		while (!file.eof()) {			//检索文件，读取数据
			file.getline(tempstr,256,'\n');
			tempStr = string(tempstr);
			if (phonenum == tempStr) {
				Yuser.Setnum(phonenum);			//读取手机号
				file.seekg(-27, ios::cur);	    //让文件指针从当前位置向文件开始方向移动个字节 
				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				Yuser.Setaccount(tempStr);		//读取账户
				file.seekg(13, ios::cur);
				file.getline(tempstr, 256, '\n');

				tempStr = string(tempstr);
		
				Yuser.Setpassword(tempStr);		//读取密码

				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				money = atoi(tempStr.c_str());
				Yuser.Setmoney(money);		   //读取金额

				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				Yuser.Setname(tempStr);		   //读取姓名
				break;
			}
			 
		}   //  
		file.close();
		GotoPosXY(9, 34);cout << "输入密码   ";
		GotoPosXY(11, 26);cout << "请输入六位的数字密码：";
		GotoPosXY(10, 39);cout << "         ┍━━━━━━━━┑";
		GotoPosXY(11, 48);cout << "│        │  ";
		GotoPosXY(12, 39);cout << "         ┕━━━━━━━━┙";
		
		tempStr = Yuser.Getpassword();
		while (1) {
			GotoPosXY(11, 50);
			cin >> password;
			if (password == tempStr) {
				GotoPosXY(19, 12);cout << "登录成功！正在跳转界面……";
				Sleep(800);
				break;
			}
			else {
				GotoPosXY(19, 12);cout << "密码输入错误！请重新输入！";
				Sleep(200);
				GotoPosXY(11, 52);cout << "      ";
				continue;
			}
		}
		RefreshPage();
		UserPage();
	}

	//主界面实现
	void MainPage() {
		char x;
		system("cls");
		cout << "\n\n\n\n\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
			<< "\t※                                                  ※\n"
			<< "\t※             欢迎使用老黄银行管理系统             ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※             请选择：                             ※\n"
			<< "\t※                   1>   注册                      ※\n"
			<< "\t※                   2>   登录                      ※\n"
			<< "\t※             ·>其他任意键退出系统<·             ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※    客服电话：15507462014，如有紧急情况请拨110    ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
			<< endl;
		cout << "\n\t请选择操作方式： ";
		cin >> x;
        if (x == '1') {
			SignUp();
		}
		else if (x == '2') {
			LogIn();
		}
		else {
			exit(0);
		}

	}

	//用户操作界面实现
	void UserPage() {
		char x;
		GotoPosXY(8, 25);cout << "业务列表：";
		GotoPosXY(10, 20);cout << "1>  存款";
		GotoPosXY(10, 32);cout << "2>  取款";
		GotoPosXY(10, 44);cout << "3>  转账";
		GotoPosXY(12, 20);cout << "4>  余额";
		GotoPosXY(12, 32);cout << "5>  查询";
		GotoPosXY(12, 44);cout << "6>  退出";
		GotoPosXY(19, 10);cout << "请根据需求输入序号：";
		GotoPosXY(19, 30);cin >> x;
		while (1) {
			switch (x) {
			case '1':Deposit();
			case '2':Withdraw(); 
				break;
			case '4':
					GotoPosXY(19, 10);cout << "                             ";
					GotoPosXY(19, 10); cout << "您的余额为：" << Yuser.Getmoney(); 
				break;
			case '6':Exit(); MainPage(); 
				break;

			}
			GotoPosXY(20, 10);
			cout << "请根据需求输入您的下一步操作：     ";
			GotoPosXY(20, 42);
			cin >> x;
		}
		

	}

	//取款方法
	void Withdraw() {
		RefreshPage();
		string mon;
		GotoPosXY(9, 26);
		cout << "存取金额最大仅支持十万！";
		GotoPosXY(11, 26);
		cout << "请输入取出金额：";
		GotoPosXY(10, 33);
		cout << "         ┍━━━━━━━━┑";
		GotoPosXY(11, 42);
		cout << "│        │  ";
		GotoPosXY(12, 33);
		cout << "         ┕━━━━━━━━┙";
		GotoPosXY(11, 44);
		cin >> mon;
		while (1) {
			if (!CheckInput (c,mon)) {
				GotoPosXY(19, 16);
				cout << "请输入合理的金额！";
				Sleep(1800);
				GotoPosXY(19, 16);
				cout << "                  ";
				GotoPosXY(11, 44);
				cout << "       ";
				GotoPosXY(11, 44);
				cin >> mon;
			}
			else
				break;
		}
		int money = atoi(mon.c_str());
		if ((Yuser.Getmoney() - money) < 0) {
			GotoPosXY(19, 16);
			cout << "余额不足！";
			Sleep(500);
			GotoPosXY(19, 16);
			cout << "          ";
		}
		else {
			Yuser.Setmoney(Yuser.Getmoney() - money);
			GotoPosXY(19, 16);
			cout << "取款成功！";
			Sleep(500);
			GotoPosXY(19, 16);
			cout << "          ";
		}
		KeepData();
		RefreshPage();
		UserPage();
	}

	//存款方法
	void Deposit() {
		RefreshPage();
		string mon;
		GotoPosXY(9, 26);cout << "存取金额最大仅支持十万！";
		GotoPosXY(11, 26);cout << "请输入存入金额：";
		GotoPosXY(10, 33);cout << "         ┍━━━━━━━━┑";
		GotoPosXY(11, 42);cout << "│        │  ";
		GotoPosXY(12, 33);cout << "         ┕━━━━━━━━┙";
		GotoPosXY(11, 44);cin >> mon;
		while (1) {
			if (!CheckInput(3,mon)) {
				GotoPosXY(19, 16);cout << "请输入合理的金额！";
				Sleep(1800);
				GotoPosXY(19, 16);cout << "                  ";
				GotoPosXY(11, 44);cout << "       ";
				GotoPosXY(11, 44);cin >> mon;
			}
			else
				break;
		}
		int money = atoi(mon.c_str());
		Yuser.Setmoney(Yuser.Getmoney() + money);
		GotoPosXY(19, 16);cout << "存款成功！";
		Sleep(300);
		GotoPosXY(19, 16);cout << "          ";
		KeepData();
		RefreshPage();
		UserPage();
	}

	//保存数据方法
	void KeepData() {
		int line = GetDataLine(Yuser.Getphonenum());
		ChangeLineData(line + 1, Yuser.Getpassword());
		ChangeLineData(line + 2, to_string(Yuser.Getmoney()));
	}
	
	//退出账户方法
	void Exit() {
		Yuser.Resetting();
		Wuser.Resetting();
		GotoPosXY(19, 16);
		cout << "账户注销成功！正在跳转界面……";
		Sleep(500);
		MainPage();
	}

	//刷新界面方法
	void RefreshPage() {
        system("cls");
		cout << "\n\n\n\n\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
			<< "\t※                                                  ※\n"
			<< "\t※             欢迎使用老黄银行管理系统             ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※    客服电话：15507462014，如有紧急情况请拨110    ※\n"
			<< "\t※                                                  ※\n"
			<< "\t※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
			<< endl;
	}

	//管理员界面方法
	void AdminPage() {
		char x;
		string adminpw;
		RefreshPage();
		GotoPosXY(6, 23);cout << "老黄银行后台账户管理系统";
		GotoPosXY(14, 13);cout << "Copyright C 2019 老黄银行 All Rights Reserved.";
		GotoPosXY(9, 28);cout << "登陆中：输入密码   ";
		GotoPosXY(11, 26);cout << "请输入管理员密码：";
		GotoPosXY(10, 39);cout << "     ┍━━━━━━━━┑";
		GotoPosXY(11, 44);cout << "│        │  ";
		GotoPosXY(12, 39);cout << "     ┕━━━━━━━━┙";
		while (1) {
			GotoPosXY(11, 46);cin >> adminpw;
			if (adminpw == admin_password) {
				GotoPosXY(19, 16);cout << "登录成功！正在跳转界面……";
				Sleep(800);
				break;
			}
			else {
				GotoPosXY(19, 16);cout << "密码输入错误！请重新输入！";
				Sleep(200);
				GotoPosXY(19, 16); cout << "                         ";
				GotoPosXY(11, 46);cout << "      ";
				continue;
			}
		}
		GotoPosXY(19, 10); cout << "请输入你需要的操作：                ";
		GotoPosXY(8, 23);cout << "管理员操作：";
		GotoPosXY(9, 24);cout << "                                  ";
		GotoPosXY(10, 24);cout << "                                 ";
		GotoPosXY(11,24);cout << "                                ";
		GotoPosXY(12, 24);cout << "                                 ";
		
		GotoPosXY(10, 23);cout << "1>  用户列表	 2>  新增用户";
		GotoPosXY(12, 23);cout << "3>  删除用户	 4>  continue";
		GotoPosXY(19, 30); cin >> x;
		while (1) {
			switch (x) {
			case '1':UserList();
				break;
			case '2':Withdraw();
				break;
			case '4':
				break;

			}
			GotoPosXY(20, 10);
			cout << "请根据需求输入您的下一步操作：     ";
			GotoPosXY(20, 34);
			cin >> x;
		}

		system("pause");
	}

	//用户列表实现
	void UserList() {
		GotoPosXY(4, 66); cout <<  "※※※※※※※※※※※※※※※※※※※※※※※※※";
		GotoPosXY(5, 66); cout <<  "※                                              ※";
		GotoPosXY(6, 66); cout <<  "※               老黄银行已注册用户             ※";
		GotoPosXY(7, 66); cout <<  "※                                              ※";
		GotoPosXY(8, 66); cout <<  "※ 姓名   手机号       金额        注册时间     ※";
		GotoPosXY(9, 66); cout <<  "※                                              ※";
		GotoPosXY(10, 66); cout << "※                                              ※";
		GotoPosXY(11, 66); cout << "※                                              ※";
		GotoPosXY(12, 66); cout << "※                                              ※";
		GotoPosXY(13, 66); cout << "※                                              ※";
		GotoPosXY(14, 66); cout << "※                                              ※";
		GotoPosXY(14, 66); cout << "※                                              ※";
		GotoPosXY(15, 66); cout << "※※※※※※※※※※※※※※※※※※※※※※※※※";

		int i = 0 ,Userlocation[256] = {0};
		char tempstr[256];
		string tempStr;
		fstream show("SignUp.txt");

		//获取每个用户的数据位置
		while (1) {
			while (!show.eof()) {						//检索文件，读取数据
				show.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				if (CheckInput(b,tempStr)) {
					Userlocation[i] = GetDataLine(tempStr);
					i++;
				}
			}
			show.close();
			break;
		}

		for (int j = 0, x = 9, y = 69; j < i; j++,x++) {
			GotoPosXY(x, y); cout << ReadLineData(Userlocation[j] + 3);
			GotoPosXY(x, y + 7); cout << ReadLineData(Userlocation[j]);
			GotoPosXY(x, y + 20); cout << ReadLineData(Userlocation[j] + 2);
			GotoPosXY(x, y + 32); cout <<  ReadLineData(Userlocation[j] -1);
		}
		
		
	}
		
	//读取指定内容数据行数
	int GetDataLine(string line) {
		fstream file("SignUp.txt",ios::in);		//以只读方式打开文件
		int n = 0;
		string str;
		while (1){
			getline(file, str, '\n');
			n++;
			if (str == line)
			break;
		}
		file.close();
		return n;
	}

	//修改指定行数据
	void ChangeLineData(int lineNum, string content) {
		ifstream in;
		char line[1024] = { '\0' };
		in.open("SignUp.txt");
		int i = 0;
		string tempStr;
		while (in.getline(line, sizeof(line))) {
			i++;
			if (lineNum != i) {
				tempStr += string(line);
			}
			else {
				tempStr += content;
			}
			tempStr += '\n';
		}
		in.close();
		ofstream out;
		out.open("SignUp.txt");
		out.flush();
		out << tempStr;
		out.close();
	}

	//读取指定行内容
	char* ReadLineData(int lineNum) {
		char data[1024];
		ifstream in;	
		in.open("SignUp.txt"); 	
		int line = 1;	
		while (in.getline(data, 1024)) { 
			if (lineNum == line) { 
				break; 
			}		
			line++; 
		} 	
		in.close(); 
		return data;
	}

	//转账：搜索用户，读取数据
	void SearchUser(string pn) {
		string name, phonenum,tempStr, password, account;
		char tempstr[256];
		int money;

		fstream search("SignUp.txt");
		while (!search.eof()) {						//检索文件，读取数据
			search.getline(tempstr, 256, '\n');
			tempStr = string(tempstr);
			if (tempStr == pn) {
				Wuser.Setnum(tempStr);			    //读取手机号
				search.seekg(-28, ios::cur);	    //让文件指针从当前位置向文件开始方向移动个字节 
				search.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				int index = tempStr.find(":");
				account = tempStr.substr(0, index);
				Wuser.Setaccount(account);			//读取账户
				search.seekg(13, ios::cur);
				search.getline(tempstr, 256, '\n');

				tempStr = string(tempstr);

				Wuser.Setpassword(tempStr);			//读取密码

				search.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				money = atoi(tempStr.c_str());
				Wuser.Setmoney(money);		   //读取金额

				search.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				Wuser.Setname(tempStr);		   //读取姓名
				break;
			}
		}  
		GotoPosXY(15, 66); cout << "";
		//search.close();
	}
};
