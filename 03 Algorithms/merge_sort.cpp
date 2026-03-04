#include <vector>
#include <iostream>
using namespace std;

//THE ACTUAL MERGE LOGIC (O(n))
void merge(vector<int>& arr, int left, int mid, int right) {
    //divide arr into two subarrays
    //that would be arr[left...mid] for left subarray and arr[mid+1...right] for right subarray
    int left_size = mid - left + 1;
    int right_size = right - mid;

    //take an array of size 10 for example. because arrays are 0-indexed, if left was 0, mid was 4, and right was 9:
    //left_size must be 4-0+1 = 5, right_size must be 9-4 = 5. makes sense right? because half of 10 is 5. it's just
    //zero-indexed math.

    //create temp vectors for these subarrays
    vector<int> L(left_size), R(right_size);

    //copy the values from arr into these temp vectors
    //to avoid confusion, let i be the index variable for left, and j be the index variable for right
    int i, j;
    for(i = 0; i < left_size; i++) L[i] = arr[left+i];
    for(j = 0; j < right_size; j++) R[j] = arr[mid+1+j];

    //reset i and j, we use these values again
    i = 0, j = 0;
    int k = left;

    //merge these two vectors back into the original array[left...right], which is why we set k = left
    //the recursion guarantees that these two vectors are already SORTED. therefore we compare every element in each
    //vector on which one's the smallest value from left to right, one by one (assume sorted is in ascending order).
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

    //if there are remaining elements in either vectors, we just copy them directly
    while(i < left_size) {
        arr[k] = L[i];
        i++;
        k++;
    }

    //same for the other vector obviously
    while(j < right_size) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

//THE RECURSION FOR DIVIDE AND CONQUER LOGIC (O(log n))
void mergeSort(vector<int>& arr, int left, int right) {
    if(left >= right) return; //base case

    //divide the array into two subarrays. this repeats until there's only one element left for every subarray
    //(which is guaranteed to be SORTED).
    //because it starts at one element, for ex. [1] and [2], it's easy to compare them on which is bigger.
    //the idea here is that, after the division is done, we merge them again by comparing the left and right subarrays
    //until they become more and more sorted as they keep merging back, and the subarrays combine back into
    //the original array.

    int mid = (right - left) / 2 + left; //calculating the mid index
    mergeSort(arr, left, mid);          //divide further the left subarray
    mergeSort(arr, mid + 1, right);     //divide further the right subarray
    merge(arr, left, mid, right);       //finally merge
}

//TOTAL RUNTIME: O(n log n)

//EXAMPLE EXECUTION
int main() {
    vector<int> arr = {38, 27, 54, 12, 63, 8, 120, 34};
    int n = arr.size();

    mergeSort(arr, 0, n-1);
    for(int num : arr) cout << num << " ";

    return 0;
}