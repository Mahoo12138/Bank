#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <string.h>
#include <regex>

using namespace std;

//��ȡϵͳʱ�䣬�����˻���
string Time() {
	//��������
	SYSTEMTIME sys_time;

	//������ֵ����Ϊ����ʱ��
	GetLocalTime(&sys_time);
	long long year = sys_time.wYear;
	int month = sys_time.wMonth;
	int day = sys_time.wDay;
	int hour = sys_time.wHour;
	int minute = sys_time.wMinute;
	long long time = (year * 100000000) + (month * 1000000) + (day * 10000) + (hour * 100) + minute;
	string t = to_string(time);
	return t;
	//���ʱ��
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

//ָ��λ�����
void GotoPosXY(int y, int x) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)	//���ÿ���̨��������λ��
								/*��ȡ��׼����ľ��*/, pos);

	/*
	COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ����ꡣ�䶨��Ϊ��
		typedef struct _COORD {
		SHORT X; // horizontal coordinate
		SHORT Y; // vertical coordinate
	} COORD;
	*/
}

//�û��࣬��������
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

//����
class Bank {
private:
	string account = "admin";
	string password = "admin";
	
public:
	User user;

	//ע�᷽��
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
		cout << "ע���У������ֻ�����" ;
		GotoPosXY(11, 32);
		cout << "                                   ";
		GotoPosXY(11, 32);
		cout << "�������ֻ����룺";
		GotoPosXY(10, 45);
		cout << "   ������������������������������";
		GotoPosXY(11, 48);
		cout << "��             ��";
		GotoPosXY(12, 45);
		cout << "   ������������������������������";
		
		GotoPosXY(11, 50);
		cin >> phonenum;

		regex pn("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");		//����ʮһλ�Ϸ��ֻ���������ʽ����
		regex pw("\\d{6}$");											//������λ�Ϸ���ʽ����������ʽ����

