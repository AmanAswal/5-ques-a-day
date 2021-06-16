#include<iostream>
#include<vector>
#include<stack>

using namespace std;

// day 1

// 968. Binary Tree Cameras
// -1 : is camera required
// 0 : i'm covered
// 1 : i'm a camera

int cameras = 0;
int minCameraCover_(TreeNode* node) {
    if(node == nullptr) return 0;

    int lans = minCameraCover_(node->left);
    int rans = minCameraCover_(node->right);

    if(lans == -1 || rans == -1){   // kisibhi child ko camera required hai to return -1
        cameras++;
        return 1;
    }

    if(lans == 1 || rans == 1){ // koi sa bhi child camera hai
        return 0;
    }

    // if(lans == 0 || rans == 0)
    return -1;
}

int minCameraCover(TreeNode* root) {
    if(root->left == nullptr && root->right == nullptr) return 1;
    int ans = minCameraCover_(root);
    return (ans == -1) ? cameras + 1 : cameras;
}

// 337. House Robber III
// {robbing, not robbing}
vector<int> rob_(TreeNode* root) {
    if(root == nullptr)
        return {0,0};

    vector<int> lans = rob_(root->left);
    vector<int> rans = rob_(root->right);

    vector<int> myAns(2,0);

    myAns[0] = lans[1] + root->val + rans[1];
    myAns[1] = max(lans[0], lans[1]) + max(rans[0], rans[1]);

    return myAns;
}

int rob(TreeNode* root) {
    if(root == nullptr) return 0;
    vector<int> ans = rob_(root);
    return max(ans[0], ans[1]);
}

// 230. Kth Smallest Element in a BST
void kthSmallest_(TreeNode* root, int k, int &count, int &res){
    if(root == nullptr || count >= k) return;

    kthSmallest_(root->left, k, count, res);
    count++;
    
    if(count == k){
        res = root->val;
        return;
    }
    kthSmallest_(root->right, k, count, res);

}

int kthSmallest(TreeNode* root, int k) {
    int count = 0;
    int res = -1;
    kthSmallest_(root, k, count, res);
    return res;
}

// better method
void insertAllLeft(stack<TreeNode*> &st, TreeNode* node){
    while(node != nullptr){
        st.push(node);
        node = node->left;
    }
}

int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> st;
    insertAllLeft(st, root);

    while(k-- > 1){
        TreeNode* rn = st.top(); st.pop();
        insertAllLeft(st, rn->right);
    }

    return st.size() != 0 ? st.top()->val : -1;
}

// best method
// use morris traversal


// morris traversal related questions =>
// 1. kth smallest
// 2. https://www.geeksforgeeks.org/find-median-bst-time-o1-space/

// day 2

// 1372. Longest ZigZag Path in a Binary Tree
class pair{
public:
    int forwardSlope = -1;
    int backwardSlope = -1;
    int maxLen = 0;

    pair(){}
};

pair longestZigZag_(TreeNode* root){
    if(root == nullptr) return pair();

    pair left = longestZigZag_(root->left);
    pair right = longestZigZag_(root->right);

    pair myAns;
    myAns.maxLen = max(max(left.maxLen, right.maxLen), max(left.backwardSlope, right.forwardSlope) + 1);

    myAns.forwardSlope = left.backwardSlope + 1;
    myAns.backwardSlope = right.forwardSlope + 1;

    return myAns;
}

int longestZigZag(TreeNode* root) {
    pair ans = longestZigZag_(root);
    return ans.maxLen;
}

// method 2
// {forwardSlope, backwardSlope}
int maxLen = 0;
vector<int> longestZigZag_(TreeNode* root) {
    if(root == nullptr) return {-1, -1};

    vector<int> left = longestZigZag_(root->left);
    vector<int> right = longestZigZag_(root->right);

    vector<int> myAns(2,0);
    
    maxLen = max(maxLen, max(left[1], right[0]) + 1);

    myAns[0] = left[1] + 1;
    myAns[1] = right[0] + 1;

    return myAns;
}

int longestZigZag(TreeNode* root) {
    if(root == nullptr) return 0;
    vector<int> ans = longestZigZag_(root);
    return maxLen;
}

// 653. Two Sum IV - Input is a BST
void addAllLeft(TreeNode* root, stack<TreeNode*> &st){
    if(root == nullptr) return;
    TreeNode* curr = root;

    while(curr != nullptr){
        st.push(curr);
        curr = curr->left;
    }
}

void addAllRight(TreeNode* root, stack<TreeNode*> &st){
    if(root == nullptr) return;
    TreeNode* curr = root;

    while(curr != nullptr){
        st.push(curr);
        curr = curr->right;
    }
}

bool findTarget(TreeNode* root, int k) {
    if(root == nullptr) return false;

    stack<TreeNode*> lst;
    stack<TreeNode*> rst;

    addAllLeft(root, lst);
    addAllRight(root, rst);

    while(lst.top()->val < rst.top()->val){
        int sum = lst.top()->val + rst.top()->val;

        if(sum > k){
            TreeNode* rn = rst.top(); rst.pop();
            addAllRight(rn->left, rst);
        }
        else if(sum < k){
            TreeNode* rn = lst.top(); lst.pop();
            addAllLeft(rn->right, lst);
        }
        else{
            return true;
        }
    }
    return false;
}

