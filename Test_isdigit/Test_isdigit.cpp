#include "pch.h"
#include "CppUnitTest.h"
#include "../FindBoss_NS_PrIn_367/readXML.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testisdigit
{
	TEST_CLASS(Testisdigit)
	{
	public:
		
		//Полученное значение является числом
		TEST_METHOD(TheResultingValueIsANumber)
		{
			string sym = "7";
			bool res = true;
			bool exp_res = isdigit(sym);
			Assert::AreEqual(res, exp_res);
		}

		//Полученное значение является буквой
		TEST_METHOD(TheResultingValueIsALetter)
		{
			string sym = "q";
			bool res = false;
			bool exp_res = isdigit(sym);
			Assert::AreEqual(res, exp_res);
		}

		//Полученное значение является набором символов
		TEST_METHOD(TheResultingValueIsACharacterSet)
		{
			string sym = "U@U(*@U(#*";
			bool res = false;
			bool exp_res = isdigit(sym);
			Assert::AreEqual(res, exp_res);
		}

	};
}


/*

bool isdigit(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] < 48) || (s[i] > 57))
		{
			return false;
		}
	}
	return true;

}


*/
