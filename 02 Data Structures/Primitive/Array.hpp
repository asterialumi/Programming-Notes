#pragma once
#include <iostream>
using namespace std;

class Array {
public:
    Array(): array(new int[0]), size(0), capacity(0), allocations(0) {}

    //INSERT FUNCTIONS
    void add(int value) {
        if(size == capacity) grow(1.6);
        array[size++] = value;
    }

    void addAt(int index, int value) {
        if(index < 0 || index >= size) return; //throw OutOfBounds
        if(size == capacity) grow(1.6);

        for(int i = size; i > index; i--) {
            array[i] = array[i-1];
        }

        array[index] = value;
        size++;
    }

    //REMOVE FUNCTIONS
    void remove() {
        if(size == 0) return; //throw-->EmptyContainer
        array[--size] = 0;
    }

    void removeAt(int index) {
        if(index < 0 || index >= size) return; //throw-->OutOfBounds

        for(int i = index; i+1 < size; i++) {
            array[i] = array[i+1];
        }

        array[--size] = 0;
    }

    //ACCESS FUNCTIONS
    int get(int index) {
        if(index < 0 || index >= size) return -1; //throw-->OutOfBounds
        return array[index];
    }
    
    int getSize() { return size; }
    int getCapacity() { return capacity;}

    //DISPLAY FUNCTIONS
    void display() {
        cout << "[";
        for(int i = 0; i < size; i++) {
            cout << array[i];
            if(i+1 < capacity) cout << ",";
        }
        cout << "]";
    }
    // void display(int start) {}
    // void display(int start, int end) {}

    //SPECIAL FUNCTIONS
    void set(int index, int value) {
        if(index < 0 || index >= size) return; //throw-->OutOfBounds
        array[index] = value;
    }

    void expand(int elements) {
        if(size + elements > capacity) reserve(size + elements + 2);
        
        for(int i = 0; i < elements; i++) {
            array[i + size] = 0;
        }

        size += elements;
    }

    void resize(int elements) {
        if(elements < 0) return; //throw-->InvalidAmount
        if(elements > capacity) reserve(elements + 2);

        for(int i = size - 1; i < elements; i++) {
            array[i] = 0;
        }

        for(int i = elements - 1; i < size; i++) {
            array[i] = 0;
        }

        size = elements;
    }
    
    void reserve(int memory) {
        if(memory < capacity) return; //throw-->InvalidAmount

        capacity = memory;
        array = allocate(array, capacity);
        allocations++;
    }

    void reduce(int memory) {
        if(memory < size) return; //throw-->LengthUnderflow
        if(memory > capacity) return; //throw-->InvalidAmount
        
        capacity = memory;
        array = allocate(array, capacity);
        allocations++;
    }

private:
    int *array;
    int size;
    int capacity;
    int allocations;

    void grow(float factor) {
        capacity = capacity == 0 ? 1: capacity * 1.5;
        array = allocate(array, capacity);
        allocations++;
    }

    int* allocate(int* origin, int memory) {
        int* desti = new int[memory];

        for(int i = 0; i < size; i++) {
            desti[i] = origin[i];
        }

        delete[] origin;
        return desti;
    }
};