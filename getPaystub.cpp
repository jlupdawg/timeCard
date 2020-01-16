#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void printDatesMenu(int);
string getUsername();
void getTodaysDate(int&);
void recordHours(string, string, int, int, int, int);
void writeStub(string, vector<vector<int>>);

string usernameFile = "usernames.txt";
string rawTimesheetRoot = "_rawTimes.txt";
string payStubRoot = "_payStub.txt";
int year = 2020;
int day1 = 2;
int day2 = 15;

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
        mm2 = option/2 + 1;
        dd1 = day2+1;
        dd2 = day1-1;
    }
    else{
        mm1 = mm2 = option;
        dd1 = day1;
        dd2 = day2;
    }

    recordHours(rawTimesheet, payStub, mm1, mm2, dd1, dd2);
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
            cout << i+i-1 << ".) " << i << "/" << day1 << "/" << to_string(year) << " - " << i << "/" << day2 << "/" << to_string(year) << endl;
            if((i+1) < 12){
                cout << i+i << ".) " << i << "/" << day2+1 << "/" << to_string(year) << " - " << (i+1) << "/" << day1-1 << "/" << to_string(year) << endl;
            }
            else{
                cout << i+i << ".) " << i << "/" << day2 << "/" << to_string(year) << " - " << 1 << "/" << day1 << "/" << to_string(year+1) << endl;
            }
    }
}

void getTodaysDate(int &mm){
        
    time_t theTime = time(NULL);
    theTime -= 6*60*60;
    struct tm *aTime = localtime(&theTime);
    
    mm = aTime->tm_mon + 1; 
}

void recordHours(string file1, string file2, int mm1, int mm2, int dd1, int dd2){
    string templine;
    string status;
    vector<vector<int>> times; 
    vector<int> tempVec; 
    int hour1, hour2, minute1, minute2;
    int tempMonth, tempDay, temp;
    ifstream inF;
    stringstream SS; 

    inF.open(file1);

    if(!inF.is_open()){
        cout << "File cannot be found!" << endl;
        exit(1);
    }

    while(!inF.eof()){
        do{
            SS.str("");
            getline(inF, templine);
            SS << templine;
            SS >> status >> tempDay >> tempMonth;
            if(status == "OUT"){
                break;
            }
            if(tempMonth < mm1 || tempMonth > mm2){
                continue;
            }
            if(tempMonth == mm1 && tempDay < dd1){
                continue;
            }
            if(tempMonth == mm2 && tempDay > dd2){
                continue;
            }
            SS >> temp >> hour1 >> minute1;
        }while(status != "IN");

        do{
            SS.str("");
            getline(inF, templine);
            SS << templine;
            SS >> status >> tempDay >> tempMonth;
            if(status == "IN"){
                break;
            }
            if(tempMonth < mm1 || tempMonth > mm2){
                continue;
            }
            if(tempMonth == mm1 && tempDay < dd1){
                continue;
            }
            if(tempMonth == mm2 && tempDay > dd2){
                continue;
            }
            SS >> temp >> hour2 >> minute2;

            tempVec.push_back(tempDay);
            tempVec.push_back(tempMonth);
            tempVec.push_back(hour1);
            tempVec.push_back(minute1);
            tempVec.push_back(hour2);
            tempVec.push_back(minute2);
            times.push_back(tempVec);
            tempVec.clear();

        }while(status != "OUT");


        
    }
    inF.close();

    writeStub(file2, times);
}

void writeStub(string file2, vector<vector<int>> times){
    vector<int> tempVec; 
    ofstream oF;
    int totalHours, totalMinutes, total;
    int dailyHours, dailyMinutes, dailyTotal;
    oF.open(file2);

    if(!oF.is_open()){
        cout << "File cannot be opened!" << endl;
        exit(1);
    }

        oF << left << setw(5) << setfill(' ') << "DATE";
        oF << "\t";
        oF << left << setw(13) << setfill(' ') <<  "WORKED";
        oF << "\t";
        oF << left << "TOTAL" << endl;

    total = 0;
    for(int i = 0; i < times.size(); i++){
        tempVec.clear();
        tempVec = times.at(i);

        dailyTotal = tempVec.at(4)*60 + tempVec.at(5) - tempVec.at(2)*60 - tempVec.at(3);
        dailyHours = dailyTotal/60;
        dailyMinutes = dailyTotal%60;

        oF << setprecision(2);
        oF << right << setw(2) << setfill('0') << tempVec.at(0) << "/";
        oF << right << setw(2) << setfill('0') << tempVec.at(1) << "\t";
        oF << right << setw(2) << setfill('0') << tempVec.at(2) << ":";
        oF << right << setw(2) << setfill('0') << tempVec.at(3) << " - ";
        oF << right << setw(2) << setfill('0') << tempVec.at(4) << ":";
        oF << right << setw(2) << setfill('0') << tempVec.at(5) << "\t";
        oF << right << setw(2) << setfill('0') << dailyHours << ":";
        oF << right << setw(2) << setfill('0') << dailyMinutes << endl;

        total += dailyTotal;
    }
        totalHours = total/60;
        totalMinutes = total%60;

        oF << endl << "GRAND TOTAL : ";
        oF << right << setw(2) << setfill('0') << totalHours << ":";
        oF << right << setw(2) << setfill('0') << totalMinutes << endl;

    oF.close();
}