		while (1) {
			
			if (!regex_match(phonenum, pn)) {
				GotoPosXY(19, 16);
				cout << "��������ȷ�ֻ��ţ�";
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
		cout << "��������";

		GotoPosXY(10, 45);
		cout << "                    ";
		GotoPosXY(11, 48);
		cout << "                 ";
		GotoPosXY(12, 45);
		cout << "                    ";

		GotoPosXY(11, 32);
		cout << "����������������";
		
		GotoPosXY(10, 45);
		cout << "   ��������������������������";
		GotoPosXY(11, 48);
		cout << "��           ��";
		GotoPosXY(12, 45);
		cout << "   ��������������������������";

		GotoPosXY(11, 50);
		cin >> name;
		
		user.Setname(name);

		GotoPosXY(9, 40);
		cout << "��������   ";
		GotoPosXY(11, 32);
		cout << "��������λ���������룺";
		GotoPosXY(10, 45);
		cout << "         ��������������������";
		GotoPosXY(11, 54);
		cout << "��        ��  ";
		GotoPosXY(12, 45);
		cout << "         ��������������������";
		GotoPosXY(11, 56);
		cin >> password;

		while (1) {

			if (!regex_match(password, pw)) {
				GotoPosXY(19, 16);
				cout << "�������ʽ��ȷ�����룡";
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
			cout << "������          ";
			GotoPosXY(11, 32);
			cout << "����������    ";
			GotoPosXY(10, 39);
			cout << "         ��������������������";
			GotoPosXY(11, 48);
			cout << "��        ��  ";
			GotoPosXY(12, 39);
			cout << "         ��������������������";
			GotoPosXY(11, 50);
			cin >> money;
			if (money < 0) {
				GotoPosXY(19, 16);
				cout << "��������������������룡";
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

	//��¼����
	void LogIn(User user) {
		string name,phonenum,tempStr,password;
		char tempstr[256],key;
		int money;
		string account;

		fstream check("SignUp.txt");
		if (check.fail()) {
			check.close();
			GotoPosXY(19, 16);
			cout << "��ǰ��ע���û�����ע�ᣡ";
			Sleep(1500);
			GotoPosXY(19, 16);
			cout << "                         ";
			SignUp(user);
			GotoPosXY(19, 16);
			cout << "���ѳɹ�ע�ᣬ���������¼���棡";
			Sleep(800);
		}
		else {
			key = check.get();	//��ͼȥ��һ���ַ�

			if (check.eof()) {	//һ���ַ���δ��������ʾ�ļ�Ϊ��
				GotoPosXY(19, 16);
				cout << "��ǰ��ע���û�����ע�ᣡ";
				Sleep(1500);
				GotoPosXY(19, 16);
				cout << "                         ";
				SignUp(user);
				GotoPosXY(19, 16);
				cout << "���ѳɹ�ע�ᣬ���������¼���棡";
				Sleep(800);
			}
		}
		check.close();
		RefreshPage();
		GotoPosXY(9, 32);
		cout << "��¼�У������ֻ���";

		GotoPosXY(11, 32);
		cout << "�������ֻ����룺";
		GotoPosXY(10, 45);
		cout << "   ������������������������������";
		GotoPosXY(11, 48);
		cout << "��             ��";
		GotoPosXY(12, 45);
		cout << "   ������������������������������";

		GotoPosXY(11, 50);
		cin >> phonenum;

		regex p("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");	//����������ʽ����

		while (1) {

			if (!regex_match(phonenum, p)) {
				GotoPosXY(19, 16);
				cout << "��������ȷ�ֻ��ţ�";
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
		file.seekg(0, ios::beg);		//���ļ�ָ��ص���ʼλ�ã�����Ӱ���¼����
		while (!file.eof()) {
			cout << "��ʼ����";
			file.getline(tempstr,256,'\n');
			cout << tempstr;
			tempStr = string(tempstr);
			if (phonenum == tempStr) {
				cout << "�ҵ���";
				user.Setnum(phonenum);
				file.seekg(-28, ios::cur);	//���ļ�ָ��ӵ�ǰλ�����ļ���ʼ�����ƶ����ֽ� 
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
		cout << "��������   ";
		GotoPosXY(11, 32);
		cout << "��������λ���������룺";
		GotoPosXY(10, 45);
		cout << "         ��������������������";
		GotoPosXY(11, 54);
		cout << "��        ��  ";
		GotoPosXY(12, 45);
		cout << "         ��������������������";
		
		tempStr = user.Getpassword();
		while (1) {
			GotoPosXY(11, 56);
			cin >> password;
			if (password == tempStr) {
				GotoPosXY(19, 16);
				cout << "��¼�ɹ���������ת���桭��";
				Sleep(800);
				break;
			}
			else {
				GotoPosXY(19, 16);
				cout << "��������������������룡";
				Sleep(200);
				GotoPosXY(11, 56);
				cout << "      ";
				continue;
			}
		}
		RefreshPage();
		UserPage();
	}

	//������ʵ��
	void MainPage(User user) {
		char x;
		system("cls");
		cout << "123456789012345678901234567890123456789012345678901234567890" << endl;
		cout << "\n\n\n\t\t������������������������������������������������������\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��             ��ӭʹ���ϻ����й���ϵͳ             ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��             ��ѡ��                             ��\n"
			<< "\t\t��                   1>   ע��                      ��\n"
			<< "\t\t��                   2>   ��¼                      ��\n"
			<< "\t\t��             ��>����������˳�ϵͳ<��             ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��    �ͷ��绰��15507462014�����н�������벦110    ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t������������������������������������������������������\n"
			<< endl;
		cout << "\n\t\t��ѡ�������ʽ�� ";
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

	//�û�����ʵ��
	void UserPage() {
		char x;
		GotoPosXY(8, 31);
		cout << "�������Ҫ������ţ�";
		GotoPosXY(10, 32);
		cout << "1>  ���";
		GotoPosXY(10, 44);
		cout << "2>  ȡ��";
		GotoPosXY(12, 32);
		cout << "3>  ת��";
		GotoPosXY(12, 44);
		cout << "4>  �˳�";
		GotoPosXY(19, 16);
		cout << "��������������������룡";
		GotoPosXY(19, 36);
		cin >> x;
		

	}

	//ˢ�½���
	void RefreshPage() {
        system("cls");
		cout << "\n\n\n\n\t\t������������������������������������������������������\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��             ��ӭʹ���ϻ����й���ϵͳ             ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t��    �ͷ��绰��15507462014�����н�������벦110    ��\n"
			<< "\t\t��                                                  ��\n"
			<< "\t\t������������������������������������������������������\n"
			<< endl;
	}
};
