#pragma once
#include "Backtester.h"
struct PerformanceMetrics {
    double totalReturnPct = 0.0;
    double annualizedReturnPct = 0.0;
    double maxDrawdownPct = 0.0;
    double sharpeRatio = 0.0;
    int totalTrades = 0;
    int winningTrades = 0;
    double winRatePct = 0.0;
};
class Metrics {
public:
    static PerformanceMetrics compute(const BacktestResult& result);
};