#include "Portfolio.h"
#include <cmath>
#include<stdexcept>
using namespace std;
Portfolio::Portfolio(double initialCash)
    : m_initialCash(initialCash), m_cash(initialCash), m_shares(0), m_avgCost(0.0){}
void Portfolio::buy(const string& date, double price){
    if(m_shares >0) return;
    if(price <= 0.0) return;
    int sharesToBuy = static_cast<int>(floor(m_cash / price));
    if(sharesToBuy <= 0) return;
    m_shares = sharesToBuy;
    m_avgCost = price;
    m_cash -= sharesToBuy * price;
    Trade t;
    t.date = date;
    t.action = Signal::BUY;
    t.price = price;
    t.shares = sharesToBuy;
    t.pnl = 0.0;
    m_trades.push_back(t);
}
void Portfolio::sell(const string& date, double price){
    if (m_shares <= 0) return;
    if (price <= 0.0) return;
    double proceeds = m_shares * price;
    double pnl = proceeds - (m_shares * m_avgCost);
    Trade t;
    t.date = date;
    t.action = Signal::SELL;
    t.price = price;
    t.shares = m_shares;
    t.pnl = pnl;
    m_trades.push_back(t);
    m_cash += proceeds;
    m_shares = 0;
    m_avgCost = 0.0;
}
void Portfolio::recordEquity(const string& date, double closePrice){
    EquityPoint ep;
    ep.date = date;
    ep.equity = totalEquity(closePrice);
    m_equityCurve.push_back(ep);
}
double Portfolio::totalEquity(double closePrice) const{
    return m_cash + (m_shares * closePrice);
}