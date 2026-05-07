#include<iostream>
#include<iomanip>
#include<memory>
#include<vector>
#include"DataLoader.h"
#include"Backtester.h"
#include"SMAStrategy.h"
#include"RSIStrategy.h"
#include"Metrics.h"
#include"CSVExporter.h"
using namespace std;
static void printMetrics(const string& name, const PerformanceMetrics& m){
    cout << "\n===================================\n";
    cout << " Strategy : " << name << "\n";
    cout << "=======================================\n";
    cout << fixed << setprecision(2);
    cout << " Total Return: " << m.totalReturnPct << " $\n";
    cout << " Annualized Return: " << m.annualizedReturnPct << " %\n";
    cout << " Sharpe Ratio: " << m.sharpeRatio << "\n";
    cout << " Max Drawdown: " << m.maxDrawdownPct << " %\n";
    cout << " Total Trades: " << m.totalTrades << "\n";
    cout << " Winning Trades: " << m.winningTrades << "\n";
    cout << " Win Rate: " << m.winRatePct << " %\n";
    cout << "======================================\n";
}
int main(int argc, char* argv[]){
    string dataFile = "data/sample_ohlcv.csv";
    string outputDir = "results";
    double capital = 100'000.0;
    if (argc>=2) dataFile = argv[1];
    if (argc>=3) outputDir = argv[2];
    cout << "=== Algorithmic Trading Strategy Backtester ===\n";
    cout << "Data file: " << dataFile << "\n";
    cout << "Output directory: " << outputDir << "\n";
    cout << "Capital: $" << capital << "\n";
    vector<OHLCV> data;
    try {
        data = DataLoader::load(dataFile);
    } catch (const exception& e) {
        cerr << "[ERROR] " << e.what() << "\n";
        return 1;
    }
    cout << "\nLoaded " << data.size() << " price bars" << " (" << data.front().date << " -> " << data.back().date << ")\n";
    vector<unique_ptr<Strategy>> strategies;
    strategies.emplace_back(make_unique<SMAStrategy>(20, 50));
    strategies.emplace_back(make_unique<RSIStrategy>(14, 30.0, 70.0));
    Backtester engine(capital);
    CSVExporter exporter(outputDir);
    for(auto& strat:strategies){
        BacktestResult result = engine.run(*strat, data);
        PerformanceMetrics pm = Metrics::compute(result);
        printMetrics(result.strategyName, pm);
        exporter.exportEquityCurve(result);
        exporter.exportTradeLog(result);
        exporter.exportSummary(result, pm);
    }
    cout << "\nAll Results written to: " << outputDir << "\n";
    return 0;
}