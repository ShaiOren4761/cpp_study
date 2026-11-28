#include <iostream>
#include <vector>

using namespace std;



void recurse(const vector<int>& nums, vector<vector<int>>& result, vector<int>& combo, int target, int start, int sum){
    if (sum > target) return;
    if (sum == target){
        result.push_back(combo);
        return;
    }

    for (int i=start; i<nums.size(); i++){
        combo.push_back(nums[i]);

        recurse(nums, result, combo, target, i, sum + nums[i]);

        combo.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& nums, int target) {
    vector<vector<int>> result;
    vector<int> combinations;

    recurse(nums, result, combinations, target, 0, 0);

    return result;
}

void printCombinations(const vector<vector<int>>& results) {
    cout << "[ ";
    for (const auto& combination : results) {
        cout << "[ ";
        for (int val : combination)
            cout << val << " ";
        cout << "] ";
    }
    cout << "]\n";
}

int main(){
    vector<int> nums{2,3,5};
    int target = 7;

    printCombinations(combinationSum(nums, target));
    return 0;
}