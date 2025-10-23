#pragma once

#include<iostream>
#include<vector>
#include<iomanip>
#include"clsScreen.h"
#include"clsCurrency.h"

using namespace std;

class clsCurrenciesListScreen:protected clsScreen
{
private:

	static void _PrintCurrentyRecordLine(clsCurrency Currency)
	{

		cout << setw(8) << left << "" << "| " << setw(25) << left << Currency.Country();
		cout << "| " << setw(15) << left << Currency.CurrencyCode();
		cout << "| " << setw(25) << left << Currency.CurrencyName();
		cout << "| " << setw(15) << left << Currency.Rate();
		

	}

public: 

	static void ShowCurrenciesListScreen()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Title = "Currencies list Screen";
		string SubTitle = "(" + to_string(vCurrencies.size()) + ") Records";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Country";
		cout << "| " << left << setw(15) << "Currency Code";
		cout << "| " << left << setw(25) << "Currency Name";
		cout << "| " << left << setw(15) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		if (vCurrencies.size() == 0)
		{
			cout << "\t\t\t\t No Correncies Available in the syetem \n";
		}
		
		for (clsCurrency C : vCurrencies)
		{
			_PrintCurrentyRecordLine(C);
			cout << endl;
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;


	}



};

