1.Compilation and Application Usage:
For simplicity, I have kept most of the things in header file so we will have to just compile main source file containing main function
$ g++ --version
g++ (GCC) 4.9.1 20140922 (Red Hat 4.9.1-10)

2.Linux version and release:
$ cat /etc/centos-release
CentOS release 6.9 (Final)

3.Application Compilation:
$ g++ third_string_valid_shuffle_of_first_two.cpp -std=c++14 -o ValidShuffle


4.Algorithm and Time/Space complexity:

As we are checking first or second string character on every recursive iteration, there are 2 options on each path
So, Time complexity is O(2 pow n) = 2*2*2...n times
Space complexity is constant i.e. O(1)

5.Output and few sample test run:
Input for test:

    ValidateShuffle("aab", "aac", "aacaaab"); 
    ValidateShuffle("aabd", "aac", "aabdaac"); 
    ValidateShuffle("ab", "dc", "dcab"); 
    ValidateShuffle("ab", "a", "aab"); 
    ValidateShuffle("ba", "a", "aab"); 
    ValidateShuffle("aab", "aac", "aaaacb");

Output:

aacaaab is not valid shuffle of aab and aac
aabdaac is valid shuffle of aabd and aac
dcab is valid shuffle of ab and dc
aab is valid shuffle of ab and a
aab is not valid shuffle of ba and a
aaaacb is valid shuffle of aab and aac
