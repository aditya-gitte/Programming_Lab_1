#include <iostream>
#include <vector>
#include <fstream>
// #include<bits/stdc++.h>
#include<sstream>
using namespace std;





class Table
{

private:
    int columnSize;
    vector<vector<string> > table;

public:
    vector<string> rowStringSpliter(string rowString)
    {
        rowString+=" ";
        string word="";
        vector<string> row;
        for( int i=0;i<rowString.length();i++)
        {
            if(rowString[i]==' ')
            {
                if(word=="")
                {
                    word="$";
                }    
                row.push_back(word);
                word="";
            }
            else
            {
                word+=rowString[i];
            }
        }
        while(row.size()<columnSize)
        {
            row.push_back("$");
        }
        return row;
    }

    Table(int columnSize)
    {
        this->columnSize=columnSize;
    }

    void readFromTxt(string path)
    {
        ifstream file(path);
        string rowStr;
        while(getline(file,rowStr))
        {
            vector<string> row=rowStringSpliter(rowStr);
            table.push_back(row);
        }
        
    }

    vector<string> getRowByColumn(int columnNumber, string key)
    {
        
        for(int i=0;i<table.size();i++)
        {
            if(table[i][columnNumber-1]==key)
            {
                return table[i];
            }
        }
        throw invalid_argument("the string entered is not is not in the table");
    }

    void append(vector<string> row)
    {
       while(row.size()<columnSize)
       {
            row.push_back("$");
       }
       table.push_back(row);
    }

    void writeToTxt(string path)
    {
        ofstream file;
        file.open(path);
        for (int i=0;i<table.size();i++)
        {
            for (int j=0;j<table[i].size();j++)
            {
                file<< table[i][j]<<" ";
            }
            file<<"\n";
        }

    }

    void printTableToConsole()
    {
        for (int i=0;i<table.size();i++)
        {
            for (int j=0;j<table[i].size();j++)
            {
                cout<< table[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

    int length()
    {
        return table.size();
    }

    string getItemByCoordinate(int x, int y)
    {
        return table[x][y];
    }
};

// testing 
// int main()
// {
//     Table AT(4);
//     AT.readFromTxt("/Users/aditya_gitte/Projects/Programming Lab 1/Programming Lab 1/Assembler/Assembly.txt");
//     // AT.printTableToConsole();
//     // vector<string> temp=AT.getRowByColumn(2,"MOVER");
//     // for(int i=0;i<temp.size();i++)
//     // {
//     //     cout<<temp[i]<<" ";
//     // }
//     AT.writeToTxt("/Users/aditya_gitte/Projects/Programming Lab 1/Programming Lab 1/Assembler/IntermediateTable.txt");
//     return 0;

    

// }