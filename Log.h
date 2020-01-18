#ifndef LOG_H
#define LOG_H

#include<vector>
#include<string>

using namespace std;

class Log{
    private:
        int numUsers;
        vector<string> usernameVec;
        vector<vector<int>> userData;
        string usernameFile;
        string rawDataFile;
        string paystubFile;
        int day, month, hour, minute;

        void sortUserData();
        void getDateTime();
        void getDate();
        void overrideData();

    public:
        int GetNumUsers() const;
        string GetUsername(int) const;
        void SetUserFile(string);
        void SetRawDataFile(string);
        void SetPaystubFile(string);
        void clockIn();
        void clockOut();
        void customInOut(int, int, int, int, int);
        void printPaystub(int);
};

#endif