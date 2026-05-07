#include "Metrics.h"
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;

PerformanceMetrics Metrics::compute(const BacktestResult& result) {  // fixed: Performance Metrics -> PerformanceMetrics
    PerformanceMetrics pm;
    const auto& curve = result.equityCurve;
    if (curve.empty()) return pm;

    pm.totalReturnPct = (result.finalEquity / result.initialEquity - 1.0) * 100.0;

    double years = static_cast<double>(curve.size()) / 252.0;
    if (years > 0.0) {
        pm.annualizedReturnPct = (pow(result.finalEquity / result.initialEquity, 1.0 / years) - 1.0) * 100.0;  // fixed: itialEquity -> initialEquity
    }

    vector<double> dailyReturns;
    dailyReturns.reserve(curve.size() - 1);
    for (size_t i = 1; i < curve.size(); ++i) {  // fixed: t -> i
        if (curve[i - 1].equity > 1e-10) {
            dailyReturns.push_back((curve[i].equity - curve[i - 1].equity) / curve[i - 1].equity);  // fixed: missing parentheses
        }
    }

    if (!dailyReturns.empty()) {
        double mean = accumulate(dailyReturns.begin(), dailyReturns.end(), 0.0) / static_cast<double>(dailyReturns.size());
        double variance = 0.0;
        for (double r : dailyReturns) {
            variance += (r - mean) * (r - mean);
        }
        variance /= static_cast<double>(dailyReturns.size());
        double stddev = sqrt(variance);
        pm.sharpeRatio = (stddev > 1e-10) ? (mean / stddev * sqrt(252.0)) : 0.0;
    }

    double peak = curve[0].equity;
    double maxDD = 0.0;
    for (const auto& ep : curve) {
        if (ep.equity > peak) peak = ep.equity;
        double dd = (peak - ep.equity) / peak;
        if (dd > maxDD) maxDD = dd;
    }
    pm.maxDrawdownPct = maxDD * 100.0;

    for (const auto& t : result.trades) {
        if (t.action == Signal::SELL) {
            ++pm.totalTrades;
            if (t.pnl > 0.0) ++pm.winningTrades;
        }
    }

    pm.winRatePct = (pm.totalTrades > 0) ? (static_cast<double>(pm.winningTrades) / pm.totalTrades * 100.0) : 0.0;
    return pm;
}