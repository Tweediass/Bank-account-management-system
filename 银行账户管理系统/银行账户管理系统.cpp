// 银行账户管理系统.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Account//用户类，公有继承ATM类
{
public:
	string cardNo;//卡号
	string name;//姓名
	double Money;//金额
	string idCard;//身份证
	string address;//地址
	string telPhone;//电话
	string password;//密码

	void selFunction(Account acc[], int N);//功能选择
	void transfer(Account acc[], int N);//转账
	void chaPassword(Account acc[], int N);//修改密码
	void deposit();//存款
	void withdraw();//取款
	void checBalance();//查看余额
};

class ATM //ATM类
{
public:
	static void setAccount();//银行开户
	static void delAccount(Account acc[], int N);//注销用户
	static void logiAccount(Account acc[], int N);//登录账户
	static void outFile(Account acc[], int N);//输出文件
	static void initMenu();//用户操作界面
};

class Administrator :public Account//管理员类，公有继承Account类
{
public:
	static void admAccount(string password);//管理员账户
	static void addAccount(Account acc[], int N);//增加用户
	static void logoAccount(Account acc[], int N);//删除用户
	static void altAccount(Account acc[], int N);//修改用户信息
	static void seaAccount(Account acc[], int N);//查找用户信息
	static void chaAdmPasswd(string password);//修改管理员账号密码
};

void ATM::setAccount()//银行开户功能
{
	string a, b, c, d, e, passwd, rePasswd;
	double m;
	ofstream outfile("Account.dat", ios::app);//以输出方式打开文件Account.dat,输出至文件末尾
	cout << "Please enter account opening information." << endl;
	cout << "cardNo\tname\taccountMoney\tidCard\taddress\ttelPhone" << endl;
	do {
		cin >> a >> b >> m >> c >> d >> e;
		if (m > 0)//判断输入金额是否正确
			break;
		else
			cout << "Please re-enter the correct information." << endl;
	} while (true);
	cout << "Please enter the password." << endl;
	do {
		cin >> passwd;//输入密码
		cout << "Please enter the password again (be sure to enter the same password for the first time)." << endl;
		cin >> rePasswd;//确认密码
		if (passwd == rePasswd)
		{
			cout << "Successfully registered your account." << endl;
			break;
		}
		else
		{
			cout << "Two passwords are different. Please re-enter." << endl;
		}
	} while (true);
	outfile << a << "\t" << b << "\t" << m << "\t" << c << "\t" << d << "\t" << e << "\t" << passwd << endl;//将开户的数据存放至文件Account.dat末尾
	outfile.close();//关闭文件Account.dat
}

void ATM::delAccount(Account acc[], int N)//银行注销用户功能
{
	string No;
	string passwd;
	int i, flag = 0;
	cout << "Please enter the account number you need to cancel." << endl;
	cin >> No;
	for (i = 0; i < N; i++)
	{
		if (acc[i].cardNo == No)
		{
			cout << "Please enter the password." << endl;
			while (true)
			{
				cin >> passwd;
				if (passwd == acc[i].password)
				{
					N--;//注销成功,用户个数 N 减一
					flag = 1;
					for (; i < N; i++)
					{
						acc[i] = acc[i + 1];//将用户对象数组在i之后的用户,往前移一位
					}
					break;
				}
				else
				{
					cout << "The password is incorrect. Please re-enter it." << endl;
				}
			}
		}
		if (flag) break;
	}
	if (flag)
	{
		ATM::outFile(acc, N);//调用静态台函数 ATM::outFile(acc, N); 实现数据的更新
		cout << "Successfully canceled the account." << endl;
	}
	else
	{
		cout << "The entered account number is incorrect and will return to the main menu." << endl;
	}
}

