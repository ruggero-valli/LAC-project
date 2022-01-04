#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "libIO.h"
#include "libUnits.h"

using namespace std;
using namespace units;

double units::M = 0;
double units::L = 0;
double units::G = 0;
double units::T = 0;

void parseFile(string& cfgFilePath);
void parseLine(string& line);
void checkMissing();

void units::init(string& cfgFilePath){
    parseFile(cfgFilePath);
    checkMissing();
    T = sqrt(L*L*L/M/G);
    G = 1;
}

void parseFile(string& cfgFilePath){
    ifstream cfgFile(cfgFilePath);
    if (cfgFile.is_open()){
        string line;
        while (getline(cfgFile, line)){
            parseLine(line);
        }
        cfgFile.close();
    }
}

void parseLine(string& line){
    string command, value;
    if (line[0] == '%' || line.empty()){
        return; // lines starting with '%' are comments
    }
    parseCommand(line, command, value);
    if (command == "M"){
        M = stof(value);
    } else if (command == "L"){
        L = stof(value);
    } else if (command == "G"){
        G = stof(value);
    } else {
        cout << "Error: command '" << line << "' not recognized!\n";
        exit(1);
    }
}

void checkMissing(){
    if (M==0){
        cout << "Error: variable M not set";
        exit(2);
    } else if (L==0){
        cout << "Error: variable L not set";
        exit(2);
    } else if (G==0){
        cout << "Error: variable G not set";
        exit(2);
    }
}