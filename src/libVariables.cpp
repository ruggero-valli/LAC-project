#include "libUnits.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "libUtils.h"
#include "libVariables.h"

using namespace std;

namespace variables{
int nSteps;
int t0=-1;
int tmax;
std::string method = "";

void parseCfgFile(string& cfgFilePath);
bool parseCommand(ifstream& cfgFile);
void checkMissing();

void init(std::string& cfgFilePath){
    parseCfgFile(cfgFilePath);
    checkMissing();
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
    if (command == "nSteps"){
        nSteps = stoi(value);
    }else if (command == "t0"){
        t0 = stoi(value);
    }else if (command == "tmax"){
        tmax = stoi(value);
    }else if (command == "method"){
        method = readString(value);    
    } else {
        cout << "Error: command '" << line << "' not recognized!\n";
        exit(1);
    }
    return false;
}

void checkMissing(){
    if (nSteps==0){
        cout << "Error: variable nSteps not set\n";
        exit(2);
    } else if (t0==-1){
        cout << "Error: variable t0 not set\n";
        exit(2);
    } else if (tmax==0){
        cout << "Error: variable tmax not set\n";
        exit(2);
    } else if (method == ""){
        cout << "Error: variable method not set\n";
        exit(2);
    }
}




}