#pragma once
#include "Strategy.h"
using namespace std;
class RSIStrategy : public Strategy {
public:
    explicit RSIStrategy(int period = 14, double oversold = 30.0, double overbought = 70.0);
    Signal generateSignal(const vector<OHLCV>& history, int index) override;
    string getName() const override;
private:
    int m_period;
    double m_oversold;
    double m_overbought;
    double computeRSI(const vector<OHLCV>& history, int index) const;
};