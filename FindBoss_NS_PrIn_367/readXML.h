#pragma once
#include <iostream> //��� ������ � ����������� � ���������
#include <fstream> //��� ������ � ������� 
#include <string> //��� ������ getline
#include <exception> 
#include <vector>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

struct Person {
    string Name;//��� ����������
    int id;//id ����������
};

vector <int> headers;
vector <bool> habsent;
vector <Person> person;


/*!������� ������������� id � ���
*
* \param[in] id-����������(�������)
* return �������� ��� ��������������� ��� id
*/
string MatchingIdAndName(int id_for_name)
{
    try {
        for (int i = 0; i < person.size(); i++)
        {
            //���� ������� id ������������ id_����� ��������
            if (person[i].id == id_for_name)
            {
                //���������� �������� ��� ���
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

//���������� ����������� � ����
void SavingResultsToAFile()
{
    ofstream fout; // ������ ������ ofstream
    fout.open("output.txt", std::ios::app);
    for (int i = headers.size() - 2; i >= 0; i--)
    {
        //���� ��������� ������������ �� ������� �����, ���������� ��� � �������� ����
        if (habsent[i])
        {
            //���������� ���������� � �������� ����
            fout << MatchingIdAndName(headers[i]) << endl;
        }
    }
    //�������� �����
    fout.close();

}

/*!
* \������� ������ ����������� �������� ����������*****
*
* \param [in] node - ��������� �� ������� � XML-�����
* \param [in] findid - id ����������
*/
void SearchSuperiorsOfTheDesiredEmployee(XMLElement* node, int findid)
{
    //���� �� ����� ���������(���� ��������)???????????????????
    while (node != NULL)
    {
        string element = string((char*)node->Value());//�������������� char � string?????????????
        //���� �������� �������� ���� "Department"
        if (element == "Department")
        {
            int id;
            node->QueryIntAttribute("head", &id);//��������� �������� "head" � "Department"(��������� ������)
            headers.push_back(id);//���������� id
            habsent.push_back(true);//������������� ����������
        }
        //���� �������� �������� ���� "Person"
        if (element == "Person")
        {
            int id;
            int absent;
            int findAbsent = 1;
            Person p;
            node->QueryIntAttribute("id", &id);//��������� �������� "id"
            p.Name = node->GetText();//���������� ��������
            p.id = id;
            person.push_back(p);//���������� ����������
            node->QueryIntAttribute("absent", &absent);//��������� �������� "absent"
            //���� �������� ���������� ��� �� ������� �����, ������� � ���������� ����������
            if (findAbsent == absent)
            {
                int i = 0;
                while (i < headers.size())
                {
                    //���� ����������� id ���������
                    if (headers[i] == id)
                    {
                        //���������� �������� false 
                        habsent[i] = false;
                    }
                    //������������� ������� ���������� � ������� � ����������
                    i++;
                }
            }
            //���� ����������� id �� txt-����� �������
            if (findid == id)
            {
                //���� ��������� �����������
                if (findAbsent == absent)
                {
                    //����� ��������� �� ������
                    cout << "The person is absent" << endl;
                }
                //�����
                else
                {
                    //���� id=1, �������������-��� ����� �����, 
                    if (id == 1) { cout << "No solution"; }
                    SavingResultsToAFile();//���������� ����������� � ����
                }
            }
        }
        //����������� �����: ��� ������ �������� ���������� � �������� ���������
        SearchSuperiorsOfTheDesiredEmployee(node->FirstChildElement(), findid);
        if (element == "Department") {
            headers.pop_back();//��������
            habsent.pop_back();
        }
        node = node->NextSiblingElement();//������� � ���������� ��������
    }
}

//�������� ������ �� txt-�����
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

/*��������� id �� txt-�����*/
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
        if (e == 1) {cout << "Invalid input file specified. The file may not exist" << endl;}
        if (e == 2) { cout << "Data entered incorrectly. The input string contains a set of different characters" << endl; }

    }
}


/*������ � xml ������*/
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

