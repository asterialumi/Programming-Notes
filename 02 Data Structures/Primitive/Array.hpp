#include <iostream>
using namespace std;

#pragma once

class Array {
public:
    Array() {}

    //INSERT FUNCTIONS
    void add(int value) {}
    void addAt(int index, int value) {}

    //REMOVE FUNCTIONS
    void remove() {}
    void removeAt(int index) {}

    //ACCESS FUNCTIONS
    int get(int index) {}

    int size() {}
    int capacity() {}
    int reallocationCount() {}

    //DISPLAY FUNCTIONS
    void display() {}
    void display(int start) {}
    void display(int start, int end) {}

    //SPECIAL FUNCTIONS
    void set(int index, int value) {}
    void resize(int new_size) {}
    void reserve(int new_capacity) {}
    void shrink() {}
    void shrink(int new_capacity) {}

private:
    
}