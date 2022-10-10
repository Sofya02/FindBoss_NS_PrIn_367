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
* 
* return �������� ��� ��������������� ��� id
*/
string MatchingIdAndName(int id_for_name)
{
    for (int i = 0; i < person.size(); i++)
    {
        //���� ������� id ������������ id_����� ��������
        if (person[i].id == id_for_name)
        {
            //���������� �������� ��� ���
            return person[i].Name;
        }
    }
}

/*!
* \������� ������ ����������� �������� ����������*****
* \param [in]
* \param [out]
* \param [in | out]


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
            p.Name = node->GetText();
            p.id = id;
            person.push_back(p);
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
                    //���� id=1, �������������-��� ����� �����, ����.��������, ����� �� ������
                    if (id == 1) { cout << "No solution" << endl; }
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
            }//if (!findid) { cout << "Invalid employee id. Perhaps it doesn't exist." << endl; }
        }
        //����������� �����: ��� ������ �������� ���������� � �������� ���������
        SearchSuperiorsOfTheDesiredEmployee(node->FirstChildElement(), findid);
        if (element == "Department") {
            headers.pop_back();
            habsent.pop_back();
        }
        node = node->NextSiblingElement();//������� � ���������� ��������
    }
    
}

/*��������� id �� txt-�����*/
int GettingIdFromTxtFile(const char* file_txt)
{
    int id_txt;
    //��������� �������� id �� txt - �����
    fstream file;
    //��������� ���� � ������ ������
    file.open(file_txt);
    //���� �������� ����� ������ ���������, ��
    if (file)
    {
       // if (file.tellg() == 0) { cout << "ERROR" << endl; }
        //���� ��� ������ �������� �� �����; ���������� ����� ���������,
           // ����� ��������� ����� �����, � ���� ������ F.eof() ������ ������.
        while (!file.eof())
        {
            //������ ���������� �������� �� ������ F � ���������� a
            file >> id_txt;
            if (isdigit(id_txt) == false)
            { 
                return id_txt;
            }
        }
        //�������� �����
        file.close();
    }
    else
    {
        //����� ��������� �� ������ � ���������� ������ ���������
        cout << "Invalid input file specified. The file may not exist" << endl;
        return 0;
    }
}


/*XML*/
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

