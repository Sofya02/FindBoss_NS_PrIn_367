#include "pch.h"
#include "CppUnitTest.h"
#include "../FindBoss_NS_PrIn_367/readXML.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestWorkingWithXMLFile
{
	TEST_CLASS(TestWorkingWithXMLFile)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const char* file_xml = "";
            bool res = true;
            bool exp_res = WorkingWithXMLFile(file_xml);
            Assert::AreEqual(res, exp_res);
		}
	};
}


/*

bool WorkingWithXMLFile(const char* file_xml)
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
    return true;
}

*/