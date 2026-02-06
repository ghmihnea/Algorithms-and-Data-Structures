#include <iostream>
using namespace std;

class Node {
    public:
    int key;
    int value;
    /*elements of hashtables are of form: [key, value]*/
    Node (int key, int value) {
        this->key = key;
        this->value = value;
    };
};
class HashTable {
    private:
        Node **arr;
        /*array of pointers to Nodes <=> the hashtable*/
        int maxSize;
        int currentSize;
    public:
        HashTable(int newSize = 11)
        /*constructor that initilizes the hash table with the given size
        (default = 11)*/ 
        {
            maxSize = newSize;
            currentSize = 0;

            arr = new Node*[maxSize];
            /*dinamically allocating array for the hash table*/
            for(int i = 0; i < maxSize; i ++) {
                arr[i] = nullptr;
            }            
        }
        int hashCode(int key) {
            return key % maxSize;
            /*returns index by performing the operation above*/
        }
        void insertNode(int key, int value) {
            if (currentSize == maxSize) {
                cout << "Table overflow";
                return;
            }
            int i = 0;
            int hashpos;

            do {
                hashpos = (hashCode(key) + i) % maxSize;
                /*calculating index with linear probing:
                trying the hash position first, proceeding to probe forward if
                needed*/

                if(arr[hashpos] == nullptr) {
                    arr[hashpos] = new Node(key, value);
                    currentSize ++;
                    return;
                }
                else if (arr[hashpos]->key == key) 
                /*particular case: if the key already exists we update
                the value*/
                {
                    arr[hashpos]->value = value;
                    return;
                }
                i ++;
            } while (i < maxSize);
            /*keep probing until we find an empty spot or remain
            without slots*/
            cout << "Element couldn t have been inserted to the list";
        }
        int get(int key) {
            int i = 0;
            int hashpos;

            do {
                hashpos = (hashCode(key) + i) % maxSize;

                if(arr[hashpos] == nullptr) {
                    return -1;
                }
                else if (arr[hashpos]->key == key) {
                    return arr[hashpos]->value;
                }
            } while(i < maxSize);
            cout << "no element found at the specified key";
            return -1;
        }
        bool isEmpty(){
            return currentSize == 0;
        }
};
int main() {
    HashTable hashtbl(11);

    hashtbl.insertNode(1, 10);
    hashtbl.insertNode(2, 20);
    hashtbl.insertNode(3, 30);
    hashtbl.insertNode(1, 40);

    cout << "value for key 1: " << hashtbl.get(1) << endl;
    cout << "value for key 3: " << hashtbl.get(3) << endl;

    return 0;
}
