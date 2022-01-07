#include "libUtils.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

void parseLine(const string line, string& command, string& value){
    int eqIndex = line.find('=');
    command = line.substr(0,eqIndex);
    value = line.substr(eqIndex+1, line.size());
    erase(command, ' ');
    erase(value, ' ');
}

Array1D readArray1D(string& str, int len){
    Array1D arr(len);
    erase(str, ' ');
    stringstream ss(str);
    int i=0;
    while(ss.good()){
        string num;
        getline(ss, num, ',');
        arr[i] = stof(num);
        i++;
    }
    return arr;
}

Array2D readArray2D(ifstream& cfgFile, int rows, int cols){
    string line;
    Array1D row;
    Array2D arr;
    for (int i=0; i<rows; i++){
        if (!getline(cfgFile, line)){
            cout << "Error: malformed stream. Expected " << rows << "rows\n";
            exit(3);
        }
        row = readArray1D(line, cols);
        for (int j=0; j<cols; j++){
            arr(i,j) = row[j];
        }
    }
    return arr;
}

void erase(string& str, char c){
    str.erase(std::remove(str.begin(), str.end(), c), str.end());
}

void split(Array1D& U, Array1D& r, Array1D& v){
    r = U(seq(0,last/2));
    v = U(seq(last/2 + 1, last));
}

void join(Array1D& U, Array1D& r, Array1D& v){
    U.resize(r.size()+v.size());
    U(seq(0,last/2)) = r;
    U(seq(last/2 + 1, last)) = v;
}

void UtoRV(Array1D& U, Array2D& r, Array2D& v){
    int N = U.size()/6;
    Array1D rflat,vflat;

    split(U,rflat,vflat);
    r = rflat.matrix().reshaped(3, N).array();
    v = vflat.matrix().reshaped(3, N).array();
}

void RVtoU(Array1D& U, Array2D& r, Array2D& v){
    int N = U.size()/6;
    Array1D rflat,vflat;

    rflat = r.matrix().reshaped(3*N, 1).array();
    vflat = v.matrix().reshaped(3*N, 1).array();
    join(U,rflat,vflat);
}