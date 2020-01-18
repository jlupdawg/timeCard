#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Display.h"
#include "Log.h"

using namespace std;

void Display::printData() const{
    cout << right << setw(6) << setfill(' ') << inputStatus << " ";
    cout << right << setw(2) << setfill('0') << inputData.at(0) << "/";
    cout << right << setw(2) << setfill('0') << inputData.at(1) << "\t";
    cout << right << setw(2) << setfill('0') << inputData.at(2) << ":";
    cout << right << setw(2) << setfill('0') << inputData.at(3) << endl;
}

void Display::clearData(){
    inputStatus = "";
    inputData.clear();
}

void Display::setData(string status, vector<int> data){
    inputStatus = status;
    inputData = data;
}

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

    username = myIO.GetUsername(option);
    
    return username;
}

int Display::printOptions(){
    int option;
    cout << "What would you like to do?" << endl;
    cout << "1. Clock In" << endl;
    cout << "2. Clock Out" << endl;
    cout << "3. Custom Time" << endl;
    cout << "4. Print Paystub" << endl;
    
    do{
        cin >> option;
        if(option < 1 || option > 4)
            cout << "Option Not Valid";
    }while(option < 1 || option > 4);

    return option;
}

Display::Display(){
    inputStatus = "";
    inputData.resize(4);
}

Display::Display(string status, vector<int> data){
    inputStatus = status;
    inputData = data;
}
