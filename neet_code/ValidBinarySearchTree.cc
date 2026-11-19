#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool isValidBST(TreeNode* root);
void BSTtoVector(TreeNode* root, vector<int>*v);



int main(){
    
    TreeNode* t = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    isValidBST(t);
  
}



bool isValidBST(TreeNode* root) {
    vector<int>v;

    BSTtoVector(root, &v);
    
    for (int i=0; i<v.size()-1; i++){
        if (v[i] > v[i+1]) return false;
    }

    return true;
}

void BSTtoVector(TreeNode* root, vector<int>*v){
    if (!root) return;

    BSTtoVector(root->left, v);
    
    v->push_back(root->val);
    
    BSTtoVector(root->right, v);

}
