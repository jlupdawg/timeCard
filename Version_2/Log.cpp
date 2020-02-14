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

void Log::customInOut(int status , int month, int day, int year, int hour, int minute){
    // TODO Come Up With This
}

void Log::printAllPaystubs(string path, int mm1, int mm2, int dd1, int dd2){
    int option;
    int mm1, mm2, dd1, dd2;
    int day1 = 2, day2 = 15; //Also change in Display.cpp
    vector<int> tempVec;

    ofstream oF;
    int totalHours, totalMinutes, total;
    int day1Total, day2Total, hoursTotal, minutesTotal;
    string tempPath = (path+paystubFile);
    oF.open(tempPath);
    if(!oF.is_open()){
        //cout << "FILE NOT OPENED" << endl;
        exit(1);
    }
        refreshUserData();
        //Delete all data not in range
        //cout << "USERDATA SIZE: " << userData.size() << endl;
        for(unsigned int j = 0; j < userData.size();){
            tempVec = userData.at(j); 
            if(tempVec.at(1) < mm1 || tempVec.at(1) > mm2){
                userData.erase(userData.begin() + j);
                //cout << "ERASED 1" << endl;
            }
            else if(tempVec.at(1) == mm1 && tempVec.at(2) < dd1){
                userData.erase(userData.begin() + j);
                //cout << "ERASED 2" << endl;
            }
            else if(tempVec.at(1) == mm2 && tempVec.at(2) > dd2){
                userData.erase(userData.begin() + j);
                //cout << "ERASED 3" << endl;
            }
            else{
                j++;
            }
        }

        //cout << "USERDATA SIZE: " << userData.size() << endl;

        oF << setw(40) << setfill('-') << "-" << endl;
        oF << "PAYSTUB FOR ";
        oF << setw(2) << setfill('0') << mm1 << "/";
        oF << setw(2) << setfill('0') << dd1 << " - ";
        oF << setw(2) << setfill('0') << mm2 << "/";
        oF << setw(2) << setfill('0') << dd2 << endl;



        unsigned int p = 0;
        while(p < userData.size()){
            tempVec = userData.at(p);
            day1Total = 1440*tempVec.at(2) + 60*tempVec.at(3) + tempVec.at(4);
            oF << right << setw(2) << setfill('0') << tempVec.at(1) << "/";
            oF << right << setw(2) << setfill('0') << tempVec.at(2) << "\t";
            oF << right << setw(2) << setfill('0') << tempVec.at(3) << ":";
            oF << right << setw(2) << setfill('0') << tempVec.at(4) << " - ";

            p++;

            tempVec = userData.at(p);
            day2Total = 1440*tempVec.at(2) + 60*tempVec.at(3) + tempVec.at(4);
            oF << right << setw(2) << setfill('0') << tempVec.at(1) << "/";
            oF << right << setw(2) << setfill('0') << tempVec.at(2) << "\t";
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

        oF << setw(40) << setfill('-') << "-" << endl;
    }
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