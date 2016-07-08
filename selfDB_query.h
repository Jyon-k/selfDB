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
/*
int main(){

    while(1){
        cout << ">> ";
        string tmp;
        getline(cin, tmp);
        cout << tmp << endl;
        const char* ctmp = tmp.c_str();
        if(!strcmp(ctmp, "exit")) return 0;
        vector<string> vtmp = split(tmp);
        for(vector<string>::iterator it = vtmp.begin(); it != vtmp.end(); ++it){
            cout << (*it) << endl;
        }
    }
}
*/
