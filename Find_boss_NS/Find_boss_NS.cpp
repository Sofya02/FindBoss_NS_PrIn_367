#define _CRT_SECURE_NO_WARNINGS
#include <iostream> //Для работы с клавиатурой и монитором
#include <fstream> //для работы с файлами 
#include <string> //для работы getline
#include <exception> 
#include "tinyxml2.h"
#include <vector>
#include "readXML.h"

using namespace std;
using namespace tinyxml2;


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    
    XMLDocument doc;
    doc.LoadFile("hierarchy_tree.xml");
    if (doc.ErrorID() != 0) {
        cout << "read xml error!" << endl;
        return false;
    }

    int id_from_txt = GettingIdFromTxtFile();
    XMLElement* node = doc.FirstChildElement()->FirstChildElement("Department");
    SearchSuperiorsOfTheDesiredEmployee(node, id_from_txt);
   
    return 0;
}







