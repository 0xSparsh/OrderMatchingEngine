#include "MatchingEngine.h"

MatchingEngine::MatchingEngine() : _books(65536) {}

bool MatchingEngine::processOrder(const Order& order)
{
    if (order.stockLocate >= _books.size()) { return false; } //  invalid locate - reject order

    return _books[order.stockLocate].addOrder(order);
}
