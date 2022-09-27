#include <iostream>
#include <vector>
#include <fstream>
#include<sstream>
#include <unordered_set>
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

    vector<string> getRowByColumnSearch(int columnNumber, string key)
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

    vector<string> getRowByIndex(int index)
    {
        return table[index];
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

class Macro
{
    string inputPath;
    Table *MNT,*KPDTAB,*MDT;
    public:
    Macro(string inputFilePath)
    {
        inputPath=inputFilePath;
        MNT=new Table(4);
        KPDTAB=new Table(2);
        MDT=new Table(2);
    }
    
    void parameterPopulator(vector<string> parameterList)
    {

    }
    
    void rowSplitter(string row)//this adds the name of the macro to MNT and creates a parameter vecotr
    {
        
        vector<string> tableEntryRow;
        
        vector<string> parameterList;
        string name="";
        int i=0;
        while(row[i]!=' ')  
        {
            name+=row[i];
            i++;
        }
        tableEntryRow.push_back(name);
        MNT->append(tableEntryRow);
        
        for(;i<row.length();i++)
        {
            string parameter="";
            if(row[i]=='&')
            {
                int j=i+1;
                while(row[j]!=','||j!=(row.length())-1)
                {
                    parameter+=row[j];
                }
            }
            parameterList.push_back(parameter);
        }
        
    }




    void run()
    {
        vector<string> rowVector; //vector containing all lines of the code
        ifstream file(inputPath);
        string row;
        int macroCounter=0;
        while(getline(file,row)) // row is a single line that keeps incrementing
        {

            rowVector.push_back(row);
        }
        for(int i=0;i<rowVector.size();i++)
        {
            if(rowVector[i]=="MACRO")
            {
               
            } 
        }

    }

};
int main()
{

}