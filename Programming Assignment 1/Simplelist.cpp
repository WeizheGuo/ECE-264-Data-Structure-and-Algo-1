//
//  Simplelist.cpp
//  Programming Assignment 1
//
//  Created by GUOWEIZHE on 4/15/18.
//  Copyright © 2018 GUOWEIZHE. All rights reserved.
//

#include "Simplelist.hpp"
#include <stdio.h>

//simpleList constructor and its attributes
template <typename T>
SimpleList<T>::SimpleList (string listname) {
    size = 0;
    name = listname;
    head = nullptr;
    tail = nullptr;
}

//define the Node class constructor
template<typename T>
SimpleList<T>::Node::Node(Node *ptr, T element) {
    //The pointer points to the nextnode and the node value equals to the type T input
    this->Nextnode = ptr;
    this->Nodeval = element;
}

//implement the following functions: insert_front, insert_end, remove_front
template <typename T>
void SimpleList<T>::insert_front (T element) {
    //create a new node points to the head of the SimpleList
    Node *newNode = new Node(head, element);
    //redefine the head to be the new node
    head = newNode;
    size++;
}

template <typename T>
void SimpleList<T>::insert_end (T element) {
    //create a new node with a nullptr
    Node *newNode = new Node(nullptr, element);
    if (size == 0) {
        head = newNode;
    }
    else {
        tail->Nextnode = newNode;
    }
    //redefine the tail to be the new node
    tail = newNode;
    size++;
}

template <typename T>
T SimpleList<T>::remove_front () {
    //create a newNode to store and pop the value of the current header node
    Node *newNode = head;
    //redefine the header node
    head = head->Nextnode;
    T val = newNode->Nodeval;
    //free the unused memory
    delete newNode;
    return val;
}

//create the constructor of the derieved class Stack
template <typename T>
Stack<T>::Stack(string listname): SimpleList<T>(listname){
}

//implement the Stack push function by calling insert_front
template <typename T>
void Stack<T>::push(T element){
    this->insert_front(element);
}

//implment the Stack pop function by calling remove_front
template <typename T>
T Stack<T>::pop(){
    this->size--;
    return this->remove_front();
}

//implement a getsize function to use the protected data size
template <typename T>
int Stack<T>::getsize () {
    return this->size;
}

//create Queue constructor and its push and pop functions similarly
//the difference is calling insert_end to implement its push function
template <typename T>
Queue<T>::Queue(string listname): SimpleList<T>(listname){
}

template <typename T>
void Queue<T>::push(T element){
    this->insert_end(element);
}

template <typename T>
T Queue<T>::pop(){
    this->size--;
    return this->remove_front();
}

template <typename T>
int Queue<T>::getsize () {
    return this->size;
}
