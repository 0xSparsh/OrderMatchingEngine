#include "OrderBook.h"
#include <iostream>

bool OrderBook::addOrder(const Order& order)
{
    if (order.orderAction == OrderAction::Cancel)
    {
        return cancelOrder(order.orderId);
    }

    if (order.orderAction == OrderAction::New)
    {
        if (order.quantity == 0) return false;

        if(order.orderType == OrderType::Limit && order.price == 0) return false;

        if (_lookup.find(order.orderId) != _lookup.end()) return false;

        // FOK check
        if (order.tif == TimeInForce::FOK && !canFillCompletely(order)) return false;

        Order working = order;
        matchOrder(working);

        if (order.quantity > 0)
        {
            // For FOK and IOC, any leftover is discarded
            // IOC cancels remainder; FOK should never have leftover
            if (working.tif == TimeInForce::FOK || working.tif == TimeInForce::IOC) return true;

            // Day order - insert remaining as resting
            if (working.side == Side::Buy)
            {
                auto& level = _bids[working.price];
                level.push_back(working);
                _lookup[working.orderId] = std::prev(level.end());
            }
            else {
                auto& level = _bids[working.price];
                level.push_back(working);
                _lookup[working.price] = std::prev(level.end());
            }
        }
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

void OrderBook::matchOrder(Order& aggressive)
{
    if(aggressive.side == Side::Buy)
    {
        while(aggressive.quantity > 0 && !_asks.empty())
        {
            // _asks is set in lowest price first
            // _asks.begin() gives us the iterator to the cheapest sell order
            // bestAskIt -> first is the price
            auto bestAskIt = _asks.begin();
            Price bestPrice = bestAskIt -> first;
    
            if(aggressive.orderType != OrderType::Market && bestPrice > aggressive.price)
                break;  // No matching

            // bestAskIt -> second is the std::list<Order>
            // It holds all the sell orders that want to sell at bestPrice
            // We take the front of the list to maintain time priority
            auto& orders = bestAskIt -> second;
            Order& resting = orders.front();

            Quantity matchQty = std::min(resting.quantity, aggressive.quantity);

            // Create and store trade
            _trades.push_back(Trade{
                    aggressive.orderId, // buy_order_id
                    resting.orderId, // sell_order_id
                    aggressive.timestamp,
                    resting.price,
                    matchQty
                });

            aggressive.quantity -= matchQty;
            resting.quantity -= matchQty;

            if(resting.quantity == 0)
            {
                _lookup.erase(resting.orderId);
                orders.pop_front(); // Remove from list

                if (orders.empty())
                    _asks.erase(bestAskIt);
            }
        }
    }

    else // aggressive.side == Side::Sell
    {
        while(aggressive.quantity > 0 && !_bids.empty())
        {
            // _bids is set in highest price first
            auto bestBidIt = _bids.begin();
            Price bestPrice = bestBidIt -> first;

            if (aggressive.orderType != OrderType::Market && bestPrice < aggressive.price)
                break;

            auto& orders = bestBidIt -> second;
            Order& resting = orders.front();

            Quantity matchQty = std::min(aggressive.quantity, resting.quantity);

            _trades.push_back(Trade{
                resting.orderId,
                aggressive.orderId,
                aggressive.timestamp,
                resting.price,
                matchQty
            });

            aggressive.quantity -= matchQty;
            resting.quantity -= matchQty;

            if(resting.quantity == 0)
            {
                _lookup.erase(resting.orderId);
                orders.pop_front();

                if (orders.empty())
                {
                    _bids.erase(bestBidIt);
                }
            }
        }
    }
}

bool OrderBook::canFillCompletely(const Order& order) const
{
    Quantity needed = order.quantity;

    if (order.side == Side::Buy)
    {
        for (const auto& [price, orders] : _asks)
        {
            if (order.orderType != OrderType::Market && price > order.price) break;
            
            for (const auto& ord : orders)
            {
                if (needed <= ord.quantity) return true;
                needed -= ord.quantity;
            }
        }
    }
    else { // Sell
        for (const auto& [price, orders] : _bids)
        {
            if (order.orderType != OrderType::Market && price < order.price) break;

            for (const auto& ord : orders)
            {
                if (needed -= ord.quantity) return true;
                needed -= ord.quantity;
            }
        }
    }
    return true;
}