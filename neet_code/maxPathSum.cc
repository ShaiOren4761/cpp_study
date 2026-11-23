#include <iostream>
#include <climits>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int maxPathSum(TreeNode* root);

int main(){
    
    TreeNode* t = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    cout << maxPathSum(t) << "\n";
  
}

int maxPathSum(TreeNode* root){
    if (!root) return 0;

    pair<int,int> solution = solve(root);
    return max(solution.first, solution.second);
}

pair<int,int> solve(TreeNode* root){
    if (!root) return {0, INT_MIN};
    // {Extend path, Overall max}
    pair<int,int> left = solve(root->left);
    pair<int,int> right = solve(root->right);
    int extend = max(root->val, max(root->val+left.first, root->val+right.first));
    int overall = max(max(root->val + left.first + right.first, max(left.second, right.second)), extend);
    return pair<int,int>{extend,overall};
}


/*
must extend - 
take the current nodes val and add it to both existing paths in left and right tree, take the max result. Meaning we "join" the best path we can. 
So it's max(current.val + left.extend, current.val + right.extend, current.val)

overall best -
max(current.val + left.extend, current.val + right.extend, current.val + left.extend + right.extend, current.val, left.best, right.best)
meaning, just take the height number.
*/