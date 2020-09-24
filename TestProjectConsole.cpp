// TestProjectConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cctype>
#include<iomanip>
#include <string>
#include<sstream>
#include <stdio.h>
using namespace std;

class account
{
	
	int accountNum;
	char name[50];
	int deposit;
	char accountType;
	
public:
	void create_acct();
	void print_account();
	void mod();
	void dep(int);
	void withdraw(int);
	void report_table() const;
	int return_accountNum() const;
	int return_deposit() const;
	char return_acctType() const;		
};



void account::create_acct()
{
	printf("\nEnter account number: ");
	cin>>accountNum;
	printf("\n\nEnter the account holder's name: ");
	cin.ignore();
	cin.getline(name, 50);
	printf("\nEnter account type: ");
	cin>>accountType;
	accountType = toupper(accountType);
	printf("\nEnter initial deposit amount: ");
	cin>> deposit;
	printf("\nAccount has been created");		
}

void account::print_account() 
{
	printf("\nAccount number: %d", accountNum);
	printf("\nPrimary account holder: %s", name);
	printf("\nAccount type: %c", accountType);
	printf("\nAccount balance: %d", deposit);
}

void account::mod()
{
	printf("\nAccount number: %d", accountNum);
	printf("\nChange account holder's name: ");
	cin.ignore();
	cin.getline(name, 50);
	printf("\nChange account type: ");
	cin >> accountType;
	accountType = toupper(accountType);
	printf("\nChange balance: ");
	cin>> deposit;
}

void account::dep(int x)
{
	deposit += x;
}

void account::withdraw(int x)
{
	deposit -= x;
}

void account::report_table() const
{
	printf("%d %s %c %d \n",accountNum,name, accountType, deposit);
}
int account::return_accountNum() const
{
	return accountNum;
}
int account::return_deposit() const
{
	return deposit;
}
char account::return_acctType() const
{
	return accountType;
}

void save_account();
void disp_sp(int);
void mod_account(int);
void delete_account(int);
void show_account();
void deposit_withdraw(int, int);
void home();




