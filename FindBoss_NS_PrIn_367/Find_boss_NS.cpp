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
    
    const char* xml_file = "hierarchy_tree.xml";

    WorkingWithXMLFile(xml_file);
    
   
    return 0;
}







