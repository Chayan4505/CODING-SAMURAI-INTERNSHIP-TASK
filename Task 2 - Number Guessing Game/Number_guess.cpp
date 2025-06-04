#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

using namespace std;

int main() {
    srand(time(0));
    
    int Number = rand() % 100 + 1;
    int guess;
    int attempts = 0;

    cout << " Welcome to the Number Guessing Game! \n I'm thinking of a number between 1 and 100." << endl;

    do {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;

        if (guess < Number) {
            cout << "Too low! Try again." << endl;
        } else if (guess > Number) {
            cout << "Too high! Try again." << endl;
        } else {
            cout << " Congratulations! You guessed the number in " << attempts << " attempts." << endl;
        }

    } while (guess != Number);

    return 0;
}
