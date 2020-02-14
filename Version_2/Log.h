#ifndef LOG_H
#define LOG_H

#include<vector>
#include<string>

using namespace std;

class Log{
    private:
        vector<string> usernameVec;
        vector<vector<int>> userData;
        string usernameFile;
        string rawDataFile;
        string paystubFile;
        int day, month, year;
        int timeStamp;


        void sortUserData();
        void getDateTime();
        void overrideData();
        void getUserData();
        void pullUsernames();
        void refreshUserData();

    public:
        int GetNumUsers() const;
        string GetUsername(int) const;
        void SetUserFile(string);
        void SetRawDataFile(string);
        void SetPaystubFile(string);
        void clockIn();
        void clockOut();
        void customInOut(int, int, int, int, int, int);
        void printAllPaystubs(string, int, int, int, int);
        void checkTimes(bool&, int&, int&, int&);
};

#endif