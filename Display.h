#ifndef DISPLAY_H
#define DISPLAY_H

#include<string>
#include<vector>

#include "Log.h"

using namespace std;

class Display{
    private:
        vector<int> inputData;
        string inputStatus;
        Log myIO;
    public:
        void printData() const;
        void clearData();
        void setData(string, vector<int>);
        string printNames();
        int printOptions();
                
        Display();
        Display(string,vector<int>);
};


#endif