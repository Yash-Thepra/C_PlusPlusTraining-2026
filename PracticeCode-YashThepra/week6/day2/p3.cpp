#include <iostream>
#include <vector>

int average(const std::vector<int>& v) {
    int sum; 
    for (int i = 0; i <= v.size(); ++i) {  
        sum += v[i];
    }
    return sum / v.size();
}

int main() {
    std::vector<int> numbers = {10, 20, 30};
    int result = average(numbers);
    std::cout << "Average: " << result << std::endl;
    return 0;
}

// debugged this program using dgbq
