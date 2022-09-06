#include <iostream>
#include <vector>
#include <fstream>
#include<sstream>
#include "Table.cpp"
using namespace std;


class Pass1
{
    private:
    Table *OPT, *AT, *ST, *IT, *LT;
    public:
    Pass1(string MOTPath, string ATPath, string STPath)
    {
        OPT=new Table(4);
        OPT->readFromTxt(MOTPath);

        AT=new Table(4);
        AT->readFromTxt(ATPath);

        IT=new Table(4);

        LT=new Table(2);
        

    }


    string getICOPCode(string key)
    {
        vector<string> row = OPT->getRowByColumnSearch(0,key);
        string opcode = row[1]+row[2];
        return opcode;
    }


    void run()
    {
        int lc=stoi(AT->getItemByCoordinate(0,2));
        
        
        // line 1 of the intermediate table
        vector<string> startRow;
        int lc=stoi(AT->getItemByCoordinate(0,2));
        if(AT->getItemByCoordinate(0,1)=="START")
        {
            startRow=AT->getRowByIndex(0);
            startRow.push_back("$");
            startRow.push_back(getICOPCode(AT->getItemByCoordinate(0,1)));
            string op2="C"+AT->getItemByCoordinate(0,2);
            startRow.push_back(op2);
            startRow.push_back("$");
        }
        else
        {
            cout<<"error in line 1";
            return;
        }





        for(int i=0;i<AT->length();i++)
        {
            vector<string> labelRow;
            vector<string> row=AT->getRowByIndex(i);


            //label handeling
            if(AT->getItemByCoordinate(i,0)!="$")
            {
                labelRow.push_back(AT->getItemByCoordinate(i,0));
                labelRow.push_back(to_string(lc));
                LT->append(labelRow);

            }

            //adding location counter
            row.push_back(to_string(lc));

            //adding opcodes for commands
            row.push_back(getICOPCode(AT->getItemByCoordinate(i,1)));
            
            //handling operand 1
            
            
        }
    }


};
