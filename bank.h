﻿ #include <iostream>
 #include <fstream>
 #include <Windows.h>
 #include <string>
 #include <regex>

using namespace std;

int a = 1, b = 2, c = 3, d = 4;		
//CheckInput()函数辅助变量：'1'->密码，'2'->号码，'3'->金额，'4'->时间
//SaveLog()存储账单辅助变量：'1'->存款，'2'->取款, '3'->转账，'4'->收账

string Datapath = "SignUp.txt";		//指定数据路径

//获取系统时间，创建账户名
string Time() {
	//声明变量
	SYSTEMTIME sys_time;
	int time_int[5];
	string time_str[5];
	//将变量值设置为本地时间
	GetLocalTime(&sys_time);
	time_int[0] = sys_time.wYear;
	time_int[1] = sys_time.wMonth;
	time_int[2] = sys_time.wDay;
	time_int[3] = sys_time.wHour;
	time_int[4] = sys_time.wMinute;
	
	for (int i = 0; i < 5; i++) {
		if (time_int[i] < 10) {
			time_str[i] = "0" + to_string(time_int[i]);
		}
		else {
			time_str[i] = to_string(time_int[i]);
		}
	}
	string t = time_str[0] + time_str[1] + time_str[2] + time_str[3] + time_str[4];
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
	regex mon("^\\d{1,}$");											//定义合法金额正则表达式规则
	regex time("\\d-\\d{12}$");										//检测时间正则表达式规则
	if (key == 1) {
		return regex_match(str, pw);
	}
	else if (key == 2) {
		return regex_match(str, pn);
	}
	else if(key == 3){
		return regex_match(str, mon);
	}
	else {
		return regex_match(str, time);
	}
}

//获得指定内容数据行数
int GetDataLine(string line,string _file) {
	fstream file(_file, ios::in);		//以只读方式打开文件
	int n = 0;
	string str;
	while (!file.eof()) {
		getline(file, str, '\n');
		n++;
		if (str == line)
			break;
	}
	file.close();
	return n;
}

//获取文件行数
int GetLine(string data) {
	fstream file(data, ios::in);		//以只读方式打开文件
	int n = 0;
	string str;
	while (!file.eof()) {
		getline(file, str, '\n');
		n++;
	}
	file.close();
	return n;
}

//修改指定行数据	原理类似于删除字符串
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
string ReadLineData(int lineNum,string path) {
	string data;
	ifstream in;
	in.open(path);
	int line = 1;
	while (getline(in,data)) {
		if (lineNum == line) {
			break;
		}
		line++;
	}
	in.close();
	return data;
}

//删除指定行数据	原理：一次读取文件一行，存入字符串，直到读到指定行数，将其转为空字符串存入字符串，再将字符串写入文件
void DelLineData(int lineNum) {
	ifstream in;
	in.open("SignUp.txt");
	string strFileData = "";
	int line = 1;
	char lineData[1024] = { 0 };
	while (in.getline(lineData, sizeof(lineData))) {
		if (line == lineNum) {
			strFileData += "";
		}
		else {
			strFileData += string(lineData);
			strFileData += "\n";
		}
		line++;
	}
	in.close();
	ofstream out;
	out.open("SignUp.txt");
	out.flush();
	out << strFileData;
	out.close();
}

