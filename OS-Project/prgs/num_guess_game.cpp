#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	int number_to_guess, guess, no_of_tries = 0;
	srand(time(0)); 
	number_to_guess = rand() % 1000 + 1; 
	cout << "---------------  Number Guess Game --------------- \n\n";
	do
	{
		cout << "Enter a guess between 1 and 1000 : ";
		cin >> guess;
		no_of_tries++;

		if (guess > number_to_guess)
			cout << "Your guess is above the actual number !\n\n";
		else if (guess < number_to_guess)
			cout << "Your guess is below the actual number !\n\n";
		else
			cout << "\nHURRAHH! You got it in " << no_of_tries << " guesses!\n";
	} while (guess != number_to_guess);

	return 0;
}