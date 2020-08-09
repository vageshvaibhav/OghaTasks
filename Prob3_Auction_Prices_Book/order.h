#include<string>
#include<iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;

class Order
{
    string m_auctionOrderId;
    string m_productId;
    int m_price;
    int m_side;
    uint64_t m_timestamp_order_placed;
    public:
    Order(string ordId, string productId, int price, int side, uint64_t timestamp_order_placed)
        : m_auctionOrderId(ordId) , m_productId(productId), m_price(price), m_side(side), m_timestamp_order_placed(0) 
    {
    }
    //Getters
    string getAuctionOrderId() const {return m_auctionOrderId;} 
    int getPrice() const {return m_price;}
    string getProductId() const {return m_productId;}
    int getSide() const{return m_side;}

    //Setters
    void setPrice(int price){m_price=price;}
    void setTimestampOrderPlaced(uint64_t time) {m_timestamp_order_placed = time;}

    //Overload operators
    friend bool operator < (const Order& lhs,const Order& rhs);
    friend bool operator > (const Order& lhs,const Order& rhs);
    friend bool operator == (const Order& lhs,const Order& rhs);
    friend bool operator != (const Order& lhs,const Order& rhs);
    friend ostream & operator<< (ostream & ost,const Order & ord);
    friend istream & operator>> (istream & ist,Order & ord);
};

bool operator< (const Order& lhs,const Order& rhs)
{
    if(lhs.m_price < rhs.m_price) return true;
    else if (lhs.m_price == rhs.m_price && lhs.m_timestamp_order_placed < rhs.m_timestamp_order_placed){return true;} //To Sort Sell Orders Ascending on m_price,time
    else return false;
}

bool operator> (const Order& lhs,const Order& rhs)
{
    if(lhs.m_price > rhs.m_price) return true;
    else if (lhs.m_price == rhs.m_price && lhs.m_timestamp_order_placed < rhs.m_timestamp_order_placed){return true;}  //To sort Buy Order on 1. Descending on Price
    else return false;                                                           //2.if Price are same , Ascending on m_auctionOrderId(time)
}

bool operator== (const Order& lhs,const Order& rhs)
{
    return (lhs.m_auctionOrderId == rhs.m_auctionOrderId && lhs.m_productId == rhs.m_productId && lhs.m_price == rhs.m_price && lhs.m_side == rhs.m_side );
}

bool operator!= (const Order& lhs,const Order& rhs)
{
    return !(lhs == rhs);
}

//Modify less and greater functor for Order to sort the set of set of Orders on m_price/time
namespace std
{
    template <>
        struct less<Order>
        {
            bool operator() (const Order& lhs, const Order& rhs)
            {
                return lhs < rhs;
            }
        };
    template<>
        struct greater<Order>
        {
            bool operator() (const Order& lhs, const Order& rhs)
            {
                return lhs > rhs;
            }
        };
}

ostream & operator<< (ostream& ost,const Order& ord)
{
    ost << ord.m_productId <<","<<ord.m_auctionOrderId<<","<<ord.m_side<<","<<","<<ord.m_price;
    return ost;
}

istream & operator>> (istream & ist,Order& ord)
{
    ist>> ord.m_productId >>ord.m_auctionOrderId >>ord.m_side>>ord.m_price;
    return ist;
}

