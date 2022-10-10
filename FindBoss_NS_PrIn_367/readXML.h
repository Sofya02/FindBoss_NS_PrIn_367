#pragma once
#include <iostream> //Для работы с клавиатурой и монитором
#include <fstream> //для работы с файлами 
#include <string> //для работы getline
#include <exception> 
#include <vector>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

struct Person {
    string Name;//ФИО сотрудника
    int id;//id сотрудника
};

vector <int> headers;
vector <bool> habsent;
vector <Person> person;


/*!Функция сопоставления id и ФИО
*
* \param[in] id-сотрудника(текущее)
* return значение ФИО соответствующее его id
*/
string MatchingIdAndName(int id_for_name)
{
    try {
        for (int i = 0; i < person.size(); i++)
        {
            //Если текущее id соответсвует id_имени человека
            if (person[i].id == id_for_name)
            {
                //возвращаем значение его ФИО
                return person[i].Name;
            }
        }
        throw 1;
    }
    catch (int e)
    {
        if (e == 1) { cout << "Invalid employee id. Perhaps it doesn't exist."; }
    }
}

//Сохранение результатов в файл
void SavingResultsToAFile()
{
    ofstream fout; // объект класса ofstream
    fout.open("output.txt", std::ios::app);
    for (int i = headers.size() - 2; i >= 0; i--)
    {
        //Если сотрудник присутствует на рабочем месте, записываем его в выходной файл
        if (habsent[i])
        {
            //Записываем сотрудника в выходной файл
            fout << MatchingIdAndName(headers[i]) << endl;
        }
    }
    //Закрытие файла
    fout.close();

}

/*!
* \Функция поиска начальников искомого сотрудника*****
*
* \param [in] node - указатель на элемент в XML-файле
* \param [in] findid - id сотрудника
*/
void SearchSuperiorsOfTheDesiredEmployee(XMLElement* node, int findid)
{
    //Пока не конец документа(есть элементы)???????????????????
    while (node != NULL)
    {
        string element = string((char*)node->Value());//преобразование char в string?????????????
        //Если название элемента есть "Department"
        if (element == "Department")
        {
            int id;
            node->QueryIntAttribute("head", &id);//Получение значения "head" у "Department"(начальник отдела)
            headers.push_back(id);//добавление id
            habsent.push_back(true);//подтверждение добавления
        }
        //Если название элемента есть "Person"
        if (element == "Person")
        {
            int id;
            int absent;
            int findAbsent = 1;
            Person p;
            node->QueryIntAttribute("id", &id);//получение значения "id"
            p.Name = node->GetText();//присвоение значений
            p.id = id;
            person.push_back(p);//добавление сотрудника
            node->QueryIntAttribute("absent", &absent);//получение значение "absent"
            //Если текущего сотрудника нет на рабочем месте, переход к следующему сотруднику
            if (findAbsent == absent)
            {
                int i = 0;
                while (i < headers.size())
                {
                    //Если соответсвие id произошло
                    if (headers[i] == id)
                    {
                        //присвоение значения false 
                        habsent[i] = false;
                    }
                    //Игнорирование данного сотрудника и переход к следующему
                    i++;
                }
            }
            //Если соответсвие id из txt-файла найдено
            if (findid == id)
            {
                //Если сотрудник отсутствует
                if (findAbsent == absent)
                {
                    //Вывод сообщения об ошибке
                    cout << "The person is absent" << endl;
                }
                //Иначе
                else
                {
                    //Если id=1, следовательно-это глава фирмы, 
                    if (id == 1) { cout << "No solution"; }
                    SavingResultsToAFile();//Сохранение результатов в файл
                }
            }
        }
        //Рекурсивный вызов: для поиска искомого сотрудника в дочерних элементах
        SearchSuperiorsOfTheDesiredEmployee(node->FirstChildElement(), findid);
        if (element == "Department") {
            headers.pop_back();//удаление
            habsent.pop_back();
        }
        node = node->NextSiblingElement();//Переход к следующему элементу
    }
}

//проверка данных из txt-файла
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

/*Получение id из txt-файла*/
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
        if (e == 1) {cout << "Invalid input file specified. The file may not exist" << endl;}
        if (e == 2) { cout << "Data entered incorrectly. The input string contains a set of different characters" << endl; }

    }
}


/*Работа с xml файлом*/
int WorkingWithXMLFile(const char* file_xml)
{
    XMLDocument doc;
    doc.LoadFile("hierarchy_tree.xml");
    if (doc.ErrorID() != 0) {
        cout << "Invalid input file specified. The file may not exist" << endl;
        return false;
    }
    const char* txt_file = "id.txt";
    int id_from_txt = GettingIdFromTxtFile(txt_file);
    XMLElement* node = doc.FirstChildElement()->FirstChildElement("Department");
    SearchSuperiorsOfTheDesiredEmployee(node, id_from_txt);
}

