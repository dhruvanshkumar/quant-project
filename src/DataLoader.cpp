#include "DataLoader.h"
#include<fstream>
#include<sstream>
#include<stdexcept>
using namespace std;
vector<OHLCV> DataLoader::load(const string& filePath){
    ifstream file(filePath);
    if(!file.is_open()){
        throw runtime_error("Could not open file: " + filePath);
    }
    vector<OHLCV> data;
    string line;
    getline(file, line); 
    while(getline(file, line)){
        if(line.empty()) continue;
        istringstream ss(line);
        string token;
        OHLCV bar;
        getline(ss, bar.date, ',');
        getline(ss, token, ','); bar.open = stod(token);
        getline(ss, token, ','); bar.high = stod(token);
        getline(ss, token, ','); bar.low = stod(token);
        getline(ss, token, ','); bar.close = stod(token);
        getline(ss, token, ','); bar.volume = stoll(token);
        data.push_back(bar);
    }
    if(data.empty()){
        throw runtime_error("No data loaded from file: " + filePath);
    }
    return data;
}