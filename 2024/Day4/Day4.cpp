// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>

using namespace std;
// Serach for horizontal XMAS or SAMX
int findHorizontalXMAS(string line) {
    int count = 0;
    
    regex pattern1("XMAS");
    regex pattern2("SAMX");
    smatch matches;

    string auxLine = line;
    while (regex_search(line, matches, pattern1)) { //XMAS
        //cout << matches[0] << endl;
        count++;
        line = matches.suffix();
    }

    while (regex_search(auxLine, matches, pattern2)) { //SAMX
        //cout << matches[0] << endl;
        count++;
        auxLine = matches.suffix();
    }
    return count;
}

//Search from top to bottom
int verticalAndDiagonalXMAS(vector<string> lines) {
    int count = 0;
    int position = -1; //Position of X or S

    for (int i = 0; i < lines.size() - 3;i++) {// 3 rows of margin to avoid out of range
        position = -1;
        do {//left to right
            position = lines[i].find("X",position+1);
            if (lines[i].size() - position >= 4 && position != string::npos ) {
                //Check next lines in diagonal to right
                if (lines[i + 1][position + 1] == 'M') {
                    if (lines[i + 2][position + 2] == 'A') {
                        if (lines[i + 3][position + 3] == 'S') {
                            count++;
                        }
                    }
                }
            }
        } while (position != string::npos); 
        
        do {//Left to right BACKWARDS
            position = lines[i].find("S", position + 1);
            if (lines[i].size() - position >= 4 && position != string::npos) {
                //Check next lines in diagonal to right
                if (lines[i + 1][position + 1] == 'A') {
                    if (lines[i + 2][position + 2] == 'M') {
                        if (lines[i + 3][position + 3] == 'X') {
                            count++;
                        }
                    }
                }
            }
        } while (position != string::npos);

        do {//Right to left
            position = lines[i].find("X", position + 1);
            if (position >= 3  && position != string::npos) {
                //Check next lines in diagonal to right
                if (lines[i + 1][position - 1] == 'M') {
                    if (lines[i + 2][position - 2] == 'A') {
                        if (lines[i + 3][position - 3] == 'S') {
                            count++;
                        }
                    }
                }
            }
        } while (position != string::npos);

        do {//Right to left BACKWARDS
            position = lines[i].find("S", position + 1);
            if (position >= 3 && position != string::npos) {
                //Check next lines in diagonal to right
                if (lines[i + 1][position - 1] == 'A') {
                    if (lines[i + 2][position - 2] == 'M') {
                        if (lines[i + 3][position - 3] == 'X') {
                            count++;
                        }
                    }
                }
            }
        } while (position != string::npos);

        do {//Vertical
            position = lines[i].find("X", position + 1);
            if (position != string::npos) {
                //Check next lines in diagonal to right
                if (lines[i + 1][position] == 'M') {
                    if (lines[i + 2][position] == 'A') {
                        if (lines[i + 3][position] == 'S') {
                            count++;
                        }
                    }
                }
            }
        } while (position != string::npos);

        do {//Vertical BACKWARDS
            position = lines[i].find("S", position + 1);
            if (position != string::npos) {
                //Check next lines in diagonal to right
                if (lines[i + 1][position] == 'A') {
                    if (lines[i + 2][position] == 'M') {
                        if (lines[i + 3][position] == 'X') {
                            count++;
                        }
                    }
                }
            }
        } while (position != string::npos);
    }

    return count;
}

//Search from top to bottom
int getCrossMAS(vector<string> lines) {
    int count = 0;
    int position; //Position of A
    bool partial = false;

    for (int i = 1; i < lines.size() - 1; i++) {// 1 rows of margin to avoid out of range. It also starts at secind row since in has to be a cross MAS
        position = -1;
        do {//left to right
            position = lines[i].find("A", position + 1);
            if (lines[i].size() - position > 1 && position > 0 && position != string::npos && position != -1) {
                //Check Cross since A is in the middle of it
                if (lines[i - 1][position + 1] == 'M') { //Top right is an M
                    if (lines[i + 1][position - 1] == 'S') {//Bottom left is an S
                        partial = true;
                    }
                    else {
                        partial = false;
                    }
                }
                else if (lines[i - 1][position + 1] == 'S') { //Top right is an S
                    if (lines[i + 1][position - 1] == 'M') {//Bottom left is an M
                        partial = true;
                    }
                    else {
                        partial = false;
                    }
                }
                if (partial) { //If partial cross MAS proceed, otherwise skip nfollowing logic
                    if (lines[i - 1][position - 1] == 'M') { //Top left is an M
                        if (lines[i + 1][position + 1] == 'S') {//Bottom right is an S
                            count++;
                        }
                    }
                    else if (lines[i - 1][position - 1] == 'S') { //Top left is an S
                        if (lines[i + 1][position + 1] == 'M') {//Bottom right is an M
                            count++;
                        }
                    }
                    partial = false;
                }                
            }
        } while (position != string::npos);
    }

    return count;
}

int main()
{
    vector<string> xmasLines;

    int totalXMAS = 0;

    //Read input file
    fstream input;
    input.open("input.txt", ios::in); //Open input file in READ mode
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            //Fill vector of vectors
            //totalXMAS += findHorizontalXMAS(line); //Part 1
            xmasLines.push_back(line);
            //cout << line << endl;
        }
        
        //Close file
        input.close();
    }

    //totalXMAS += verticalAndDiagonalXMAS(xmasLines); //Part 1
    totalXMAS = getCrossMAS(xmasLines);
    cout << totalXMAS;
}