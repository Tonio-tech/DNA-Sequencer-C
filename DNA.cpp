#include "DNA.h"

DNA::DNA() {
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

DNA::DNA(string name) {
    m_name = name;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

DNA::~DNA() {
    Node *curr = m_head;
    while(curr != nullptr) { //Iterates through and removes each node
        m_head = curr; //sets m_head to curr
        curr = curr ->m_next; //moves curr to next node
        delete m_head; //delete m_head;
    }
    //Resets all of the static linked list pointers
    m_head = nullptr; //Sets the pointer to point at nothing
    m_tail = nullptr; //Sets the pointer to point at nothing
    m_size = 0;
}

void DNA::InsertEnd(char data) {
    //inserts node at the ends of the list, not the beginning
    Node *temp = new Node();
    temp->m_data = data;

    if(m_head == nullptr){ //Checks to see if the linked list is empty
        m_head = temp; //Inserts the first node to the linked list
        m_tail = temp;
        //Inserts the first node to the linked list
    } else{
        m_tail->m_next = temp;
        m_tail = temp;
    }
    m_size++;
}

string DNA::GetName() {
    return m_name;
}

int DNA::GetSize() {
    return m_size;
}

void DNA::ReverseSequence() {
    Node *curr = m_head;
    Node *prev = nullptr;
    Node *next = nullptr;
    
    while(curr != nullptr) {
        // keep moving each node
        next = curr->m_next; 
        curr->m_next = prev;
        prev = curr;
        curr = next;
    }

    //update m_tail and m_head afterwards
    m_tail = m_head; 
    m_head = prev;
}

bool DNA::CompareSequence(DNA &evidence) {
    // two will traverse, one will stay at m_head in evidence, evidence -> m_head
    Node *sus_ptr1 = m_head; 
    Node *sus_ptr2 = m_head;
    Node *e_ptr = evidence.m_head;
    bool doesMatch = true;
    int counter = 0;

    while(sus_ptr1 != nullptr && e_ptr != nullptr && sus_ptr2 != nullptr) {
        //boolean flag to let us start over when we dont hit a match
        doesMatch = true; 
        counter = 0;
        sus_ptr1 = sus_ptr2;
        // have one ptr move to the next as like a checkpoint
        sus_ptr2 = sus_ptr2->m_next;

        while(sus_ptr1 != nullptr && e_ptr != nullptr && doesMatch) {
            if(sus_ptr1->m_data == e_ptr->m_data) {
                // if they match keep moving
                sus_ptr1 = sus_ptr1->m_next;
                e_ptr = e_ptr->m_next;
                counter++;
            } else {
                // set the evident ptr back to the start
                e_ptr = evidence.m_head;
                doesMatch = false;
            }
        }  
    }

    if(counter == evidence.GetSize()) { 
        return true; 
    } 
    
    return false;
}

char DNA::GetData(int nodeNum) {
    int counter = 0;
    Node *temp = m_head;

    // keeps counting until we hit the given number, then cout the data at the point
    while(counter != nodeNum) {
        temp = temp->m_next;
        counter++;
    }

    return temp->m_data;
}

ostream &operator<< (ostream &output, DNA &myDNA) {
    Node *temp = myDNA.m_head;
    while(temp != nullptr) {
      output << temp->m_data << "->";
      temp = temp->m_next;
    }
    output << "END";
    cout << endl;
    return output;
  }

