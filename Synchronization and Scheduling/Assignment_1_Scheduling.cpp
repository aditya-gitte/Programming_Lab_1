#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Process
{
    public:
    int AT,BT,CT,TAT,WT;
    Process(int AT,int BT)
    {
        this->AT=AT;
        this->BT=BT;
        CT=0;
        TAT=0;
        WT=0;
    }
};



// bool comaprator(Process p1, Process p2)
// {
//     return p1.AT<p2.AT;
// }


bool comparor(Process p1, Process p2)
{
   return p1.AT<p2.AT;
}

class Scheduler
{
    int clock,totalTurnAroundTime,waitTime;
    vector<Process> pr;
    public:
    Scheduler(vector<Process> v)
    {
        pr=v;
        clock=0;
        totalTurnAroundTime=0;
        waitTime=0;
    }
    void printFcfsStats()
    {
        clock=0;
        sort(pr.begin(),pr.end(),[](Process p1, Process p2) -> bool{return p1.AT<p2.AT;} );
        
//        sort(pr.begin(),pr.end(),[](Process p1, Process p2) -> bool{return p1.AT<p2.AT;} );
//        for(int i=0;i<pr.size();i++)
//        {
//            cout<<pr[i].AT<<"\n";
//        }
        cout<<"Process ID  ArrivalTime  BurstTime  CompletionTime  TurnAroundTime  WaitTime\n";
        for(int i=0;i<pr.size();i++)
        {
            if(clock>=pr[i].AT)
            {
                pr[i].CT=pr[i].BT+clock;
                clock=pr[i].BT+clock;
                
            }
            else
            {
                pr[i].CT=pr[i].BT+pr[i].AT;
                clock=pr[i].BT+pr[i].AT;
                
            }
            pr[i].TAT=pr[i].CT-pr[i].AT;
            pr[i].WT=pr[i].TAT-pr[i].BT;
            totalTurnAroundTime+=pr[i].TAT;
            waitTime+=pr[i].WT;
            cout<<i<<"  "<<pr[i].AT<<"  "<<pr[i].BT<<"  "<<pr[i].CT<<"  "<<pr[i].TAT<<"  "<<pr[i].WT<<"\n";
        }
        cout<<"Avg Turn around time = "<<totalTurnAroundTime/pr.size()<<endl;
        cout<<"Avg Wait time = "<<waitTime/pr.size()<<endl;
        

    }

};

vector<Process> processCreator()
{
    cout<<"Enter the number of processes\n";
    vector<Process> pr;
    int nop;
    cin>>nop;
    for(int a=0;a<nop;a++)
    {
        cout<<"Enter the arrival time of procees "<<(a+1)<<"\n";
        int AT;
        cin>>AT;
        cout<<"Enter the burst time of procees "<<(a+1)<<"\n";
        int BT;
        cin>>BT;
        Process p(AT,BT);
        pr.push_back(p);
    }
    return pr;
}

int main()
{
    vector<Process> v;
    Scheduler obj(processCreator());
    
    obj.printFcfsStats();
    
}

