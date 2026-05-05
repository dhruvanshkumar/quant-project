#pragma once
#include "Types.h"
#include<string>
#include<vector>
using namespace std;
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual Signal generateSignal(const vector<OHLCV>& history, int index) = 0;
    virtual string getName() const = 0;
};