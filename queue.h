#pragma once

#include <iostream>
#include <string>

using namespace std;

struct trafficPthread{
    int amountOfCars;
    int trafficLightID;
    int timeStamp;
};

class Node {
public:
    trafficPthread info;
    Node* next;

    Node(int iD, int cars, int time);
};

class Queue {
private:
    Node* rear;

public:
    Queue();
    bool is_empty();
    void enqueue(trafficPthread val);
    void dequeue();
    void insertAt();
    void delete_at();
    trafficPthread peek();
    void print();
};