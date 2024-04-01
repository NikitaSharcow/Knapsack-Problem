#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Parcer{
protected:
    int N, backpack_weight;
    vector <int> value, weight;
public:
    Parcer (ifstream &f_in){
        string str;
        f_in >> str;
        N = stoi(str);
        f_in >> str;
        backpack_weight = stoi(str);
        for(int i=0;i<N;i++){
            f_in >> str;
            value.push_back(stoi(str));
            f_in >> str;
            weight.push_back(stoi(str));
        }
    };
};