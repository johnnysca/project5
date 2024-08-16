#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_set>
#include <time.h>

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


void small(){
    // 5 to 50
    std::vector<std::vector<int>> tests;
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
        tests.push_back(test);
    }
}
void medium(){
    // 50 to 249
    std::vector<std::vector<int>> tests;
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
        tests.push_back(test);
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
        tests.push_back(test);
    }
}



int main() {
    std::vector<int> S = {4,2,8,5,9,3,6,23,335,55};

    small();
    medium();
    large();

    
    std::cout << quickselect(S, 3, 0, S.size()-1) << std::endl;
    
    return 0;
}