void ATM::logiAccount(Account acc[], int N)//账户登录功能
{
	int i, flag = 0;
	string No, passwd;
	cout << "Please enter the card number." << endl;
	cin >> No;//输入卡号
	for (i = 0; i < N; i++)
	{
		if (acc[i].cardNo == No)//判断是否存在此卡号
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		cout << "Please enter the password." << endl;
		while (true)
		{
			cin >> passwd;//输入密码
			if (acc[i].password == passwd)//核对密码是否正确
			{
				acc[i].selFunction(acc,N);//登陆成功.调用对象的成员函数 selFunction(acc, N); 进入功能选择界面
				break;
			}
			else
			{
				cout << "Wrong password and re-enter." << endl;
			}
		}
	}
	else
	{
		cout << "The card number is wrong and will return to the main menu." << endl;
	}
}

void ATM::outFile(Account acc[], int N)//输出文件功能,用于更新数据
{
	ofstream outfile("Account.dat", ios::out);
	for (int i = 0; i < N; i++)
	{
		outfile << acc[i].cardNo << "\t";
		outfile << acc[i].name << "\t";
		outfile << acc[i].Money << "\t";
		outfile << acc[i].idCard << "\t";
		outfile << acc[i].address << "\t";
		outfile << acc[i].telPhone << "\t";
		outfile << acc[i].password << endl;
	}
	outfile.close();
}

void Administrator::admAccount(string password)//进入管理员界面
{
	string admPasswd;
	int N;
	Account acc[100];
	cout << "Please enter the administrator password." << endl;
	cin >> admPasswd;//输入管理员密码
	if (admPasswd == password)//判断密码是否正确
	{
		//N++;
		int flag = 1;
		char Satan;//Switch标志变量
		do {
			ifstream infile1("Administrator.dat", ios::in);//以输入方式打开文件Administrator.dat
			infile1 >> admPasswd;
			infile1.close();
			N = 0;
			ifstream infile("Account.dat", ios::in);//以输入方式打开文件Account.dat
			while (infile)//文件内容赋值于对象数组acc
			{
				infile >> acc[N].cardNo;
				infile >> acc[N].name;
				infile >> acc[N].Money;
				infile >> acc[N].idCard;
				infile >> acc[N].address;
				infile >> acc[N].telPhone;
				infile >> acc[N++].password;
			}
			infile.close();
			N--;
			//进入管理员界面
			cout << endl;
			cout << "\t\t*************************************************" << endl;
			cout << "\t\t*    Welcome to the administrator account       *" << endl;
			cout << "\t\t*                 1-add                         *" << endl;
			cout << "\t\t*                 2-delete                      *" << endl;
			cout << "\t\t*                 3-alter                       *" << endl;
			cout << "\t\t*                 4-search                      *" << endl;
			cout << "\t\t*                 5-change_Password             *" << endl;
			cout << "\t\t*                 6-return                      *" << endl;
			cout << "\t\t*************************************************" << endl;
			cin >> Satan;
			switch (Satan)
			{
			case '1':
			{
				Administrator::addAccount(acc, N);//管理员账户:增加功能
				break;
			}
			case '2':
			{
				Administrator::logoAccount(acc, N);//管理员账户:删除功能
				break;
			}
			case '3':
			{
				Administrator::altAccount(acc, N);//管理员账户:修改功能
				break;
			}
			case '4':
			{
				Administrator::seaAccount(acc, N);//管理员账户:查询功能
				break;
			}
			case '5':
			{
				Administrator::chaAdmPasswd(admPasswd);//管理员账户:修改管理员密码
				break;
			}
			case '6'://返回初始界面
			{
				flag = 0;
				break;
			}
			default:
			{
				cout << "Incorrect input. Please re-enter." << endl;
				break;
			}
			}
		} while (flag);
	}
	else
	{
		cout << "The password is incorrect and returns to the menu." << endl;
	}
}

