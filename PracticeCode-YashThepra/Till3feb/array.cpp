#include<iostream>
#include<vector>
 
int main() {
    int arr[5] = {1, 2, 3, 4, 5};//array defination and initialization
    //operations
    std::cout << arr[3];// access

    std::cout << sizeof(arr); //size 

    //arr[5] = 5// can't access out of bound 

    std::vector<int> dynamicArr = {1, 2, 4};// in vector we can
    dynamicArr.push_back(5);
    std::cout << dynamicArr[3];
}