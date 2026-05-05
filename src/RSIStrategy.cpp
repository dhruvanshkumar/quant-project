#include "RSIStrategy.h"
#include<cmath>
using namespace std;
RSIStrategy::RSIStrategy(int period, double oversold, double overbought)
    : m_period(period), m_oversold(oversold), m_overbought(overbought) {}
string RSIStrategy::getName() const {
    return "RSI_MeanReversion(" + to_string(m_period)+")";
}
double RSIStrategy::computeRSI(const vector<OHLCV>& history, int index) const {
    if (index < m_period) return 50.0; // Not enough data, return neutral RSI
    double avgGain = 0.0;
    double avgLoss = 0.0;
    for(int i=index - m_period + 1; i <= index; ++i) {
        double change = history[i].close - history[i-1].close;
        if (change > 0) avgGain += change;
        else avgLoss -= change; // Loss is negative
    }
    avgGain /= m_period;
    avgLoss /= m_period;
    if(avgLoss < 1e-10) return 100.0; // Avoid division by zero, RSI is 100 if no losses
    double rs = avgGain / avgLoss;
    return 100.0 - (100.0 / (1.0 + rs));
}
Signal RSIStrategy::generateSignal(const vector<OHLCV>& history, int index) {
    if(index<m_period) return Signal::HOLD;
    double rsi = computeRSI(history, index);
    if(rsi < m_oversold) return Signal::BUY;
    else if(rsi > m_overbought) return Signal::SELL;
    else return Signal::HOLD;
    
}