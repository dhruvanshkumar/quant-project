#pragma once
#include "Types.h"
#include <vector>
using namespace std;

class Portfolio {
public:
    explicit Portfolio(double initialCash = 100'000.0);
    void buy(const string& date, double price);
    void sell(const string& date, double price);
    void recordEquity(const string& date, double closePrice);
    double cash() const { return m_cash; }
    int shares() const { return m_shares; }
    double initialCash() const { return m_initialCash; }
    const vector<Trade>& trades() const { return m_trades; }          // fixed: added const
    const vector<EquityPoint>& equityCurve() const { return m_equityCurve; }  // fixed: added const
    double totalEquity(double currentPrice) const;

private:
    double m_initialCash;
    double m_cash;
    int m_shares;
    double m_avgCost;   // fixed: was missing
    vector<Trade> m_trades;
    vector<EquityPoint> m_equityCurve;
};