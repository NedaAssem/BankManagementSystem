#pragma once
#include"clsScreen.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"clsString.h"
#include<iomanip>
#include"clsUser.h"
using namespace std;

class clsLoginRegisterListScreen:public clsScreen
{
	static void _PrintLoginRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(12) << left << LoginRegisterRecord.DateTime;
		cout << "| " << setw(25) << left << LoginRegisterRecord.UserName;
		cout << "| " << setw(12) << left << LoginRegisterRecord.Password;
		cout << "| " << setw(20) << left << LoginRegisterRecord.Permissions;

	}

public:

	static void ShowLoginRegisterList()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegisterList))
		{
			return ;
		}
		vector <clsUser::stLoginRegisterRecord> vLines = clsUser::GetLoginRegisterList();

		string Title = "Login Register List Screen";
		string SubTitle = to_string(vLines.size()) + " Record(s)";

		_DrawScreenHeader(Title,SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(12) <<"Date/Time";
		cout << "| " << left << setw(25) << "UserName";
		
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		
		for(clsUser::stLoginRegisterRecord Record:vLines)
		{
				_PrintLoginRecordLine(Record);
				cout << endl;
		}


	}
};

