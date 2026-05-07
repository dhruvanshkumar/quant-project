#pragma once
#include "Types.h"
#include "Strategy.h"
#include "Portfolio.h"
#include<vector>
#include<memory>
struct BacktestResult {
    std::string strategyName;
    std::vector<Trade> trades;
    std::vector<EquityPoint> equityCurve;
    double initialEquity = 0.0;
    double finalEquity = 0.0;
};
class Backtester {
public:
    explicit Backtester(double initialCash = 100'000.0);
    BacktestResult run(Strategy& strategy, const std::vector<OHLCV>& data);
private:
    double m_initialCash;
};