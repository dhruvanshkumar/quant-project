#include "SMAStrategy.h"
#include<numeric>
using namespace std;
SMAStrategy::SMAStrategy(int shortPeriod, int longPeriod) 
    : m_short(shortPeriod), m_long(longPeriod) {}
string SMAStrategy::getName() const {
    return "SMA_Crossover(" + to_string(m_short) + ", " + to_string(m_long) + ")";
}
double SMAStrategy::sma(const vector<OHLCV>&history, int endIndex, int period) const {
    double sum = 0.0;
    for(int i=endIndex-period+1; i<=endIndex; ++i){
        sum += history[i].close;
    }
    return sum / period;
}
Signal SMAStrategy::generateSignal(const vector<OHLCV>&history, int index) {
    if(index<m_long) return Signal::HOLD;
    double shortNow = sma(history, index, m_short);
    double longNow = sma(history, index, m_long);
    double shortPrev = sma(history, index-1, m_short);
    double longPrev = sma(history, index-1, m_long);
    if(shortPrev <= longPrev && shortNow > longNow) return Signal::BUY;
    if(shortPrev >= longPrev && shortNow < longNow) return Signal::SELL;
    return Signal::HOLD;
}