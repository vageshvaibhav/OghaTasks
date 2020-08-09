#include "auction_prices.h"

int main(int argc, char* argv[]) 
{
    ConcreteAuctionPrices ofp;
    ofp.AddNewOrder("item1","auction1", 1, 100);
    ofp.AddNewOrder("item1","auction2", 1, 101);
    ofp.AddNewOrder("item2","order3", 1, 99);
    ofp.AddNewOrder("item2","order4", 2, 100);
    ofp.Print();
    ofp.DeleteOrder("item1","auction1");
    ofp.Print();
    ofp.DeleteOrder("item1","auction2");
    ofp.Print();
    ofp.DeleteOrder("item2","order3");
    ofp.Print();
    ofp.DeleteOrder("item2","order4");
    ofp.Print();
    return 0;
}
