#include "libNBody.h"
#include <string>
#include <iostream>
#include <fstream>
#include "libUtils.h"

using namespace std;

namespace NBody{

int Npart;
Array1D m;
Array2D r0;
Array2D v0;

void parseCfgFile(string& cfgFilePath);
bool parseCommand(ifstream& cfgFile);
void checkMissing();

void init(string& cfgFilePath){
    Npart = 0;
    parseCfgFile(cfgFilePath);
    checkMissing();
}

void parseCfgFile(string& cfgFilePath){
    ifstream cfgFile(cfgFilePath);
    if (cfgFile.is_open()){
        bool isEOF;
        while (!isEOF){
            isEOF = parseCommand(cfgFile);
        }
        cfgFile.close();
    }
}

bool parseCommand(ifstream& cfgFile){
    string line, command, value;
    if (!getline(cfgFile, line)){
        return false;
    }
    erase(line, ' ');
    if (line[0] == '%' || line.empty()){
        return true; // lines starting with '%' are comments
    }
    parseLine(line, command, value);

    if (command == "Npart"){
        Npart = stoi(value);
    }else if (command == "m"){
        erase(value, '[');
        erase(value, ']');
        m = readArray1D(value, Npart);
    }else if (command == "r0"){
        r0 == readArray2D(cfgFile, 3, Npart);
    }else if (command == "v0"){
        v0 == readArray2D(cfgFile, 3, Npart);
    } else {
        cout << "Error: command '" << line << "' not recognized!\n";
        exit(1);
    }
    return true;
}

void checkMissing(){
    if (Npart==0){
        cout << "Error: variable N not set";
        exit(2);
    } else if (m.size()==0){
        cout << "Error: variable m not set";
        exit(2);
    } else if (r0.size()==0){
        cout << "Error: variable r0 not set";
        exit(2);
    } else if (v0.size()==0){
        cout << "Error: variable v0 not set";
        exit(2);
    }
}

}