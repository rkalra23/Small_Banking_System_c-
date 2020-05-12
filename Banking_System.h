#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
#include<iomanip>
using namespace std;

#define MIN_BALANCE 500
class Account
{
	private:
		long Acc_Num;                                         //
		string FirstName;
		string LastName;
		float balance;
		static long NextAcc_Num;
	public:
		Account(){}
		Account(string name,string lastname,float balance);
		long get_Acc_num(){return Acc_Num;}
		string get_first_name(){return FirstName;}
		string get_last_name(){return LastName;}
		float  get_balance(){return balance;}
		void Deposit(float amount);
		void Withdraw(float amount);
		static void setLastAccountNumber(long accountNumber);
		static long getLastAccountNumber();
		friend ofstream & operator<<(ofstream &ofs,Account &acc);
		friend ifstream & operator>>(ifstream &ifs,Account &acc);
		friend ostream & operator<<(ostream &os,Account &acc);
};
long Account::NextAcc_Num=0;

class Bank
{
	private:
		map<long,Account> accounts;
	public:
		Bank();
		Account OpenAccount(string fname,string lname,float balance);
		Account BalanceEnquiry(long acc_num);
		Account Deposit(long acc_num,float ammount);
		Account Withdrawl(long acc_num,float ammount);
		void CloseAccount(long acc_num);
		void ShowAllAccount();
		~Bank();
};

