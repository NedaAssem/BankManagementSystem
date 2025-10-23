#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

#include"clsString.h"


using namespace std;


class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLinetoCurrencyObject(string DataLine ,string Seperator="#//#")
	{
		vector<string> vData = clsString::Split(DataLine, Seperator);
		return (clsCurrency(enMode::UpdateMode, vData[0], vData[1], vData[2], stod(vData[3])));
	}

   static vector <clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector <clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}
		return vCurrencies;
	}

   static string _ConverCurrencyObjectToDataLine(clsCurrency Currency,string Seperator="#//#")
   {
	   string DataLine = "";
	   DataLine += Currency.Country() + Seperator;
	   DataLine += Currency.CurrencyCode() + Seperator;
	   DataLine += Currency.CurrencyName() + Seperator;
	   DataLine += to_string(Currency.Rate()) ;
	   return DataLine;
   }

   static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencies)
   {
	   fstream MyFile;
	   MyFile.open("Currencies.txt", ios::out);//overwrite 

	   string DataLine;

	   if (MyFile.is_open())
	   {

		   for (clsCurrency C : vCurrencies)
		   {
				   DataLine = _ConverCurrencyObjectToDataLine(C);
				   MyFile << DataLine << endl;
		   }

		   MyFile.close();

	   }

   }

	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrencyDataFromFile();
		for (clsCurrency &C : vCurrencies)
		{
			if (C.Country() == _Country)
			{
				C = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return (clsCurrency(enMode::EmptyMode, "", "", "", 0));
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencyDataFromFile();
	}

	bool IsEmpty()
	{
		return(_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	float Rate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}

	static   clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();

	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());

	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

    float ConvertToUSD(float CurrencyAmount)
	{
		 return (float)(CurrencyAmount / Rate());
	}

	float ConvertToOtherCurrency(float Amount,clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}
		
		return (AmountInUSD * Currency2.Rate());
	}


};

