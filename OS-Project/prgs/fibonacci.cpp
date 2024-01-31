#include <iostream>
using namespace std;

// 0 1 1 2 3 5 8 13
// sum of two previous consequtive numbers
int main() {
    int end_number, num1 = 0, num2 = 1, nextTerm = 0;

    cout << "Enter the number of terms: ";
    cin >> end_number;
    cout << "----------------- Fibonacci Series till given number ----------\n ";
    for (int i = 1; i <= end_number; i++) {
        // Prints the first two terms.
        if(i == 1) {
            cout <<num1<< ", ";
            continue;
        }
        if(i == 2) {
            cout << num2 << ", ";
            continue;
        }
        nextTerm = num1 + num2;
        num1 = num2;
        num2 = nextTerm;
        
        cout << nextTerm << ", ";
    }
    return 0;
}