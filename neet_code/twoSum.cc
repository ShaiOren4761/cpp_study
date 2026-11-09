#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


vector<int> twoSum(vector<int>& nums, int target) {
    
    unordered_map<int,int> seen; // {target-val : index}

    for (int i=0; i<nums.size(); i++){
        auto other_index = seen.find(nums[i]);

        if (other_index != seen.end()){ // Valid pair found
            vector<int>indices;
            indices.push_back(other_index->second); // Earlier valid pair
            indices.push_back(i); // Current element
            return indices;
        }
        else{ // No valid pair exists, add to map
            seen[target - nums[i]] = i;
        }
    }
    return {};
}


int main(){
    vector<int> nums = {3,4,5,6};
    int target = 7;
   
    auto output = twoSum(nums,target); 
    cout << output[0] << " " << output[1] << "\n";
}