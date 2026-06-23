#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <sstream>

class OrderBook{
    
};

enum class Side {
    BUY,
    SELL
};

enum class Type {
    NEW,
    CANCEL
};

struct Order {
    int64_t timestamp;
    int64_t orderId;
    Type type;
    Side side;
    int64_t price;
    uint32_t quantity;
};

struct Trade {
    int64_t buy_order_id;
    int64_t sell_order_id;
    int64_t price;
    uint32_t quantity;
};

int main(){
    
}