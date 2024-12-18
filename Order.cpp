#include "Order.h"

Order::Order(std::string id, char type, int quantity, double price, bool isMarket)
    : id(id), type(type), quantity(quantity), price(price), isMarket(isMarket) {}

std::string Order::getId() const { return id; }
char Order::getType() const { return type; }
int Order::getQuantity() const { return quantity; }
double Order::getPrice() const { return price; }
bool Order::isMarketOrder() const { return isMarket; }

void Order::setQuantity(int newQuantity) { quantity = newQuantity; }

bool Order::operator<(const Order& other) const {
    if (type != other.type) return type < other.type; 
    if (isMarket != other.isMarket) return isMarket > other.isMarket;
    if (type == 'B') {
        if (price != other.price) return price > other.price;
    } else {
        if (price != other.price) return price < other.price;
    }
    return id < other.id;
}