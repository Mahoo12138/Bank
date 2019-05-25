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

//�������Ϸ�
int CheckInput(string str) {
	regex pn("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");		//����ʮһλ�Ϸ��ֻ���������ʽ����
	regex pw("\\d{6}$");											//������λ�Ϸ���ʽ����������ʽ����
	if (str.length() <= 6) {
		return regex_match(str, pw);
	}
	else {
		return regex_match(str, pn);
	}

}
int CheckMoney(string mon) {
	regex pw("^\\d{1,}$");
	return regex_match(mon, pw);
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
};

//����
class Bank {
private:
	string account = "admin";
	string password = "admin";
	
public:
	User Yuser,Wuser;

	//ע�᷽��
	void SignUp() {
		string name;
		string phonenum;
		int money;
		string password;

		RefreshPage();

		ofstream fout("SignUp.txt", ios::app);

		
		Yuser.Setaccount();
		fout << Yuser.Getaccount();
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

		while (1) {
			
			if (!CheckInput(phonenum)){
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
		Yuser.Setname(phonenum);

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
		
		Yuser.Setname(name);

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

			if (!CheckInput(password)) {
				GotoPosXY(19, 16);
				cout << "�������ʽ��ȷ�����룡";
				Sleep(1800);
				GotoPosXY(19, 16);
				cout << "                         ";
				GotoPosXY(11, 54);
				cout << "        ";
				GotoPosXY(11, 54);
				cin >> password;
			}
			else
				break;
		}

		Yuser.Setpassword(password);
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
				Yuser.Setmoney(money);
				fout << money ;
				fout << "\n";
			}
			break;
		}
		fout << name + '\n';
		fout.close();
	}

	//��¼����
	void LogIn() {
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
			SignUp();
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
				SignUp();
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

		while (1) {

			if (!CheckInput(phonenum)) {
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
		while (!file.eof()) {			//�����ļ�����ȡ����
			file.getline(tempstr,256,'\n');
			tempStr = string(tempstr);
			if (phonenum == tempStr) {
				Yuser.Setnum(phonenum);			//��ȡ�ֻ���
				file.seekg(-28, ios::cur);	    //���ļ�ָ��ӵ�ǰλ�����ļ���ʼ�����ƶ����ֽ� 
				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				int index = tempStr.find(":");
				string account = tempStr.substr(0, index);
				Yuser.Setaccount(account);		//��ȡ�˻�
				file.seekg(13, ios::cur);
				file.getline(tempstr, 256, '\n');

				tempStr = string(tempstr);
		
				Yuser.Setpassword(tempStr);		//��ȡ����

				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				money = atoi(tempStr.c_str());
				Yuser.Setmoney(money);		   //��ȡ���

				file.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				Yuser.Setname(tempStr);		   //��ȡ����
				break;
			}
			 
		}   //  
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
		
		tempStr = Yuser.Getpassword();
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
	void MainPage() {
		char x;
		system("cls");
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
			SignUp();
		}
		else if (x == '2') {
			LogIn();
		}
		else {
			exit(0);
		}

	}

	//�û���������ʵ��
	void UserPage() {
		char x;
		GotoPosXY(8, 31);
		cout << "ҵ���б�";
		GotoPosXY(10, 28);
		cout << "1>  ���";
		GotoPosXY(10, 40);
		cout << "2>  ȡ��";
		GotoPosXY(10, 52);
		cout << "3>  ת��";
		GotoPosXY(12, 28);
		cout << "4>  ���";
		GotoPosXY(12, 40);
		cout << "5>  ��ѯ";
		GotoPosXY(12, 52);
		cout << "6>  �˳�";
		GotoPosXY(19, 16);
		cout << "���������������ţ�";
		GotoPosXY(19, 36);
		cin >> x;
		while (1) {
			switch (x) {
				case '2':Withdraw(); break;
				case '4':
					GotoPosXY(19, 16);cout << "                             ";
					GotoPosXY(19, 16); cout << "�������Ϊ��" << Yuser.Getmoney(); break;
				case '6':Exit(); break;

			}
			GotoPosXY(20, 16);
			cout << "�������������������һ��������        ";
			GotoPosXY(20, 48);
			cin >> x;
		}
		

	}

	//ȡ���
	void Withdraw() {
		RefreshPage();
		string mon;
		GotoPosXY(9, 32);
		cout << "��ȡ�������֧��ʮ��";
		GotoPosXY(11, 32);
		cout << "������ȡ����";
		GotoPosXY(10, 39);
		cout << "         ��������������������";
		GotoPosXY(11, 48);
		cout << "��        ��  ";
		GotoPosXY(12, 39);
		cout << "         ��������������������";
		GotoPosXY(11, 50);
		cin >> mon;
		while (1) {
			if (!CheckMoney(mon)) {
				GotoPosXY(19, 16);
				cout << "���������Ľ�";
				Sleep(1800);
				GotoPosXY(19, 16);
				cout << "                  ";
				GotoPosXY(11, 50);
				cout << "       ";
				GotoPosXY(11, 50);
				cin >> mon;
			}
			else
				break;
		}
		int money = atoi(mon.c_str());
		if ((Yuser.Getmoney() - money) < 0) {
			GotoPosXY(19, 16);
			cout << "���㣡";
			Sleep(300);
			GotoPosXY(19, 16);
			cout << "          ";
		}
		Yuser.Setmoney(Yuser.Getmoney() - money);
		GotoPosXY(19, 16);
		cout << "ȡ��ɹ���";
		Sleep(300);
		GotoPosXY(19, 16);
		cout << "          ";
		RefreshPage();
		UserPage();
	}

	//�˳�����
	void Exit() {
		int line = GetDataLine(Yuser.Getphonenum());
		cout << line;
		ChangeLineData(line + 2, Yuser.Getpassword());
		ChangeLineData(line + 3, to_string(Yuser.Getmoney()));
		exit(0);
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
		
	//��ȡָ��������������
	int GetDataLine(string line) {
		fstream file("SignUp.txt",ios::in);		//��ֻ����ʽ���ļ�
		int n = 0;
		string str;
		while (1){
			getline(file, str, '\n');
			n++;
			if (str == line);
			break;
		}
		file.close();
		return n;
	}

	//�޸�ָ��������
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

	//�����û�����ȡ����
	void SearchUser() {
		string name, phonenum, tempStr, password;
		char tempstr[256], key;
		int money;
		string account;

		fstream search("SignUp.txt");
		while (!search.eof()) {					//�����ļ�����ȡ����
			search.getline(tempstr, 256, '\n');
			tempStr = string(tempstr);
			if (phonenum == tempStr) {
				Wuser.Setnum(phonenum);			//��ȡ�ֻ���
				search.seekg(-28, ios::cur);	    //���ļ�ָ��ӵ�ǰλ�����ļ���ʼ�����ƶ����ֽ� 
				search.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				int index = tempStr.find(":");
				string account = tempStr.substr(0, index);
				Wuser.Setaccount(account);		//��ȡ�˻�
				search.seekg(13, ios::cur);
				search.getline(tempstr, 256, '\n');

				tempStr = string(tempstr);

				Wuser.Setpassword(tempStr);		//��ȡ����

				search.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				money = atoi(tempStr.c_str());
				Wuser.Setmoney(money);		   //��ȡ���

				search.getline(tempstr, 256, '\n');
				tempStr = string(tempstr);
				Wuser.Setname(tempStr);		   //��ȡ����
				break;
			}

		}  
		search.close();
	}
};
