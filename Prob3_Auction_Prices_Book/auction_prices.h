#include"order.h"
#include<set>
#include<unordered_map>
#include<unordered_set>

//All the typedefs used in main program
typedef set<Order,std::less<Order> > SetOfSellOrder;
typedef set<Order,std::greater<Order> > SetOfBuyOrder;

typedef unordered_map<std::string,SetOfSellOrder > MapOfSellOrder;
typedef unordered_map<std::string,SetOfBuyOrder > MapOfBuyOrder;

class AuctionPrices
{   
    public:
    virtual int AddNewOrder(char *itemId, char *auctionId, int Side, int Price) = 0;
    virtual int DeleteOrder(char *itemId, char *auctionId) = 0;
    virtual int Print() = 0;
};

class ConcreteAuctionPrices : public AuctionPrices
{
    MapOfBuyOrder m_perProductBuyOrderBook;
    MapOfSellOrder m_perProductSellOrderBook;
    unordered_map<string,unordered_map<string,Order>> m_productToOrderMap;

    public:

    /*Buy and Sell Order Books are maintained as Set of sorted price/time records.
     * Buy Orders sorted on price/time as :
     * 1.Descending on Price (High to Low)2. If two buy orders price are equal, ascending on time(first come first serve)
     * Sell orders sorted on price/time as :
     * 1.Ascending on price (low to high)2. If two sell orders price are equal , ascending on time (first come first serve)
     * Any AddOrder operation would involve 
     * O(1) const unordered_map lookup to find order book for particular company
     * O(logn) for adding entry in buy/sell side set
     * Const O(1) for m_productToOrderMap lookup, add and remove as unordered hased containers used
     * Any Delete order operation would involve
     * O(1) const unordered_map lookup to find order book for particular company
     * O(logn) for removing entry in buy/sell side set
     * Const O(1) for m_productToOrderMap operation
     * Space complexity : O(n+n/2+n/2) = O(2n) ~ O(n)
     */
    virtual int AddNewOrder(char *itemId, char *auctionId, int Side, int Price) override
    {
        string prod(itemId);
        string order_id(auctionId);
        auto timestamp = std::chrono::duration_cast< nanoseconds >(system_clock::now().time_since_epoch()).count(); // timestamp of order entry for sorting on price/time
        Order ord(order_id, prod, Price, Side, timestamp);
        if (Side == 1) //Buy
        {
            auto buyIter = m_perProductBuyOrderBook.find(prod);
            if (buyIter == m_perProductBuyOrderBook.end())
            {
                SetOfBuyOrder tempSetBuy;
                tempSetBuy.insert(ord);
                m_perProductBuyOrderBook.insert(make_pair(prod,tempSetBuy));
            }
            else
            {
                auto res = buyIter->second.insert(ord);
                if (!res.second)
                {
                    cout << "AddNewOrder failed for buy order=" << ord << endl;
                    return 0; //Returns 0 in case of errors.
                }
            }
        }
        else if (Side == 2) //Sell
        {
            auto sellIter = m_perProductSellOrderBook.find(prod);
            if (sellIter == m_perProductSellOrderBook.end())
            {   
                SetOfSellOrder tempSetSell;
                tempSetSell.insert(ord);
                m_perProductSellOrderBook.insert(make_pair(prod,tempSetSell));
            }  
            else
            {   
                auto res = sellIter->second.insert(ord);
                if (!res.second)
                {   
                    cout << "AddNewOrder failed for sell order=" << ord << endl;
                    return 0; //Returns 0 in case of errors.
                }
            }
        }
        auto prodIter = m_productToOrderMap.find(prod);
        if (prodIter == m_productToOrderMap.end())
        {
            unordered_map<string,Order> tempProdOrderMap;
            tempProdOrderMap.insert(std::make_pair(order_id,ord));
            m_productToOrderMap.insert(std::make_pair(prod,tempProdOrderMap));
        }
        else
        {
            prodIter->second.insert(std::make_pair(order_id,ord));
        }
        return 1; //success
    }

    virtual int DeleteOrder(char *itemId, char *auctionId) override
    {
        auto prodIter = m_productToOrderMap.find(string(itemId));
        if (prodIter != m_productToOrderMap.end())
        {
            auto orderIter = prodIter->second.find(string(auctionId)); 
            if (orderIter != prodIter->second.end())
            {
                auto ord = orderIter->second;
                if (ord.getSide() == 1) //Buy
                {
                    m_perProductBuyOrderBook[string(itemId)].erase(ord);
                }
                else if (ord.getSide() == 2) //Sell
                {
                    m_perProductSellOrderBook[string(itemId)].erase(ord);
                }
                prodIter->second.erase(orderIter); //Erase from m_productToOrderMap
            }
            else 
            {
                cout << "DeleteOrder failed as Order does not exist in internal datastructure for auctionId=" << auctionId << endl;
                return 0; //itemId not found Returns 0 in case of errors.
            }
        }
        else
        {
            cout << "DeleteOrder failed as Product does not exist in internal datastructure for itemId=" << itemId << endl;
            return 0; //itemId not found Returns 0 in case of errors.
        }
        return 1; //success
    }

    virtual int Print() override
    {
        if (m_productToOrderMap.empty())
        {
            return 0; //Error Nothing to Print
        }
        for (const auto& pair : m_productToOrderMap)
        {
            cout << endl << pair.first << ":" << endl;
            cout << "Buy:" << endl;
            for (const auto& order : m_perProductBuyOrderBook[pair.first])
            {
                cout << order.getAuctionOrderId() << " " << order.getPrice() << endl;
            }
            cout << "Sell:" << endl;
            for (const auto& order : m_perProductSellOrderBook[pair.first])
            {
                cout << order.getAuctionOrderId() << " " << order.getPrice() << endl;
            }
        }
        return 1; //success
    }
};
