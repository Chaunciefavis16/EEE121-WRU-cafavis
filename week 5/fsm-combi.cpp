#include <iostream>
#include <vector>
#include <string>
using namespace std;

void genStateCombi(vector<string> &stateList, int numStates, string stateTrans)
{
    
    int spaces = 0;
    for (int i = 0; i < stateTrans.length(); i++)
    {
        if (stateTrans[i] == ' ')
        {
            spaces = spaces + 1;
        }
    }

    if (spaces == 4)
    { 
        cout << stateTrans << endl;
    }
    else
    { 
        for (int i = 0; i < numStates; i++)
        {
            string newTrans = stateTrans + stateList[i] + " ";
            genStateCombi(stateList, stateList.size(), newTrans);
        }
    }
}

void printAllStates(vector<string> &stateList)
{
    genStateCombi(stateList, stateList.size(), "");
}

int main()
{
    vector<string> stateList;
    stateList = {"RESET", "IDLE", "ACTIVE", "DONE"};
    printAllStates(stateList);
    return 0;
}
