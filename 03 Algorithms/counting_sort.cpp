#include <iostream>
using namespace std;

void print(int array[], int n);

int* counting_sort(int array[], int n) {
    int min = 100000, max = 0;

    for(int i = 0; i < n; i++) {
        if(array[i] < min) min = array[i];
        if(array[i] >= max) max = array[i];
    }

    int size = max-min+1;
    int freq[size];

    for(int i = 0; i < size; i++) freq[i] = 0;
    for(int i = 0; i < n; i++) freq[array[i]-min]++;
    cout << "FREQUENCY: ";
    print(freq, size);

    for(int i = 1; i < size; i++) {
        freq[i] += freq[i-1];
    }
    cout << "CUMULATIVE: ";
    print(freq, size);
    
    int* res = new int[n];
    for(int i = 0; i < n; i++) {
        res[freq[array[i]-min] - 1] = array[i];
        freq[array[i]-min]--;
    }

    return res;
}

int main() {
    int test[] = {2, 4, 1, 8, 8, 2, 3, 9, 1, 7, 3, 6, 3, 5, 8, 2, 9, 1};
    int n = 18;

    int* sorted = counting_sort(test, n);
    cout << "FINAL RESULT: ";
    for(int i = 0; i < n; i++) cout << sorted[i] << " ";
}

void print(int array[], int n) {
    for(int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}