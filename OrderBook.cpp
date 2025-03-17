

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

class orderBook {

    enum class OrderType{ Market, Limit, Stop,
                        GoodTillCancele, FillOrKill_Limit};
    enum class Side { Buy, Sell};
    // define the possible order types
    // weather an order is a buy or sell

    class Order {
	public: // paramter constructor with initilise list needs parameters to be passed
        Order(int id, OrderType type, Side side, double price, int quantity)
            : id(id), type(type), side(side), price(price), quantity(quantity) {
        } 
        // getter functions gname() to pll the data from private
        int getId() const { return id; }
        OrderType getType() const { return type; }
        Side getSide() const { return side; }
        double getPrice() const { return price; }
        int getQuantity() const { return quantity; }

        void setQuantity(int new_quantity) { quantity = new_quantity; }

        std::vector<Order> orders; // vector to store our orders in the order book

    private:
        int id;
        OrderType type;
        Side side;
        double price;
        int quantity;
       };


private:
	std::vector<Order> orders; // vector to store our orders in the order book


};



    

    

int main()
{






	return 0;
}
    