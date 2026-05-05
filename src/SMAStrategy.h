#pragma once
#include"Strategy.h"
using namespace std;
class SMAStrategy: public Strategy {
public:
    explicit SMAStrategy(int shortPeriod = 20, int longPeriod = 50);
    Signal generateSignal(const vector<OHLCV>&history, int index) override;
    string getName() const override;
private:
    int m_short;
    int m_long;
    double sma(const vector<OHLCV>&history, int endIndex, int period) const;
};