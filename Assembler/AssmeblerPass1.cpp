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

    bool isValidOpCode(string OP)
    {
        bool flag=false;
        for(int i=0;i<table.size();i++)
        {
            if(table[i][0]==OP)
            {
                flag=true;
                break;
            }
        }
        return flag;

    }

    vector<string> getOpCodeVector(string OP)
    {
        if(isValidOpCode(OP)==true)
        {
            for(int i=0;i<table.size();i++)
            {
            if(table[i][0]==OP)
                {
                return table[i];
                }
            }
        }
        else
        {
            throw invalid_argument("the string entered is not is not in the given OPCODE table");
        }
        
        
        
        
    }

    void printTable()
    {
        for(int i=0;i<table.size();i++)
        {
            cout<<table[i][0]<<"  "<<table[i][1]<<"  "<<table[i][2]<<"\n";
        }
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
    
    bool isValidRegister(string R)
    {
        bool flag=false;
        for(int i=0;i<table.size();i++)
        {
            if(table[i][0]==R)
            {
                flag=true;
                break;
            }
        }
        return flag;

    }

    vector<string> getRegisterVector(string R)
    {
        if(isValidRegister(R)==true)
        {
            for(int i=0;i<table.size();i++)
            {
            if(table[i][0]==R)
                {
                return table[i];
                }
            }
        }
        else
        {
            throw invalid_argument("the string entered is not is not in the given Register table");
        }
        
        
    }
};

class SymbolTable
{
    private:
    vector<pair<string,int>> table;
    public:
    void append(string s, int i)
    {
        pair<string, int> temp;
        temp.first=s;
        temp.second=i;
        table.push_back(temp);
    }
    bool isSymbolValid(string s)
    {
        bool flag=false;
        for (int i=0;i<table.size();i++)
        {
            if(s==table[i].first)
            {
                flag=true;
                break;
            }
        }
        return flag;
    }
    vector<string> getSymbolVector(string s)
    {
        vector<string> t1;
        pair<string, int> temp;
        if(isSymbolValid(s)==true)
        {
            stringstream ss;
            for (int i=0;i<table.size();i++)
            {
                if(s==table[i].first)
                {
                    temp=table[i];
                    break;
                }
            }
            string loc;
            ss<<temp.second;
            ss>>loc;
            t1.push_back(temp.first);
            t1.push_back(loc);
            return t1;
        }
        else
        {
            throw invalid_argument("the string entered is not is not in the symbol table");
        }


        

    }
};

class Pass1
{
    private:

    OpCodeTable *ot;
    RegisterTable *rt;
    public:
    Pass1(string path1, string path2)
    {
        ot=new OpCodeTable(path1);
        rt=new RegisterTable(path2);
    }
    
    

};


int main()
{
    OpCodeTable ot("Optable.txt");
    ot.printTable();
    cout<<"RUNIING";
    return 0;
}
