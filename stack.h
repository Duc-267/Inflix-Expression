#ifndef STACK_H
#define STACK_H

#include<iostream>
using namespace std;

struct Node {
    string s = "\n";
    Node* next = NULL;
};

class Stack {
private:
    Node* head;
public:
    Stack() {
        head = NULL;
    }
    string top()
    {
        if (!head)
            return "";
        return head->s;
    }
    void pop() {
        if (!head)
            return;
        if (!head->next) {
            delete head;
            head = NULL;
            return;
        }
        Node* temp = head->next;
        delete head;
        head = temp;
    }
    void push(string s) {
        Node* temp = new Node;
        if (temp == 0) {
            return;
        }
        if (head == NULL) {
            temp->s = s;
            temp->next = NULL;
            head = temp;
            return;
        }
        else {
            temp->s = s;
            temp->next = head;
            head = temp;
            return;
        }
    }
    bool empty() {
        if (head == NULL)
            return 1;
        else return 0;
    }
};

struct NodeFloat
{
    float s;
    NodeFloat* next = NULL;
};

class StackFloat{
private:
    NodeFloat* head;
public:
    StackFloat() {
        head = NULL;
    }
    float top()
    {
        if (!head)
            return 234843.7243432;
        return head->s;
    }
    void pop() {
        if (!head)
            return;
        if (!head->next) {
            delete head;
            head = NULL;
            return;
        }
        NodeFloat* temp = head->next;
        delete head;
        head = temp;
    }
    void push(float s) {
        NodeFloat* temp = new NodeFloat;
        if (temp == 0) {
            return;
        }
        if (head == NULL) {
            temp->s = s;
            temp->next = NULL;
            head = temp;
            return;
        }
        else {
            temp->s = s;
            temp->next = head;
            head = temp;
            return;
        }
    }
    bool empty() {
        if (head == NULL)
            return 1;
        else return 0;
    }
};

#endif