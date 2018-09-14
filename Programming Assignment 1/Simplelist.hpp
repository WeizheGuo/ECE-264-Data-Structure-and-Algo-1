//
//  Simplelist.hpp
//  Programming Assignment 1
//
//  Created by GUOWEIZHE on 4/15/18.
//  Copyright © 2018 GUOWEIZHE. All rights reserved.
//

#ifndef simpleList_h
#define simpleList_h

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class SimpleList{
protected:
    // three protected functions used in the virtual pop and push functions
    void insert_front(T element);
    void insert_end(T element);
    T remove_front();
    int size;
public:
    SimpleList(string listname);
    string name;
    //virtual functions that will be specified in derieved classes Stack and Queue
    virtual void push(T element) = 0;
    virtual T pop() = 0;
    //implement getsize function to use the protected data member "size"
    virtual int getsize()=0;
    
private:
    //use the nested node class to create node with a pointer and a value
    class Node {
    public:
        Node(Node* ptr, T element);
        Node* Nextnode;
        T Nodeval;
    };
    //declare the header node and the tail node of the list
     Node *head, *tail;
};


template <typename T>
class Stack : public SimpleList <T>{
public:
    // specify the virtual push and pop function in derieved class Stack
    Stack(string listname);
    void push (T element);
    T pop();
    int getsize();
};

template <typename T>
class Queue : public SimpleList <T>{
public:
    // specify the virtual push and pop function in derived class Queue
    Queue(string listname);
    void push (T element);
    T pop();
    int getsize();
};

#endif /* simpleList_h */

