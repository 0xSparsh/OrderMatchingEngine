#pragma once

#include "Types.h"
#include <cstdint>

using Timestamp = uint32_t;
using OrderId = uint64_t;
using Price = int32_t;
using Quantity = uint32_t;

struct Order
{
    Timestamp timestamp;
    OrderId orderId;

    Type type;
    Side side;
    
    Price price;
    Quantity quantity;
};