// 437. Path Sum III
int ans = 0;
void pathSumIII(TreeNode* root, int targetSum, unordered_map<int,int> &map, int prefixSum) {
    if(root == nullptr) return;

    prefixSum += root->val;

    ans += map.find(prefixSum - targetSum) != map.end() ? map[prefixSum - targetSum] : 0;
    
    map[prefixSum]++;

    pathSumIII(root->left, targetSum, map, prefixSum);
    pathSumIII(root->right, targetSum, map, prefixSum);

    map[prefixSum]--;
}

int pathSum(TreeNode* root, int targetSum) {
    // prefix sum, frequency
    unordered_map<int,int> map;
    map[0] = 1;

    pathSumIII(root, targetSum, map, 0);
    return ans;
}

// 662. Maximum Width of Binary Tree
class pair{
public:
    TreeNode* node = nullptr;
    long unsigned w = 0;

    pair(TreeNode* node, long unsigned w){
        this->node = node;
        this->w = w;
    }
};

int widthOfBinaryTree(TreeNode* root) {
    if(root == nullptr) return 0;
    queue<pair> que;
    que.push(pair(root,1));

    long unsigned ans = 0;

    while(que.size() != 0){
        int size = que.size();
        long unsigned fi = que.front().w;
        long unsigned li = que.front().w;

        while(size-- > 0){
            pair rp = que.front(); que.pop();
            TreeNode* node = rp.node;
            long unsigned w = rp.w;
            li = w;

            if(node->left != nullptr)
                que.push(pair(node->left, 2 * w));

            if(node->right != nullptr)
                que.push(pair(node->right, 2 * w + 1));
        }

        ans = max(ans, li - fi + 1);
    }

    return ans;
}

// 226. Invert Binary Tree
TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr) return nullptr;
    invertTree(root->left);
    invertTree(root->right);        

    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    return root;
}

// day 3

// 617. Merge Two Binary Trees
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if(root1 == nullptr || root2 == nullptr)
        return root1 != nullptr ? root1 : root2;

    root1->val += root2->val;

    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);

    return root1;
}

// 938. Range Sum of BST
// TC -> O(n)
int rangeSumBST(TreeNode* root, int low, int high) {
    if(root == nullptr) return 0;
    int count = 0;

    if(root->val >= low && root->val <= high){
        count += root->val;
    }
        
    count += rangeSumBST(root->left, low, high);
    count += rangeSumBST(root->right, low, high);
    return count;
}

// best TC-> O(logn), avg and worst -> O(n)
int rangeSumBST(TreeNode* root, int low, int high) {
    if(root == nullptr) return 0;
    int count = 0;

    if(root->val < high)
        count += rangeSumBST(root->right, low, high);
    if(root->val > low)
        count += rangeSumBST(root->left, low, high);

    if(root->val >= low && root->val <= high)
        count += root->val;
    return count;
}

// 1038. Binary Search Tree to Greater Sum Tree
void bst(TreeNode* root, int &sum) {
    if(root == nullptr) return;

    bst(root->right, sum);
    sum += root->val;
    root->val = sum;
    bst(root->left, sum);
}

TreeNode* bstToGst(TreeNode* root) {
    if(root == nullptr) return root;
    int sum = 0;
    bst(root, sum);
    return root;
}

// 129. Sum Root to Leaf Numbers
int ans = 0;
void sumNumbers_(TreeNode* root, int val) {
    if(root == nullptr) return;

    val *= 10;
    val += root->val;

    if(root->left == nullptr && root->right == nullptr){
        ans += val;
        return;
    }

    sumNumbers_(root->left, val);
    sumNumbers_(root->right, val);
}

int sumNumbers(TreeNode* root) {
    if(root == nullptr) return 0;
    sumNumbers_(root, 0);
    return ans;
}

// 897. Increasing Order Search Tree
// tc - O(n), sc - O(n)
vector<TreeNode*> list;
TreeNode* increasingBST(TreeNode* root) {
    if(root == nullptr) return nullptr;
    
    inorder(root);

    for(int i = 0; i < list.size() - 1; i++){
        list[i]->right = list[i + 1];
        list[i]->left = nullptr;
    }

    list.back()->left = nullptr;
    list.back()->right = nullptr;
    return list[0];
}

void inorder(TreeNode* root){
    if(root == nullptr) return;

    inorder(root->left);
    list.push_back(root);
    inorder(root->right);
}

// better
// tc -> O(n), sc -> O(h) recursive space
TreeNode* curr = nullptr;
TreeNode* increasingBST(TreeNode* root) {
    if(root == nullptr) return nullptr;
    TreeNode* res = new TreeNode(-1);
    curr = res;
    inorder(root);

    return res->right;
}

void inorder(TreeNode* root){
    if(root == nullptr) return;

    inorder(root->left);
    root->left = nullptr;
    curr->right = root;
    curr = root;
    inorder(root->right);
}

int main(){
    return 0;
}