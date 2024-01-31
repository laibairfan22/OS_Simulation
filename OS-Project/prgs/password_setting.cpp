#include<iostream>
#include<string>
#include<fstream>
using namespace std;
bool root_entrance;
void root_password();
void password_reset_func()
{
	system("cls");
	ofstream pass_obj, email_obj;
	
	string newpass1,newpass2,newemail;
	cout << "ENTER THE NEW PASSWORD :" << endl;
	cin >> newpass1;
	cout << "ENTER PASSWORD AGAIN TO CONFIRM : " << endl;
	cin >> newpass2;
	if (newpass1 == newpass2)
	{
		system("cls");
		cout << "YOUR PASSWORD IS MATCH : " << endl;
		cout << "ENTER YOUR EMAIL : " << endl;
		cin >> newemail;
		pass_obj.open("pass_read.txt",ios::in);
		email_obj.open("email_read.txt", ios::in);
		pass_obj << newpass1;
		email_obj << newemail;
		pass_obj.close();
		email_obj.close();
		system("cls");
		cout << "YOUR PASS WORD IS SET :" << endl;
		if (root_entrance)
		{
			return;
		}
		else
	    {
			root_password();
		}

	}
	else
	{
		system("cls");
		cout << "YOUR PASSWORD NOT MATCH ENTER AGAIN : " << endl;
		system("pause");
		password_reset_func();
	}

}
void root_password()
{
	
	string pass;
	cout << "ENTER THE PASSWORD : " << endl;
	cin >> pass;
	string pass_check_from_file;
	ifstream obj1;
	obj1.open("pass_read.txt",ios::out);
	obj1 >> pass_check_from_file;
	obj1.close();
	if (pass == pass_check_from_file)
	{
		root_entrance = true;
		cout << "TRUE";

	}
	else
	{
		string decision;
		root_entrance = false;
		cout << "YOU ENTER THE WRONG PASSWORD : " << endl;
		cout << "IF YOU FORGET THE PASSWORD PRESS 'Y/y' OTHERWISE N/n : " << endl;
		cin >> decision;
		if (decision=="Y"||decision=="y")
		{
			string email;
			cout << "ENTER YOUR EMAIL : " << endl;
			cin >> email;
			string email_check_from_file;
			ifstream obj2;
			obj2.open("email_read.txt",ios::out);
			obj2 >> email_check_from_file;
			obj2.close();
			if (email==email_check_from_file)
			{
				cout << "False" << endl;
				password_reset_func();
			}
			else
			{
				cout << "YOUR EMAIL IS INCORRECT : " << endl;
			}
		}
		cout << "FALSE";
	}
	
}
int main()
{
	root_password();
	system("pause");
	return 0;
}