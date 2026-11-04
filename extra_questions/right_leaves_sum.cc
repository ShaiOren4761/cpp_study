#include <iostream>


 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int sumOfRightLeaves(TreeNode* root){
    if (!root) return 0;

    if (root->right && (!root->right->right && !root->right->left)){ // Right Leaf check
        return root->right->val + sumOfRightLeaves(root->left);// + sumOfRightLeaves(root->right);
    }
    else return sumOfRightLeaves(root->left) + sumOfRightLeaves(root->right);
}


int main() {
    auto test = [](const char* name, TreeNode* root, int expected) {
        int actual = sumOfRightLeaves(root);
        std::cout << name << ": "
             << "Expected = " << expected
             << ", Actual = " << actual
             << (actual == expected ? " [PASS]" : " [FAIL]")
             << "\n";
    };

    // Test 1: Empty tree
    test("Empty tree", nullptr, 0);

    // Test 2: Single node
    test("Single node", new TreeNode(5), 0);

    // Test 3: Only left child
    test("Only left child",
        new TreeNode(10, new TreeNode(4), nullptr), 0);

    // Test 4: Only right child
    test("Only right child",
        new TreeNode(10, nullptr, new TreeNode(7)), 7);

    // Test 5: Two children
    test("Two children",
        new TreeNode(10, new TreeNode(4), new TreeNode(7)), 7);

    // Test 6: Balanced tree
    //          10
    //        /    \
    //       4      12
    //      / \    /  \
    //     2   6  11  15
    test("Balanced tree",
        new TreeNode(10,
            new TreeNode(4, new TreeNode(2), new TreeNode(6)),
            new TreeNode(12, new TreeNode(11), new TreeNode(15))
        ), 21);

    // Test 7: Deep tree
    //       1
    //      /
    //     2
    //      \
    //       3
    //        \
    //         4
    test("Deep tree",
        new TreeNode(1,
            new TreeNode(2, nullptr,
                new TreeNode(3, nullptr, new TreeNode(4))
            ), nullptr
        ), 4);

    // Test 8: Negative values and zero
    //        1
    //       / \
    //      2   3
    //       \ / \
    //       -5 4 0
    test("Negative values",
        new TreeNode(1,
            new TreeNode(2, nullptr, new TreeNode(-5)),
            new TreeNode(3, new TreeNode(4), new TreeNode(0))
        ), -5);

    return 0;
}
