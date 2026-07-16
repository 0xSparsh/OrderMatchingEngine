#pragma once

#include <map>
#include <list>
#include <vector>
#include <unordered_map>
#include "Order.h"
#include "Trade.h"

class OrderBook
{
public:
    OrderBook() = default;

    // Delete copy constructors
    OrderBook(const OrderBook&) = delete;
    OrderBook& operator=(const OrderBook&) = delete;

    // Default move constructors
    OrderBook(OrderBook&&) noexcept = default;
    OrderBook& operator=(OrderBook&&) noexcept = default;

    // Add orders to the Orderbook
    bool addOrder(const Order& order);

    // Cancel orders 
    bool cancelOrder(OrderId orderId);

    // Getter function for trades
    const std::vector<Trade>& getTrade() const { return _trades; }

private:
    std::map<Price, std::list<Order>, std::greater<Price>> _bids;
    std::map<Price, std::list<Order>, std::less<Price>> _asks;
    std::unordered_map<OrderId, std::list<Order>::iterator> _lookup;
    std::vector<Trade> _trades;

    void matchOrder(Order& aggressive);
    bool canFillCompletely(const Order& order) const;
};