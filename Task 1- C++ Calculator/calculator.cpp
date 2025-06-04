#include<iostream>
using namespace std;

int main() {
    int a, b;
    char operation;

    cout << "Enter 1st number: ";
    cin >> a;

    cout << "Enter operation to perform (+, -, *, /): ";
    cin >> operation;

    cout << "Enter 2nd number: ";
    cin >> b;

    if (operation == '+') {
        cout << a + b;
    } else if (operation == '-') {
        cout << a - b;
    } else if (operation == '*') {
        cout << a * b;
    } else if (operation == '/') {
        if (b != 0)
            cout << a / b;
        else
            cout << "Error: Division by zero!";
    } else {
        cout << "Invalid operation.";
    }

    return 0;
}
