//
//  main.cpp
//  NextPermutation
//
//  Created by Jason Jeon on 7/2/22.
//

// Next Permutation from LeetCode
// https://leetcode.com/explore/interview/card/google/59/array-and-strings/3050/

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

class Solution {
public:
    void nextPermutation(std::vector<int>& nums)
    {
        // if nums[i] is the biggest one, then return the smallest one
        
        // e.g. 178132 -> 178213 -> 178231 -> 178312 -> 178321 -> 181237
        
        // when change the number a, find the number larger than a but smallest among the right group
        
        int size { static_cast<int>(nums.size()) };
        
        std::vector<int> numbers (nums); // copy
        
        using pair_int = std::pair<int, int>;
        
        // ex)32
        
        for(int idx=size-2; idx>=0; --idx)
        {
            int num = numbers[idx];
            
            std::priority_queue<pair_int, std::vector<pair_int>, std::greater<pair_int>> bigger;
            
            for(int right=idx+1; right<size; ++right)
            {
                if( numbers[right] > num )
                    bigger.push({numbers[right], right});
            }
            
            // no need to exchange in this frame -> continue to expand the frame
            if( bigger.empty() )
                continue;
            
            
            // make the result, and break
            
            // e.g. 23
            
            assert(!bigger.empty());
            
            int new_idx = bigger.top().second;
            int next_num = bigger.top().first;
            
            numbers[new_idx] = std::move(numbers[idx]);
            numbers[idx] = next_num;
            std::sort(numbers.begin()+idx+1, numbers.end());
        
            assert(numbers.size() == size);
        
            break;
            
        }
        
        // the original nums is not changed (it was the biggest one)
        // -> make it smallest one
        if( nums == numbers )
        {
            std::sort(nums.begin(), nums.end());
        }
        else
        {
            nums.swap(numbers);
        }
        
    }
};

void print_vector_int(const std::vector<int> &v)
{
    for(auto x: v)
    {
        std::cout << x <<", ";
    }
    std::cout <<"\n";
}

void check_answer(std::vector<int> &&input, const std::vector<int> &&expected)
{
    Solution s;
    s.nextPermutation(input);
    
    std::cout << "Expected: ";
    print_vector_int(expected);
    std::cout << "Result: ";
    print_vector_int(input);
    
    if(input == expected)
    {
        std::cout << "Correct!\n";
    }
    else
    {
        std::cout << "Wrong!\n";
        assert(!"Wrong");
    }
    std::cout <<"============\n";
}
    
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
    // e.g. 178132 -> 178213 -> 178231 -> 178312 -> 178321 -> 181237
    
    check_answer({1,7,8,1,3,2}, {1,7,8,2,1,3});
    check_answer({1,7,8,2,1,3}, {1,7,8,2,3,1});
    check_answer({1,7,8,2,3,1}, {1,7,8,3,1,2});
    check_answer({1,7,8,3,2,1}, {1,8,1,2,3,7});
    check_answer({1,8,1,2,3,7}, {1,8,1,2,7,3});
    
    
    
    return 0;
}


/**
 A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

 For example, for arr = [1,2,3], the following are considered permutations of arr: [1,2,3], [1,3,2], [3,1,2], [2,3,1].
 The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

 For example, the next permutation of arr = [1,2,3] is [1,3,2].
 Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
 While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
 Given an array of integers nums, find the next permutation of nums.

 The replacement must be in place and use only constant extra memory.

  

 Example 1:

 Input: nums = [1,2,3]
 Output: [1,3,2]
 

 Example 2:
 
 Input: nums = [3,2,1]
 Output: [1,2,3]
 
 
 Example 3:

 Input: nums = [1,1,5]
 Output: [1,5,1]
  

 Constraints:

 1 <= nums.length <= 100
 0 <= nums[i] <= 100
 */
