#include "pch.h"
#include "CppUnitTest.h"
#include "../FindBoss_NS_PrIn_367/readXML.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestGettingIdFromTxtFile
{
	TEST_CLASS(TestGettingIdFromTxtFile)
	{
	public:
		
        //���������� id �������
		TEST_METHOD(IdMatchFound)
		{
            int id = 5;
            string name = "������� ���� ��������������";
            string exp_Name = MatchingIdAndName(id);

		}

        //���������� �� �������
        TEST_METHOD(InvalidId)
        {
            int id = 55;
            string exp_Name = MatchingIdAndName(id);
            Assert::IsTrue("Invalid employee id. Perhaps it doesn't exist.");
        }
	};
}

