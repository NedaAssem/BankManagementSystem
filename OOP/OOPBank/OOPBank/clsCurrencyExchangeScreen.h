#pragma once

#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsCurrenciesListScreen.h"
#include"clsCurrencyFindScreen.h"
#include"clsUpdateCurrencyScreen.h"
#include"clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen:protected clsScreen
{
    enum enCurrencyExchangeOption {
        eListCurrencies = 1, eFindCurrency = 2,
        eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5
    };
    static short _ReadCurrencyExchangeOption()
    {
        short Choice;
        cout << "Choose whate do you want to do? [1-5]? : ";
        Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrencyExchangeMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Menu...\n";

        system("pause>0");
        ShowCurrencyExchangeScreen();

    }

    static void _ShowListCurrenciesScreen()
    {
        //cout << "\n List Currencies will be here\n ";
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        //cout << "\n Find Currency will be here\n ";
        clsCurrencyFindScreen::ShowCurrencyFindScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "\n Update Rate will be here\n ";
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        //cout << "\n  Currency Calculator will be here\n ";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }


  


    static void _PerfromCurrencyExchangeMenu(enCurrencyExchangeOption Option)
    {
       
        switch (Option)
        {
        case clsCurrencyExchangeScreen::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case clsCurrencyExchangeScreen::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case clsCurrencyExchangeScreen::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case clsCurrencyExchangeScreen::eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case clsCurrencyExchangeScreen::eMainMenu:
        {

        }
        }

    }


public:

	static void ShowCurrencyExchangeScreen()
	{
		system("cls");
        _DrawScreenHeader("\t\tCurrency Exchange");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tCurrency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currencies.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Screen.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrencyExchangeMenu((enCurrencyExchangeOption)_ReadCurrencyExchangeOption());
	}
};

