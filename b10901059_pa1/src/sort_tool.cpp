// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ll long long 
#define INF 0xFFFFFF
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); i++) {
        int key = data[i];
        int j = i - 1;
        while( j >= 0 && data[j] > key ) {
            data[j+1] = data[j];
            j--;
        }
        data[++j] = key;
    }
    // DONE
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS

    int ptn;    // partition postion
    
    if (flag) {
        // randomized QS
        if ( low < high) {
            ptn = RandomizedPartition(data, low, high);
            QuickSortSubVector(data, low, ptn, 1);
            QuickSortSubVector(data, ptn+1, high, 1);
        }
    }
    else {
        // normal QS
        if ( low < high) {
            ptn = Partition(data, low, high);
            QuickSortSubVector(data, low, ptn, 0);
            QuickSortSubVector(data, ptn + 1, high, 0); 
        }
    }
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    srand(time(NULL));
    int i = rand() % (high - low + 1) + low;
    // swap two elements
    int tmp = data[i];
    data[i] = data[low];
    data[low] = tmp;

    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int tmp = data[low];
    int i = low - 1;
    int j = high + 1;
    while(1){
        while(data[--j] > tmp){

        }
        while(data[++i] < tmp){

        }
    
        if (i < j) {
            int tmp2 = data[i];
            data[i] = data[j];
            data[j] = tmp2;
        }
        else return j;  // return partition point
    }

}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low < high){
        int mid = floor((low+high)/2);
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid + 1, high);
        Merge(data, low, mid, mid + 1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n_1 = middle1 - low + 1; // size of left subarray
    int n_2 = high - middle2 + 1; // size of right subarray

    int L[n_1 + 1];
    int R[n_2 + 1];
    for (int i = 0; i < n_1; i++) {
        L[i] = data[low + i];
    }
    for (int i = 0; i < n_2; i++) {
        R[i] = data[middle2 + i];
    }
    L[n_1] = INF;
    R[n_2] = INF;
    int pos_1 = 0;
    int pos_2 = 0;
    
    for (int i = low; i <= high; i++) {
        if (L[pos_1] <= R[pos_2]) {     // check whether one array has ended
            data[i] = L[pos_1++];
        }
        else if (L[pos_1] > R[pos_2]) {
            data[i] = R[pos_2++];
        }
    }

}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int tmp = root;
    if (left < heapSize && data[left] > data[tmp]) {
        tmp = left;
    }
    if (right < heapSize && data[right] > data[tmp]) {
        tmp = right;
    }
    if (tmp != root) {
        int tmp2 = data[tmp];
        data[tmp] = data[root];
        data[root] = tmp2;
        MaxHeapify(data, tmp);
    } 
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = floor(data.size()/2) - 1 ; i >= 0 ; i-- ){
        MaxHeapify(data, i);
    }
}
