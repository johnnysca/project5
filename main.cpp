#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <unordered_set>
#include <random>

std::vector<std::vector<int>> smallTests;
std::vector<std::vector<int>> medTests;
std::vector<std::vector<int>> largeTests;

int partition(std::vector<int>& S, int left, int right) {
    int pivotIndex = left + rand() % (right - left + 1);
    int pivotElement = S[pivotIndex];
    std::swap(S[pivotIndex], S[right]);

    int i = left;
    for (int j = left; j < right; j++) {
        if (S[j] <= pivotElement) {
            std::swap(S[i], S[j]);
            i++;
        }
    }
    std::swap(S[i], S[right]);
    return i;
}

// int partition(std::vector<int> &S, int left, int right){
//     int pivotElement = S[right], i = left;
    
//     for(int j = left; j < right; j++){
//         if(S[j] <= pivotElement){
//             std::swap(S[i], S[j]);
//             i++;
//         }
//     }
//     std::swap(S[i], S[right]);
//     return i;
// }
int quickselect(std::vector<int> &S, int k, int left, int right){
    int pivotIndex = partition(S, 0, right);
    
    if(pivotIndex+1 == k){
        return S[pivotIndex];
    }
    else if(pivotIndex+1 > k){
        return quickselect(S, k, left, pivotIndex-1);
    }
    return quickselect(S, k, pivotIndex+1, right);
    
}

void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int findMedian(std::vector<int>& arr, int left, int right, int k) {
    insertionSort(arr, left, right);
    return arr[left + k - 1];
}

int findMedianOfMedians(std::vector<int>& arr, int left, int right) {
    int n = right - left + 1;
    if (n <= 5) {
        return findMedian(arr, left, right, (n + 1) / 2);
    }

    int numMedians = (n + 4) / 5;
    std::vector<int> medians(numMedians);
    for (int i = 0; i < numMedians; i++) {
        int subLeft = left + i * 5;
        int subRight = std::min(subLeft + 4, right);
        medians[i] = findMedian(arr, subLeft, subRight, (subRight - subLeft + 1) / 2);
    }

    return findMedianOfMedians(medians, 0, numMedians - 1);
}

int kthSmallestElement(std::vector<int>& arr, int left, int right, int k) {
    if (k > 0 && k <= right - left + 1) {
        int medianOfMedians = findMedianOfMedians(arr, left, right);
        int pivotIndex = partition(arr, left, right);

        if (k == pivotIndex - left + 1) {
            return arr[pivotIndex];
        }
        else if (k < pivotIndex - left + 1) {
            return kthSmallestElement(arr, left, pivotIndex - 1, k);
        }
        else {
            return kthSmallestElement(arr, pivotIndex + 1, right, k - (pivotIndex - left + 1));
        }
    }

    return -1;  // Return -1 if k is out of range
}

int findKthSmallest(const std::vector<int>& vector, int k) 
{
    std::vector<int> sortedVector = vector;  
    std::sort(sortedVector.begin(), sortedVector.end());  
    return sortedVector[k-1];  
}

void small() {
    int M = 46, N = 100;
    std::srand(time(0));

    for (int i = 0; i < 5; i++) {
        int size = std::rand() % M + 5;
        std::unordered_set<int> sett;
        std::vector<int> test(size);
        for (int j = 0; j < size; j++) {
            int num = std::rand() % N;
            while (sett.find(num) != sett.end()) {
                num = std::rand() % N;
            }
            test[j] = num;
            sett.insert(num);
        }
        smallTests.push_back(test);
    }
}

void medium() {
    int M = 201, N = 1e3;
    std::srand(time(0));

    for (int i = 0; i < 5; i++) {
        int size = std::rand() % M + 50;
        std::unordered_set<int> sett;
        std::vector<int> test(size);
        for (int j = 0; j < size; j++) {
            int num = std::rand() % N;
            while (sett.find(num) != sett.end()) {
                num = std::rand() % N;
            }
            test[j] = num;
            sett.insert(num);
        }
        medTests.push_back(test);
    }
}

void large() {
    int M = 251, N = 1e5;
    std::srand(time(0));

    for (int i = 0; i < 5; i++) {
        int size = std::rand() % M + 250;
        std::unordered_set<int> sett;
        std::vector<int> test(size);
        for (int j = 0; j < size; j++) {
            int num = std::rand() % N;
            while (sett.find(num) != sett.end()) {
                num = std::rand() % N;
            }
            test[j] = num;
            sett.insert(num);
        }
        largeTests.push_back(test);
    }
}

int main() {
    small();
    medium();
    large();

    std::vector<int> arr = { 7, 10, 4, 3, 20, 15, 25, 30, 40, 60, 25, 75};
    int x;

    std::cout<<"Enter the methodology you want to run"<< std::endl<< "1 for sort-and-return"<<std::endl<<"2 for quickSelect"<<std::endl<<"3 for median-of-five"<<std::endl;
    std::cin>> x;
    int k = 1 + (rand() % arr.size());

    int sol;

    auto start = std::chrono::high_resolution_clock::now();
    if (x == 1){
        sol = findKthSmallest(arr, k);
    }
    else if(x == 2){
        sol = quickselect(arr, k, 0, arr.size()-1);
    }
    else{
        sol = kthSmallestElement(arr, 0, arr.size() - 1, k);
    }

    // int kthSmallest = kthSmallestElement(arr, 0, arr.size() - 1, k);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout<<"Execution time is "<<duration.count()<<std::endl;
    if (sol != -1)
        std::cout << "The " << k << "th smallest element is: " << sol << std::endl;
    else
        std::cout << "Invalid value of k." << std::endl;


    // for (int i = 0; i < medTests.size(); i++) {
    //     std::cout<<std::endl;
    //     std::cout << "Test " << (i + 1) << ": Input Size is " << medTests[i].size() << std::endl;
    //     std::cout<<std::endl;

    //     int k = 1 + (rand() % medTests[i].size());

    //     auto start = std::chrono::high_resolution_clock::now();
    //     int kthSmallest = kthSmallestElement(medTests[i], 0, medTests[i].size() - 1, k);
    //     auto end = std::chrono::high_resolution_clock::now();
    //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    //     auto startqs = std::chrono::high_resolution_clock::now();
    //     int kthSmallestqs = quickselect(medTests[i], k, 0, medTests[i].size() - 1);
    //     auto endqs = std::chrono::high_resolution_clock::now();
    //     auto durationqs = std::chrono::duration_cast<std::chrono::microseconds>(endqs - startqs).count();

    //     auto startbf = std::chrono::high_resolution_clock::now();
    //     int kthSmallestbf = findKthSmallest(medTests[i], k);
    //     auto endbf = std::chrono::high_resolution_clock::now();
    //     auto durationbf = std::chrono::duration_cast<std::chrono::microseconds>(endbf - startbf).count();
        

    //     std::cout << "Kth Smallest Element using Median of Five: " << kthSmallest << std::endl;
    //     std::cout << "Time taken for Median of Five: " << duration << " microseconds" << std::endl;
    //     std::cout << std::endl;

    //     std::cout << "Kth Smallest Element using QuickSelect: " << kthSmallestqs << std::endl;
    //     std::cout << "Time taken for QuickSelect is: " << durationqs << " microseconds" << std::endl;
    //     std::cout << std::endl;


    //     std::cout << "Kth Smallest Element using BruteForce: " << kthSmallestbf << std::endl;
    //     std::cout << "Time taken for BruteForce is: " << durationbf << " microseconds" << std::endl;
    //     std::cout << std::endl;
    //     std::cout<<"*************************************************************************************";
    // }

    return 0;
}
