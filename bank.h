#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string.h>

using namespace std;

//��ȡϵͳʱ�䣬�����˻���
long long Time() {
	//��������
	SYSTEMTIME sys_time;

	//������ֵ����Ϊ����ʱ��
	GetLocalTime(&sys_time);
	long long year = sys_time.wYear;
	int month = sys_time.wMonth;
	int day = sys_time.wDay;
	int hour = sys_time.wHour;
	int minute = sys_time.wMinute;
	return year * 100000000 + month * 1000000 + day * 10000 + hour * 100 + minute;
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

//�����࣬�����û�
class Bank {

public:
	//ע�᷽��
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
		cout << "�����������:";
		GotoPosXY(10, 45);
		cout << "��������������������������\n";
		GotoPosXY(11, 45);
		cout << "��           ��\n";
		GotoPosXY(12, 45);
		cout << "��������������������������";
		
		GotoPosXY(11, 47);
		cin >> name;
		fout << name + '\n';
		user.Setname(name);
		
		GotoPosXY(11, 32);
		cout << "�������ֻ����룺";
		GotoPosXY(10, 45);
		cout << "��������������������������\n";
		GotoPosXY(11, 45);
		cout << "��           ��\n";
		GotoPosXY(12, 45);
		cout << "��������������������������";
		cin >> phonenum;
		fout << phonenum + '\n';
		user.Setname(phonenum);
		while (1) {
			GotoPosXY(11, 32);
			cout << "��������λ���������룺";
			cin >> password;
			if (password < 100000 || password > 999999) {
				cout << "���������������������룡";
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
			cout << "����������";
			cin >> money;
			if (money < 0) {
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
		fout << "\n";
		fout.close();
	}

	//��¼����
	void LogIn() {
		cout << "�ѵ�¼" << endl;
		system("cls");
		MainPage();
	}

	//������ʵ��
	void MainPage() {
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
			GotoPosXY(9, 32);
			cout << "ע���У���������"<< endl;
			SignUp();
		}
		else if (x == '2') {
			GotoPosXY(9, 32);
			cout << "��½��" << endl;
			LogIn();
		}
		else {
			exit(0); 
		}         

	}

	//��½�����ʼ��
	void LogInPage() {

	}

	//ע������ʼ��
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