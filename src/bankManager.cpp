//============================================================================
// Name        : bankManager.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cctype>
#include <iomanip>
#include <fstream>

using namespace std;

class BankAccount{
	int acc_nr;
	char name[50];
	int deposit;
	char type;

public:
	void createAccount();
	void showAccout() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacc_nr() const;
	int retdeposit() const;
	char rettype() const;
};

void BankAccount::createAccount(){
	system("CLS");
	cout<<"\n\t\t\tEnter the Account No. : ";
	cin>>acc_nr;
	cout<<"\n\t\t\tEnter the name of the account holder: ";
	cin.ignore();
	cin.getline(name, 50);
	cout<<"\n\t\t\tEnter Type of the Account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tEnter the initial amount : ";
	cin>>deposit;
	cout<<"\n\t\t\tAccount created!";

}

void BankAccount::showAccout() const
{
	cout<<"\n\t\t\tAccount No. :"<<acc_nr;
	cout<<"\n\t\t\tAccount holder name: ";
	cout<<name;
	cout<<"\n\t\t\tType of account : "<<type;
	cout<<"\n\t\t\tBalance amount: "<<deposit;
}
void BankAccount::modify() {
	cout<<"\n\t\t\tAccount No. :"<<acc_nr;
	cout<<"\n\t\t\tModify Account Holder Name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout<<"\n\t\t\tModify Type of Account: ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tModify Balance Amount: ";
	cin>>deposit;

}

void BankAccount::dep(int x){
	deposit+=x;
}

void BankAccount::draw(int x){
	deposit-=x;
}

void BankAccount::report() const{
	cout<<acc_nr<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int BankAccount::retacc_nr() const{
	return acc_nr;
}
int BankAccount::retdeposit() const{
	return deposit;
}
char BankAccount::rettype() const{
	return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);


int main() {
	char ch;
	int num;
	do
	{
		system("CLS");
		cout<<"\n\n\t\t\t\t==============================\n";
		cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM";
		cout<<"\n\n\t\t\t\t==============================\n";

		cout<<"\t\t\t\t      ::MAIN MENU/n";
		cout<<"\n\t\t\t\t  1. NEW ACCOUNT";
		cout<<"\n\t\t\t\t  2. DEPOSIT AMOUNT";
		cout<<"\n\t\t\t\t  3. WITHDRAW AMOUNT";
		cout<<"\n\t\t\t\t  4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t  5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t\t\t  6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t\t\t  7. MODIFY AN ACCOUNT";
		cout<<"\n\t\t\t\t  8. EXIT";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("CLS");
			cout<<"\n\n\t\t\tEnter the account No. : ";cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout<<"\n\n\t\t\tEnter the account No. : ";cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout<<"\n\n\t\t\tEnter the account No. : ";cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout<<"\n\n\t\t\tEnter the account No. : ";cin>>num;
			delete_account(num);
			break;
		case '7':
			system("CLS");
			cout<<"\n\n\t\t\tEnter the account No. : ";cin>>num;
			delete_account(num);
			break;
		case '8':
			system("CLS");
			break;
		default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');

	return 0;
}

void write_account(){
	BankAccount ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary|ios::app);
	ac.createAccount();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
	outFile.close();
}

void display_sp(int n){
	BankAccount ac;
	bool flag = false;
	ifstream(inFile);
	inFile.open("account.dat", ios::binary);
	if(!inFile){
		cout<<"File could not be open!! Press any key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount))){
		if(ac.retacc_nr()==n)
		{
			ac.showAccout();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}

void modify_account(int n){
	bool found=false;
	BankAccount ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"File could not be open!! Press any key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
		if(ac.retacc_nr()==n)
		{
			ac.showAccout();
			cout<<"\n\n\t\t\tEmter the new detail of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(BankAccount));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord not found!";
}

void delete_account(int n)
{
	BankAccount ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount)))
	{
		if(ac.retacc_nr()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout<<"\n\nRecord Delete ..";
}

void display_all()
{
	system("CLS");
	BankAccount ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"=======================================================\n";
	cout<<"A/c no.       NAME          TYPE BALANCE\n";
	cout<<"=======================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	BankAccount ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
		if(ac.retacc_nr()==n)
		{
			ac.showAccout();
			if(option==1)
			{
				cout<<"\n\n\t\t\tTO DEPOSTI AMOUNT";
				cout<<"\n\n\t\t\tEnter the amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter the amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
			cout<<"\n\n\t\t\tRecord Updated";
			found==true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found";
}
