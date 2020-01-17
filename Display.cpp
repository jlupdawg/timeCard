#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Display.h"

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
    //TODO add compatability with storage class
    /*
    numUsers = stoClass.GetNumUsers();
    for(int i = 0; i < numUsers; i++){
        cout << i+1 << "." << stoClass.GetUsername(i);
    }

    do{
        cin >> option;
        if(option < 1 || option > numUsers)
            cout << "Option Not Valid. Please Try Again!";
    }while(option < 1 || option > numUsers);

    username = stoClass.getUsername(option);
    */
    return username;
}

int Display::printOptions(){
    int option;
    cout << "What would you like to do?" << endl;
    cout << "1. Clock In" << endl;
    cout << "2. Clock Out" << endl;
    cout << "3. Custom Time" << endl;
    //TODO add storage class sorting in a vector
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
