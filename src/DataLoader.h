#pragma once
#include "Types.h"
#include <string>
#include <vector>
using namespace std;
class DataLoader {
public:
    static vector<OHLCV> load(const string& filePath);
};