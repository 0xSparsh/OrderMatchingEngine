#pragma once

#include "Types.h"
#include "Order.h"

using BuyOrderId = OrderId;
using SellOrderId = OrderId;

struct Trade
{
    BuyOrderId buy_order_id;
    SellOrderId sell_order_id;
    Timestamp timestamp;
    Price price;
    Quantity quantity;
};