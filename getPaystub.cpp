#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void printDatesMenu(int);
string getUsername();
void getTodaysDate(int&);
void makePaystub(string, string, int, int, int, int);

string usernameFile = "usernames.txt";
string rawTimesheetRoot = "_rawTimes.txt";
string payStubRoot = "_payStub.txt";
int year = 2020;

int main(){
    int mm;
    getTodaysDate(mm);
    int option;
    string username = getUsername();
    
    string rawTimesheet = username + rawTimesheetRoot;
    string payStub = username + payStubRoot;

    int mm1,dd1;
    int mm2,dd2;

    printDatesMenu(mm);
    do{
        cin >> option;
    }while(option < 0 || option > mm*2);

    if(option%2 == 0){
        mm1 = option/2;
        mm2 = option;
        dd1 = 17;
        dd2 = 1;
    }
    else{
        mm1 = mm2 = option;
        dd1 = 2;
        dd2 = 16;
    }
    makePaystub(rawTimesheet, payStub, mm1, mm2, dd1, dd2);
}

string getUsername(){
    vector<string> inNames;
    string temp;
    int tempInt;
    int namesCount = 0;
    ifstream inF;
    
    inF.open(usernameFile);
    if(!inF.is_open()){
        cout << "File could not be found";
        exit(1);
    }
    while(!inF.eof()){
        getline(inF,temp);
        inNames.push_back(temp);
        namesCount++;
    }
    inF.close();
    
    for(int i = 0; i < namesCount; i++){
        cout << i+1 << ". " << inNames.at(i) << endl; 
    }
    
    do{
        cin >> tempInt;
    }while(tempInt > namesCount || tempInt < 1);
    
    return inNames.at(tempInt-1);
}

void printDatesMenu(int mm){
    cout << "Select Pay Period" << endl ;
    for(int i = 1; i <= mm; i++){
            cout << i+i-1 << ".) " << i << "/2/" << to_string(year) << " - " << i << "/16/" << to_string(year) << endl;
            if((i+1) < 12){
                cout << i+i << ".) " << i << "/17/" << to_string(year) << " - " << (i+1) << "/1/" << to_string(year) << endl;
            }
            else{
                cout << i+i << ".) " << i << "/17/" << to_string(year) << " - " << 1 << "/1/" << to_string(year+1) << endl;
            }
    }
}

void getTodaysDate(int &mm){
        
    time_t theTime = time(NULL);
    theTime -= 6*60*60;
    struct tm *aTime = localtime(&theTime);
    
    mm = aTime->tm_mon + 1; 
}

void makePaystub(string file1, string file2, int mm1, int mm2, int dd1, int dd2){
    string templine;
    string status;

    ifstream inF;
    stringstream SS; 
    inF.open(file1);

    if(!inF.is_open()){
        cout << "File cannot be found!" << endl;
        exit(1);
    }

    while(!inF.eof()){
        do{
        getline(inF, templine);
        SS << templine;
        cout << templine << endl;
        }while(status != "OUT");


    }
    inF.close();
}