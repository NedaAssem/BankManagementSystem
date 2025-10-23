#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"clsString.h"
#include"clsPerson.h"

using namespace std;

class clsBankClient:public clsPerson
{

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewClientMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line,string Seperator= "#//#")
	{
		
		vector <string> vClient = clsString::Split(Line, Seperator);
		return clsBankClient (enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3],
			vClient[4], vClient[5], stod(vClient[6]));
		 
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		
		return vClients;
	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string Line = "";
		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.AccountNumber() + Seperator;
		Line += Client.PinCode + Seperator;
		Line += to_string(Client.AccountBalance) ;
		return Line;
	}

	static void _SaveCleintsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open())
		{
			string Line;
			for (clsBankClient C : vClients)
			{
				if(C.MarkedForDeleted()==false)
				{
					Line = _ConverClientObjectToLine(C);
					MyFile << Line << endl;
				}
			}
			MyFile.close();
		}
	}

	void _UpDate()
	{
		vector <clsBankClient> vClient = _LoadClientsDataFromFile();
		for (clsBankClient& C : vClient)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveCleintsDataToFile(vClient);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	string _PreperTransferLogRecord(double Amount,clsBankClient Destination,
		 string Seperator="#//#")
	{
		string TransferLog = "";
		TransferLog += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLog += AccountNumber() + Seperator;
		TransferLog += Destination.AccountNumber() + Seperator;
		TransferLog += to_string(Amount)+Seperator;
		TransferLog +=to_string (AccountBalance) + Seperator;
		TransferLog +=to_string (Destination.AccountBalance) + Seperator;
		TransferLog += CurrentUser.UserName;
		return TransferLog;
	}

	void _RegisterTransferLog(double Amount, clsBankClient DestinationClient)
	{
		string stDataLine = _PreperTransferLogRecord(Amount, DestinationClient);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	struct stTransferLog;
	
	static stTransferLog _ConvertTransferLogLineToRecord(string Line,string Seperator="#//#")
	{
		stTransferLog TransferLog;
		vector <string> vTransferLog = clsString::Split(Line, Seperator);

		TransferLog.DateTime = vTransferLog[0];
		TransferLog.SourceAccountNumber = vTransferLog[1];
		TransferLog.DestinationAccountNumber = vTransferLog[2];
		TransferLog.Amount = stod(vTransferLog[3]);
		TransferLog.SourceBalance = stod(vTransferLog[4]);
		TransferLog.DestinationBalance = stod(vTransferLog[5]);
		TransferLog.UserName = vTransferLog[6];
		return TransferLog;
	}


public:

	struct stTransferLog
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount;
		double SourceBalance;
		double DestinationBalance;
		string UserName;
	};

	clsBankClient(enMode Mode,string FirstName, string LastName, string Email, string Phone ,
		 string AccountNumber, string PinCode, double Balance)
		:clsPerson(FirstName, LastName, Email, Phone )
	{
		 _Mode = Mode;
		 _AccountNumber = AccountNumber;
		 _PinCode = PinCode;
		 _AccountBalance = Balance;
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}


	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		 _PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	
	void SetBalance(float Balance)
	{
	    _AccountBalance = Balance;
	}

	float GetBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetBalance, put = SetBalance)) float AccountBalance;

	 bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	/* No UI related code inside object
	void Print()
	 {
		 cout << "\nClient Card:";
		 cout << "\n___________________";
		 cout << "\nFirstName   : " << FirstName;
		 cout << "\nLastName    : " << LastName;
		 cout << "\nFull Name   : " << FullName();
		 cout << "\nEmail       : " << Email;
		 cout << "\nPhone       : " << Phone;
		 cout << "\nAcc. Number : " << _AccountNumber;
		 cout << "\nPassword    : " << _PinCode;
		 cout << "\nBalance     : " << _AccountBalance;
		 cout << "\n___________________\n";

	 }*/

	 static clsBankClient Find(string AccountNumber)
	 {
		 fstream MyFile;
		 MyFile.open("Clients.txt", ios::in);
		 if (MyFile.is_open())
		 { 
			 string Line;
			 while (getline(MyFile, Line))
			 {
				 clsBankClient Client = _ConvertLineToClientObject(Line);
				 if (Client.AccountNumber() == AccountNumber)
				 {
					 MyFile.close();
					 return Client;
				 }
				
			 }
			 MyFile.close();
		 }
		 return _GetEmptyClientObject();
	 }

	 static clsBankClient Find(string AccountNumber,string PinCode)
	 {
		 fstream MyFile;
		 MyFile.open("Clients.txt", ios::in);
		 if (MyFile.is_open())
		 {
			 string Line;
			 while (getline(MyFile, Line))
			 {
				 clsBankClient Client = _ConvertLineToClientObject(Line);
				 if (Client.AccountNumber() == AccountNumber && Client.PinCode== PinCode)
				 {
					 MyFile.close();
					 return Client;
				 }

			 }
			 MyFile.close();
		 }
		 return _GetEmptyClientObject();
	 }

	 static bool IsClientExist(string AccountNumber)
	 {
		 clsBankClient Client = Find(AccountNumber);
		 return (!Client.IsEmpty());
	 }


	 enum enSaveResults{svFaildEmptyObject=0,svSucceeded=1, svFaildAccountNumberExists=2
	 };

	 enSaveResults Save()
	 {
		 switch (_Mode)
		 {
		 case clsBankClient::EmptyMode:
		 {
			 if(IsEmpty())
			 {
				 return enSaveResults::svFaildEmptyObject;
			 }
		 }
		 case clsBankClient::UpdateMode:
		 {
			 _UpDate();
			 return enSaveResults::svSucceeded;
		 }
		 case clsBankClient::AddNewClientMode:
		 {
			 if (clsBankClient::IsClientExist(_AccountNumber))
			 {
				 return enSaveResults::svFaildAccountNumberExists;
			 }
			 else
			 {
				 _AddNew();
				 _Mode = enMode::UpdateMode;
				 return enSaveResults::svSucceeded;
			 }
		 }
		 }
	 }

	 static clsBankClient GetAddNewClientObject(string AccontNumber)
	 {
		 return clsBankClient(enMode::AddNewClientMode, "", "", "", "", AccontNumber, "", 0);
	 }

	 bool Delete()
	 {
		 vector<clsBankClient> vClients;
		 vClients = _LoadClientsDataFromFile();
		 for (clsBankClient& C : vClients)
		 {
			 if (C.AccountNumber() == _AccountNumber)
			 {
				C._MarkedForDelete = true;
			 }
		 }
		 _SaveCleintsDataToFile(vClients);
		 *this = _GetEmptyClientObject();

		 return true;
		 
	 }

	 static vector<clsBankClient> GetClientsList()
	 {
		 return _LoadClientsDataFromFile();
	 }

	 static double GetTotalBalances()
	 {
		
		 vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		 double TotalBalance = 0;

		 for (clsBankClient C:vClients)
		 {
			 TotalBalance += C.AccountBalance;
		 }
		 return TotalBalance;
	 }

	 void Deposit(double Amount)
	 {
		 _AccountBalance += Amount;
		 Save();
	 }

	 bool Withdraw(double Amount)
	 {
		 if (Amount > _AccountBalance)
		 {
			 return false;
		 }
		 else
		 {
			 _AccountBalance -= Amount;
			 Save();
			 return true;
		 }

	 }

	 bool Transfer(double Amount, clsBankClient& DestinationClient)
	 {
		 if (Amount > AccountBalance)
		 {
			 return false;
		 }
		 else
		 {
			 Withdraw(Amount);
			 DestinationClient.Deposit(Amount);
			 _RegisterTransferLog(Amount, DestinationClient);
			 return true;
		 }
	 }

	 static  vector <stTransferLog> GetTransfersLogList()
	 {
		 vector <stTransferLog> vTransferLogRecord;

		 fstream MyFile;
		 MyFile.open("TransferLog.txt", ios::in);//read Mode

		 if (MyFile.is_open())
		 {

			 string Line;

			 stTransferLog TransferRecord;

			 while (getline(MyFile, Line))
			 {

				 TransferRecord = _ConvertTransferLogLineToRecord(Line);

				 vTransferLogRecord.push_back(TransferRecord);

			 }

			 MyFile.close();

		 }

		 return vTransferLogRecord;

	 }

};

