#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<vector<int>> levelOrder(TreeNode* root) {

    // init root -> [[root]], pointers -> left, right of root

    // iterate -> create new vector<int> of vals, add final vector<int> to output. collect pointers of each node for next iteration.
    // while pointers - run.

    if (!root) return {};

    vector<vector<int>> levels;
    vector<int> vals;
    levels.emplace_back(root->val);

    vector<TreeNode*> pointers;
    if (root->left) pointers.push_back(root->left);
    if (root->right) pointers.push_back(root->right);
    pointers.push_back(nullptr); // sentinel

    while (!pointers.empty()){
        while (pointers.front() != nullptr){
            vals.push_back(pointers.front().val);
        }
        vals.clear();
    }

    return levels;
}


int main(){
    auto printLevels = [](const vector<vector<int>>& levels) {
        cout << "[";
        for (size_t i = 0; i < levels.size(); i++) {
            if (i > 0) cout << ",";
            cout << "[";
            for (size_t j = 0; j < levels[i].size(); j++) {
                if (j > 0) cout << ",";
                cout << levels[i][j];
            }
            cout << "]";
        }
        cout << "]";
    };

    auto test = [&](const char* name, TreeNode* root,
                    vector<vector<int>> expected) {
        auto actual = levelOrder(root);
        cout << name << ": ";
        printLevels(actual);
        cout << (actual == expected ? " [PASS]" : " [FAIL]");
        cout << "\n";
    };

    // Test 1: Empty tree
    test("Empty", nullptr, {});

    // Test 2: Single node
    test("Single",
        new TreeNode(5),
        {{5}});

    // Test 3: Two children
    test("Two children",
        new TreeNode(1, new TreeNode(2), new TreeNode(3)),
        {{1}, {2, 3}});

    // Test 4: Classic example
    //        3
    //       / \
    //      9  20
    //        /  \
    //       15   7
    test("Classic",
        new TreeNode(3,
            new TreeNode(9),
            new TreeNode(20, new TreeNode(15), new TreeNode(7))),
        {{3}, {9, 20}, {15, 7}});

    // Test 5: Left-skewed
    test("Left skewed",
        new TreeNode(1,
            new TreeNode(2, new TreeNode(3), nullptr),
            nullptr),
        {{1}, {2}, {3}});

    // Test 6: Right-skewed
    test("Right skewed",
        new TreeNode(1, nullptr,
            new TreeNode(2, nullptr, new TreeNode(3))),
        {{1}, {2}, {3}});

    // Test 7: Sparse tree
    //        1
    //       / \
    //      2   3
    //       \ /
    //       4 5
    test("Sparse",
        new TreeNode(1,
            new TreeNode(2, nullptr, new TreeNode(4)),
            new TreeNode(3, new TreeNode(5), nullptr)),
        {{1}, {2, 3}, {4, 5}});

    // Test 8: Negative values
    test("Negative",
        new TreeNode(0,
            new TreeNode(-3, new TreeNode(-10), nullptr),
            new TreeNode(8, nullptr, new TreeNode(12))),
        {{0}, {-3, 8}, {-10, 12}});
}

