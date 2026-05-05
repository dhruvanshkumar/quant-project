#include"CSVExporter.h"
#include<fstream>
#include<iostream>
#include<algorithm>
#include<stdexcept>
CSVExporter::CSVExporter(const std::string& outputDir)
    : m_outputDir(outputDir) {}
std::string CSVExporter::safeFilename(const std:: string& name) {
    std::string safe = name;
    std::replace_if(safe.begin(), safe.end(), [](char c){ return c=='(' || c==')' || c==',';},'_');
    return safe;
}
void CSVExporter::exportEquityCurve(const BacktestResult& result) const {
    std::string path = m_outputDir + "/" + safeFilename(result.strategyName) + "_equity.csv";
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("CSVExporter: cannot write: " + path);
    }
    file << "date, equity \n";
    for (const auto& ep: result.equityCurve) {
        file << ep.date << "," << ep.equity << "\n";
    }
    std::cout << "[Export] Equity curve ->" << path << "\n";
}
void CSVExporter::exportTradeLog(const BacktestResult& result) const {
    std::string path = m_outputDir + "/" + safeFilename(result.strategyName) + "_trades.csv";
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("CSVExporter: cannot write: " + path);
    }
    file << "date, action, price, shares, pnl \n";
    for(const auto& t: result.trades){
        std::string action = (t.action == Signal::BUY) ? "BUY" : "SELL";
        file << t.date << "," << action << "," << t.price << "," << t.shares << "," << t.pnl << "\n";
    }
    std::cout << "[Export] Trade log ->" << path << "\n";
}
void csvExporter::exportSummary(const BacktestResult& result, const PerformanceMetrics& metrics) const {
    std::string path = m_outputDir + "/summary.csv";
    bool needsHeader = false;
    {
        std::ifstream check(path);
        needsHeader = !check.good();
    }
    std::ofstream file(path, std::ios::app);
    if(!file.is_open()) {
        throw std::runtime_error("CSVExporter: cannot write: " + path);
    }
    if(needsHeader) {
        file<< "strategy, total_return_pct, annualized_return_pct, sharpe_ratio, max_drawdown_pct, total_trades, winning_trades, win_rate_pct \n";
    }
    file << result.strategyName << "," << metrics.totalReturnPct << "," << metrics.annualizedReturnPct << "," << metrics.sharpeRatio << "," << metrics.maxDrawdownPct << "," << metrics.totalTrades << "," << metrics.winningTrades << "," << metrics.winRatePct << "\n";
    std::cout << "[Export] Summary ->" << path << "\n";
}