#pragma once

#include <map>
#include <list>
#include <unordered_map>
#include "Order.h"

class OrderBook
{
public:
    OrderBook() = default;

    // Delete copy constructors
    OrderBook(const OrderBook&) = delete;
    OrderBook& operator=(const OrderBook&) = delete;

    // Default move constructors
    OrderBook(OrderBook&&) = default;
    OrderBook& operator=(OrderBook&&) = default;

    // Add orders to the Orderbook
    bool addOrder(const Order& order);

    // Cancel orders 
    bool cancelOrder(OrderId orderId);

private:
    std::map<Price, std::list<Order>, std::greater<Price>> _bids;
    std::map<Price, std::list<Order>, std::less<Price>> _asks;
    std::unordered_map<OrderId, std::list<Order>::iterator> _lookup;
};