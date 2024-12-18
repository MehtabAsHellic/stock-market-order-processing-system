#include "OrderMatcher.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

OrderMatcher::OrderMatcher(double initialPrice) : lastTradedPrice(initialPrice) {}

void OrderMatcher::processOrder(const Order& order) {
    originalOrders.push_back(order);
    if (order.getType() == 'B') processBuyOrder(order);
    else processSellOrder(order);
}

void OrderMatcher::processBuyOrder(Order buyOrder) {
    while (orderBook.hasSellOrders() && buyOrder.getQuantity() > 0) {
        Order sellOrder = orderBook.getTopSellOrder();
        if (canExecute(buyOrder, sellOrder)) {
            executeOrder(buyOrder, sellOrder);
            if (sellOrder.getQuantity() > 0) {
                orderBook.addOrder(sellOrder);
            }
        } else {
            orderBook.addOrder(sellOrder);
            break;
        }
    }
    if (buyOrder.getQuantity() > 0) {
        orderBook.addOrder(buyOrder);
    }
}

void OrderMatcher::processSellOrder(Order sellOrder) {
    while (orderBook.hasBuyOrders() && sellOrder.getQuantity() > 0) {
        Order buyOrder = orderBook.getTopBuyOrder();
        if (canExecute(buyOrder, sellOrder)) {
            executeOrder(buyOrder, sellOrder);
            if (buyOrder.getQuantity() > 0) {
                orderBook.addOrder(buyOrder);
            }
        } else {
            orderBook.addOrder(buyOrder);
            break;
        }
    }
    if (sellOrder.getQuantity() > 0) {
        orderBook.addOrder(sellOrder);
    }
}

bool OrderMatcher::canExecute(const Order& buyOrder, const Order& sellOrder) const {
    if (buyOrder.isMarketOrder() || sellOrder.isMarketOrder()) return true;
    return buyOrder.getPrice() >= sellOrder.getPrice();
}

void OrderMatcher::executeOrder(Order& buyOrder, Order& sellOrder) {
    int executedQuantity = std::min(buyOrder.getQuantity(), sellOrder.getQuantity());
    double executionPrice = determineExecutionPrice(buyOrder, sellOrder);

    buyOrder.setQuantity(buyOrder.getQuantity() - executedQuantity);
    sellOrder.setQuantity(sellOrder.getQuantity() - executedQuantity);

    lastTradedPrice = executionPrice;

    std::stringstream ss;
    ss << "order " << buyOrder.getId() << " " << executedQuantity << " shares purchased at price " 
       << std::fixed << std::setprecision(2) << executionPrice << "\n";
    ss << "order " << sellOrder.getId() << " " << executedQuantity << " shares sold at price " 
       << std::fixed << std::setprecision(2) << executionPrice << "\n";
    executionResults.push_back(ss.str());
}

double OrderMatcher::determineExecutionPrice(const Order& buyOrder, const Order& sellOrder) const {
    if (buyOrder.isMarketOrder() && sellOrder.isMarketOrder()) {
        return lastTradedPrice;
    }
    if (buyOrder.isMarketOrder()) return sellOrder.getPrice();
    if (sellOrder.isMarketOrder()) return buyOrder.getPrice();
    return (buyOrder.getId() < sellOrder.getId()) ? buyOrder.getPrice() : sellOrder.getPrice();
}

void OrderMatcher::displayOrderBook() const {
    orderBook.displayPendingOrders(std::cout);
}

double OrderMatcher::getLastTradedPrice() const {
    return lastTradedPrice;
}

void OrderMatcher::writeExecutionResults(std::ostream& out) const {
    for (const auto& result : executionResults) {
        out << result;
    }
}

void OrderMatcher::writeUnexecutedOrders(std::ostream& out) const {
    std::vector<Order> pendingOrders = orderBook.getAllPendingOrders();
    for (const auto& order : originalOrders) {
        auto it = std::find_if(pendingOrders.begin(), pendingOrders.end(),
            [&order](const Order& o) { return o.getId() == order.getId(); });
        if (it != pendingOrders.end()) {
            out << "order " << it->getId() << " " << it->getQuantity() << " shares unexecuted\n";
        }
    }
}