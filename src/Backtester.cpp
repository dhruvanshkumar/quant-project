#include<Backtester.h>
Backtester::Backteseter(double initialCash)
    : m_initialCash(initialCash) {}

BacktestResult Backtester::run(Strategy & strategy, const std::vector<OHLCV>& data) {
    Portfolio port(m_initialCash);
    const int n = static_cast<int>(data.size());
    for(int i=0; i<n; ++i){
        Signal sig = strategy.generateSignal(data, i);
        if (i+1<n) {
            doble fillPrice = data[i+1].open;
            if(sig == Signal::BUY){
                port.buy(data[i+1].date, fillPrice);
            } else if(sig == Signal::SELL){
                port.sell(data[i+1].date, fillPrice);
            }
        }
        port.recordEquity(data[i].date, data[i].close);
    }
    if(port.shares()>0 && n >0){
        port.sell(data[n-1].date, data[n-1].close);
    }
    BacktestResult result;
    result.strategyName = strategy.getName();
    result.trades = port.trades();
    result.equityCurve = port.equityCurve();
    result.initialEquity = m_initialCash;
    result.finalEquity = port.totalEquity(n>0?data[n-1].close:0.0);
    return result;
}
   