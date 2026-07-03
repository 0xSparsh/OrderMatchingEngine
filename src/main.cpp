#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <list>

enum class Side {
    BUY,
    SELL
};

enum class Type {
    NEW,
    CANCEL
};

using Timestamp = int64_t;
using OrderId = int64_t;
using Price = int64_t;
using Quantity = uint32_t;

struct Order {
    Timestamp timestamp;
    OrderId orderId;
    Type type;
    Side side;
    Price price;
    Quantity quantity;
};

using BuyOrderId = int64_t;
using SellOrderId = int64_t;

struct Trade {
    BuyOrderId buy_order_id;
    SellOrderId sell_order_id;
    Price price;
    Quantity quantity;
};


class OrderBook{
public:
    OrderBook() = default;

    bool add_order(const Order& order) {

        // Cancel Orders
        if (order.type == Type::CANCEL) {
            return cancel_order(order.orderId);
        }

        if (order.side == Side::BUY) {
            // Creates a list (constant time insertions and deletions)
            // If the key order.price already exists, it returns a reference to the existing std::list<Order>
            // If it doesnt exist, it creates a new empty std::list<Order> at that key and returns a reference
            auto& level = bids_[order.price];

            // Newest order at the back
            level.push_back(order);

            // Iterator at the newest order
            auto it = std::prev(level.end());
            lookup_[order.orderId] = it;
        }
        else {
            auto& level = asks_[order.price];
            level.push_back(order);
            auto it = std::prev(level.end());
            lookup_[order.orderId] = it;
        }
        return true;
    }

    // Cancel an order by orderId
    bool cancel_order(Order orderId) {
        auto it = lookup_.find(orderId);
        if (it == lookup_.end()) {
            return false; // Order not found
        }

        // Iterator to std::list<Order>
        auto listIter = it -> second;

        // Determine which side and type this order belongs to
        const Order& ord = *listIter;
        if(ord.side == Side::BUY) {
            auto levelIt = bids_.find(ord.price);
            levelIt -> second.erase(listIter);
            if (levelIt -> second.empty()) {
                bids_.erase(levelIt);
            }
        }
        else {
            auto levelIt = asks_.find(ord.price);
            levelIt -> second.erase(listIter);
            if (levelIt -> second.empty()) {
                bids_.erase(levelIt);
            }
        }

        lookup_.erase(it);
        return true;
    }

private:
    // Bids are sorted in descending order (highest first)
    std::map<Price, std::list<Order>, std::greater<Price>> bids_;

    // Asks are sorted in ascending order (lowest first)
    std::map<Price, std::list<Order>, std::less<Price>> asks_;

    // Unordered Map for fast lookup 
    // Average time complexity - O(1)
    // Worst time complexity - O(n)
    std::unordered_map <OrderId, std::list<Order>::iterator> lookup_;
};

int main(){
    
}