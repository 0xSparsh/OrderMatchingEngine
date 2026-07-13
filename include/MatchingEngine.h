#pragma once

#include <vector>
#include "OrderBook.h"

class MatchingEngine
{
public:
    MatchingEngine();

    // Process an order by matching it to correct book
    bool processOrder(const Order& order);

private:
    // vector of OrderBook 
    // The max size will be 2^16
    // NASDAQ stocklocate is 2 byte (16 bit unsigned integer)
    std::vector<OrderBook> _books;
};