void Administrator::addAccount(Account acc[], int N)//增加用户(管理员)
{
	string a, b, c, d, e, passwd, rePasswd;
	double m;
	ofstream outfile("Account.dat", ios::app);
	cout << "Please enter the newly added user's information." << endl;
	cout << "cardNo\tname\taccountMoney\tidCard\taddress\ttelPhone" << endl;
	do {
		cin >> a >> b >> m >> c >> d >> e;
		if (m > 0)
			break;
		else
			cout << "Please re-enter the correct information." << endl;
	} while (true);
	do {
		cout << "Please enter the password." << endl;
		cin >> passwd;
		cout << "Please enter the password again (be sure to enter the same password for the first time)." << endl;
		cin >> rePasswd;
		if (passwd == rePasswd)
		{
			cout << "Successfully add account." << endl;
			break;
		}
		else
		{
			cout << "Two passwords are different. Please re-enter." << endl;
		}
	} while (true);
	outfile << a << "\t" << b << "\t" << m << "\t" << c << "\t" << d << "\t" << e << "\t" << passwd << endl;
	outfile.close();
}

void Administrator::logoAccount(Account acc[], int N)//删除用户(管理员)
{
	string No;
	int i, flag = 0;
	cout << "Please enter the account number you need to cancel." << endl;
	cin >> No;
	for (i = 0; i < N; i++)
	{
		if (acc[i].cardNo == No)
		{
			N--;
			flag = 1;
			for (; i < N; i++)
			{
				acc[i] = acc[i + 1];
			}
			break;
		}
	}
	if (flag)
	{
		ATM::outFile(acc, N);
		cout << "Successfully canceled the account." << endl;
	}
	else
	{
		cout << "The entered account number is incorrect and will return to the main menu." << endl;
	}
}

void Administrator::altAccount(Account acc[], int N)//修改信息(管理员)
{
	string No;
	int i, flag = 0;
	cout << "Please enter the card number to be queried." << endl;
	cin >> No;
	for (i = 0; i < N; i++)
	{
		if (acc[i].cardNo == No)
		{
			flag = 1;
			cout << "cardNo\tname\taccountMoney\tidCard\taddress\ttelPhone\tpassword" << endl;
			cout << acc[i].cardNo << "\t";
			cout << acc[i].name << "\t";///////////////////////////////////////
			cout << acc[i].Money << "\t\t";////////输出当前用户的具体信息////////
			cout << acc[i].idCard << "\t";/////////////////////////////////////
			cout << acc[i].address << "\t";
			cout << acc[i].telPhone << "\t\t";
			cout << acc[i].password << endl;
			cout << "Please enter the updated information." << endl;
			cout << "cardNo\tname\taccountMoney\tidCard\taddress\ttelPhone\tpassword" << endl;
			cin >> acc[i].cardNo >> acc[i].name >> acc[i].Money >> acc[i].idCard >> acc[i].address >> acc[i].telPhone >> acc[i].password;
			cout << "Successfully modified." << endl;
			ATM::outFile(acc, N);
			break;
		}
	}
	if (!flag)
	{
		cout << "The card number is incorrect and will return to the menu." << endl;
	}
}

void Administrator::seaAccount(Account acc[], int N)//查询用户信息(管理员)
{
	string No;
	int i;
	cout << "Please enter the card number to be queried." << endl;
	cin >> No;
	for (i = 0; i < N; i++)
	{
		if (acc[i].cardNo == No)
		{
			cout << "cardNo\tname\taccountMoney\tidCard\taddress\ttelPhone\tpassword" << endl;
			cout << acc[i].cardNo << "\t";
			cout << acc[i].name << "\t";
			cout << acc[i].Money << "\t\t";
			cout << acc[i].idCard << "\t";
			cout << acc[i].address << "\t";
			cout << acc[i].telPhone << "\t\t";
			cout << acc[i].password << endl;
			break;
		}
	}
	if (i == N)
	{
		cout << "The card number is incorrect and will return to the menu." << endl;
	}
}

