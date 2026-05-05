#pragma once
#include<string>
#include<vector>
using namespace std;
struct OHLCV {
    string date;
    double open = 0.0;
    double high = 0.0;
    double low = 0.0;
    double close = 0.0;
    double volume = 0.0;
};
enum class Signal (BUY, SELL, HOLD);
struct Trade{
    string date;
    Signal action = Signal::HOLD;
    double price = 0.0;
    int shares = 0;
    double pnl = 0.0;
};
struct EquityPoint{
    string date;
    double equity = 0.0;
};