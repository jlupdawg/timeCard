#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

void printMainMenu();
string getUsername();
void printTime(int, int, int, int, int, int);
void getTime(int&, int&, int&, int&, int&, int&);
void toFile(string, string, string, int, int, int, int, int, int);

string usernameFile = "usernames.txt";
string rawTimesheetRoot = "_rawTimes.txt";
string formattedTimesheetRoot = "_formattedTimes.txt";

int main()
{
    int d, mm, yyyy, h, min, sec;
    int temp;
 
    int usernameCount = 0;

    string username = getUsername();
    
    string rawTimesheet = username + rawTimesheetRoot;
    string formattedTimesheet = username + formattedTimesheetRoot;

    
    while(1){
        do{
            printMainMenu();
            cin >> temp;
        }while(temp > 2 || temp < 1);
        
        switch (temp){
            case 1:
                getTime(d, mm, yyyy, h, min, sec);
                toFile("IN", rawTimesheet, formattedTimesheet, d, mm, yyyy, h, min, sec);
                printTime(d, mm, yyyy, h, min, sec);
                break;
            case 2:
                getTime(d, mm, yyyy, h, min, sec);
                toFile("OUT", rawTimesheet, formattedTimesheet, d, mm, yyyy, h, min, sec);
                printTime(d, mm, yyyy, h, min, sec);
                exit(0);
                break;
        }
    }

    return 0;
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


void printMainMenu(){
    cout << "Main Menu" << endl ;
    cout << "1.Clock In" << endl;
    cout << "2.Clock Out" << endl;
}

void getTime(int &d, int &mm, int &yyyy, int &h, int &min, int &sec){
        
    time_t theTime = time(NULL);
    theTime -= 6*60*60;
    struct tm *aTime = localtime(&theTime);
    
    d = aTime->tm_mday;
    mm = aTime->tm_mon + 1; 
    yyyy = aTime->tm_year + 1900; 
    h = aTime->tm_hour;
    min = aTime->tm_min;
    sec = aTime->tm_sec; 
}

void printTime(int d, int mm, int yyyy, int h, int min, int sec){
  
    cout << mm << "/" << d << "/" << yyyy << " ";
    cout << h << ":" << min << ":" << sec << endl;
}

void toFile(string status,string file1, string file2, int d, int mm, int yyyy, int h, int min, int sec){
    ofstream oF;
    
    oF.open(file1, ofstream::app);
    oF << status << " " << d << " " << mm << " " << yyyy << " " << h << " " << min << " " << sec << endl;
    oF.close();
    
    oF.open(file2, ofstream::app);
    oF << mm << "/" << d << "/" << yyyy << " ";
    oF << status << " ";
    oF << h << ":" << min << ":" << sec << endl;
    oF.close();
}
