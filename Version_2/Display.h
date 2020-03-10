#ifndef DISPLAY_H
#define DISPLAY_H

#include<string>
#include<vector>

#include "Log.h"

using namespace std;

class Display{
    private:
        Log myIO;
    public:
        string printNames();
        int printOptions();
        void SetLog(Log);
        void printReminder(int, int, int, int&, int&);
        void customInOut(int&, int&, int&, int&, int&, int&);
        int printPayPeriods();
        void customString(string);
        string GetPath();
        void GetStartDur(int&, int&);
};


#endif