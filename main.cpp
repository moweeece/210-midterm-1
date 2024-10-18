// COMSC-210 | Mauricio Espinosa | Midterm #1
// IDE Used: Visual Studio Code & Github

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// class declaration
class DoublyLinkedList {
// private member variables
private:
    struct Node {
        int data;
        Node* prev;   // pointer for previous node in the list
        Node* next;   // pointer for next node in the list
        // constructor which initializes each variable inside the Node struct
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // sets data equal to what val has stored
            prev = p;   // sets the previous pointer
            next = n;   // sets the next pointer
        }
    };

    Node* head;   // pointer for the first node of the list
    Node* tail;   // pointer for the last node of the list

// public member variables
public:
    // consturctor setting the head and tail nodes to nullptr. Avoids dangling pointers
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // method to insert a value after a specified position
    void insert_after(int value, int position) {
        if (position < 0) {   // input validation statement
            cout << "Position must be >= 0." << endl;  // error output
            return;   // exit the function
        }

        Node* newNode = new Node(value);  // create a new node and stores the value in the node
        if (!head) {   // if the list is empty or head is nullptr
            head = tail = newNode;   // both head and tail point to the new node
            return;   // exit the function
        }

        Node* temp = head;   // creates a temporary node and sets it to point to head
        for (int i = 0; i < position && temp; ++i)   // for loop to traverse the list
            temp = temp->next;  // move temp pointer to next node

        if (!temp) {  // if temp is nullptr meaning it reaches one past the end of the list
            cout << "Position exceeds list size. Node not inserted.\n";  // output statement
            delete newNode;  // delete the ndoe to free dynamic memory and avoid memory leak
            return;   // exit the function
        }

        // temp has stopped and we are inserting a node after temp so we need to do some "rewiring" / "replumbing" 
        newNode->next = temp->next;   // set the newNodes next pointer to the temp next node position
                                      // i.e. to the node that is going to be ahead of newNode
        newNode->prev = temp;         // set the newNodes prev pointer to where temp is pointing
                                      // i.e. to the node that is going to be behind newNode
        
        if (temp->next)   // if there is a node after where temp is pointing, meaning there is more nodes ahead..
            temp->next->prev = newNode;  // then set the "after" temp node's previous pointer to the newNode
        else
            tail = newNode;   // if temp was the last node then move tail to the newNode as that is the new tail
        temp->next = newNode;   // temp next pointer gets updated to point to newNode
    }

    void delete_val(int value) {
        if (!head) return;   // if the list is empty or head is nullptr

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}