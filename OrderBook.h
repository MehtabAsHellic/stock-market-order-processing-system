#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <set>
#include <vector>
#include "Order.h"

class OrderBook {
public:
    void addOrder(const Order& order);
    Order getTopBuyOrder();
    Order getTopSellOrder();
    bool hasBuyOrders() const;
    bool hasSellOrders() const;
    void displayPendingOrders(std::ostream& out) const;
    std::vector<Order> getAllPendingOrders() const;

private:
    std::multiset<Order> buyOrders;
    std::multiset<Order> sellOrders;
    
    void displayOrders(const std::multiset<Order>& orders, std::ostream& out) const;
};

#endif