#pragma once

#include "Types.h"
#include <cstdint>

using Timestamp = uint32_t;
using OrderId = uint64_t;
using Price = int32_t;
using Quantity = uint32_t;
using StockLocate = uint16_t;

struct Order
{
    StockLocate stockLocate; // NASDAQ instrument id

    Timestamp timestamp;
    OrderId orderId;

    OrderAction orderAction;
    Side side;
    TimeInForce tif{TimeInForce::Day};
    OrderType orderType;
    
    Price price;
    Quantity quantity;
};