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
    
    vector<int> mins(4); //minMonth, minDay, minHour, minMinute;

    int minPos = 0;
    vector<int> minVec = userData.at(minPos);
    currentVec = userData.at(minPos);

    bool case1, case1b, case2, case2b, case3, case3b, case4;

    for(unsigned int i = 1; i < currentVec.size(); i++){
        mins.at(i-1) = currentVec.at(i);
    }

    for(unsigned int i = 0; i < userData.size(); i++){
        for(unsigned int j = i; j < userData.size(); j++){
            currentVec = userData.at(j);
            case1 = (currentVec.at(1) < mins.at(0));
            case1b = (currentVec.at(1) == mins.at(0));
            case2 = (currentVec.at(2) < mins.at(1));
            case2b = (currentVec.at(2) == mins.at(1));
            case3 = (currentVec.at(3) < mins.at(2));
            case3b = (currentVec.at(3) == mins.at(2));
            case4 = (currentVec.at(4) < mins.at(3));

            if(case1 || (case1b&&case2) || (case1b&&case2b&&case3) || (case1b&&case2b&&case3b&&case4)){
                swapVec = userData.at(i);
                userData.at(i) = currentVec;
                currentVec = swapVec;
                for(unsigned int i = 1; i < currentVec.size(); i++){
                    mins.at(i-1) = currentVec.at(i);
                }
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
            oF << temp.at(i) << " ";
        }
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
        SS << templine;
        tempVec.clear();
        for(unsigned int i = 0; i < 5; i++){
            SS >> tempInt;
            tempVec.push_back(tempInt);
        }
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
    //sortUserData(); //TODO FIX THIS!!!
    //overrideData();
    //userData.clear();
    //getUserData();
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
    oF << endl << 1 << " " << month << " " << day << " " << hour << " " << minute << endl;
    oF.close();
    refreshUserData();
}

void Log::clockOut(){
    ofstream oF;
    getDateTime();
    oF.open(rawDataFile, ofstream::app);
    oF << endl << 0 << " " << month << " " << day << " " << hour << " " << minute << endl;
    oF.close();
    refreshUserData();
}

void Log::customInOut(int status , int month, int day, int hour, int minute){
    ofstream oF;
    oF.open(rawDataFile, ofstream::app);
    oF << endl << status << " " << month << " " << day << " " << hour << " " << minute << endl;
    oF.close();
    refreshUserData();
}

void Log::printPaystub(int option){
    int mm1, mm2, dd1, dd2;
    int day1 = 2, day2 = 15;
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
        mm1 = mm2 = option;
        dd1 = day1;
        dd2 = day2;
    }

    //Delete all data not in range
    for(unsigned int i = 0; i < userData.size();){
        tempVec = userData.at(i); 
        if(tempVec.at(0) < mm1 || tempVec.at(0) > mm2){
            userData.erase(userData.begin() + i);
        }
        else if(tempVec.at(0) == mm1 && tempVec.at(1) < dd1){
            userData.erase(userData.begin() + i);
        }
        else if(tempVec.at(0) == mm2 && tempVec.at(1) > dd2){
            userData.erase(userData.begin() + i);
        }
        else{
            i++;
        }
    }

    oF.open(paystubFile);
    if(!oF.is_open()){
        exit(1);
    }

    oF << left << setw(5) << setfill(' ') << "DATE";
    oF << "\t";
    oF << left << setw(13) << setfill(' ') <<  "WORKED";
    oF << "\t";
    oF << left << "TOTAL" << endl;


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
        oF << right << setw(2) << setfill('0') << tempVec.at(4) << endl;

        hoursTotal = (day2Total - day1Total)/60;
        minutesTotal = (day2Total - day1Total)%60;
        total += day2Total - day1Total;

        p++;
    }

    totalHours = total/60;
    totalMinutes = total%60;

    oF << endl << endl;
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