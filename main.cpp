// COMSC-210 | Lab 22 | Dan Pokhrel
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void delete_pos(int pos){
        if (!head) return; // Empty list
        if (pos < 0) {cout << "\nInvalid Index\n"; return;}

        int i = 0;
        Node* curr = head;
        while (curr && i!=pos){ // loop through list until index reaches pos
            curr = curr->next;
            i++;
        }
        if (!curr) return; // out of bounds

        // Handle head and tail
        if (curr == head){
            head = curr->next;
            head->prev = nullptr;
        }
        if (curr == tail){
            tail = curr->prev;
            tail->next = nullptr;
        }

        // update links node
        if (curr->prev && curr->next){
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
        // delete node
        delete curr;
    }

    void pop_front(){
        if (!head) return; // Empty list
        
        Node *tmp = nullptr;
        if (head->next){
            tmp = head->next;
            tmp->prev = nullptr;
        }
        delete head;
        head = tmp;
    }

    void pop_back(){
        if (!tail) return; // Empty list

        Node *tmp = nullptr;
        if (tail->prev){
            tmp = tail->prev;
            tmp->next = nullptr;
        }
        delete tail;
        tail = tmp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS; // random list size

    for (int i = 0; i < size; ++i) // populate list
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "\nEnter index to delete node: ";
    int i; cin >> i;
    list.delete_pos(i-1);
    cout << "\nList forward: ";
    list.print();

    cout << "\nDeleting head node...";
    list.pop_front();
    cout << "\nList forward: ";
    list.print();

    cout << "\nDeleting tail node...";
    list.pop_back();
    cout << "\nList forward: ";
    list.print();

    return 0;
}
