#pragma once

#include"clsCurrency.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

class clsUpdateCurrencyScreen:protected clsScreen
{
private:

	static float _ReadRate()
	{
		float NewRate;
		cout << "\n Enter Now Rate : ";
		NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";

	}


public:

	static void ShowUpdateCurrencyScreen()
	{
		_DrawScreenHeader("Update Currency Screen");

		string CurrencyCode = "";
		cout << "\n Please Enter Currency Code : ";
		CurrencyCode = clsInputValidate::ReadString();

		
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\n Currency is not found , Choose another one : ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		
		_PrintCurrency(Currency);
		char Answer = 'n';
		cout << "\n Are you sure you want to update this Rate : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			
			cout << "\n Update Currency Rate ";
			cout << "\n _____________________";
			Currency.UpdateRate(_ReadRate());
			cout << "\n Currency Rate Updated sccessfully \n";
			_PrintCurrency(Currency);
		}
		
		

	}


};