//用户类，处理数据
class User {
private:
	string name,phonenum, money,password,account;
public:
	void Setname(string name) {
		this->name = name;
	}
	void Setnum(string num) {
		this->phonenum = num;
	}
	void Setmoney(string mon) {
		this->money = mon;
	}
	void Setmoney_i2s(int mon) {
		this->money = to_string(mon);
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
	string Getmoney() {
		return money;
	}
	int Getmoney_int() {
		return atoi(money.c_str());
	}
	string Getpassword() {
		return password;
	}
	void Resetting() {
		name = "";
		phonenum = "";
		money = "0";
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
	//系统用户名和密码
public:
	User Yuser,Wuser;

	//注册方法
	void SignUp() {
		string name;
		string phonenum;
		string money;
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
		if (GetDataLine(phonenum, Datapath) < GetLine(Datapath)) {
			GotoPosXY(19, 10); cout << "该用户已注册，请登录！";
			Sleep(1800);
			GotoPosXY(19, 10); cout << "                         ";
			LogIn();
		}
		fout << phonenum + '\n';
		Yuser.Setnum(phonenum);

		GotoPosXY(9, 34);cout << "             ";
		GotoPosXY(9, 34);cout << "设置姓名";

		GotoPosXY(10, 39);cout << "                    ";
		GotoPosXY(11, 42);cout << "                 ";
		GotoPosXY(12, 39);cout << "                    ";

		GotoPosXY(11, 26);cout << "请输入您的姓名：";
		
		GotoPosXY(10, 39);cout << "   ┍━━━━━━━━━━━┑";
		GotoPosXY(11, 42);cout << "│           │";
		GotoPosXY(12, 39);cout << "   ┕━━━━━━━━━━━┙";
		cin.ignore();
		GotoPosXY(11, 44);getline(cin,name);
		
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
				GotoPosXY(11, 49);cout << "        ";
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
			if (!CheckInput(c,money)) {
				GotoPosXY(19, 10);cout << "金额输入有误，请重新输入！";
				continue;
			}
			else {
				Yuser.Setmoney(money);
				fout << money ;
				fout << "\n";
				SaveLog(a, money);
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
		char key;
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
				GotoPosXY(19, 10);
				cout << "当前无注册用户，请注册！";
				Sleep(1500);
				GotoPosXY(19, 10);
				cout << "                         ";
				SignUp();
				GotoPosXY(19, 10);
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
				GotoPosXY(19, 16);cout << "请输入正确手机号！";
				Sleep(1800);
				GotoPosXY(19, 16);cout << "                  ";
				GotoPosXY(11, 44);cout << "            ";
				GotoPosXY(11, 44);cin >> phonenum;
			}
			else
				break;
		}
		if (GetDataLine(phonenum, Datapath) >= GetLine(Datapath)) {
			GotoPosXY(19, 16); cout << "该用户未注册！";
			Sleep(1800);
			LogIn();
		}  
		tempStr = ReadLineData(GetDataLine(phonenum, Datapath) + 1, Datapath);

		GotoPosXY(9, 34);cout << "输入密码   ";
		GotoPosXY(11, 26);cout << "请输入六位的数字密码：";
		GotoPosXY(10, 39);cout << "         ┍━━━━━━━━┑";
		GotoPosXY(11, 48);cout << "│        │  ";
		GotoPosXY(12, 39);cout << "         ┕━━━━━━━━┙";
		
		while (1) {
			GotoPosXY(11, 50);cin >> password;
			if (password == tempStr) {
				GotoPosXY(19, 12);cout << "登录成功！正在跳转界面……";
				Yuser.Setmoney(ReadLineData(GetDataLine(phonenum, Datapath) + 2,Datapath));
				Yuser.Setnum(phonenum);
				Sleep(800);
				break;
			}
			else {
				GotoPosXY(19, 12);cout << "密码输入错误！请重新输入！";
				Sleep(200);
				GotoPosXY(11, 50);cout << "      ";
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
			ExitPage(); Sleep(2500); exit(0);
		}

	}

	//用户操作界面实现
	void UserPage() {
		mciSendString(TEXT("close bgm"), NULL, 0, NULL);	//停止播放bgm
		Sleep(100);
		mciSendString(TEXT("open _bgm.wma alias _bgm"), NULL, 0, NULL);	//将bgm文件命名为_bgm
		mciSendString(TEXT("play _bgm repeat"), NULL, 0, NULL);	//播放_bgm
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
				break;
			case '2':Withdraw(); 
				break;
			case '3':Transfer();
				break;
			case '4':
					GotoPosXY(19, 10);cout << "                             ";
					GotoPosXY(19, 10); cout << "您的余额为：" << Yuser.Getmoney(); 
				break;
			case '5':LogPage(Yuser.Getphonenum());
				break;
			case '6':Exit(); 
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
		if ((Yuser.Getmoney_int() - money) < 0) {
			GotoPosXY(19, 16);
			cout << "余额不足！";
			Sleep(500);
			GotoPosXY(19, 16);
			cout << "          ";
		}
		else {
			Yuser.Setmoney_i2s(Yuser.Getmoney_int() - money);
			GotoPosXY(19, 16);
			cout << "取款成功！";
			Sleep(500);
			GotoPosXY(19, 16);
			cout << "          ";
		}
		KeepData();
		SaveLog(b, mon);
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
		Yuser.Setmoney_i2s(Yuser.Getmoney_int() + money);
		GotoPosXY(19, 16);cout << "存款成功！";
		Sleep(300);
		GotoPosXY(19, 16);cout << "          ";
		KeepData();
		SaveLog(a, mon);
		RefreshPage();
		UserPage();
	}

	//转账方法
	void Transfer() {
		int tranmoney = 0;
		string phonenum,tranuser_money;
		GotoPosXY(4, 62); cout <<  "※※※※※※※※※※※※※※※※※※※※※※※※";
		GotoPosXY(5, 62); cout <<  "※                      ┍━━━━━━━━━━━━━┑       ※";
		GotoPosXY(6, 62); cout <<  "※  请输入收款手机号码：│             │       ※";
		GotoPosXY(7, 62); cout <<  "※                      ┕━━━━━━━━━━━━━┙       ※";
		GotoPosXY(8, 62); cout <<  "※                      ┍━━━━━━━━┑            ※";
		GotoPosXY(9, 62); cout << "※  请输入转账金额：    │        │            ※";
		GotoPosXY(10, 62); cout << "※                      ┕━━━━━━━━┙            ※";
		GotoPosXY(11, 62); cout <<  "※※※※※※※※※※※※※※※※※※※※※※※※";
		GotoPosXY(6, 88); cin >> phonenum;
		while (1) {
			if (!CheckInput(b, phonenum)|| GetDataLine(phonenum, Datapath) >= GetLine(Datapath)) {
				GotoPosXY(12, 68);cout << "手机号格式错误或无此用户，请重试！";
				Sleep(1500);GotoPosXY(12, 68);cout << "                                  ";
				GotoPosXY(6, 88);cout << "            ";
				GotoPosXY(6, 88);cin >> phonenum;
			}
			else if (phonenum == Yuser.Getphonenum()) {
				GotoPosXY(12, 68); cout << "不支持转账给自身账户，请重试！";
				Sleep(1500); GotoPosXY(12, 68); cout << "                                  ";
				GotoPosXY(6, 88); cout << "            ";
				GotoPosXY(6, 88); cin >> phonenum;
			}
			else
				break;
		}
		Wuser.Setnum(phonenum);
		GotoPosXY(9, 88); cin >> tranmoney;
		while (1) {
			if (!CheckInput(c, to_string(tranmoney))) {
				GotoPosXY(10, 68); cout << "金额格式错误，请重试！";
				Sleep(1500); GotoPosXY(10, 68); cout << "                      ";
				GotoPosXY(9, 88); cout << "        ";
				GotoPosXY(9, 88); cin >> tranmoney;
			}
			else
				break;
		}
		SaveLog(d, to_string(tranmoney));
		SaveLog(c, to_string(tranmoney));
		Yuser.Setmoney_i2s(Yuser.Getmoney_int() - tranmoney);	//登录用户转账后余额设置
		tranmoney = atoi(ReadLineData(GetDataLine(phonenum, Datapath) + 2,Datapath).c_str()) + tranmoney;	//被转账用户转账后余额设置
		tranuser_money = to_string(tranmoney);	

		ChangeLineData(GetDataLine(phonenum, Datapath) + 2, tranuser_money);
		ChangeLineData(GetDataLine(Yuser.Getphonenum(), Datapath) + 2, Yuser.Getmoney());
		GotoPosXY(13, 62); cout << "转账成功！";
		Sleep(1500);
		GotoPosXY(13, 62); cout << "      ";
		Wuser.Resetting();
		RefreshPage();
		UserPage();
	}

	//账单显示方法
	void LogPage(string strnum) {
		string logstr;
		int i = GetLine("./Log/" + strnum + ".txt"),LogLocation[256] = { 0 }, lines, n = 0;
		GotoPosXY(4, 62); cout << "※※※※※※※※※※※※※※※※※※※※※※※※";
		GotoPosXY(5, 62); cout << "※                                            ※";
		GotoPosXY(6, 62); cout << "※            您的所有账单详情如下            ※";
		GotoPosXY(7, 62); cout << "※                                            ※";
		GotoPosXY(8, 62); cout << "※  时间            业务类型     金额         ※";
		for (int lines = 0; lines < (i/3)+1; lines++) {
			GotoPosXY(9 + lines, 62); cout << "※                                            ※";
		}
		GotoPosXY(10 + (i/3), 62); cout << "※※※※※※※※※※※※※※※※※※※※※※※※";  
		for (int n = 1; n < 5; n++) {
			GotoPosXY(10 + (i / 3) + n, 62); cout << "                                              ";
		}
		fstream log("./Log/" + strnum + ".txt");
		while (!log.eof()) {
			getline(log, logstr);
			if (CheckInput(4, logstr)) {
				lines = GetDataLine(logstr, "./Log/" + strnum + ".txt");
				LogLocation[n] = lines;
				n++;
			}
		}
		for (int j = 0, x = 9, y = 66; j < i/3; j++, x++) {
			GotoPosXY(x, y); cout << ReadLineData(LogLocation[j], "./Log/" + strnum + ".txt").substr(2,13); Sleep(200);	//输出时间
			GotoPosXY(x, y + 17); cout << ReadLineData(LogLocation[j] + 1, "./Log/" + strnum + ".txt");Sleep(200);	//业务类型
			GotoPosXY(x, y + 30); cout << ReadLineData(LogLocation[j] + 2, "./Log/" + strnum + ".txt"); Sleep(200);	//输出手机号
			Sleep(200);
		}
	}

	//保存数据方法
	void KeepData() {
		int line = GetDataLine(Yuser.Getphonenum(),Datapath);
		ChangeLineData(line + 2, Yuser.Getmoney());
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
		char ad;
		string adminpw;
		int i = 0, Userlocation[256] = { 0 },deluser;
		char tempstr[256];
		string tempStr;
		fstream show("SignUp.txt");

		//获取每个用户的数据位置
		while (1) {
			while (!show.eof()) {						//检索文件，读取数据
				show.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				if (CheckInput(b, tempStr)) {
					Userlocation[i] = GetDataLine(tempStr,Datapath);
					i++;
				}
			}
			show.close();
			break;
		}

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
				GotoPosXY(19, 10);cout << "登录成功！正在跳转界面……";
				Sleep(800);
				break;
			}
			else {
				GotoPosXY(19, 16);cout << "密码输入错误！请重新输入！";
				Sleep(200);
				GotoPosXY(19, 16); cout << "                         ";
				GotoPosXY(11, 44);cout << "        ";
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
		GotoPosXY(12, 23);cout << "3>  删除用户	 4>  退出系统";
		GotoPosXY(19, 30); cin >> ad;
		while (1) {
			switch (ad) {
			case '1':UserList(i,Userlocation);
				break;
			case '2':NewUser();
				break;
			case '3': GotoPosXY(19, 10); cout << "请输入被删除用户序号：     ";
				GotoPosXY(19, 40); cin >> deluser; DelUser(Userlocation[deluser-1]); UserList(--i, Userlocation);
				break;
			case '4':Exit();
				break;

			}
			GotoPosXY(19, 10);cout << "请根据需求输入您的下一步操作：     ";
			GotoPosXY(19, 40);cin >> ad;
		}
	}

	//用户列表实现
	void UserList(int i,int* Userlocation) {		//'i'为系统已注册用户，Userlocation为存储每个用户手机号数据行号的数组
		for (int n = 0; n < 4; n++) {
			GotoPosXY(11 + i + n, 62); cout << "                                                    ";
		}
		GotoPosXY(4, 62); cout <<  "※※※※※※※※※※※※※※※※※※※※※※※※※※";
		GotoPosXY(5, 62); cout <<  "※                                                ※";
		GotoPosXY(6, 62); cout <<  "※               老黄银行已注册用户               ※";
		GotoPosXY(7, 62); cout <<  "※                                                ※";
		GotoPosXY(8, 62); cout <<  "※ 序号 姓名    手机号      金额     注册时间     ※";
		GotoPosXY(9, 62); cout <<  "※                                                ※";
		for (int lines = 0; lines < i;lines++) {
			GotoPosXY(10 + lines, 62); cout << "※                                                ※";
		}
		GotoPosXY(10 + i, 62); cout << "※※※※※※※※※※※※※※※※※※※※※※※※※※";
		

		for (int j = 0, x = 9, y = 69; j < i; j++,x++) {
			GotoPosXY(x, y - 4); cout << j+1 <<">"; Sleep(200);	//输出序号
			GotoPosXY(x, y); cout << ReadLineData(Userlocation[j] + 3,Datapath); Sleep(200);	//输出姓名
			GotoPosXY(x, y + 9); cout << ReadLineData(Userlocation[j], Datapath); Sleep(200);	//输出手机号
			GotoPosXY(x, y + 21); cout << ReadLineData(Userlocation[j] + 2, Datapath); Sleep(200);	//输出金额
			GotoPosXY(x, y + 30); cout <<  ReadLineData(Userlocation[j] -1, Datapath); Sleep(200);	//输出注册时间
			Sleep(200);
		}	
	}

	//新增用户方法
	void NewUser() {
		string name;
		string phonenum;
		string money;
		string password;
		RefreshPage();
		ofstream fout("SignUp.txt", ios::app);
		fout << Time();
		fout << "\n";

		GotoPosXY(8, 23); cout << "                               ";
		GotoPosXY(9, 23); cout << "                               ";
		GotoPosXY(11, 23); cout << "                              ";
		GotoPosXY(8, 23); cout << "请按步骤输入新用户消息：";
		GotoPosXY(11, 26); cout << "请输入手机号码：";
		GotoPosXY(10, 39); cout << "   ┍━━━━━━━━━━━━━┑";
		GotoPosXY(11, 42); cout << "│             │";
		GotoPosXY(12, 39); cout << "   ┕━━━━━━━━━━━━━┙";

		GotoPosXY(11, 44);
		cin >> phonenum;

		while (1) {
			if (!CheckInput(b, phonenum)) {
				GotoPosXY(19, 10); cout << "请输入正确手机号！";
				Sleep(1800);
				GotoPosXY(19, 10); cout << "                         ";
				GotoPosXY(11, 44); cout << "            ";
				GotoPosXY(11, 44); cin >> phonenum;
			}
			else
				break;
		}
		fout << phonenum + '\n';

		GotoPosXY(9, 34); cout << "             ";
		GotoPosXY(10, 39); cout << "                    ";
		GotoPosXY(11, 42); cout << "                 ";
		GotoPosXY(12, 39); cout << "                    ";

		GotoPosXY(11, 26); cout << "请输入用户的姓名：";

		GotoPosXY(10, 41); cout << "   ┍━━━━━━━━━━━┑";
		GotoPosXY(11, 44); cout << "│           │";
		GotoPosXY(12, 41); cout << "   ┕━━━━━━━━━━━┙";
		cin.ignore();
		GotoPosXY(11, 46); getline(cin, name);

		GotoPosXY(11, 26); cout << "请设置六位的数字密码：";
		GotoPosXY(10, 39); cout << "         ┍━━━━━━━━┑";
		GotoPosXY(11, 48); cout << "│        │  ";
		GotoPosXY(12, 39); cout << "         ┕━━━━━━━━┙";
		GotoPosXY(11, 50); cin >> password;

		while (1) {

			if (!CheckInput(a, password)) {
				GotoPosXY(19, 10); cout << "请输入格式正确的密码！";
				Sleep(1800);
				GotoPosXY(19, 10); cout << "                         ";
				GotoPosXY(11, 48); cout << "        ";
				GotoPosXY(11, 48); cin >> password;
			}
			else
				break;
		}
		fout << password;
		fout << "\n";


		while (1) {
			GotoPosXY(10, 36); cout << "                   ";
			GotoPosXY(11, 48); cout << "            ";
			GotoPosXY(12, 36); cout << "                      ";
			GotoPosXY(11, 26); cout << "请输入存入金额：    ";
			GotoPosXY(10, 33); cout << "         ┍━━━━━━━━┑        ";
			GotoPosXY(11, 42); cout << "│        │  ";
			GotoPosXY(12, 33); cout << "         ┕━━━━━━━━┙";
			GotoPosXY(11, 44); cin >> money;
			if (atoi(money.c_str()) < 0|| CheckInput(3,money)) {
				GotoPosXY(19, 10); cout << "金额输入有误，请重新输入！";
				continue;
			}
			else {
				Wuser.Setmoney(money);
				fout << money;
				fout << "\n";
			}
			break;
		}
		fout << name + '\n';
		fout.close();
		RefreshPage();
		Wuser.Resetting();
		GotoPosXY(19, 10); cout << "新增用户成功！";
		Sleep(500);
		GotoPosXY(19, 10); cout << "               ";
		AdminPage();
	}

	//删除用户方法实现
	void DelUser(int line) {
		for(int i=0;i<5;i++)
		DelLineData(line - 1);
	}

	//转账：搜索用户，读取数据
	int SearchUser(string pn) {
		char tempstr[256];
		string tempStr;
		fstream file("SignUp.txt");
		while (!file.eof()) {
			file.getline(tempstr, 256, '\n');
			tempStr = string(tempstr);
			if (pn == tempStr) {
				GotoPosXY(23, 16); cout << GetDataLine(pn,Datapath);
				return GetDataLine(pn, Datapath);
			}
		}
		GotoPosXY(19, 16); cout << "无此用户，请重新查询！";
		Sleep(500);
		GotoPosXY(19, 16); cout << "                      ";
	}

	//存储账单方法
	void SaveLog(int n,string value) {
		fstream log("./Log/" + Yuser.Getphonenum() + ".txt",ios::app);
		int lines = (GetLine("./Log/" + Yuser.Getphonenum() + ".txt"))/3;
		if (n == 1) {
			log << lines << "-"<< Time() + '\n' << "存款\n" << value + '\n';
		}
		if (n == 2) {
			log << lines << "-" << Time() + '\n' << "取款\n"<< value + '\n';
		}
		if (n == 3){
			log << lines << "-" << Time() + '\n' << "转账\n" << value + '\n';
		}
		if (n == 4){
			fstream _log("./Log/" + Wuser.Getphonenum() + ".txt", ios::app);
			_log << lines << "-" << Time() + '\n' << "收账\n" << value + '\n';
			_log.close();
		}
		log.close();
	}

	//退出界面方法
	void ExitPage() {
		system("cls");
		cout << "\n\n\n\n\n\n\n\t\t  ------------ ----    ----    ------    ----    ---- ----    ---- ------------" << endl;
		cout << "\t\t  ************ ****    ****   ********   *****   **** ****   ****  ************" << endl;
		cout << "\t\t  ------------ ----    ----  ----------  ------  ---- ----  ----   ----         " << endl;
		cout << "\t\t      ****     ************ ****    **** ************ *********    ************ " << endl;
		cout << "\t\t      ----     ------------ ------------ ------------ ---------    ------------ " << endl;
		cout << "\t\t      ****     ****    **** ************ ****  ****** ****  ****          *****" << endl;
		cout << "\t\t      ----     ----    ---- ----    ---- ----   ----- ----   ----  ------------" << endl;
		cout << "\t\t      ****     ****    **** ****    **** ****    **** ****    **** ************ " << endl;
		cout << "\n\t\t\t\t\t 程序已安全退出，感谢您的使用！\n\n\n";
	}
};