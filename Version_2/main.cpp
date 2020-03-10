#include<string>
#include<iostream>

#include "Display.h"
#include "Log.h"

using namespace std;

int main(){
    string usernameFile = "usernames.txt";
    string rawTimesheetRoot = "_rawTimes.txt";
    string paystubRoot = "_payStub.txt";

    string username;
    string tempPath;
    int option;

    bool allGood;
    int month, day, status, time;
    int durHours, durMin;
    int start, duration;

    Display terminal;
    Log data;

    data.SetUserFile(usernameFile);
    terminal.SetLog(data);
    username = terminal.printNames();

    string rawTimeSheetFile = username + rawTimesheetRoot;
    string paystubFile = username + paystubRoot;

    data.SetRawDataFile(rawTimeSheetFile);
    data.SetPaystubFile(paystubFile);

    while(1){
        terminal.SetLog(data);
        data.checkTimes(allGood, status, month, day, time);
        cout << "ALL GOOD " << allGood << endl;
        cout << "TODO -- FIX CHECK";
        exit(1);
        while(!allGood){
            terminal.printReminder(status, month, day, durHours, durMin);

            if(status == 0){
                data.customInOut(0, time - (durHours*3600 + durMin*60));
            }
            else
            {
                data.customInOut(1, time + (durHours*3600 + durMin*60));
            }
            
            data.checkTimes(allGood, status, month, day, time);
        }
        option = terminal.printOptions();
        switch (option){
            case 1:
                data.clockIn();
                terminal.customString("You've Clocked In!");
                break;
            case 2:
                data.clockOut();
                terminal.customString("You've Clocked Out!");
                break;
            case 3:
                tempPath = terminal.GetPath();
                terminal.GetStartDur(start, duration);
                data.printAllPaystubs(tempPath, start, duration);
                terminal.customString(("You Can Find Your Paystub In " + tempPath + paystubFile));
                break;
            case 4: 
                terminal.customString("Thank you for using this program!");
                terminal.customString("Goodbye!");
                exit(0);
                break;
        }
    }
    return 0;
}
