#include <iostream>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int n) {
        data = n;
        left = NULL;
        right = NULL;
    }
};
struct ListNode {
    int data;
    ListNode* next;
    ListNode(int x) {
        data = x;
        next = NULL;
    }
};
void inorderTraversal(TreeNode* root, ListNode*& head, ListNode*& tail) {
    if(!root) return;

    inorderTraversal(root->left, head, tail);
    /*traversing until reaching the leftmost node(the smallest in value)*/

    ListNode* newNode = new ListNode(root->data);
    /*creating a list node with the value of the smallers
    node*/
    if(!head) {
        head = tail = newNode;
        /*if the list we are creating is empty
        we point both the head and tail to the
        new node*/
    } else {
        tail->next = newNode;
        tail = newNode;
        /*otherwise we add the element at the end
        of the list and also update the value of tail witb its value*/
    }
    inorderTraversal(root->right, head, tail);
}
ListNode* BSTtoLinkedList(TreeNode* root) {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    inorderTraversal(root, head, tail);
    return head;
    /*this function makes use of the recursive function
    above to create the linked list*/
}
void printList(ListNode* head) {
    while(head) {
        cout << head->data << "->";
        head = head->next;
    }
    cout << "NULL" << endl; 
}
void deleteTree(TreeNode* root) {
    if(!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
void deleteList(ListNode* head) {
    while(head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}
int main() {

    TreeNode* root = new TreeNode(8);

    root->left = new TreeNode(3);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(6);

    root->right = new TreeNode(11);
    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(13);

    ListNode* topOfList = BSTtoLinkedList(root);

    printList(topOfList);

    deleteTree(root);
    deleteList(topOfList);
    /*deleting the dinamically allocated memory*/

    return 0;
}
