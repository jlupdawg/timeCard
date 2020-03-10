#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Display.h"
#include "Log.h"

using namespace std;

string Display::printNames(){
    string username = "";   
    int numUsers;
    int option;
    cout << "Select your name" << endl;
    
    numUsers = myIO.GetNumUsers();
    for(int i = 0; i < numUsers; i++){
        cout << i+1 << "." << myIO.GetUsername(i) << endl;
    }

    do{
        cin >> option;
        if(option < 1 || option > numUsers)
            cout << "Option Not Valid. Please Try Again!";
    }while(option < 1 || option > numUsers);

    username = myIO.GetUsername(option-1);
    
    return username;
}

int Display::printOptions(){
    int option;
    cout << "What would you like to do?" << endl;
    cout << "1. Clock In" << endl;
    cout << "2. Clock Out" << endl;
    cout << "3. Print All Paystubs" << endl;
    cout << "4. Exit the program" << endl;
    
    do{
        cin >> option;
        if(option < 1 || option > 4)
            cout << "Option Not Valid";
    }while(option < 1 || option > 4);

    return option;
}

void Display::SetLog(Log IO){
    myIO = IO;
}

void Display::printReminder(int status, int month, int day, int& hours, int& minutes){
    if(status == 1){
        cout << "You forgot to clock out on " << month << "/" << day << "." << endl;
        cout << "How many hours and minutes did you work? (seperate by a space)" << endl;
        cin >> hours >> minutes;
    }
    else if(status == 0){
        cout << "You forgot to clock in on " << month << "/" << day << "." << endl;
        cout << "How many hours and minutes did you work? (seperate by a space)" << endl;
        cin >> hours >> minutes;
    }
}

void Display::customInOut(int& status, int& month, int& day, int& year, int& hour, int& minute){
    cout << endl << "Would you like to: " << endl;
    cout << "1. Clock In" << endl;
    cout << "2. Clock Out" << endl;

    do{
        cin >> status;
        if(status < 1 || status > 2){
            cout << "Invalid Option. Please try again." << endl;
        }
    }while(status < 1 || status > 2);
    if(status == 2){
        status = 0;
    }

    cout << "Please enter the month, day, year, hour, and minute seperated by spaces.";
    do{
        cin >> month >> day >> hour >> minute;
        if(month < 0 || month > 12){
            cout << "Invalid Month. Please Try Again." << endl;
            continue;
        }
        if(day < 0 || day > 31){
            cout << "Invalid Day. Please Try Again." << endl;
            continue;
        }
        if(hour < 0 || hour > 24){
            cout << "Invalid Hour. Please Try Again." << endl;
            continue;
        }
        if(minute < 0 || minute > 60){
            cout << "Invalid Minute. Please Try Again." << endl;
        }
    }while((month < 0 || month > 12) || (day < 0 || day > 31) || (hour < 0 || hour > 24) || (minute < 0 || minute > 60));

}

void Display::customString(string message){
    cout << message << endl;
}

string Display::GetPath(){
    string tempPath;
    cout << "Please enter the path: " << endl;
    cin >> tempPath;
    return tempPath;
}

void Display::GetStartDur(int& startTime, int& payPeriodLen){
    cout << "Please enter the start time and duration of the pay periods seprated by a space: " << endl;
    cin >> startTime >> payPeriodLen;
}
