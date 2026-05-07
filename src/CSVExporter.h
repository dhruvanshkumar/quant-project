#pragma once
#include "Backtester.h"
#include "Metrics.h"
#include<string>
using namespace std;
class CSVExporter {
public:
    explicit CSVExporter(const string& outputDir = "results" );
    void exportEquityCurve(const BacktestResult& result) const;
    void exportTradeLog(const BacktestResult& result) const;
    void exportSummary(const BacktestResult& result, const PerformanceMetrics& metrics) const;
private:
    string m_outputDir;
    static string safeFilename(const string& name);
};