#include<unordered_set>
#include<vector>
#include<cstdlib>
#include<iostream>
using namespace std;

/* As we iterate over the vector atmost once, time complexity is O(n) where n is size of vector
 * We are taking extra unordered_set for lookup , space complexity is O(n)
 */

vector<int> NearestPairTargetSum(const vector<int>& input_vec, int target)
{
    vector<int> result_sum_pair;
    unordered_set<int> already_processed_items;
    for(const auto& item: input_vec)
    {
        auto iter_find = already_processed_items.find(target-item);
        if(iter_find != already_processed_items.end())
        {
            if(result_sum_pair.empty())
            {
                result_sum_pair.push_back(*iter_find);
                result_sum_pair.push_back(item);
            }
            else
            {
                auto intervening_numbers_curr = abs(*iter_find - item); 
                auto intervening_numbers_stored = abs(result_sum_pair[0] - result_sum_pair[1]);
                if (intervening_numbers_curr < intervening_numbers_stored)
                {
                    result_sum_pair[0] = *iter_find;
                    result_sum_pair[1] = item;
                }
            }
        }
        else
        {
            already_processed_items.insert(item);
        }
    }
    return result_sum_pair;
}

void ValidateNearestPairTargetSum(const vector<int>& input_vec, int target)
{
    auto res_vec = NearestPairTargetSum(input_vec,target);
    if (!res_vec.empty())
    {
        std::cout << "Resultant pair for target sum with min intervening numbers=(" << res_vec[0] << "," <<res_vec[1] << ") for target=" << target << "\n";
    }
    else
    {
        std::cout << "No pair found for target sum for target=" << target << "\n" ;
    }
}

int main()
{
    vector<int> input_vec_1{1,3,5,6,4,2};
    ValidateNearestPairTargetSum(input_vec_1,7);

    vector<int> input_vec_2{-9,3,-5,6,11,2,-3};
    ValidateNearestPairTargetSum(input_vec_2,6);

    vector<int> input_vec_3{5,6,2};
    ValidateNearestPairTargetSum(input_vec_3,9);

    vector<int> input_vec_4{1,2,3,-4,-2,-3,4,-1};
    ValidateNearestPairTargetSum(input_vec_4,0);
    return 0;
}
