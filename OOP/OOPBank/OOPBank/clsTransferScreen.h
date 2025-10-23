#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
#include"clsLoginScreen.h"

using namespace std;

class clsTransferScreen:public clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

	static string _ReadAcountNumber()
	{
		string AccountNumber1 = "";
		cout << "\n Please Enter Account Number to Transfer From : ";
		AccountNumber1 = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber1))
		{
			cout << "\n  Account Number is Not Found ,Please Enter another one : ";
			AccountNumber1 = clsInputValidate::ReadString();
		}
		return AccountNumber1;
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{
		double Amount = 0;
		cout << "\n Please Enter Transfer Amount : ";
		Amount = clsInputValidate::ReadDblNumber();
		while (Amount > SourceClient.AccountBalance)
		{
			cout << "Amount Exceeds the available balance,Enter another amount : ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}


public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAcountNumber());
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAcountNumber());
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Answer = 'n';
		cout << "\nAre you sure you want to perform this operation : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient))
			{
				cout << "\n Transfer done seccessfully \n";

				
			}
			else
			{
				cout << "\n Transfer Faild \n";

			}
	
		}
		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
		




	}



};

