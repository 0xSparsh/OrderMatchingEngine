#pragma once

enum class Side
{
    Buy,
    Sell
};

enum class OrderAction
{
    New,
    Cancel
};

enum class TimeInForce
{
    Day,
    IOC, // Immediate-or-Cancel
    FOK // Fill-or-Kill
};

enum class OrderType
{
    Limit,
    Market
};
