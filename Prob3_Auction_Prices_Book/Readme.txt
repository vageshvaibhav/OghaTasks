1.Compilation and Application Usage:
For simplicity, I have kept most of the things in header file so we will have to just compile main source file containing main function
$ g++ --version
g++ (GCC) 4.9.1 20140922 (Red Hat 4.9.1-10)

2.Linux version and release:
$ cat /etc/centos-release
CentOS release 6.9 (Final)

3.Application Compilation:
$ g++ application_main.cpp -std=c++14 -o AuctionPrices

Note : With g++ (GCC) 4.9.1 version , default conversion from string constant to ‘char*’ is depricated and that's why you may get below warnings. To resolve that warnings, std::string should be used instead of char* on interface functions. Since that interface was given in problem statement, I have not changed that.

Sample warning:
application_main.cpp:6:47: warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]
     ofp.AddNewOrder("item1","auction1", 1, 100);

4.Algorithm and Time/Space complexity:

      Buy and Sell Order Books are maintained as Set of sorted price/time records.
      Buy Orders sorted on price/time as :
      1.Descending on Price (High to Low)2. If two buy orders price are equal, ascending on time(first come first serve)
      Sell orders sorted on price/time as :
      1.Ascending on price (low to high)2. If two sell orders price are equal , ascending on time (first come first serve)
      Time Complexity :
      Any AddOrder operation would involve 
      O(1) const unordered_map lookup to find order book for particular company
      O(logn) for adding entry in buy/sell side set
      Const O(1) for m_productToOrderMap lookup, add and remove as unordered hased containers used
      Any Delete order operation would involve
      O(1) const unordered_map lookup to find order book for particular company
      O(logn) for removing entry in buy/sell side set
      Const O(1) for m_productToOrderMap operation
      Space complexity : O(n+n/2+n/2) = O(2n) ~ O(n)
     


5.Assumption:

Since there was no mention of how to sort order with same prices for a particular product and side, I have taken order time into consideration by adding current 
timestamp while adding order in to system


6.Output and few sample test run:
Input for test:
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

output:

$ ./AuctionPrices

item2:
Buy:
order3 99
Sell:
order4 100

item1:
Buy:
auction2 101
auction1 100
Sell:

item2:
Buy:
order3 99
Sell:
order4 100

item1:
Buy:
auction2 101
Sell:

item2:
Buy:
order3 99
Sell:
order4 100

item1:
Buy:
Sell:

item2:
Buy:
Sell:
order4 100

item1:
Buy:
Sell:

item2:
Buy:
Sell:

item1:
Buy:
Sell:
