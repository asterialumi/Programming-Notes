#pragma once
#include <iostream>
using namespace std;

class Array {
public:
    Array(): array(new int[0]), _size(0), _capacity(0), allocations(0) {}

    //INSERT FUNCTIONS
    void add(int value) {
        if(_size == _capacity) grow(1.6);
        array[_size++] = value;
    }

    void addAt(int index, int value) {
        if(index < 0 || index >= _size) return; //throw OutOfBounds
        if(_size == _capacity) grow(1.6);

        for(int i = _size; i > index; i--) {
            array[i] = array[i-1];
        }

        array[index] = value;
        _size++;
    }

    //REMOVE FUNCTIONS
    void remove() {
        if(_size == 0) return; //throw-->EmptyContainer
        array[--_size] = 0;
    }

    void removeAt(int index) {
        if(index < 0 || index >= _size) return; //throw-->OutOfBounds

        for(int i = index; i+1 < _size; i++) {
            array[i] = array[i+1];
        }

        array[--_size] = 0;
    }

    //ACCESS FUNCTIONS
    int get(int index) {
        if(index < 0 || index >= _size) return -1; //throw-->OutOfBounds
        return array[index];
    }
    
    int size() { return _size; }
    int capacity() { return _capacity;}

    //DISPLAY FUNCTIONS
    void display() {
        cout << "[";
        for(int i = 0; i < _size; i++) {
            cout << array[i];
            if(i+1 < _capacity) cout << ",";
        }
        cout << "]";
    }
    // void display(int start) {}
    // void display(int start, int end) {}

    //SPECIAL FUNCTIONS
    void set(int index, int value) {
        if(index < 0 || index >= _size) return; //throw-->OutOfBounds
        array[index] = value;
    }

    void expand(int elements) {
        if(_size + elements > _capacity) reserve(_size + elements + 2);
        
        for(int i = 0; i < elements; i++) {
            array[i + _size] = 0;
        }

        _size += elements;
    }

    void resize(int elements) {
        if(elements < 0) return; //throw-->InvalidAmount
        if(elements > _capacity) reserve(elements + 2);

        for(int i = _size - 1; i < elements; i++) {
            array[i] = 0;
        }

        for(int i = elements - 1; i < _size; i++) {
            array[i] = 0;
        }

        _size = elements;
    }
    
    void reserve(int memory) {
        if(memory < _capacity) return; //throw-->InvalidAmount

        _capacity = memory;
        array = allocate(array, _capacity);
        allocations++;
    }

    void reduce(int memory) {
        if(memory < _size) return; //throw-->LengthUnderflow
        if(memory > _capacity) return; //throw-->InvalidAmount
        
        _capacity = memory;
        array = allocate(array, _capacity);
        allocations++;
    }

private:
    int *array;
    int _size;
    int _capacity;
    int allocations;

    void grow(float factor) {
        _capacity = _capacity == 0 ? 2 : _capacity * 1.5;
        array = allocate(array, _capacity);
        allocations++;
    }

    int* allocate(int* origin, int memory) {
        int* desti = new int[memory];

        for(int i = 0; i < _size; i++) {
            desti[i] = origin[i];
        }

        delete[] origin;
        return desti;
    }
};