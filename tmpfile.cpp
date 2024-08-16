#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <unordered_set>
#include <time.h>
#include <random>


std::vector<std::vector<int>> smallTests;
std::vector<std::vector<int>> medTests;
std::vector<std::vector<int>> largeTests;

int partition(std::vector<int> &S, int left, int right){
    int pivotElement = S[right], i = left;
    
    for(int j = left; j < right; j++){
        if(S[j] <= pivotElement){
            std::swap(S[i], S[j]);
            i++;
        }
    }
    std::swap(S[i], S[right]);
    return i;
}



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



// partition index and return pivot of index
// int partition(std::vector<int>& arr, int low, int high) {
//     int pivot = arr[high];
//     int i = low;

//     for (int j = low; j < high; j++) {
//         if (arr[j] <= pivot) {
//             std::swap(arr[i], arr[j]);
//             i++;
//         }
//     }

//     std::swap(arr[i], arr[high]);
//     return i;
// }

int findMedian(std::vector<int>& arr, int low, int high, int k) {
    // std::vector<int> subArray(high - low + 1);
    // std::copy(arr.begin() + low, arr.begin() + high + 1, subArray.begin());
    // std::sort(subArray.begin(), subArray.end());
    // return subArray[k - 1];
    if (low <= high && k > 0 && k <= high - low + 1) {
        return quickselect(arr, k,  low, high);
    }
    return -1;
}

int findMedianOfMedians(std::vector<int>& arr, int low, int high) {
    int n = high - low + 1;
    std::vector<int> medians;

    for (int i = low; i <= high; i += 5) {
        int subHigh = std::min(i + 4, high);
        int median = findMedian(arr, i, subHigh, (subHigh - i + 1) / 2);
        medians.push_back(median);
    }

    if (medians.size() == 1) {
        return medians[0];
    }

    return findMedianOfMedians(medians, 0, medians.size() - 1);
}

int kthSmallestElement(std::vector<int>& arr, int low, int high, int k) {
    if (k > 0 && k <= high - low + 1) {
        int medianOfMedians = findMedianOfMedians(arr, low, high);
        int pivotIndex = partition(arr, low, high);

        if (k == pivotIndex - low + 1) {
            return arr[pivotIndex];
        }
        else if (k < pivotIndex - low + 1) {
            return kthSmallestElement(arr, low, pivotIndex - 1, k);
        }
        else {
            return kthSmallestElement(arr, pivotIndex + 1, high, k - (pivotIndex - low + 1));
        }
    }

    return -1;  // Return -1 if k is out of range
}


int findKthSmallestBruteForce(const std::vector<int>& vector, int k) 
{
    std::vector<int> sortedVector = vector;  
    std::sort(sortedVector.begin(), sortedVector.end());  
    return sortedVector[k-1];  
}




void small(){
    // 5 to 50
    // std::vector<std::vector<int>> tests;
    int M = 46, N = 100; // M for size of vector, N numbers in range of 1 to 100
    std::srand(time(0));

    for(int i = 0; i<5; i++){
        int size = std::rand() % M + 5;
        std::unordered_set<int> sett;
        std::vector<int> test(size);
        for(int j = 0; j<size; j++){
            int num = std::rand() % N;
            while(sett.find(num) != sett.end()){
                num = std::rand() % N;
            }
            test[j] = num;
            sett.insert(num);
        }
        smallTests.push_back(test);
    }
}
void medium(){
    // 50 to 249
    // std::vector<std::vector<int>> tests;
    int M = 201, N = 1e3; // numbers in range of 1 to 1e3
    std::srand(time(0));

    for(int i = 0; i<5; i++){
        int size = std::rand() % M + 50;
        std::unordered_set<int> sett;
        std::vector<int> test(size);
        for(int j = 0; j<size; j++){
            int num = std::rand() % N;
            while(sett.find(num) != sett.end()){
                num = std::rand() % N;
            }
            test[j] = num;
            sett.insert(num);
        }
        medTests.push_back(test);
    }
}
void large(){
    // 250-500
    std::vector<std::vector<int>> tests;
    int M = 251, N = 1e5; // numbers in range of 1 to 1e5
    std::srand(time(0));

    for(int i = 0; i<5; i++){
        int size = std::rand() % M + 250;
        std::unordered_set<int> sett;
        std::vector<int> test(size);
        for(int j = 0; j<size; j++){
            int num = std::rand() % N;
            while(sett.find(num) != sett.end()){
                num = std::rand() % N;
            }
            test[j] = num;
            sett.insert(num);
        }
        largeTests.push_back(test);
    }
}



int main() {
    // std::vector<int> arr = { 7, 10, 4, 3, 20, 15, 25, 30, 40, 60, 25, 75};
    // int k = 6;
    int x;
    small();
    medium();
    large();

    // std::cout<<"Enter the methodology you want to run"<< std::endl<< "1 for sort-and-return"<<std::endl<<"2 for quickSelect"<<std::endl<<"3 for median-of-five"<<std::endl;
    // std::cin>> x;
    // int sol = kthSmallestElementMedianFive(arr, 0, arr.size() - 1, k);
    

    for (auto & arr: medTests) {
        std::cout<<"Input Size is "<<arr.size()<<std::endl;

        // for(int k = 0; k < arr.size(); k++){
        //     std::cout<<arr[k];
        // }

        int sol;
        int k = 1 + (rand()%arr.size());

        auto start = std::chrono::high_resolution_clock::now();

        sol = findKthSmallestBruteForce(arr, k);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout<<"Execution time for bruteforce is "<<duration.count()<<std::endl;
        
        auto startqs = std::chrono::high_resolution_clock::now();


        
        
        int qsSol = quickselect(arr, k, 0, arr.size()-1);

        auto stopqs = std::chrono::high_resolution_clock::now();
        auto durationqs = std::chrono::duration_cast<std::chrono::microseconds>(stopqs - startqs);
        
        std::cout<<"Execution time for quickselect "<<durationqs.count()<<std::endl;

        auto startmed = std::chrono::high_resolution_clock::now();

        
        // int medianSol = kthSmallestElement(arr,k);
        int medianSol = kthSmallestElement(arr, 0, arr.size() - 1, k);

        auto stopmed = std::chrono::high_resolution_clock::now();
        auto durationmed = std::chrono::duration_cast<std::chrono::microseconds>(stopmed - startmed);
          std::cout<<"Execution time for median of five "<<durationmed.count()<<std::endl;
    

        // int kthSmallest = kthSmallestElement(arr, 0, arr.size() - 1, k);


        // std::cout<<"Execution time is "<<duration.count()<<std::endl;
        // if (sol != -1)
        std::cout << "The " << k << "th smallest element bf is: " << sol << std::endl;
        std::cout << "The " << k << "th smallest element qs is: " << qsSol << std::endl;
        std::cout << "The " << k << "th smallest element mf is: " << medianSol << std::endl;
        // else
        //     std::cout << "Invalid value of k." << std::endl;

    }

    // int sol;

    // auto start = std::chrono::high_resolution_clock::now();
    // if (x == 1){
    //     sol = findKthSmallestBruteForce(arr, k);
    // }
    // else if(x == 2){
    //     sol = quickselect(arr, k, 0, arr.size()-1);
    // }
    // else{
    //     sol = kthSmallestElementMedianFive(arr, 0, arr.size() - 1, k);
    // }

    // // int kthSmallest = kthSmallestElement(arr, 0, arr.size() - 1, k);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // std::cout<<"Execution time is "<<duration.count()<<std::endl;
    // if (sol != -1)
    //     std::cout << "The " << k << "th smallest element is: " << sol << std::endl;
    // else
    //     std::cout << "Invalid value of k." << std::endl;

    return 0;
}
