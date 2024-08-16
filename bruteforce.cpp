#include <iostream>
#include <vector>
#include <algorithm>

int findKthSmallest(const std::vector<int>& vector, int k) 
{
    std::vector<int> sortedVector = vector;  
    std::sort(sortedVector.begin(), sortedVector.end());  
    return sortedVector[k-1];  
}



int main() 
{
    std::vector<int> vector = {9, 2, 5, 1, 7, 4, 8, 3, 6};  // Example input vector
    int k = 3;  
    int result = findKthSmallest(vector, k);
    std::cout << "The " << k << "th smallest element is: " << result << std::endl;

    return 0;
}