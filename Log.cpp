#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "log.h"

#include <iostream> //REMOVE 

using namespace std;
       
void Log::sortUserData(){
    vector<int> currentVec;
    vector<int> swapVec;

    vector<int> minVec = userData.at(0);

    bool case1, case1b, case2, case2b, case3, case3b, case4;

    for(unsigned int i = 0; i < userData.size(); i++){
        for(unsigned int j = i+1; j < userData.size()-1; j++){
            currentVec = userData.at(j);
            minVec = userData.at(i);
            case1 = (currentVec.at(1) < minVec.at(1));
            case1b = (currentVec.at(1) == minVec.at(1));
            case2 = (currentVec.at(2) < minVec.at(2));
            case2b = (currentVec.at(2) == minVec.at(2));
            case3 = (currentVec.at(3) < minVec.at(3));
            case3b = (currentVec.at(3) == minVec.at(3));
            case4 = (currentVec.at(4) < minVec.at(4));
            //cout << "ENTRY: " << i << "," << j << " " << case1 << case1b << case2 <<case2b << case3 << case3b << case4 << endl;

            if(case1 || (case1b&&case2) || (case1b&&case2b&&case3) || (case1b&&case2b&&case3b&&case4)){
                //cout << "CALLED MINS CASE" << endl;
                swapVec = userData.at(i);
                userData.at(i) = userData.at(j);
                userData.at(j) = swapVec;
            }
        }
    }
}

void Log::getDateTime(){ 
    time_t theTime = time(NULL);
    //theTime -= 6*60*60;
    struct tm *aTime = localtime(&theTime);
    
    day = aTime->tm_mday;
    month = aTime->tm_mon + 1; 
 
    hour = aTime->tm_hour;
    minute = aTime->tm_min;
}

void Log::getDate(){
    time_t theTime = time(NULL);
    //theTime -= 6*60*60;
    struct tm *aTime = localtime(&theTime);
    
    day = aTime->tm_mday;
    month = aTime->tm_mon + 1; 

}

void Log::overrideData(){
    ofstream oF;
    vector<int> temp;
    oF.open(rawDataFile);
    if(!oF.is_open()){
        exit(1);
    }
    for(unsigned int i = 0; i < userData.size(); i++){
        temp = userData.at(i);
        for(unsigned int j = 0; j < temp.size(); j++){
            oF << temp.at(j) << " ";
            //cout << "WRITING " << temp.at(j);
        }
        //cout << endl;
        oF << endl;
    }

    oF.close();
}

void Log::getUserData(){
    ifstream inF;
    stringstream SS;
    string templine;
    vector<int> tempVec;
    int tempInt;
    inF.open(rawDataFile);
    if(!inF.is_open()){
        exit(1);
    }
    while(!inF.eof()){
        getline(inF, templine);
        if(templine == ""){
            continue;
        }
        SS.clear();
        SS << templine;
        //cout << "TEMPLINE: " << templine << endl;
        tempVec.clear();
        for(unsigned int i = 0; i < 5; i++){
            SS >> tempInt;
            tempVec.push_back(tempInt);
            //cout << tempInt << " ";
        }
        //cout << endl;
        userData.push_back(tempVec);
    }
    inF.close();
}

void Log::pullUsernames(){
    ifstream inF;
    string templine;
    inF.open(usernameFile);
    if(!inF.is_open()){
        exit(1);
    }

    while(!inF.eof()){
        getline(inF, templine);
        if(templine == ""){
            continue;
        }
        usernameVec.push_back(templine);
    }
    inF.close();
}

void Log::refreshUserData(){
    userData.clear();
    getUserData();
    sortUserData();
    overrideData();
    userData.clear();
    getUserData();
}

int Log::GetNumUsers() const{
    return usernameVec.size();
}

string Log::GetUsername(int i) const{
    return usernameVec.at(i);
}

void Log::SetUserFile(string usernameFile){
    this->usernameFile = usernameFile;
    pullUsernames();
}

void Log::SetRawDataFile(string rawDataFile){
    this->rawDataFile = rawDataFile;
}

void Log::SetPaystubFile(string paystubFile){
    this->paystubFile = paystubFile;
}

void Log::clockIn(){
    ofstream oF;
    getDateTime();
    oF.open(rawDataFile, ofstream::app);
    oF << endl << 1 << " " << month << " " << day << " " << hour << " " << minute;
    oF.close();
    refreshUserData();
}

