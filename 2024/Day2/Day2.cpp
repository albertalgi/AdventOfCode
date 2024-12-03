// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

//Objective: Find number of safe reports
//Safe if:
// All increasing or decreasing order AND adjacents by 1, 2 or 3
// Input: vectors of space delimited values (5)
// 

bool isReportValid(vector<int> report) {
    int ascending = 2;//Initial state
    cout << "Report size : " << report.size() << endl;

    for (vector<int>::iterator it = report.begin(); it < report.end() - 1; ++it) { //it < report.end() - 1 --> Because we want to avoid n + 1 out of range
        cout <<*it << *(it + 1) << " ";
        if ((abs(*it - *(it + 1)) - 3 > 0) || (*it - *(it+1) == 0)) { // Distance between djacents greater that 3 or are equal numbers
            return false;
        }
        if (*it - *(it + 1) > 0) { //Ascending
            if (ascending == 0)
                return false;//Was not ascending before
            ascending = 1;
        }
        else {
            if (ascending == 1)
                return false;//Was not ascending before
            ascending = 0;
        }
    }
    cout << " SAFE!" << endl;
    return true;
}

/*
Returns: 1 --> Safe report
Returns: 0 --> Unsafe report
*/
int getReportStatus(string inputReport) {

    istringstream stream(inputReport);
    string auxString;
    
    vector<int> report;

    while (stream >> auxString) {
        report.push_back(stoi(auxString));
    }
    
    if(isReportValid(report))
        return 1;
    return 0;
}

int main()
{
    // Number of safe reports
    int safeReports = 0;
    int numReports = 0;

    //Read input file
    fstream input;
    input.open("input.txt", ios::in); //Open input file in READ mode
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            numReports++;
            if (getReportStatus(line)) {
                safeReports++;
                cout << "Safe reports: " << safeReports << endl;
            }
        }
        //Close file
        input.close();
    }
    cout << safeReports << "/" << numReports;
}