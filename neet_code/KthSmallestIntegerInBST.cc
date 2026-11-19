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

void inOrder(TreeNode* root, int* k, int* min);
int kthSmallest(TreeNode* root, int k);

int main(){
    
    TreeNode* t = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    cout << kthSmallest(t, 2) << "\n";
  
}

int kthSmallest(TreeNode* root, int k) {
    int min = 10001; // out of range val
    int* minptr = &min;
    int* kptr = &k;

    inOrder(root, kptr, minptr);

    return min;
}

void inOrder(TreeNode* root, int* k, int* min){
    if (!root || (*k)) return;
    
    inOrder(root->left, k, min);

    if (*k) {
        *min = root->val;
        (*k)--;
    }

    inOrder(root->right, k, min);
    
}