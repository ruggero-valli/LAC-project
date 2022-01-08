#include "libUnits.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "libUtils.h"

using namespace std;

namespace units{

double M = 0;
double L = 0;
double G = 0;
double T = 0;

void parseCfgFile(string& cfgFilePath);
bool parseCommand(ifstream& cfgFile);
void checkMissing();

void init(string& cfgFilePath){
    parseCfgFile(cfgFilePath);
    checkMissing();
    T = sqrt(L*L*L/M/G);
    G = 1;
}

void parseCfgFile(string& cfgFilePath){
    ifstream cfgFile(cfgFilePath);
    if (cfgFile.is_open()){
        bool isEOF=false;
        while (!isEOF){
            isEOF = parseCommand(cfgFile);
        }
        cfgFile.close();
    }
}

bool parseCommand(ifstream& cfgFile){
    string line, command, value;
    if (!getline(cfgFile, line)){
        return true;
    }
    erase(line, ' ');
    if (line[0] == '%' || line.empty()){
        return false; // lines starting with '%' are comments
    }
    parseLine(line, command, value);
    
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
    return false;
}

void checkMissing(){
    if (M==0){
        cout << "Error: variable M not set\n";
        exit(2);
    } else if (L==0){
        cout << "Error: variable L not set\n";
        exit(2);
    } else if (G==0){
        cout << "Error: variable G not set\n";
        exit(2);
    }
}

}