#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

void merge(int array[], int low, int mid, int high, int size) {
    int temp[size];
    int i = low;
    int j = mid + 1;
    int k = 0;
    while ((i <= mid) && (j <= high)) {
        if (array[i] >= array[j]) {
            temp[k] = array[j];
            k++;
            j++;
        } else {
            temp[k] = array[i];
            k++;
            i++;
        }
    }
    while (i <= mid) {
        temp[k] = array[i];
        k++;
        i++;
    }
    while (j <= high) {
        temp[k] = array[j];
        k++;
        j++;
    }

    k = 0;
    for (int i = low; i <= high; i++) {
        array[i] = temp[k];
        k++;
    }
}

void mergesort(int array[], int low, int high, int size) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergesort(array, low, mid, size);
        mergesort(array, mid + 1, high, size);

        merge(array, low, mid, high, size);
    }
}

void perform_merge_sort(int arr[], int size) {
    int array[size];
    for (int i = 0; i < size; i++) {
        array[i] = arr[i];
    }
    double start = clock();
    mergesort(array, 0, size - 1, size);
    double end = clock();
    cout << "Merge Sort:\n";
     for(int i = 0 ; i < size; i++){
     cout << array[i] << " ";
     }
    cout << endl;
    cout << "Time Required: " << double(end-start) /CLOCKS_PER_SEC<< endl;
}

void p_mergesort(int array[], int low, int high, int size) {
    if (low < high) {
        int mid = (low + high) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            p_mergesort(array, low, mid, size);
#pragma omp section
            p_mergesort(array, mid + 1, high, size);
        }
        merge(array, low, mid, high, size);
    }
}

void perform_p_merge_sort(int arr[], int size) {
    int array[size];
    for (int i = 0; i < size; i++) {
        array[i] = arr[i];
    }
    double start = omp_get_wtime();
    p_mergesort(array, 0, size - 1, size);
    double end = omp_get_wtime();
    cout << "Parallel Merge Sort:\n";
     for(int i = 0 ; i < size; i++){
     cout << array[i] << " ";
     }
    cout << endl;
    cout << "Time Required: " << end - start << endl;
}

int main(int argc, char const *argv[]) {
    int SIZE;
    int MAX = 1000;
    cout << "Enter size of array: ";
    cin >> SIZE;
    int array[SIZE];
    cout << "Enter elements of array:\n";
    for (int i = 0; i < SIZE; i++) {
        cin >> array[i];
    }
     cout << "Initial Array:\n";
     for(int i = 0 ; i < SIZE; i++){
     cout << array[i] << " ";
     }
    cout << endl;
    perform_merge_sort(array, SIZE);
    perform_p_merge_sort(array, SIZE);
    return 0;
}
