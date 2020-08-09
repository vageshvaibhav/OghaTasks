#include<iostream>
#include"feed_processor.h"
using namespace std;

int main(int argc, char* argv[]) 
{
    if ( argc != 2 ) 
    {
        cout<<"Wrong number of arguments passed,Input file name needed"<<endl; 
        return 1;
    }
    string inputFile(argv[1]);
    
    FeedProcessor ofp(inputFile,100);
    auto first_repeating_number = ofp.GetFirstRepeatingIntFromInputFile();
    if (first_repeating_number != INT_MAX)
    {   
        cout<< "First repeating number is=" << first_repeating_number << endl;
    }
    else
    {   
        cout<< "Repeating number not found" << endl;
    }
    return 0;
}