void Log::clockOut(){
    ofstream oF;
    getDateTime();
    oF.open(rawDataFile, ofstream::app);
    oF << endl << 0 << " " << month << " " << day << " " << hour << " " << minute;
    oF.close();
    refreshUserData();
}

void Log::customInOut(int status , int month, int day, int hour, int minute){
    ofstream oF;
    oF.open(rawDataFile, ofstream::app);
    oF << endl << status << " " << month << " " << day << " " << hour << " " << minute;
    oF.close();
    refreshUserData();
}

void Log::printPaystub(int option){
    int mm1, mm2, dd1, dd2;
    int day1 = 2, day2 = 15; //Also change in Display.cpp
    vector<int> tempVec;

    ofstream oF;
    int totalHours, totalMinutes, total;
    int day1Total, day2Total, hoursTotal, minutesTotal;

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
    refreshUserData();
    //Delete all data not in range
    //cout << "USERDATA SIZE: " << userData.size() << endl;
    for(unsigned int i = 0; i < userData.size(); i++){
        tempVec = userData.at(i); 
        if(tempVec.at(1) < mm1 || tempVec.at(1) > mm2){
            userData.erase(userData.begin() + i);
            //cout << "ERASED 1" << endl;
        }
        else if(tempVec.at(1) == mm1 && tempVec.at(2) < dd1){
            userData.erase(userData.begin() + i);
            //cout << "ERASED 2" << endl;
        }
        else if(tempVec.at(1) == mm2 && tempVec.at(2) > dd2){
            userData.erase(userData.begin() + i);
            //cout << "ERASED 3" << endl;
        }
    }

    //cout << "USERDATA SIZE: " << userData.size() << endl;

    oF.open(paystubFile);
    if(!oF.is_open()){
        exit(1);
    }

    oF << "PAYSTUB FOR ";
    oF << setw(2) << setfill('0') << mm1 << "/";
    oF << setw(2) << setfill('0') << dd1 << " - ";
    oF << setw(2) << setfill('0') << mm2 << "/";
    oF << setw(2) << setfill('0') << dd2 << endl;



    unsigned int p = 0;
    while(p < userData.size()){
        tempVec = userData.at(p);
        day1Total = 1440*tempVec.at(2) + 60*tempVec.at(3) + tempVec.at(4);
        oF << right << setw(2) << setfill('0') << tempVec.at(2) << "/";
        oF << right << setw(2) << setfill('0') << tempVec.at(1) << "\t";
        oF << right << setw(2) << setfill('0') << tempVec.at(3) << ":";
        oF << right << setw(2) << setfill('0') << tempVec.at(4) << " - ";

        p++;

        tempVec = userData.at(p);
        day2Total = 1440*tempVec.at(2) + 60*tempVec.at(3) + tempVec.at(4);
        oF << right << setw(2) << setfill('0') << tempVec.at(2) << "/";
        oF << right << setw(2) << setfill('0') << tempVec.at(1) << "\t";
        oF << right << setw(2) << setfill('0') << tempVec.at(3) << ":";
        oF << right << setw(2) << setfill('0') << tempVec.at(4) << " -- ";

        hoursTotal = (day2Total - day1Total)/60;
        minutesTotal = (day2Total - day1Total)%60;

        oF << right << setw(2) << setfill('0') << hoursTotal << ":";
        oF << right << setw(2) << setfill('0') << minutesTotal << endl;

        total += day2Total - day1Total;

        p++;
    }

    totalHours = total/60;
    totalMinutes = total%60;

    oF << endl;
    oF << endl << "GRAND TOTAL : ";
    oF << right << setw(2) << setfill('0') << totalHours << ":";
    oF << right << setw(2) << setfill('0') << totalMinutes << endl;
    oF.close();
}

void Log::checkTimes(bool& allGood, int& inOut, int& month, int& day){
    int status, lastStatus = 0;
    vector<int> tempVec;
    allGood = true;
    for(unsigned int i = 0; i < userData.size(); i++){
        tempVec = userData.at(i);
        status = tempVec.at(0);
        if(status == lastStatus){
            allGood = false;
            inOut = status;
            month = tempVec.at(1);
            day = tempVec.at(2);
            break;
        }
        lastStatus = status;
    }
    
}