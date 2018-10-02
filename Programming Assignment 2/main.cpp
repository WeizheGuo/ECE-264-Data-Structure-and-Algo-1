//
//  sort.cpp
//  Programming Assignment 2
//
//  Created by GUOWEIZHE on 5/1/18.
//  Copyright © 2018 GUOWEIZHE. All rights reserved.
//

// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>


using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
    unsigned int val1;
    unsigned int val2;
    char val3;
    string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {
    
    ifstream input(filename.c_str());
    if (!input) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;
    
    // Load the data
    for (int i = 0; i < size; i++) {
        getline(input, line);
        stringstream ss2(line);
        Data *pData = new Data();
        ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
        l.push_back(pData);
    }
    
    input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {
    
    ofstream output(filename.c_str());
    if (!output) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    // Write the size first
    int size = l.size();
    output << size << endl;
    
    // Write the data
    for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
        output << (*ipD)->val1 << " "
        << (*ipD)->val2 << " "
        << (*ipD)->val3 << " "
        << (*ipD)->val4 << endl;
    }
    
    output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    list<Data *> theList;
    loadDataList(theList, filename);
    
    cout << "Data loaded.  Executing sort..." << endl;
    
    int field = 0;
    cout << "Enter an integer from 1 - 4, representing field to sort: ";
    try {
        cin >> field;
        if (field < 1 || field > 4) {
            cerr << "Error: invalid field" << endl;
            exit(1);
        }
    }
    catch (...) {
        cerr << "Error: invalid field" << endl;
        exit(1);
    }
    
    clock_t t1 = clock();
    sortDataList(theList, field);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    
    cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;
    
    cout << "Enter name of output file: ";
    cin >> filename;
    writeDataList(theList, filename);
    
    return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
// include queue class to use in quicksort
#include <queue>

bool comparator(const Data* d1, const Data* d2){
    return (d1->val1 < d2->val1);
}

bool comparator2(const Data* d1, const Data* d2) {
    return (d1->val2 < d2->val2);
}

bool comparator3(const Data* d1, const Data* d2) {
    return (d1->val3 < d2->val3);
}

bool comparator4(const Data* d1, const Data* d2) {
    return (d1->val4 < d2->val4);
}

//Thanks for Zheng (Alex) Liu for helping me construct a improved insertion sort that significantly improve the time
// Load in a 0 at the beginning of the data set and thus can avoid the condition of comparing with the beginning
void insertionsort (list<Data *> &l){

    list<Data*>::iterator it;
    Data *d = new Data();
    d->val1 = 0;
    l.push_front(d);
    for(list<Data*>::iterator it = next(l.begin(),2);it!=l.end();it++){
        list<Data*>::iterator temp = it;
        d = *it;
        for(list<Data*>::iterator it2=it;comparator(d,*(--it2));){
            *temp = *it2;
            temp--;
        }
        *temp = d;
    }
    l.pop_front();
}
    /*
    list<Data *>::iterator begin = l.begin();
    list<Data *>::iterator end = l.end();
    list<Data *>::iterator it1, it2;
    
    for(it1 = next(begin,1); it1 != end; it1++){
        Data* temp = *it1;
        for(it2 = it1; (it2 != begin) && comparator(temp, *prev(it2,1));it2--){
            *it2 = *prev(it1,1);
        }
        *it2 = temp;
        
    }
    */


//radixsort of a 2048 base
void radixsort(list<Data*> &l){
    unsigned int power =1;
    for(int digit =0;digit<3;digit++){

        vector<Data*> bucket[2048];
        list<Data*>::const_iterator it;
        list<Data*>::iterator it2 = l.begin();
        
        for (it = l.begin(); it != l.end(); it++) {
            bucket[((*it)->val2/power)%2048].push_back(*it);
        }
        
        power *= 2048;
        for (int i = 0; i < 2048; i++){
            size_t size = bucket[i].size();
            for (size_t j = 0; j < size; j++){
                *it2 = bucket[i].at(j);
                it2++;
            }
        }
    }
}


//a simple bucketsort
void bucketsort(list<Data *> &l){
    vector<Data *> bucket[94];
    list<Data *>::const_iterator it = l.begin();
    list<Data *>::iterator it2 = l.begin();
    
    for (; it != l.end(); it++)
        bucket[((int)(*it)->val3)-33].push_back(*it);
    
    for (int i = 0; i < 94; i++){
        size_t element_size = bucket[i].size();
        for (size_t j = 0; j < element_size; j++){
            *it2 = bucket[i].at(j);
            it2++;
        }
    }
}


//Thanks for Zheng Liu for giving me suggestions of a faster way
//Do a radix sort of the first two bits and then do the quicksort
void quicksort(list<Data *> &l, list<Data *>::iterator start, list<Data *>::iterator end, int curdigit) {
    if ( curdigit > 1 && curdigit < 25) {
        Data* pivot = *end;
        char pivot_char = pivot -> val4.at(curdigit);
        list<Data *>::iterator leftindex = start;
        list<Data *>::iterator midindex = start;
        list<Data *>::iterator endindex = prev(end, 1);
        while (midindex != next(endindex, 1)) {
            Data* cur = *midindex;
            if (cur -> val4.at(curdigit) <  pivot_char) {
                std::iter_swap(leftindex++, midindex++);
            }else if (cur -> val4.at(curdigit) > pivot_char) {
                std::iter_swap(midindex, endindex--);
            }else {
                midindex++;
            }
        }
        
        std::iter_swap(end, midindex);
        if (leftindex != start && prev(leftindex) != start) {
            quicksort(l, start, prev(leftindex), curdigit);
        }
        if (leftindex != midindex){
            quicksort(l, leftindex, midindex, curdigit + 1);
        }
        if (midindex != end && next(midindex) != end ) {
            quicksort(l, next(midindex), end, curdigit);
        }
    }else if (curdigit < 25){
        std::queue<Data*> bucket[94];
        for (list<Data *>::iterator it = start; it != next(end); it++){
            bucket[(unsigned) ((((*it) -> val4).at(curdigit) - '!'))].push(*it);
        }
        
        list<Data *>::iterator it = start;
        for (int i = 0; i < 94; i++){
            int bucketSize = bucket[i].size();
            list<Data *>::iterator start = it;
            for (int j = 0; j < bucketSize; j++){
                *it = bucket[i].front();
                bucket[i].pop();
                it++;
            }
            list<Data *>::iterator end = prev(it);
            if (start !=  next(end) && start != end) {
                quicksort(l, start, end, curdigit + 1);
            }
        }
    }
}

//main functions calling the above functions
void sortDataList(list<Data *> &l, int field) {
    // Fill in this function
    if (field == 1){
        insertionsort(l);
    }
    else if (field == 2){
        radixsort(l);
    }
    else if (field == 3){
        bucketsort(l);
    }
    else{
        quicksort(l, l.begin(), prev(l.end(),1), 0);
    }
}


