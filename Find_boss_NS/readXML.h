#pragma once
#include <iostream> //Для работы с клавиатурой и монитором
#include <fstream> //для работы с файлами 
#include <string> //для работы getline
#include <exception> 
#include <vector>


using namespace std;
using namespace tinyxml2;

struct Person {
    string Name;
    int id;
};

vector <int> headers;
vector <bool> habsent;
vector <Person> person;


//Функция сопоставления id и ФИО
string MatchingIdAndName(int id_for_name)
{
    for (int i = 0; i < person.size(); i++)
    {
        if (person[i].id == id_for_name)
        {
            return person[i].Name;
        }
    }
}


/*!
* \Функция поиска начальников искомого сотрудника*****
* \param [in]
* \param [out]
* \param [in | out]


*/
void SearchSuperiorsOfTheDesiredEmployee(XMLElement* node, int findid)
{
    while (node != NULL) {
        string s = string((char*)node->Value());
        if (s == "Department")
        {
            int id;
            node->QueryIntAttribute("head", &id);
            headers.push_back(id);
            habsent.push_back(true);
        }
        if (s == "Person")
        {
            int id;
            int absent;
            int findAbsent = 1;
            Person p;
            node->QueryIntAttribute("id", &id);
            p.Name = node->GetText();
            p.id = id;
            person.push_back(p);
            node->QueryIntAttribute("absent", &absent);

            if (findAbsent == absent)
            {
                int i = 0;
                while (i < headers.size())
                {
                    if (headers[i] == id)
                    {

                        habsent[i] = false;
                    }
                    i++;
                }
            }
            if (findid == id)
            {
                if (findAbsent == absent)
                {
                    cout << "The person is absent" << endl;
                }
                else
                {
                    if (id == 1) { cout << "No solution" << endl; }
                    ofstream fout; // объект класса ofstream
                    fout.open("output.txt", std::ios::app);
                    for (int i = headers.size() - 2; i >= 0; i--)
                    {
                        if (habsent[i]) { fout << MatchingIdAndName(headers[i]) << endl; }
                    }
                    fout.close();
                }
            }
        }
        SearchSuperiorsOfTheDesiredEmployee(node->FirstChildElement(), findid);
        if (s == "Department") {
            headers.pop_back();
            habsent.pop_back();
        }
        node = node->NextSiblingElement();//Переход к следующему элементу
    }
}

/*Получение id из txt-файла*/
int GettingIdFromTxtFile()
{
    int id_txt;
    //Получение значения id из txt - файла
    fstream file;
    //открываем файл в режиме чтения
    file.open("id.txt");
    //если открытие файла прошло корректно, то
    if (file)
    {
        //цикл для чтения значений из файла; выполнение цикла прервется,
           // когда достигнем конца файла, в этом случае F.eof() вернет истину.
        while (!file.eof())
        {
            //чтение очередного значения из потока F в переменную a
            file >> id_txt;
            return id_txt;
        }
        //закрытие файла
        file.close();
    }
    else
    {
        //Вывод сообщения об ошибке и завершение работы программы
        cout << "read txt error!" << endl;
        return 0;
    }
}

