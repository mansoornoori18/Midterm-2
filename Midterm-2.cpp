#include <iostream>   // COMSC-210 | Exam-Midterm-2 | Mansoor Noori
#include <fstream>    // IDE Visual Studio,
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
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
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;
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
        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
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

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(string v) {
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
        Node* temp = head;
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
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }
    // Return front value as string or empty if list empty
    string front(){
        return head ? head->data : "";
    }
    // Return back value as string or empty if list empty
    string back(){
        return tail ? tail->data : "";
    }
    int size(){
        int count = 0;
        Node* current = head;
        while (current){
            count++;
            current = current->next;
        }
         return count;   // Return number of nodes in the list
    }
    string get(int pos){
        Node* current = head;
        int i = 1;
        while (current && i < pos){
            current = current->next;
            i++;
        }
        return current ? current->data : "";  // Return value at pos as string or empty if invalid
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

    srand(time(0));    // Seed random number generator to get different results each run

    // Load customer names from the file "names.txt" into a vector<string>
    vector<string> names;
    ifstream fin("names.txt");
    string line;
    while (getline(fin, line)){
        if (!line.empty())
        names.push_back(line); // Add non-empty names to vector
    }
    fin.close();

    DoublyLinkedList lineList;  // Create the doubly linked list to represent the line

    // Store opens - add 5 customers immediately
    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; i++){
        string name = names[rand() % names.size()];  // Pick a random name
        lineList.push_back(name);                     // Add to the end of the line
        cout << "    " << name << " joins the line" << endl;
    }
    cout << "    Resulting line:" << endl;
    lineList.print();  // Show initial line

    // Run simulation for time steps 2 through 20
    for (int t = 2; t <= 20; t++){
        cout << "Time step #" << t << ":" << endl;

        // 40% chance the front customer is served and leaves the line
        int prob = rand() % 100 + 1;
        if (prob <= 40 && lineList.size() > 0){
            string served = lineList.front();  // Get the front customer name
            lineList.pop_front();               // Remove them from line
            cout << "    " << served << " is served" << endl;
        }
        // 60% chance a new customer joins the end of the line
        prob = rand() % 100 + 1;
        if (prob <= 60){
            string name = names[rand() % names.size()];
            lineList.push_back(name);
            cout << "    " << name << " joins the line" << endl;
        }
        
    }

    return 0;
}