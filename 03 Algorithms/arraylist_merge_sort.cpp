#include <vector>
#include <iostream>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;
    vector<int> L(left_size), R(right_size);

    int i, j;
    for(i = 0; i < left_size; i++) L[i] = arr[left+i];
    for(j = 0; j < right_size; j++) R[j] = arr[mid+1+j];

    i = 0, j = 0;
    int k = left;

    while(i < left_size && j < right_size) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < left_size) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < right_size) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if(left >= right) return;

    int mid = (right - left) / 2 + left;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    vector<int> arr = {38, 27, 54, 12, 63, 8, 120, 34};
    int n = arr.size();

    mergeSort(arr, 0, n-1);
    for(int num : arr) cout << num << " ";

    return 0;
}