int main()
{
	
	char ch;
	int num;
	home();
	do
	{
		system("cls");
		printf("\n\n\nMain Menu");
		printf("\n\n\t1. New Account");
		printf("\n\n\t2. Deposit Amount");
		printf("\n\n\t3. Withdrawal Amount");
		printf("\n\n\t4. Balance");
		printf("\n\n\t5. Account Holder's List");
		printf("\n\n\t6. Close Account");
		printf("\n\n\t7. Change Account Details");
		printf("\n\n\t8 Exit");
		printf("\n\n\tSelect menu option (1-8) ");
		cin>> ch;
		system("cls");
		switch(ch)
		{
		case '1':
			save_account();
			break;
		case '2':
			printf("\n\n\tEnter the account number: ");
			cin>> num;
			deposit_withdraw(num, 2);
			break;
		case '3':
			printf("\n\n\tEnter the account number:");
			cin>> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			printf("\n\n\tEnter the account number:");
			cin>> num;
			disp_sp(num);
			break;
		case '5':
			show_account();
			break;
		case '6' :
			printf("\n\n\tEnter account number:");
			cin>>num;
			delete_account(num);
			break;
		case '7':
			printf("\n\n\tEnter account number:");
			cin>> num;
			break;
		case '8':
			printf("\n\n\tExiting banking system");
			break;
		default:printf("\a");
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}
void save_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_acct();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}

void disp_sp(int n)
{
	account ac;
	bool flag =false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		printf("File not found....press any key");
		return;
	}
	printf("\nBalance Details\n");

	while(inFile.read(reinterpret_cast<char *>(&ac),sizeof(account)))
	{
		if(ac.return_accountNum()==n)
		{
			ac.print_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		printf("\n\nAccount number does not exist");
}
void mod_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if(!File)
	{
		printf("Could not open file....press any key to continue");
		return;
	}while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if(ac.return_accountNum()==n)
		{
			ac.print_account();
			printf("\n\nEnter the new account details");
			ac.mod();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			printf("\n\n\tAccount Updated");
			found = true;
			
		}
	}
	File.close();
	if (found == false)
		printf("\n\nAccount not found");
}
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		printf("Could not open file....any key to escape");
	    return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if(ac.return_accountNum()!=n)
		{
			outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	_Must_inspect_result_("Temp.dat", "account.dat");
	printf("\n\n\tAccount deleted");
		
}
void show_account()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		printf("File could not be opened....any key to escape");
		return;
	}
	printf("\n\n\t\tList of Account Holders\n\n");
	printf("==============================================================\n");
	printf("Account Number      NAME       Account type  Balance\n");
	printf("==============================================================\n");
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report_table();
	}
	inFile.close();
}
void deposit_withdraw(int n, int option)
{
	int amount;
	string mystr;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if(!File)
	{
		printf("File not found....escape any key");
		return;
	}while(!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if(ac.return_accountNum()==n)
		{
			ac.print_account();
			if(option==1)
			{
				printf("\n\n\tAmount to deposit ");
				printf("\n\nEnter the amount deposited");
				getline(cin, mystr);
				stringstream(mystr) << amount;
				ac.dep(amount);
			}
			if(option==2)
			{
				printf("\n\n\tAmount to withdraw ");
				printf("Enter the amount to withdraw");
				getline(cin, mystr);
				stringstream(mystr) << amount;
				int bal = ac.return_deposit() - amount;
				if ((bal < 500 && ac.return_acctType() == 'S') || (bal < 1000 && ac.return_acctType() == 'C'))
					printf("Insufficient balance");
				else
					ac.withdraw(amount);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			printf("\n\n\t Account Updated");
			found = true;
		}
	}
	File.close();
	if (found == false)
		printf("\n\n Account not found");
}
void home()
{
	printf("Account \n\n\tManagement \n\n\tSystem \n\n\tVersion 1.0.0 \n\n\tTyrell Corporation Olympia Washington\n\n\tPress any key to enter....");
	cin.get();
}





	class Mortgage
	{
	private:
		int Amount, Term, monthlyTerm;
		double Interest, Payment, InterestPaid, setInterest;
	public:
		void GetAmount();
		void termRate();
		void getrateTerm();
		void amoritzation();
		void Payments();
	};

	void Mortgage::GetAmount()
	{
		system("cls");
		printf("Tyrell Financial Services Mortgage Calculator\n");
		printf("===============================================\n\n");
		printf("Enter Loan Amount: ");
		cin >> Amount;
	}


	void Mortgage::getrateTerm()
	{
		printf("\nEnter Term Length (Years): ");
		cin >> Term;
		printf("\nEnter Interest Rate: ");
		cin >> Interest;
	}
	void Mortgage::termRate()
	{
		int check = 0;
		int choice = 0;
		int arr;
		int termYr[3] = { 7,15,30 };
		double interestYr[3] = { 5.25,5.5,5.75 };

		do
		{
			printf("\n--------Loan Menu--------");
			printf("\n1. 7 years at 5.25 \n2. 15 years at 5.5 \n3. 30 years at 5.75");
			printf("\n-------------------------");
			cin >> choice;
			check = 0;
			if (choice <= 0)
			{
				system("cls");
				printf("Tyrell Financial Services Mortgage Calculator\n");
				printf("===============================================\n\n");
				printf("Enter Loan Amount: ");
				printf("\n\nEnter only 1,2,3 to choose term and rate\n");
				check = 1;
			}
			else if (choice == 1)
				arr = 0;
			else if (choice == 2)
				arr = 1;
			else if (choice == 3)
				arr = 2;
			else if (choice > 3)
			{
				system("cls");
				printf("Tyrell Financial Services Mortgage Calculator\n");
				printf("===============================================\n\n");
				printf("Enter Loan Amount: ");
				printf("\n\nEnter only 1,2,3 to choose term and rate\n");
				check = 1;
			}

		} while (check == 1);
		Term = termYr[arr];
	}
	void Mortgage::Payments()
	{
		system("cls");
		Payment = Amount * (((Interest / 100.0) / 12) / (1 - pow(1 + ((Interest / 100.0) / 12), -Term * 12)));
		monthlyTerm = (Term * 12);
		InterestPaid = ((Interest / 100.0) / 12);
	}
	void Mortgage::amoritzation()
	{
		int Month = 1;
		int listPause = 5;
		double NewBal;
		NewBal = Amount;

		printf("\n----------------------------------------------");
		printf("\nWith a loan of $%d for %d years\n at a rate of %lf \nyour monthly payment will be $%lf", Amount, Term, Interest, Payment);
		printf("\n----------------------------------------------");
		while (monthlyTerm > 0)
		{
			double Interestp = InterestPaid * NewBal;
			double endBal = (NewBal - NewBal);

			if (NewBal > Payment)
			{
				cout.setf(ios::fixed);
				printf("\n%d\t $ %lf \t\t $ %lf", Month, Interestp, NewBal - Payment + Interestp);


				if (listPause < 19)
				{
					++listPause;
				}
				else
				{
					printf("\n");
					system("PAUSE");
					listPause = 0;
					system("cls");
					printf("Payment \tInterest Paid \tNew Balance\n");
				}
			}
			else if (NewBal <= Payment)
			{
				cout.setf(ios::fixed);
				printf("\n %d \t $ %lf \t\t $%lf", Month, Interestp, endBal);
				listPause = 0;
			}
			NewBal = NewBal - Payment + Interestp;
			Month = ++Month;
			monthlyTerm = --monthlyTerm;
		}

	}

