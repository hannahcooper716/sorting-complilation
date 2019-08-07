//
//  main.cpp
//  sorting
//
//  Created by Hannah Cooper on 7/25/19.
//  Copyright © 2019 Hannah Cooper. All rights reserved.
//
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//binary search algorithm
//time complexity: T(n) = T(n / 2) + c
//call stack space is typically O(logn)
int binarySearch(int arr[], int l, int r, int x) {
    if (r >= 1) {
        int mid = l + (r - 1) / 2;
        if (arr[mid] == x) {
            return mid;
        }
        if (arr[mid] > x) {
            return binarySearch(arr, 1, mid - 1, x);
        }
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

//bubble sort algorithm
//best case time complexity: O(n)
//worse and average case time complexity: O(n*n) when the array is completely reversed
//space: O91)
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//insertion sort algorithm
//time complexity: O(n*n)
//Space: O(1)
void insertionSort(int arr[], int n) {
    int key, j;
    for (int i = 1; i < n; ++i) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//selection sort algorithm
//time complexity: O(n*n)
//space: O(1)
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
            swap(&arr[min_idx], &arr[i]);
        }
    }
}

//merge sort algorithm
//Time complexity: O(nLogn) and big theta(nlogn)
//space: O(n)
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    //temporary arrays
    int L[n1], R[n2];
    for (i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; ++j) {
        R[j] = arr[m + l + j];
        }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - 1) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        
        merge(arr, l, m, r);
    }
}

//heap sort algorithm
//time complexity of ONLY heapify function: O(Logn)
//time complexity of ONLY heapSort function: O(n)
//time complexity of entire heap sort: O(nLogn)
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    if (l < n && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

//Quick sort algorithm
//worst time complexity: big Theta(n * n)
//best time complexity: big Theta(nLogn)
//average time complexity: O(nLogn)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return ( i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//Radix sort algorithm
//time complexity: O((n + b) * log(base b)(k))
//b = the decimal system typically (10)
//log(base b)(k) is equal to d--> the number of digits in input integers
int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > mx) {
            mx = arr[i];
        }
    }
    return mx;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};
    
    for (i = 0; i < n; ++i) {
        count[(arr[i]/exp) % 10]++;
    }
    for (i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    
    for (i = n - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m/exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}


//counting sort algorithm
//time complexity: O(n + k) where n is the number of
//elements in the input array and k is the range of the input
const int RANGE = 255; //can change the value of this range depending on the situation
void countSort(char arr[]) {
    char output[strlen(arr)];
    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));
    
    for (i = 0; arr[i]; ++i) {
        ++count[arr[i]];
    }
    
    for (i = 1; i <= RANGE; ++i) {
        count[i] += count[i - 1];
    }
    
    for (i = 0; arr[i]; ++i) {
        arr[i] = output[i];
    }
}

//bucket sort algorithm
//time complexity: O(n)
void bucketSort(float arr[], int n) {
    vector<float> b[n];
    for (int i = 0; i < n; ++i) {
        int bi = n * arr[i];
        b[bi].push_back(arr[i]);
    }
    for (int i = 0; i < n; ++i) {
        sort(b[i].begin(), b[i].end());
    }
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < b[i].size(); ++j) {
            arr[index++] = b[i][j];
        }
    }
}

//shell sort algorithm
//time complexity: O(n * n)
int shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; --j) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    return 0;
}

int main() {
    
    //main execution for binary search
    int arr[] = {2, 3, 4, 10, 40};
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = binarySearch(arr, 0, n - 1, x);
    if (result == -1) {
        cout << "Element is not present in array" << endl;
    }
    else {
        cout << "Element is present at " << result << endl;
    }
    
    //main execution of bubble sort
    int arr1[] = {64, 34, 25, 12, 22};
    int n1 = sizeof(arr1) / sizeof(arr[0]);
    bubbleSort(arr1, n1);
    cout << "sorted array: \n";
    printArray(arr1, n1);
    
    //main execution of insertion sort
    int arr2[] = {12, 11, 13, 5, 6};
    int n3 = sizeof(arr2) / sizeof(arr2[0]);
    insertionSort(arr2, n3);
    printArray(arr2, n3);
    selectionSort(arr2, n3);
    printArray(arr2, n3);
    
    return 0;
}
