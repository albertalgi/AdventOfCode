// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void fillArrays(string line, vector<int> &col1, vector<int> &col2) {

    istringstream stream(line);
    string auxString;
    //0=1 | 1=2
    int column = 0;
    while (stream >> auxString) {
        if (column == 0) {
            col1.push_back(stoi(auxString));
            column = 1;
        } else {
            col2.push_back(stoi(auxString));
            column = 0;
        }        
    }
}

int calcDistance(vector<int>& col1, vector<int>& col2) {
    int distance = 0;
    for (int i = 0; i < col1.size(); i++) {
        distance += abs(col1[i] - col2[i]); //Calculate distance
    }

    return distance;
}

int main()
{
    //input vectors
    vector<int> col1;
    vector<int> col2;
    
    //Read input file
    fstream input;
    input.open("input.txt",ios::in); //Open input file in READ mode
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            fillArrays(line, col1, col2);
        }
        //Sort arrays in order to calculate distance
        sort(col1.begin(), col1.end());
        sort(col2.begin(), col2.end());        
        
        //Close file
        input.close();
    }
    cout << calcDistance(col1, col2);
}