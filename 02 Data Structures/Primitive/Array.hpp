#pragma once
#include <iostream>
using namespace std;

class Array {
public:
    Array(): array(nullptr), _size(0), _capacity(0), allocations(0) {}

    //INSERT FUNCTIONS
    void insert(int value) { insert(_size, value); }

    void insert(int index, int value) {
        if(index < 0 || index > _size) return; //throw OutOfBounds
        if(_size == _capacity) grow(1.6);

        for(int i = _size; i > index; i--) {
            array[i] = array[i-1];
        }

        array[index] = value;
        _size++;
    }

    void expand(int elements) { expand(elements, 0); }

    void expand(int elements, int value) {
        if(_size + elements > _capacity) reserve(_size + elements + 2);
        
        for(int i = 0; i < elements; i++) {
            array[i + _size] = value;
        }

        _size += elements;
    }

    //REMOVE FUNCTIONS
    void remove() { remove(_size - 1); }

    void remove(int index) {
        if(_size == 0) return; //throw-->EmptyContainer
        if(index < 0 || index >= _size) return; //throw-->OutOfBounds

        for(int i = index; i+1 < _size; i++) {
            array[i] = array[i+1];
        }

        array[--_size] = 0;
    }

    void erase(int value) { erase(_size, value); }

    void erase(int count, int value) {
        if(_size == 0) return; //throw-->EmptyContainer
        bool elementExists = false;

        for(int i = 0; i < _size; i++) {
            if(array[i] == value) {
                elementExists = true;
                remove(i);
                i--;
                count--;
                if(count == 0) return;
            }
        }

        if(!elementExists) return; //throw-->ElementDoesNotExist
    }

    void clear() {
        for(int i = 0; i < _size; i++) {
            array[i] = 0;
        }
        _size = 0;
    }

    //ACCESS FUNCTIONS
    int at(int index) {
        if(index < 0 || index >= _size) return -1; //throw-->OutOfBounds
        if(_size == 0) return -1; //throw-->EmptyContainer
        return array[index];
    }
    
    int first()    { return at(0); }
    int last()     { return at(_size - 1); }
    int size()     { return _size; }
    int capacity() { return _capacity; }

    //DISPLAY FUNCTIONS
    void display()          { display(0, _size); }
    void display(int start) { display(start, _size); }

    void display(int start, int end) {
        if(start < 0 || start >= _size || end <= 0 || end > _size) return; //throw-->OutOfBounds
        if(_size == 0) return; //throw-->EmptyContainer

        cout << "[";
        for(int i = start; i < end; i++) {
            cout << array[i];
            if(i+1 < end) cout << ",";
        }
        cout << "]";
    }

    //SPECIAL FUNCTIONS
    void set(int index, int value) {
        if(index < 0 || index >= _size) return; //throw-->OutOfBounds
        array[index] = value;
    }
    
    void resize(int elements) { return resize(elements, 0); }

    void resize(int elements, int value) {
        if(elements < 0) return; //throw-->InvalidAmount
        if(elements > _capacity) reserve(elements + 2);

        for(int i = _size; i < elements; i++) {
            array[i] = value;
        }

        for(int i = elements; i < _size; i++) {
            array[i] = value;
        }

        _size = elements;
    }
    
    void reserve(int memory) {
        if(memory < _size) return; //throw-->LengthUnderflow
        _capacity = memory;
        array = allocate(array, _capacity);
    }

private:
    int *array;
    int _size;
    int _capacity;
    int allocations;

    void grow(float factor) {
        _capacity = _capacity == 0 ? 2 : _capacity * 1.5;
        array = allocate(array, _capacity);
    }

    int* allocate(int* origin, int memory) {
        int* desti = new int[memory];

        for(int i = 0; i < _size; i++) {
            desti[i] = origin[i];
        }

        delete[] origin;
        allocations++;
        return desti;
    }
};