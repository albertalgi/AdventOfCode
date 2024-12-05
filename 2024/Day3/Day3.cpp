// Day3.cpp
//Objective: obtain mul(X,Y) patterns from corrupted memory (1 long string)

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

int multsResult(string line) {
    int result = 0;
    //Auxiliar variable to look for "do" and "don't"
    string lineAux;

    int d0 = 1; //1=do | 0=don't

    //search for do() and don't()
    std::regex doPattern(R"(do\(\))");
    std::smatch doMatches;
    std::regex dontPattern(R"(don't\(\))");
    std::smatch dontMatches;

    // Simple regular expression matching
    std::regex pattern(R"(mul\((\d+),(\d+)\))"); // regex to match mul(number, number)
    std::smatch matches;

    while(regex_search(line, matches, pattern)) {
        if (regex_search(line, dontMatches, dontPattern)) {
            //cout << "Pos don't: " << dontMatches.position() << " Pos mul: " << matches.position() << endl;
            if (dontMatches.position() < matches.position()) {
               // cout << "Dont: " << dontMatches[0].str() << endl;
                d0 = 0;
            }
        }
        if (regex_search(line, doMatches, doPattern)) {
           // cout << "Pos do: " << doMatches.position() << " Pos mul: " << matches.position() << endl;
            if (doMatches.position() < matches.position()) {
             //   cout << "Do: " << doMatches[0].str() << endl;
                d0 = 1;
            }
        }
        
        if (d0 == 1) {
            int num1 = stoi(matches[1].str());
            int num2 = stoi(matches[2].str());
            cout << "Multiply: "  << num1 << " * " << num2 << endl;
            result += (num1 * num2); //Add multiplication
        }
        else {
            int num1 = stoi(matches[1].str());
            int num2 = stoi(matches[2].str());
            //cout << "Skipping mul of: " << num1 <<  " " << num2 << endl;
        }
        
        line = matches.suffix();//Continue

        
    }

    return result;
}

int main()
{
    // Number of safe reports
    int totalResult = 0;
    int numLines = 0;

    //Read input file
    fstream input;
    input.open("input.txt", ios::in); //Open input file in READ mode
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            numLines++;
            totalResult += multsResult(line);
        }
        //Close file
        input.close();
    }
    cout << totalResult;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
