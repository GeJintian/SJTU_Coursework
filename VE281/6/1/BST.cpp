//
// Created by 69009 on 2019/11/16.
//
#include <vector>
#include <iostream>
using namespace std;
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

void recoverTree(TreeNode *root){
    TreeNode *first = nullptr;
    TreeNode *second = nullptr;
    TreeNode *current_pointer = root;
    TreeNode *last_pointer = nullptr;
    while(current_pointer != nullptr){
        if(current_pointer->left != nullptr){
            TreeNode *temp = current_pointer->left;
            while(temp->right != nullptr && temp->right != current_pointer) temp = temp->right;
            if(temp->right == nullptr){
                temp->right = current_pointer;//Connect right child to current_pointer
                current_pointer = current_pointer->left;//Go through all the nodes on the left side
                continue;
            }
            else temp->right = nullptr;
        }
        if(last_pointer != nullptr){
            if(last_pointer->val > current_pointer->val){
                if(first == nullptr) first = last_pointer;
                second = current_pointer;
            }
        }
        last_pointer = current_pointer;
        current_pointer = current_pointer->right;
    }
    //Swap first and second
    int temp = first->val;
    first->val = second->val;
    second->val = temp;
}


bool verifySquenceOfST(vector<int> sequence){
    if(sequence.size() == 1 || sequence.size() == 0) return true;
    bool if_left = true;
    vector<int>::iterator iterator_root = sequence.end();
    iterator_root --;
    int root = *iterator_root;
    iterator_root --;
    vector<int>::iterator iterator_right = iterator_root;
    vector<int>::iterator iterator_left;
    for(iterator_left = iterator_right; ; iterator_left --){
        if(*iterator_left < root) break;
        if(iterator_left == sequence.begin()) {//No left subtree
            if_left = false;
            break;
        }
    }
    if(if_left){
        for(vector<int>::iterator check = iterator_left;;check--){
            if(*check > root){
                cout<<"Root is "<<root<<" CHECK is "<<*check;
                return false;
            }
            if(check == sequence.begin()) break;
        }
        iterator_left ++;
        vector<int>left_sub(sequence.begin(),iterator_left);
        iterator_right++;
        vector<int>right_sub(iterator_left,iterator_right);
        return verifySquenceOfST(left_sub) && verifySquenceOfST(right_sub);
    }
    else{
        iterator_right++;
        vector<int>right_sub(sequence.begin(),iterator_right);
    }
}

int main(){
    vector<int> data;
    int a[] = {6,9,7,14,31,12,10};
    int size = sizeof(a)/sizeof(int);
    cout<<"Input is: ";
    for(int i = 0; i < size; i++){
        cout<<a[i]<<" ";
        data.push_back(a[i]);
    }
    cout<<endl;
    bool judge = verifySquenceOfST(data);
    if(judge) cout<<"It is a post-order traversal of a BST"<<endl;
    else cout<<"It is not a post-order traversal of a BST"<<endl;
}