void Administrator::chaAdmPasswd(string password)//修改管理员账户密码(管理员)
{
	int flag = 1;
	string newPasswd1, newPasswd2, oldPasswd;
	cout << "Please enter the password for the current administrator account." << endl;
	do {
		cin >> oldPasswd;//输入当前未更新的密码
		if (oldPasswd == password)
		{
			do {
				cout << "Please enter the password for the new administrator account." << endl;
				cin >> newPasswd1;//输出更新后的密码
				cout << "Please enter the password for the new administrator account again." << endl;
				cin >> newPasswd2;//确认更新后的密码
				if (newPasswd1 == newPasswd2)
				{
					flag = 0;
					ofstream outfile("Administrator.dat", ios::out);
					cout << "Password reset complete." << endl;
					outfile << newPasswd1;//更新后的密码存放至文件Administrator.dat
					outfile.close();
					break;
				}
				else
				{
					cout << "Two passwords are different. Please re-enter." << endl;
				}
			} while (true);
		}
		else
		{
			cout << "The password is wrong. Please re-enter the password for the current administrator account." << endl;
		}
	} while (flag);
}

void ATM::initMenu()//银行初始界面
{
	Account acc[100];//对象数组acc
	char Toxic, ch = NULL;
	int N, flag = 1;
	string admPasswd;
	ifstream infile1("Administrator.dat", ios::in);//以输入方式打开文件Administrator.dat
	infile1.get(ch);
	if (ch == NULL)//如果文件Administrator.dat内容为空,则设置管理员账户密码
	{
		infile1.close();
		cout << "Please set the password for the administrator account." << endl;
		cin >> admPasswd;
		ofstream outfile1("Administrator.dat", ios::trunc);
		outfile1 << admPasswd;
		outfile1.close();
	}
	else//否则获取文件内容至admPasswd
	{
		infile1 >> admPasswd;
		admPasswd = ch + admPasswd;
		infile1.close();
	}
	do {
		N = 0;
		ifstream infile("Account.dat", ios::in);//以输入方式打开文件Account.dat
		while (infile)//文件内容赋值于对象数组acc
		{
			infile >> acc[N].cardNo;
			infile >> acc[N].name;
			infile >> acc[N].Money;
			infile >> acc[N].idCard;
			infile >> acc[N].address;
			infile >> acc[N].telPhone;
			infile >> acc[N++].password;
		}
		N--;
		infile.close();
		cout << endl;//进入银行初始界面
		cout << "\t\t***********************************************" << endl;
		cout << "\t\t*        Welcome to the banking housing.      *" << endl;
		cout << "\t\t*              1-set_Account                  *" << endl;
		cout << "\t\t*              2-login_Account                *" << endl;
		cout << "\t\t*              3-delete_Account               *" << endl;
		cout << "\t\t*              4-administrator_Account        *" << endl;
		cout << "\t\t*              5-exit                         *" << endl;
		cout << "\t\t***********************************************" << endl;
		cin >> Toxic;
		switch (Toxic)
		{
		case '1':
		{
			ATM::setAccount();//开户
			break;
		}
		case '2':
		{
			ATM::logiAccount(acc, N);//登录
			break;
		}
		case '3':
		{
			ATM::delAccount(acc, N);//注销
			break;
		}
		case '4':
		{
			Administrator::admAccount(admPasswd);//进入管理员系统
			break;
		}
		case '5':
		{
			flag = 0;
			break;
		}
		default:
		{
			cout << "Incorrect input. Please re-enter." << endl;
			break;
		}
		}
	} while (flag);
}

