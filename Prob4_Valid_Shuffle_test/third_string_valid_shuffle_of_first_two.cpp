#include<iostream>
#include<string>
using namespace std;

/*
 * As we are checking first or second string character on every recursive iteration, there are 2 options on each path
 * So, Time complexity is O(2 pow n) = 2*2*2...n times
 * Space complexity is constant i.e. O(1)
 * allows duplicate characters in first and second string
 */
bool IsValidShuffle(const string& first,const string& second,const string& third, size_t& fpos, size_t& spos, size_t& tpos) 
{ 
    //All strings pos reached till end
    if (fpos >= first.length() && spos >= second.length() && tpos >= third.length()) 
        return true; 

    //Third string reached till end while first or second are still left
    if (tpos >= third.length()) 
        return false; 

    return ((tpos < third.length() && fpos < first.length()) && (third.at(tpos) == first.at(fpos)) && IsValidShuffle(first, second, third, 
                ++fpos , spos, ++tpos )) 
        || ((tpos < third.length() && spos < second.length()) && (third.at(tpos) == second.at(spos)) && IsValidShuffle(first, second, third, 
                    fpos, ++spos , ++tpos)); 
} 

void ValidateShuffle(const string& first, const string& second,const string& third) 
{ 
    size_t fpos = 0 , spos = 0 , tpos = 0;
    if (IsValidShuffle(first, second, third,fpos,spos,tpos)) 
        cout << third << " is valid shuffle of " << first << " and " << second << endl; 
    else
        cout << third << " is not valid shuffle of " << first << " and " << second << endl; 
} 
  
int main() 
{ 
    ValidateShuffle("aab", "aac", "aacaaab"); 
    ValidateShuffle("aabd", "aac", "aabdaac"); 
    ValidateShuffle("ab", "dc", "dcab"); 
    ValidateShuffle("ab", "a", "aab"); 
    ValidateShuffle("ba", "a", "aab"); 
    ValidateShuffle("aab", "aac", "aaaacb"); 
    return 0; 
} 

