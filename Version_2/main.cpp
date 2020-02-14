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

/*
    for(unsigned int i = 1; i <= 24; i++){
        //cout << "LOOP " << i << endl;
        option = i;
        totalHours = totalMinutes = total = 0;
        day1Total = day2Total = hoursTotal = minutesTotal = 0;

        if(option%2 == 0){
            mm1 = option/2;
            mm2 = option/2 + 1;
            dd1 = day2+1;
            dd2 = day1-1;
        }
        else{
            mm1 = mm2 = (option+1)/2;
            dd1 = day1;
            dd2 = day2;
        }
        */