#pragma once

#include "Types.h"

struct Trade
{
    BuyOrderId buy_order_id;
    SellOrderId sell_order_od;
    Timestamp timestamp;
    Price price;
    Quantity quantity;
};