#include <iostream>
#include <vector>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;

class OpCodeTable
{
    vector<vector<string>> table;
    public:
    OpCodeTable(string path)
    {
        ifstream opf(path);
        string ltext;
        while(getline(opf,ltext))
        {
            vector<string> temp;
            istringstream ss(ltext);
            string word;
            while(ss>>word)
            {
                temp.push_back(word);
            }
            table.push_back(temp);
        }

    }

    vector<string> getOpCodeVector(string OP)
    {
        for(int i=0;i<table.size();i++)
        {
            if(table[i][0]==OP)
            {
                return table[i];
            }
        }
        throw invalid_argument("the string entered is not is not in the given OPCODE table");
        
    }
};


class RegisterTable
{
    vector<vector<string>> table;
    public:
    RegisterTable(string path)
    {
        ifstream rtf(path);
        string ltext;
        while(getline(rtf,ltext))
        {
            vector<string> temp;
            istringstream ss(ltext);
            string word;
            while(ss>>word)
            {
                temp.push_back(word);
            }
            table.push_back(temp);
        }

    }

    vector<string> getRegisterVector(string R)
    {
        for(int i=0;i<table.size();i++)
        {
            if(table[i][0]==R)
            {
                return table[i];
            }
        }
        throw invalid_argument("the string entered is not is not in the given Register table");
        
    }
};

