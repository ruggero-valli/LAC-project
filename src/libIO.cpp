#include <string>
#include "libIO.h"

using namespace std;

void parseCommand(const string line, string& command, string& value){
    int eqIndex = line.find('=');
    command = line.substr(0,eqIndex);
    value = line.substr(eqIndex+1, line.size());
}