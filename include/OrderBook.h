#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_map>
#include "Orders.h"

class OrderBook
{
public:
    OrderBook() = default;

    // addOrder
    // cancelOrder
    // lookOrders (for debugging)

    // Add new orders
    bool addOrder(const Order& order)
    {
        if (order.type == Type::Cancel)
        {
            return cancelOrder(order.orderId);
        }

        if (order.side == Side::Buy)
        {
            auto& level = _bids[order.price];
            level.push_back(order);
            auto it = std::prev(level.end());
            _lookup[order.orderId] = it;
        }

        else
        {
            auto& level= _asks[order.price];
            level.push_back(order);
            auto it = std::prev(level.end());
            _lookup[order.orderId] = it;
        }

        return true;
    }

    // Cancel orders
    bool cancelOrder(OrderId orderId)
    {
        // find the order from _lookup
        auto it = _lookup.find(orderId); // it -> std::list<Order>::iterator

        if (it == _lookup.end())
        {
            return false; // Order not found
        }

        auto listIter = it -> second;
        const Order& ord = *listIter;

        if (ord.side == Side::Buy)
        {
            auto levelIt = _bids.find(ord.price);
            levelIt -> second.erase(listIter);
            if (levelIt -> second.empty())
            {
                _bids.erase(levelIt);
            }
        }

        else
        {
            auto levelIt = _asks.find(ord.price);
            levelIt -> second.erase(listIter);
            if (levelIt -> second.empty())
            {
                _asks.erase(levelIt);
            }
        }

        _lookup.erase(it);
        return true;
    }

    // Print the entire orderbook
    void printBook() const
    {

    }

private:
    // _bids - std::map - highest first 
    // _asks - std:: map - lowest first 
    // _lookup - std::unordered_map for fast lookup

    std::map<Price, std::list<Order>, std::greater<Price>> _bids;
    std::map<Price, std::list<Order>, std::less<Price>> _asks;
    std::unordered_map<OrderId, std::list<Order>::iterator> _lookup;
};