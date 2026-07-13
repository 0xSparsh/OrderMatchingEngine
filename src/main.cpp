#include <iostream>
#include "OrderBook.h"
#include "MatchingEngine.h"

int main()
{
    MatchingEngine matchingEngine;
    matchingEngine.processOrder({1, 1, 1, Type::New, Side::Buy, 110, 19});
    matchingEngine.processOrder({2, 2, 2, Type::New, Side::Sell, 119, 13});
}
