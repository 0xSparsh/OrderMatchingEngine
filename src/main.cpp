#include <iostream>
#include "OrderBook.h"

int main()
{
    OrderBook book;

    std::cout << "Adding orders...\n";

    book.addOrder({1, 1001, Type::New, Side::Buy, 100, 10});
    book.addOrder({2, 1002, Type::New, Side::Buy, 101, 20});
    book.addOrder({3, 2001, Type::New, Side::Sell, 102, 15});
    book.addOrder({4, 2002, Type::New, Side::Sell, 103, 25});

    book.printBook();

    std::cout << "\nCancel BUY order 1002\n";
    book.cancelOrder(1002);
    book.printBook();

    std::cout << "\nCancel SELL order 2001\n";
    book.cancelOrder(2001);
    book.printBook();

    std::cout << "\nTry cancelling an order that doesn't exist\n";
    if (!book.cancelOrder(9999))
    {
        std::cout << "Order not found.\n";
    }

    std::cout << "\nAdd two more orders\n";
    book.addOrder({5, 3001, Type::New, Side::Buy, 101, 30});
    book.addOrder({6, 3002, Type::New, Side::Sell, 102, 40});
    book.printBook();

    std::cout << "\nCancel using addOrder(Type::Cancel)\n";
    book.addOrder({7, 3001, Type::Cancel, Side::Buy, 0, 0});
    book.addOrder({8, 3002, Type::Cancel, Side::Sell, 0, 0});
    book.printBook();

    std::cout << "\nDone.\n";

    return 0;
}