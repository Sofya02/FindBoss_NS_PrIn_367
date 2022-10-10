#include "pch.h"
#include "CppUnitTest.h"
#include "../FindBoss_NS_PrIn_367/readXML.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestGettingIdFromTxtFile
{
	TEST_CLASS(TestGettingIdFromTxtFile)
	{
	public:
		
        //Id ��������
		TEST_METHOD(IdReceived)
		{
            const char* file_txt = "primer1IdReceived.txt";
            int id = 5;
            int exp_res = GettingIdFromTxtFile(file_txt);
            Assert::AreEqual(5, 5);
		}

        //���� ������
        TEST_METHOD(FileIsEmpty)
        {
            const char* file_txt = "primer2FileIsEmpty.txt";
            int exp_res = GettingIdFromTxtFile(file_txt);
            Assert::IsTrue("Invalid input file specified. The file may not exist");
        }

        //� ����� ������������ ������
        TEST_METHOD(IncorrectDataInTheFile)
        {
            const char* file_txt = "primer3IncorrectDataInTheFile.txt";
            int exp_res = GettingIdFromTxtFile(file_txt);
            Assert::IsTrue("Invalid input file specified. The file may not exist");

        }
	};
}


/*



//��������� id �� txt-�����
int GettingIdFromTxtFile(const char* file_txt)
{
    string id_txt;
    //��������� �������� id �� txt - �����
    fstream file;
    //��������� ���� � ������ ������
    file.open(file_txt);
    //���� �������� ����� ������ ���������, ��
    try
    {
        if (file)
        {
            //���� ��� ������ �������� �� �����; ���������� ����� ���������,
               // ����� ��������� ����� �����, � ���� ������ F.eof() ������ ������.
            while (!file.eof())
            {
                //������ ���������� �������� �� ������ F � ���������� a
                file >> id_txt;
                if (isdigit(id_txt))
                {
                    return stoi(id_txt);
                }
                else
                    throw 2;
            }
            //�������� �����
            file.close();
        }
        else
        {
            throw 1;
        }
    }
    catch (int e)
    {
        if (e == 1) { cout << "Invalid input file specified. The file may not exist" << endl; }
        if (e == 2) { cout << "Data entered incorrectly. The input string contains a set of different characters" << endl; }

    }
}






*/
