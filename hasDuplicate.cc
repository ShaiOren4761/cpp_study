#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        unordered_set<int> seen;

        for (int val: nums){
            if (seen.count(val)) return true;
            else seen.insert(val);
        }

        return false;
    }
};


int main(){
    vector<int> input = {1,2,3,3};
    Solution s;
    cout << boolalpha;
    cout << s.hasDuplicate(input) << "\n";
}