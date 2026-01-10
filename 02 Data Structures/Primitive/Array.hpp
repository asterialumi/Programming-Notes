#include <iostream>
#include <cmath>
using namespace std;

#pragma once

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
        if(size == capacity) grow(1.5);

        int shift = array[index];
        array[index] = value;

        for(int i = index + 1; i < size; i++) {
            int hold = array[i];
            array[i] = shift;
            shift = hold;
        }

        array[size++] = shift;
    }

    //REMOVE FUNCTIONS
    void remove() {
        if(size == 0) return; //throw-->EmptyContainer
        array[size--] = 0;
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
    int getAllocations() { return allocations; }

    //DISPLAY FUNCTIONS
    void display() {
        for(int i = 0; i < capacity; i++) {
            cout << "[";

            if(i < size) cout << array[i];
            else cout << "_";
            
            cout << "]";
            if(i+1 < capacity) cout << ", ";
        }
    }
    // void display(int start) {}
    // void display(int start, int end) {}

    // //SPECIAL FUNCTIONS
    void set(int index, int value) {
        if(index < 0 || index >= size) return; //throw-->OutOfBounds
        array[index] = value;
    }

    void resize(int amount) {
        if(size + amount > capacity) return; //throw-->LengthOverflow

        for(int i = 0; i < amount; i++) {
            array[i + size] = 0;
        }

        size += amount;
    }
    
    void reserve(int amount) {
        capacity += amount;
        array = allocate(array, capacity);
        allocations++;
    }

    void reduce(int amount) {
        if(capacity - amount < size) return; //throw-->LengthUnderflow
        capacity -= amount;
        array = allocate(array, capacity);
        allocations++;
    }

private:
    int *array;
    int size;
    int capacity;
    int allocations;

    void grow(float factor) {
        capacity = capacity == 0 ? ceil(factor) : ceil(capacity * factor);
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