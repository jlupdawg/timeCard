#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "log.h"
#include "Display.h"

#include <iostream> //REMOVE 

using namespace std;
       
void Log::sortUserData(){
    vector<int> currentVec;
    vector<int> swapVec;
    vector<int> minVec;;

    for(unsigned int i = 0; i < userData.size(); i++){
        for(unsigned int j = i+1; j < userData.size()-1; j++){
            currentVec = userData.at(j);
            minVec = userData.at(i);
            if(currentVec.at(1) < minVec.at(1)){
                //cout << "CALLED MINS CASE" << endl;
                swapVec = userData.at(i);
                userData.at(i) = userData.at(j);
                userData.at(j) = swapVec;
            }
        }
    }
}

void Log::getDateTime(){ 
    timeStamp = time(NULL);
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
        for(unsigned int i = 0; i < 2; i++){
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
    oF << endl << 1 << " " << timeStamp;
    oF.close();
    refreshUserData();
}

void Log::clockOut(){
    ofstream oF;
    getDateTime();
    oF.open(rawDataFile, ofstream::app);
    oF << endl << 0 << " " << timeStamp;
    oF.close();
    refreshUserData();
}

void Log::customInOut(int status, int time){
    vector<int> temp;
    temp.push_back(status);
    temp.push_back(time);

    userData.push_back(temp);
    overrideData();
    refreshUserData();
}

void Log::printAllPaystubs(string path, int start, int duration){
    vector<int> tempVec;
    ofstream oF;

    int totalHours, totalMinutes, total;
    totalHours = totalMinutes = total = 0;

    int day1Total, day2Total, hoursTotal, minutesTotal;
    int thisStart;
    int thisEnd;

    string tempPath = (path+paystubFile);

    oF.open(tempPath);
    if(!oF.is_open()){
        //cout << "FILE NOT OPENED" << endl;
        exit(1);
    }

    int i = start;
    while(i < start + 31536000){
        refreshUserData();
        //Delete all data not in range
        //cout << "USERDATA SIZE: " << userData.size() << endl;
        thisStart = i;
        thisEnd = thisStart + duration;
        for(unsigned int j = 0; j < userData.size();){
            tempVec = userData.at(j); 
            if(tempVec.at(1) < thisStart || tempVec.at(1) > thisEnd){
                userData.erase(userData.begin() + j);
                //cout << "ERASED 1" << endl;
            }
            else{
                j++;
            }
        }

        //cout << "USERDATA SIZE: " << userData.size() << endl;

        if(userData.size() > 0){
            totalHours = totalMinutes = total = 0;
            int mm1, mm2, dd1, dd2;

            GetDate(i, mm1, dd1);
            GetDate(i+duration, mm2, dd2);

            oF << setw(40) << setfill('-') << "-" << endl;
            oF << "PAYSTUB FOR ";
            oF << setw(2) << setfill('0') << mm1 << "/";
            oF << setw(2) << setfill('0') << dd1 << " - ";
            oF << setw(2) << setfill('0') << mm2 << "/";
            oF << setw(2) << setfill('0') << dd2 << endl;



            unsigned int p = 0;
            int thisHour, thisMin, thisDay, thisMonth;
            while(p < userData.size()){

                tempVec = userData.at(p);
                day1Total = tempVec.at(1);
                GetFullDT(day1Total, thisHour, thisMin, thisDay, thisMonth);
                oF << right << setw(2) << setfill('0') << thisMonth << "/";
                oF << right << setw(2) << setfill('0') << thisDay << "\t";
                oF << right << setw(2) << setfill('0') << thisHour << ":";
                oF << right << setw(2) << setfill('0') << thisMin << " - ";

                p++;

                tempVec = userData.at(p);
                day2Total = tempVec.at(1);
                GetFullDT(day2Total, thisHour, thisMin, thisDay, thisMonth);
                oF << right << setw(2) << setfill('0') << thisMonth << "/";
                oF << right << setw(2) << setfill('0') << thisDay << "\t";
                oF << right << setw(2) << setfill('0') << thisHour << ":";
                oF << right << setw(2) << setfill('0') << thisMin << " -- ";

                hoursTotal = (day2Total - day1Total)/3600;
                minutesTotal = ((day2Total - day1Total)%3600)/60;

                oF << right << setw(2) << setfill('0') << hoursTotal << ":";
                oF << right << setw(2) << setfill('0') << minutesTotal << endl;

                total += day2Total - day1Total;

                p++;
            }

            totalHours = total/3600;
            totalMinutes = (total%3600)/60;

            oF << endl;
            oF << endl << "GRAND TOTAL : ";
            oF << right << setw(2) << setfill('0') << totalHours << ":";
            oF << right << setw(2) << setfill('0') << totalMinutes << endl;

            oF << setw(40) << setfill('-') << "-" << endl;
        }
        i = i + duration;
    }
    oF.close();
}

void Log::checkTimes(bool& allGood, int& inOut, int& month, int& day, int& badTime){
    int status, lastStatus = 0;
    vector<int> tempVec;
    allGood = true;
    for(unsigned int i = 0; i < userData.size(); i++){
        tempVec = userData.at(i);
        status = tempVec.at(0);
        if(status == lastStatus){
            cout << "BAD DATE" << endl;
            allGood = false;
            inOut = status;
            if(status == 0){
                GetDate(tempVec.at(1), month, day);
            }
            else{
                tempVec = userData.at(i-1);
                GetDate(tempVec.at(1), month, day);
            }
            break;
        }
        lastStatus = status;
    }
    
}

void Log::GetDate(int seconds, int& mm, int& dd){
    time_t theTime = seconds;
    //theTime -= 6*60*60;
    struct tm *aTime = localtime(&theTime);
    
    dd = aTime->tm_mday;
    mm = aTime->tm_mon + 1; 
}

void Log::GetHourMin(int seconds, int& hr, int& min){
    time_t theTime = seconds;
    //theTime -= 6*60*60;
    struct tm *aTime = localtime(&theTime);
    hr = aTime->tm_hour;
    min = aTime->tm_min;
}

void Log::GetFullDT(int seconds, int& hr, int& min, int& dd, int& mm){
    time_t theTime = seconds;
    //theTime -= 6*60*60;
    struct tm *aTime = localtime(&theTime);
    hr = aTime->tm_hour;
    min = aTime->tm_min;
    
    dd = aTime->tm_mday;
    mm = aTime->tm_mon + 1; 
}