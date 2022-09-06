#include <iostream>
#include <vector>
#include <fstream>
// #include<bits/stdc++.h>
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
    void run()
    {
        for(int i=0;i<AT->length();i++)
        {
            
        }
    }


};
