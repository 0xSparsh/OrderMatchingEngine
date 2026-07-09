#pragma once

#include <map>
#include <list>
#include <unordered_map>
#include "Order.h"

class OrderBook
{
public:
    OrderBook();

    bool addOrder(const Order& order);
    bool cancelOrder(OrderId orderId);
    void printBook() const;

private:
    std::map<Price, std::list<Order>, std::greater<Price>> _bids;
    std::map<Price, std::list<Order>, std::less<Price>> _asks;
    std::unordered_map<OrderId, std::list<Order>::iterator> _lookup;
};