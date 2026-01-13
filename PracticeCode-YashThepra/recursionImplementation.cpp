#include <iostream>

using std::cout;
using std::cin;

int fibSeries(int fibIndex) {
    if (fibIndex == 0 || fibIndex == 1) return fibIndex;

    return fibSeries(fibIndex - 1) + fibSeries(fibIndex - 2);
}
int main() {
    int fibIndex;
    cout << "Please enter the index at which of which you want fibonacci number: ";
    cin >> fibIndex;
    cout << "\n";

    cout << "fibonacci number at index " << fibIndex << " is: " << fibSeries(fibIndex);
    return 0;
}