void Account::selFunction(Account acc[],int N)//用户登录界面
{
	int flag = 1;
	char Tweedia;
	do {
		N = 0;
		ifstream infile("Account.dat", ios::in);//以输入方式打开文件Account.dat
		while (infile)//文件内容赋值于对象数组acc
		{
			infile >> acc[N].cardNo;
			infile >> acc[N].name;
			infile >> acc[N].Money;
			infile >> acc[N].idCard;
			infile >> acc[N].address;
			infile >> acc[N].telPhone;
			infile >> acc[N++].password;
		}
		N--;
		infile.close();
		cout << "\t\t" << this->name << ",您好！" << endl;
		cout << endl;
		cout << "\t\t***********************************************" << endl;
		cout << "\t\t*            Please select function.          *" << endl;
		cout << "\t\t*                  1-deposit                  *" << endl;
		cout << "\t\t*                  2-withdraw                 *" << endl;
		cout << "\t\t*                  3-transfer                 *" << endl;
		cout << "\t\t*                  4-change_Password          *" << endl;
		cout << "\t\t*                  5-check_Balance            *" << endl;
		cout << "\t\t*                  6-return                   *" << endl;
		cout << "\t\t***********************************************" << endl;
		cin >> Tweedia;
		switch (Tweedia)
		{
		case '1':
		{
			this->deposit();//存款
			ATM::outFile(acc, N);//更新数据
			break;
		}
		case '2':
		{
			this->withdraw();//取款
			ATM::outFile(acc, N);
			break;
		}
		case '3':
		{
			this->transfer(acc, N);//转账
			ATM::outFile(acc, N);
			break;
		}
		case '4':
		{
			this->chaPassword(acc, N);//修改用户密码
			ATM::outFile(acc, N);
			break;
		}
		case '5':
		{
			this->checBalance();//查询余额
			break;
		}
		case '6':
		{
			flag = 0;
			break;
		}
		default:
		{
			cout << "Incorrect input and re-enter." << endl;
			break;
		}
		}
	} while (flag);
}

void Account::deposit()//存款
{
	double m;
	cout << "Please enter the deposit amount." << endl;
	do {
		cin >> m;//输入存款金额
		if (m > 0)
			break;
		else
			cout << "Enter the wrong amount and re-enter the amount." << endl;
	} while (true);
	this->Money += m;//增加用户金额
	cout << "Successful deposit." << endl;
}

void Account::withdraw()//取款
{
	double m;
	cout << "Please enter the withdrawal amount." << endl;
	do {
		cin >> m;//输入取款金额
		if (m > 0 && m < this->Money)
			break;
		else
			cout << "The amount entered was incorrect and reentered." << endl;
	} while (true);
	this->Money -= m;//减少用户金额
	cout << "Successful withdraw." << endl;
}

void Account::transfer(Account acc[], int N)//转账
{
	int i, flag = 1;
	double m;
	string No;
	cout << "Please enter the transfer card number." << endl;
	do {
		cin >> No;//输入转账用户
		for (i = 0; i < N; i++)
		{
			if (No == acc[i].cardNo)
			{
				flag = 0;
				cout << "Please enter the amount transferred to " << acc[i].name << "." << endl;
				cin >> m;//输入转账金额
				this->Money -= m;//减少用户金额
				acc[i].Money += m;//增加转账用户金额
				cout << "Successful transfer." << endl;
				break;
			}
		}
		if (flag)
		{
			cout << "Bad card number. Please re-enter the transfer card number." << endl;
		}
		else
			break;
	} while (true);
}

void Account::chaPassword(Account acc[], int N)//修改用户密码
{
	int flag = 1;
	string newPasswd1, newPasswd2, oldPasswd;
	cout << "Please enter the current password." << endl;
	do {
		cin >> oldPasswd;
		if (oldPasswd == this->password)
		{
			do {
				cout << "Please enter a new password." << endl;
				cin >> newPasswd1;
				cout << "Please enter the new password again." << endl;
				cin >> newPasswd2;
				if (newPasswd1 == newPasswd2)
				{
					flag = 0;
					cout << "Password reset complete." << endl;
					this->password = newPasswd1;
					break;
				}
				else
				{
					cout << "Two passwords are different. Please re-enter." << endl;
				}
			} while (true);
		}
		else
		{
			cout << "The password is wrong. Please re-enter the current password." << endl;
		}
	} while (flag);
}

void Account::checBalance()//查询用户余额
{
	cout << "The current account balance is " << this->Money << " Yuan." << endl;
}

int main()
{
	ATM::initMenu();//进入初始界面
	return 0;
}