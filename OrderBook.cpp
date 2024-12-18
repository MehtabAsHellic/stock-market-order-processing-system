#include "OrderBook.h"
#include <iostream>
#include <iomanip>

void OrderBook::addOrder(const Order& order) {
    if (order.getType() == 'B') buyOrders.insert(order);
    else sellOrders.insert(order);
}

Order OrderBook::getTopBuyOrder() {
    if (buyOrders.empty()) return Order("", 'B', 0, 0, true);
    auto top = *buyOrders.begin();
    buyOrders.erase(buyOrders.begin());
    return top;
}

Order OrderBook::getTopSellOrder() {
    if (sellOrders.empty()) return Order("", 'S', 0, 0, true);
    auto top = *sellOrders.begin();
    sellOrders.erase(sellOrders.begin());
    return top;
}

bool OrderBook::hasBuyOrders() const { return !buyOrders.empty(); }
bool OrderBook::hasSellOrders() const { return !sellOrders.empty(); }

void OrderBook::displayPendingOrders(std::ostream& out) const {
    out << "Buy Orders:\n";
    displayOrders(buyOrders, out);
    out << "Sell Orders:\n";
    displayOrders(sellOrders, out);
}

void OrderBook::displayOrders(const std::multiset<Order>& orders, std::ostream& out) const {
    for (const auto& order : orders) {
        out << order.getId() << " " << order.getQuantity() << " ";
        if (order.isMarketOrder()) {
            out << "M\n";
        } else {
            out << std::fixed << std::setprecision(2) << order.getPrice() << "\n";
        }
    }
}

std::vector<Order> OrderBook::getAllPendingOrders() const {
    std::vector<Order> allOrders;
    allOrders.insert(allOrders.end(), buyOrders.begin(), buyOrders.end());
    allOrders.insert(allOrders.end(), sellOrders.begin(), sellOrders.end());
    return allOrders;
}