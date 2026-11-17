#include "queue.h"
#include <iostream>

using namespace std;

// Node constructor
Node::Node(int iD, int cars, int time) {
    info.trafficLightID = cars;
    info.amountOfCars = iD;
    info.timeStamp = time;
    next = nullptr;
}

// Queue constructor
Queue::Queue() { 
    rear = nullptr; 
}

// Check if queue is empty
bool Queue::is_empty() {
    if (!rear)
        return true;
    return false;
}

// Enqueue data
void Queue::enqueue(trafficPthread val) {
    Node* newNode = new Node(val.amountOfCars, val.trafficLightID, val.timeStamp);
    if (!newNode) {
        cout << "Queue Overflow!\n";
        return;
    }

    if (this->is_empty()) {
        newNode->next = newNode;
        rear = newNode;
    } else {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }
}

// Dequeue data
void Queue::dequeue() {
    if (this->is_empty()) {
        cout << "Queue Underflow\n";
        return;
    }

    if (rear->next == rear) {
        delete rear;
        rear = nullptr;
    } else {
        Node* temp = rear->next;
        rear->next = temp->next;
        delete temp;
    }
}

// Peek at the first element
trafficPthread Queue::peek() {
    trafficPthread empty_traffic{ 0, 0, 0};
    if (this->is_empty()) {
        cout << "Queue is Empty!" << endl;
        return empty_traffic;
    }

    return rear->next->info;
}

// Print queue elements
void Queue::print() {
    if (!rear) {
        cout << "Queue is Empty!" << endl;
        return;
    }

    Node* temp = rear->next;

    do {
        cout << temp->info.trafficLightID << " " << temp->info.timeStamp  << " " << temp->info.amountOfCars << " ";
        temp = temp->next;
    } while (temp != rear->next);

    cout << endl;
}