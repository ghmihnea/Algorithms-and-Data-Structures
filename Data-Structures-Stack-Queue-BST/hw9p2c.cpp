#include <iostream>

using namespace std;

struct ListNode {
    int data;
    ListNode* next;
    ListNode(int x) {
        data = x;
        next = NULL;
    }
};
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};
TreeNode* LinkedListToBst(ListNode* head) {
    if(!head) return NULL;
    /*base case 1: list is empty*/

    if(!head->next) {
        return new TreeNode(head->data);
    }
    /*base case 2: list has one element so
    we return just the root pointing at 
    2 null pointers*/

    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* prev = NULL;
    /*creating 2 pointers for
    list traversals: one fast and one slow(fast - 1)
    that will store the middle of
    the list when fast reaches the end*/

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        prev = slow;
        /*after the loop is
        executed prev will 
        point before the end of the list*/
        slow = slow->next;
    }
    if(prev) {
        prev->next = NULL;
        /*disconnecting the left half of the list
        from thw mdiddle by setting prev->next to NULL*/
        
    }
    TreeNode* root = new TreeNode(slow->data);
    /*the root will be represented by the data from the
    middle*/

    root->left = LinkedListToBst(head);
    /*buliding the left subtree*/
    root->right = LinkedListToBst(slow->next);
    /*building the right subtree*/

    return root;
}
void inorderTraversal(TreeNode* root) {
    if(!root) return;
    /*if the list is empty there is nothing to return*/

    inorderTraversal(root->left);
    /*traversing the left side of the list*/
    cout << root->data << " ";
    /*also including the root in our taversal*/
    inorderTraversal(root->right);
    /*traversing the right side of the list*/
}
int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(3);
    head->next->next = new ListNode(5);
    head->next->next->next = new ListNode(7);
    head->next->next->next->next = new ListNode(9);
    head->next->next->next->next->next = new ListNode(11);

    TreeNode* BSTRoot = LinkedListToBst(head);

    cout << "in order traversal of the BST: ";
    inorderTraversal(BSTRoot);
    cout << endl;

    return 0;
}
