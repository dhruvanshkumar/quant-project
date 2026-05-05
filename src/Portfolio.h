#pragma once
#include "Types.h"
#include <vector>
using namespace std;
class Portfolio {
public:
    explicit Portfolio(double initialCash = 100'000.0);
    void buy(const string& date, double price);
    void sell(const string
    void recordEquity(const string& date, double closePrice);
    double cash() const { return m_cash;}
    int shares() const { return m_shares;}
    double initialCash() const { return m_initialCash;}
    const vector<Trade>& trades() { return m_trades;}
    const vector<EquityPoint>& equityCurve() { return m_equityCurve;}
    double totalEquity(double currentPrice) const;
private:
    double m_initialCash;
    double m_cash;
    int m_shares;
    vector<Trade> m_trades;
    vector<EquityPoint> m_equityCurve;
};