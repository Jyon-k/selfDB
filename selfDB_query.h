#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;


vector<string> &split(const string &s, char delim, vector<string> &elems){
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)){
        elems.push_back(item);
    }
    return elems;
}
vector<string> split(const string &s){
    vector<string> elems;
    char delim = ' ';
    split(s, delim, elems);
    return elems;
}
