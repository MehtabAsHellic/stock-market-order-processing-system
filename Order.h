#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
public:
    Order(std::string id, char type, int quantity, double price, bool isMarket);
    
    std::string getId() const;
    char getType() const;
    int getQuantity() const;
    double getPrice() const;
    bool isMarketOrder() const;
    
    void setQuantity(int newQuantity);

    bool operator<(const Order& other) const;

private:
    std::string id;
    char type;
    int quantity;
    double price;
    bool isMarket;
};

#endif