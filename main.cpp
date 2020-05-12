#include<iostream>
using namespace std;
#include"Banking_System.h"
#define MIN_BALANCE 500
class InsufficientFunds{};
Account::Account(string fname,string lname,float bal)
{
	NextAcc_Num++;
	Acc_Num=NextAcc_Num;
	FirstName=fname;
	LastName=lname;
	balance=bal;
}
void Account::Deposit(float ammount)
{
	balance+=ammount;
}
void Account::Withdraw(float ammount)
{
	balance-=ammount;
}
void Account::setLastAccountNumber(long accnumber)
{
	NextAcc_Num=accnumber;	
}
long Account::getLastAccountNumber()
{
	return NextAcc_Num;
}
ostream & operator <<(ostream &o,Account &a)
{
	o<<"First Name:"<<a.get_first_name()<<endl;
	o<<"Last Name:"<<a.get_last_name()<<endl;
	o<<"Account Number:"<<a.get_Acc_num()<<endl;
	o<<"Balance:"<<a.get_balance()<<endl;
	return o;
}

ifstream & operator>>(ifstream &ifs,Account &acc)
{
	ifs>>acc.Acc_Num;
	ifs>>acc.FirstName;
	ifs>>acc.LastName;
	ifs>>acc.balance;
	return ifs;
}
ofstream & operator<<(ofstream &ofs,Account &a)
{
	ofs<<a.Acc_Num<<endl;
	ofs<<a.FirstName<<endl;
	ofs<<a.LastName<<endl;
	ofs<<a.balance<<endl;
	return ofs;
}

Bank::Bank()
{
	Account account;
	ifstream infile;
	infile.open("Bank.data");
	if(!infile.is_open())
	{
		//cout<<"Error in opening file\n";
		return;
	}
	while(1)
	{
		infile>>account;
		if(infile.eof())
		break;
		accounts.insert(pair<long,Account>(account.get_Acc_num(),account));
	}
	Account::setLastAccountNumber(account.get_Acc_num());
	infile.close();
}
Account Bank::OpenAccount(string fname,string lname,float balance)
{
	ofstream outfile;
	Account account(fname,lname,balance);
	
	accounts.insert(pair<long,Account>(account.get_Acc_num(),account));
	outfile.open("Bank.data",ios::trunc);
	map<long,Account>::iterator itr;
	for(itr=accounts.begin();itr!=accounts.end();itr++)
	{
		outfile<<itr->second;
	}
	outfile.close();
	return account;
}

Account Bank::BalanceEnquiry(long acc_num)
{
	map<long,Account>::iterator itr=accounts.find(acc_num);
	return itr->second;
}
Account Bank::Deposit(long acc_num,float ammount)
{
	map<long,Account>::iterator itr=accounts.find(acc_num);
	itr->second.Deposit(ammount);
	return itr->second;
}

Account Bank::Withdrawl(long acc_num,float ammount)
{
	map<long,Account>::iterator itr=accounts.find(acc_num);
	cout<<"hhhh   Withdrawl()   "<<itr->first<<endl;
	itr->second.Withdraw(ammount);
	return itr->second;
}

void Bank::CloseAccount(long acc_num)
{
	map<long,Account>::iterator itr=accounts.find(acc_num);
	cout<<"Account deleted "<<itr->second;
	accounts.erase(acc_num);
}

void Bank::ShowAllAccount()
{
	map<long,Account>::iterator itr;
	for(itr=accounts.begin();itr!=accounts.end();itr++)
	{
		cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
	}
}

Bank::~Bank()
{
	cout<<"Good bye everuyonw   \n";
	ofstream outfile;
	outfile.open("Bank.data",ios::trunc);
	map<long,Account>::iterator itr;
	for(itr=accounts.begin();itr!=accounts.end();itr++)
	{
		outfile<<itr->second;
	}
	outfile.close();
}

int main()
{
	Bank BB;
	Account acc;
	int choice;
	string fname,lname;
	long acc_num;
	float ammount;
	float balance;
	cout<<"*****************Banking System****************"<<endl;
	do
	{
		cout<<"\n\tSelect one option below ";
		cout<<"\n\t1 Open an Account";
		cout<<"\n\t2 Balance Enquiry";
		cout<<"\n\t3 Deposit";
		cout<<"\n\t4 Withdrawal";
		cout<<"\n\t5 Close an Account";
		cout<<"\n\t6 Show All Accounts";
		cout<<"\n\t7 Quit";
		cout<<"\nEnter your choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Enter first name: ";
				cin>>fname;
				cout<<"Enter last  name: ";
				cin>>lname;
				cout<<"Enter initial balance : ";
				cin>>balance;
				acc=BB.OpenAccount(fname,lname,balance);
				cout<<endl<<"Your account is successfully opened"<<endl;
				cout<<acc;
				break;
			case 2:
				cout<<"Enter account number \n";
				cin>>acc_num;
				acc=BB.BalanceEnquiry(acc_num);
				cout<<endl<<"Your Account details \n";
				cout<<acc;
				break;
			case 3:
				cout<<"Enter account number\n";
				cin>>acc_num;
				cout<<"Enter ammount you want to deposit\n";
				cin>>ammount;
				acc=BB.Deposit(acc_num,ammount);
				cout<<endl<<"Ammount successfully deposited "<<endl;
				cout<<acc;
				break;
			case 4:
				cout<<"Enter account number\n";
				cin>>acc_num;
				cout<<"Enter ammount to be withdrawn\n";
				cin>>ammount;
				acc=BB.Withdrawl(acc_num,ammount);
				cout<<endl<<"Ammount successfully withdrawn "<<endl;
				cout<<acc;
				break;
			case 5:
				cout<<"Enter account number\n";
				cin>>acc_num;
				BB.CloseAccount(acc_num);
				cout<<endl<<"Account closed succesfully\n";
				cout<<acc;
				break;
				
			case 6:
				BB.ShowAllAccount();
				break;
			case 7:
				break;
			default:
				cout<<"Enter correct choice \n";
				exit(0);
		}
	}while(choice!=7);
	return 0;
}
