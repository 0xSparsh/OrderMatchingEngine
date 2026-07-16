#include "MatchingEngine.h"

#include <stdexcept>

MatchingEngine::MatchingEngine() : _books(65536) {}

bool MatchingEngine::processOrder(const Order& order)
{
    // StockLocate is uint16_t and size_t is platform and compiler dependent
    // size_t may be almost uint64_t on 64 bit system and uint32_t on 32 bit system
    if (static_cast<size_t>(order.stockLocate) >= _books.size()) { return false; } //  invalid locate - reject order

    return _books[order.stockLocate].addOrder(order);
}

OrderBook& MatchingEngine::getBook(StockLocate locate)
{
    if(static_cast<size_t>(locate) >= _books.size())
        throw std::out_of_range("Invalid stock locate");

    return _books[locate];
}

const OrderBook& MatchingEngine::getBook(StockLocate locate) const
{
    if(static_cast<size_t>(locate) >= _books.size())
        throw std::out_of_range("Invalid stock locate");

    return _books[locate];
}