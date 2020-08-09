1.Compilation and Application Usage:
For simplicity, I have kept most of the things in header file so we will have to just compile main source file containing main function
$ g++ --version
g++ (GCC) 4.9.1 20140922 (Red Hat 4.9.1-10)

2.Linux version and release:
$ cat /etc/centos-release
CentOS release 6.9 (Final)

3.Application Compilation:
$ g++ nearest_pair_target_sum.cpp -std=c++14 -o Nearest_Pair_Target_Sum


4.Algorithm and Time/Space complexity:

 As we iterate over the vector atmost once, time complexity is O(n) where n is size of vector
 We are taking extra unordered_set for lookup , space complexity is O(n)


5.Output and few sample test run:

Input vectors and target:
    vector<int> input_vec_1{1,3,5,6,4,2};
    ValidateNearestPairTargetSum(input_vec_1,7);

    vector<int> input_vec_2{-9,3,-5,6,11,2,-3};
    ValidateNearestPairTargetSum(input_vec_2,6);

    vector<int> input_vec_3{5,6,2};
    ValidateNearestPairTargetSum(input_vec_3,9);

    vector<int> input_vec_4{1,2,3,-4,-2,-3,4,-1};
    ValidateNearestPairTargetSum(input_vec_4,0);

$ ./Nearest_Pair_Target_Sum
Resultant pair for target sum with min intervening numbers=(3,4) for target=7
Resultant pair for target sum with min intervening numbers=(-5,11) for target=6
No pair found for target sum for target=9
Resultant pair for target sum with min intervening numbers=(1,-1) for target=0
