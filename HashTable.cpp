// Online C++ compiler to run C++ program online
#include <iostream>

struct Node {
    int key;
    int val;
    Node* next;
    Node(int k, int v){
        this->key = k;
        this->val = v;
        this->next = NULL;
    }
};

class HashTable{
    int i = 0;//loop variable used in multiple function, having it globally saves space.
    int size = 0;
    Node** table;
    int count =0;
    private:
    bool isPrime(int n){//helper function to check whether a number is prime, this will be used in nextPrime()
        if (n<=1) return false;
        else if (n == 2 || n == 3) return true;
        else if (n%2 == 0) return false;
        else{
            for(i=3;i<n;i++){
                if (n%i == 0) return false;
            }
        }
        return true;
    }
    
    int nextPrime(int n){//helper function to return the next prime interger after a given number, this will be necessary to compute the new size of the HashTable for resizing.
        i = n+1;
        while(!isPrime(i)){
            i++;
        }
        return i;
    }
    
    void resize(){
        int new_size = nextPrime(size*2);
        Node** new_table = new Node*[new_size];
        //initializing every chain in our list to be NULL
        for(i=0;i<new_size;i++) new_table[i] = NULL;
        //Now we must rehash everything into the new table
        for (int i = 0; i < size; i++) {
            Node* node = table[i];
            while (node != NULL) {
                int new_index = node->key % new_size;//rehash each new node
                Node* new_node = new Node(node->key, node->val);//this will be inserted into our table
                new_node->next = new_table[new_index]; 
                new_table[new_index] = new_node;
                node = node->next;  // Move to the next node
            }
        }
        size = new_size;
        table = new_table;
    }

    public:

    HashTable(int s){//constructor to initialize
        size = s;
        table = new Node*[size];
        for (int i = 0; i < size; i++) {
            table[i] = NULL;
        }
        count = 0;
    }

    void insert(int v){
        if((count/size)>0.8)//if we exceed the given threshold
            resize();
        int k = v;
        i = k%size;//index obtained
        Node* curr = table[i];
        while (curr!= NULL){
            if (curr->key == k){
                std::cout<<"Duplicate key insertion is not allowed"<<std::endl;
                return;//exit out
            } 
            curr = curr->next;//if key is found
        }


        //if key is not found, we insert a new node at the beginning.
        Node* new_node = new Node(k, v);
        new_node->next = table[i];
        table[i] = new_node;
        count++;

    }

    void remove(int k){
        i = k%size;
        Node* node = table[i];
        Node* prev = nullptr;
        while (node != nullptr) {
            if (node->key == k) {
                if (prev == nullptr) {
                    table[i] = node->next;  // Remove the head node
                } else {
                    prev->next = node->next;  // Remove the node from the chain
                }
                delete node;  // Delete the node
                count--;  // Decrement the count of elements
                return;
            }
            prev = node;
            node = node->next;
        }

        // Key not found
        std::cout << "Key not found" << std::endl;
    }

    int search(int v){
        for (i = 0; i < size; i++) {
        Node* node = table[i];
        while (node != nullptr) {
            if (node->val == v) {
                return i+1; 
            }
            node = node->next;
        }
    }

    return -1;//if val is not found
    }

    void printTable() {
    for (int i = 0; i < size; i++) {
        if (table[i] == NULL) {
            std::cout << "- "; 
        } else {
            Node* node = table[i];
            while (node != NULL) {
                std::cout << node->val << " ";
                node = node->next; 
            }
            // std::cout<< "- ";
        }
    }
    std::cout<< std::endl;
    }
};