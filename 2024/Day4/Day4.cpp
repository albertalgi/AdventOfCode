// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>

using namespace std;

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
            totalXMAS += findHorizontalXMAS(line);
            xmasLines.push_back(line);
            //cout << line << endl;
        }
        
        //Close file
        input.close();
    }

    totalXMAS += verticalAndDiagonalXMAS(xmasLines);
    cout << totalXMAS;
}