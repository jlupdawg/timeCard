#include<string>

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
    int month, day, status, hour, minute;

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
        data.checkTimes(allGood, status, month, day);
        if(!allGood){
            terminal.printReminder(status, month, day);
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
                terminal.customInOut(status, month, day, hour, minute);
                data.customInOut(status, month, day, hour, minute);
                terminal.customString("Time Added Successfully!");
                break;
            case 4:
                option = terminal.printPayPeriods();
                data.printPaystub(option);
                terminal.customString(("You Can Find Your Paystub In " + paystubFile));
                break;

            case 5:
                tempPath = terminal.GetPath();
                data.printAllPaystubs(tempPath);
                terminal.customString(("You Can Find Your Paystub In " + tempPath + paystubFile));
                break;

            case 6: 
                terminal.customString("Thank you for using this program!");
                terminal.customString("Goodbye!");
                exit(0);
                break;
        }
    }
    return 0;
}

//TODO ADD CUSTOM PAY PERIOD ... NEEDS DATE PULL AND PICK DATE RANGE BASED ON DATE, PRINT TO FILE LOCATION USING PWD IN BASH
