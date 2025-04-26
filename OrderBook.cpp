// OrderBook engine with price-time priority matching, O(1) cancel & printBook
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>                    
#include <deque>                  
#include <unordered_map>          
using namespace std;

class OrderBook {
public:
    enum class OrderType { Market, Limit, Stop, GoodTillCancel, FillOrKill_Limit };
    enum class Side { Buy, Sell };

    class Order {
    public:
        Order(int id, OrderType type, Side side, double price, int qty)
            : id(id), type(type), side(side), price(price), quantity(qty) {
        }
        int getId() const { return id; }
        OrderType getType() const { return type; }
        Side getSide() const { return side; }
        double getPrice() const { return price; }
        int getQuantity() const { return quantity; }
        void setQuantity(int q) { quantity = q; }
    private:
        int id;
        OrderType type;
        Side side;
        double price;
        int quantity;
    };

    // Add order to book and attempt matching
    void addOrder(const Order& o) {
        if (o.getSide() == Side::Buy) {
            auto& lvl = bids[o.getPrice()];
            lvl.push_back(o);
            size_t idx = lvl.size() - 1;
            idIdx[o.getId()] = { Side::Buy, o.getPrice(), idx };
        }
        else {
            auto& lvl = asks[o.getPrice()];
            lvl.push_back(o);
            size_t idx = lvl.size() - 1;
            idIdx[o.getId()] = { Side::Sell, o.getPrice(), idx };
        }
        match();
    }

    // Cancel order by ID
    void cancelOrder(int id) {
        auto mit = idIdx.find(id);
        if (mit == idIdx.end()) return;
        auto entry = mit->second;
        double price = entry.priceLevel;
        size_t idx = entry.index;
        if (entry.side == Side::Buy) {
            auto& lvl = bids[price];
            if (idx < lvl.size()) lvl.erase(lvl.begin() + idx);
            if (lvl.empty()) bids.erase(price);
        }
        else {
            auto& lvl = asks[price];
            if (idx < lvl.size()) lvl.erase(lvl.begin() + idx);
            if (lvl.empty()) asks.erase(price);
        }
        idIdx.erase(mit);
    }

    // Print current book state
    void printBook() const {
        cout << "  OrderBook Snapshot   \n";
        cout << "Bids: " << endl;
        for (auto& p : bids) {
            for (auto& o : p.second)
                cout << "  " << p.first << " | qty= " << o.getQuantity()
                << " | id= " << o.getId() << endl;
        }
        cout << "Ask: " << endl;
        for (auto& p : asks) {
            for (auto& o : p.second)
                cout << "  " << p.first << " | qty= " << o.getQuantity()
                << " | id= " << o.getId() << endl;
        }
    }

private:
    struct IdEntry { Side side; double priceLevel; size_t index; };
    map<double, deque<Order>, greater<double>> bids;
    map<double, deque<Order>> asks;
    unordered_map<int, IdEntry> idIdx;

    // Match possible trades
    void match() {
        while (!bids.empty() && !asks.empty() && bids.begin()->first >= asks.begin()->first) {
            auto& bidLvl = bids.begin()->second;
            auto& askLvl = asks.begin()->second;
            auto& b = bidLvl.front();
            auto& a = askLvl.front();
            int qty = min(b.getQuantity(), a.getQuantity());
            cout << "Trade " << qty << " @ " << a.getPrice() << endl;
            b.setQuantity(b.getQuantity() - qty);
            a.setQuantity(a.getQuantity() - qty);
            if (b.getQuantity() == 0) bidLvl.pop_front();
            if (a.getQuantity() == 0) askLvl.pop_front();
            if (bidLvl.empty()) bids.erase(bids.begin());
            if (askLvl.empty()) asks.erase(asks.begin());
        }
    }
};

int main() {
    OrderBook book;
    // orders
    book.addOrder({ 1, OrderBook::OrderType::Limit, OrderBook::Side::Buy, 100.0, 10 });
    book.addOrder({ 2, OrderBook::OrderType::Limit, OrderBook::Side::Sell, 105.0, 5 });
    book.addOrder({ 3, OrderBook::OrderType::Limit, OrderBook::Side::Sell, 99.5, 3 });
    book.addOrder({ 4, OrderBook::OrderType::Limit, OrderBook::Side::Buy, 106.0, 4 });
    book.cancelOrder(2);
    book.printBook();
    return 0;
}