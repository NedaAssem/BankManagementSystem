#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsCurrency.h"

class clsCurrencyFindScreen:protected clsScreen
{
private:

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

	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\n Currenty Found :-) \n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\n Currenty Not Found :-( \n";
		}

	}
	

public:

	static void ShowCurrencyFindScreen()
	{
		_DrawScreenHeader("Find Currency Screen");
		
		cout << "\nFind By: [1] Code or [2] Country ? ";
		short Answer = 1;

		cin >> Answer;

		if (Answer == 1)
		{
			string Code;
			cout << "\n Please Enter Currency Code : ";
			Code = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCode(Code);

			_ShowResult(Currency);

		}
		else
		{
			string Country;
			cout << "\n Please Enter Country : ";
			Country = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}

	}

};

