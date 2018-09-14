//  Weizhe Guo
//  DSA programming assignment 1
//  Prof. Sable

//  main.cpp
//  Programming Assignment 1
//
//  Created by GUOWEIZHE on 4/15/18.
//  Copyright © 2018 GUOWEIZHE. All rights reserved.

//Acknowledgement:
//Thanks for Zheng (Alex) Liu for helping me to debug the program
//Thanks for Zhekai (Scott) Jin for helping me construct the search_list function

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <list>
#include "Simplelist.cpp"

using namespace std;

list<SimpleList<int> *> listSLi;
list<SimpleList<double> *> listSLd;
list<SimpleList<string> *> listSLs;

template <typename T>
SimpleList<T> * search_list (string listname, list<SimpleList<T> *> * l) {
    //use the iterator to loop through the list and look for the listname
    //if found return the pointer, otherwise return a nullptr
    for (typename list<SimpleList<T> *>::const_iterator itr = l->begin(); itr != l->end(); ++itr) {
        if ((*itr)->name == listname)
            return *itr;
    }
    return nullptr;
}

//a big function reading the input file and generating lines in the output file
void read_file (string input, string output) {
    SimpleList<int> * pSLi;
    SimpleList<double> * pSLd;
    SimpleList<string> * pSLs;
    
    //read the input file and write in the output file
    ifstream input_file;
    ofstream output_file;
    input_file.open(input.c_str());
    output_file.open(output.c_str());
    
    //error checking: cannot find the input file or the output file
    if (!input_file ||!output_file) {
        cout << "Error: Unable to open the input or output file";
    }
    //valid input file and output file: continuing to process every line
    else{
        string inputLine;
        //use a while loop to process every line
        while (getline(input_file, inputLine)){
            output_file << "PROCESSING COMMAND: " << inputLine << endl;
            
            //create a buffer to load each line
            string buffer;
            stringstream ss(inputLine);
            string* lines = new string[3];
            int i = 0;
            
            while (ss >> buffer) {
                lines[i++] = buffer;
            }
            
            //seperate each line into three components - command, item, and value
            string command = lines[0];
            string item = lines[1];
            string value = lines[2];
            
            //switch depending on the command
            if (command == "create") {
                //switch depending on the type of the elements in the list(the first letter of item)
                if (item[0] == 'i') {
                    // call the search function: error if found, otherwise do push for stack or queue
                    if (search_list (item, &listSLi) != nullptr) {
                        output_file << "ERROR: This name already exists!" << endl;
                    }
                    else if (value == "stack") {
                        pSLi = new Stack<int>(item);
                        listSLi.push_front(pSLi);
                    }
                    else {
                        pSLi = new Queue<int>(item);
                        listSLi.push_front(pSLi);
                    }
                }
                else if (item[0] == 'd') {
                    if (search_list (item, &listSLd) != nullptr) {
                        output_file << "ERROR: This name already exists!" << endl;
                    }
                    else if (value == "stack") {
                        pSLd = new Stack<double>(item);
                        listSLd.push_front(pSLd);
                    }
                    else {
                        pSLd = new Queue<double>(item);
                        listSLd.push_front(pSLd);
                    }
                }
                else if (item[0] == 's') {
                    if (search_list (item, &listSLs) != nullptr) {
                        output_file << "ERROR: This name already exists!" << endl;
                    }
                    else if (value == "stack") {
                        pSLs = new Stack<string>(item);
                        listSLs.push_front(pSLs);
                    }
                    else {
                        pSLs = new Queue<string>(item);
                        listSLs.push_front(pSLs);
                    }
                }
            }
            else if (command == "push") {
                //call th search function: error if not found, otherwise push according to the type
                if (item[0] == 'i'){
                    pSLi = search_list (item, &listSLi);
                    if (pSLi == nullptr) {
                        output_file << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        //convert the string into integer and do push
                        pSLi->push(stoi(value));
                    }
                }
                if (item[0] == 'd'){
                    pSLd = search_list (item, &listSLd);
                    if (pSLd == nullptr) {
                        output_file << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        pSLd->push(stod(value));
                    }
                }
                if (item[0] == 's'){
                    pSLs = search_list (item, &listSLs);
                    if (pSLs == nullptr) {
                        output_file << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        pSLs->push(value);
                    }
                }
            }
            else{
                //call the search function similarly: check for nonexistence and empty list
                if (item[0] == 'i'){
                    pSLi = search_list(item, &listSLi);
                    if (pSLi == nullptr) {
                        output_file << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        if (pSLi->getsize() == 0) {
                            output_file << "ERROR: This list is empty!" << endl;
                        }
                        else {
                            //call the pop function
                            output_file << "Value popped: " << pSLi->pop() << endl;
                        }
                    }
                }
                if (item[0] == 'd'){
                    pSLd = search_list(item, &listSLd);
                    if (pSLd == nullptr) {
                        output_file << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        if (pSLd->getsize() == 0) {
                            output_file << "ERROR: This list is empty!" << endl;
                        }
                        else {
                            output_file << "Value popped: " << pSLd->pop() << endl;
                        }
                    }
                }
                if (item[0] == 's'){
                    pSLs = search_list(item, &listSLs);
                    if (pSLs == nullptr) {
                        output_file << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        if (pSLs->getsize() == 0) {
                            output_file << "ERROR: This list is empty!" << endl;
                        }
                        else {
                            output_file << "Value popped: " << pSLs->pop() << endl;
                        }
                    }
                }
            }
        }
    //close the two files
    input_file.close();
    output_file.close();
    }
}

int main(int argc, char** argv) {
    string infile, outfile;
    
    cout << "Name of the input file: ";
    cin >> infile;
    
    cout << "Name of the output file: ";
    cin >> outfile;
    
    //call the read_file function defined above
    read_file (infile, outfile);
    
    return 0;
}

