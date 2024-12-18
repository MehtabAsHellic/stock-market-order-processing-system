#ifndef ORDERMATCHER_H
#define ORDERMATCHER_H

#include "OrderBook.h"
#include <vector>
#include <string>

class OrderMatcher {
public:
    OrderMatcher(double initialPrice);
    void processOrder(const Order& order);
    void displayOrderBook() const;
    double getLastTradedPrice() const;
    void writeExecutionResults(std::ostream& out) const;
    void writeUnexecutedOrders(std::ostream& out) const;

private:
    OrderBook orderBook;
    double lastTradedPrice;
    std::vector<std::string> executionResults;
    std::vector<Order> originalOrders;

    void processBuyOrder(Order buyOrder);
    void processSellOrder(Order sellOrder);
    bool canExecute(const Order& buyOrder, const Order& sellOrder) const;
    void executeOrder(Order& buyOrder, Order& sellOrder);
    double determineExecutionPrice(const Order& buyOrder, const Order& sellOrder) const;
};

#endif 