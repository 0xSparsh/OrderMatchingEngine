#include "OrderBook.h"
#include <iostream>

bool OrderBook::addOrder(const Order& order)
{
    if (order.type == Type::Cancel)
    {
        return cancelOrder(order.orderId);
    }

    if (order.type == Type::New)
    {
        if (order.quantity == 0 || order.price <= 0) return false;
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

bool OrderBook::cancelOrder(OrderId orderId)
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
