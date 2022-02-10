#include "libNBody.h"
#include <string>
#include <iostream>
#include <fstream>
#include "libUtils.h"
#include "libUnits.h"

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
    cout << "1\n";
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
    if (command == "Npart"){
        Npart = stoi(value);
    }else if (command == "m"){
        m = readArray1D(value, Npart);
        m = m/units::M;
    }else if (command == "r0"){
        r0 = readArray2D(cfgFile, 3, Npart);
        r0 = r0/units::L;
    }else if (command == "v0"){
        v0 = readArray2D(cfgFile, 3, Npart);
        v0 = v0/(units::L/units::T);
    } else {
        cout << "Error: command '" << line << "' not recognized!\n";
        exit(1);
    }
    return false;
}

void checkMissing(){
    if (Npart==0){
        cout << "Error: variable N not set\n";
        exit(2);
    } else if (m.size()==0){
        cout << "Error: variable m not set\n";
        exit(2);
    } else if (r0.size()==0){
        cout << "Error: variable r0 not set\n";
        exit(2);
    } else if (v0.size()==0){
        cout << "Error: variable v0 not set\n";
        exit(2);
    }
}

}