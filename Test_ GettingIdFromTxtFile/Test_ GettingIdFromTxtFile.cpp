#include "pch.h"
#include "CppUnitTest.h"
#include "../FindBoss_NS_PrIn_367/readXML.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestGettingIdFromTxtFile
{
	TEST_CLASS(TestGettingIdFromTxtFile)
	{
	public:
		
        //Id получено
		TEST_METHOD(IdReceived)
		{
            const char* file_txt = "primer1IdReceived.txt";
            int id = 5;
            int exp_res = GettingIdFromTxtFile(file_txt);
            Assert::AreEqual(5, 5);
		}

        //Файл пустой
        TEST_METHOD(FileIsEmpty)
        {
            const char* file_txt = "primer2FileIsEmpty.txt";
            int exp_res = GettingIdFromTxtFile(file_txt);
            Assert::IsTrue("Invalid input file specified. The file may not exist");
        }

        //В файле некорректные данные
        TEST_METHOD(IncorrectDataInTheFile)
        {
            const char* file_txt = "primer3IncorrectDataInTheFile.txt";
            int exp_res = GettingIdFromTxtFile(file_txt);
            Assert::IsTrue("Invalid input file specified. The file may not exist");

        }
	};
}


/*



//Получение id из txt-файла
int GettingIdFromTxtFile(const char* file_txt)
{
    string id_txt;
    //Получение значения id из txt - файла
    fstream file;
    //открываем файл в режиме чтения
    file.open(file_txt);
    //если открытие файла прошло корректно, то
    try
    {
        if (file)
        {
            //цикл для чтения значений из файла; выполнение цикла прервется,
               // когда достигнем конца файла, в этом случае F.eof() вернет истину.
            while (!file.eof())
            {
                //чтение очередного значения из потока F в переменную a
                file >> id_txt;
                if (isdigit(id_txt))
                {
                    return stoi(id_txt);
                }
                else
                    throw 2;
            }
            //закрытие файла
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
