#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>

void PrintEmptyLines()
{
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
}

void PrintHangman(int misses, int maxNumGuesses)
{
	if (misses == 5)
	{
		std::cout << "\t  ~ RIP ~" << std::endl;
		std::cout << "\t ========" << std::endl;
		std::cout << "\t |     ||" << std::endl;
		std::cout << "\t |     ||" << std::endl;
		std::cout << "\t 0     ||" << std::endl;
		std::cout << "\t/|\\    ||" << std::endl;
		std::cout << "\t/ \\    ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t      /  \\" << std::endl;
		std::cout << "\t     |____|" << std::endl;
		std::cout << "you can only guess wrong " << maxNumGuesses - misses << " times! One more miss and you're dead!" << std::endl;
	}
	else if (misses == 4)
	{
		std::cout << "\t         " << std::endl;
		std::cout << "\t ========" << std::endl;
		std::cout << "\t |     ||" << std::endl;
		std::cout << "\t |     ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t      /  \\" << std::endl;
		std::cout << "\t     |____|" << std::endl;
		std::cout << "you can only guess wrong " << maxNumGuesses - misses << " times! One more miss and you're dead!" << std::endl;
	}
	else if (misses == 3)
	{
		std::cout << "\t         " << std::endl;
		std::cout << "\t ========" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t      /  \\" << std::endl;
		std::cout << "\t     |____|" << std::endl;
		std::cout << "you can only guess wrong " << maxNumGuesses - misses << " times! The end is near..." << std::endl;
	}
	else if (misses == 2)
	{
		std::cout << "\t         " << std::endl;
		std::cout << "\t         " << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t       ||" << std::endl;
		std::cout << "\t      /  \\" << std::endl;
		std::cout << "\t     |____|" << std::endl;
		std::cout << "you can only guess wrong " << maxNumGuesses - misses << " times! Be careful!" << std::endl;
	}		
	else if (misses == 1)
	{
		std::cout << "\t           " << std::endl;
		std::cout << "\t           " << std::endl;
		std::cout << "\t           " << std::endl;
		std::cout << "\t           " << std::endl;
		std::cout << "\t           " << std::endl;
		std::cout << "\t           " << std::endl;
		std::cout << "\t           " << std::endl;
		std::cout << "\t           " << std::endl;
		std::cout << "\t      /  \\" << std::endl;
		std::cout << "\t     |____|" << std::endl;
		std::cout << "you can only guess wrong " << maxNumGuesses - misses << " times!" << std::endl;
	}
	else
		return;
}

void DisplayWord(const std::vector<char>& letters)
{
	for (int i = 0; i < letters.size(); i++)
	{
		std::cout << letters[i] << " ";
	}
	std::cout << "\n" << std::endl;
}

void ProcessLetterInput(const std::string& word, std::vector<char>& letters, int& misses, bool& gameOver, const std::string& guess)
{
	bool foundLetter{ false };

	// If the letter is greater than 1, so basically if player 2 is trying to guess the entire word instead of a letter, AND if the guess is correct, we reveal all letters
	// in the letters vector that is displayed on the screen
	if (guess.size() > 1 && guess == word)
	{
		foundLetter = true;
		for (int i = 0; i < word.size(); ++i)
		{

			letters[i] = word[i];

		}
	}
	// If players tries to guess the word but guesses incorrectly, the foundletter flag gets set to false and it increases the "misses" variable at the end of this function
	else if (guess.size() > 1 && guess != word)
	{
		foundLetter = false;

	}
	// If the player guessed a single letter, check if any exists in the word and  if so, place them in the displayed word
	else
	{
		for (int i = 0; i < word.size(); ++i)
		{
			if (guess[0] == word[i])
			{
				letters[i] = word[i];
				foundLetter = true;
			}
		}
	}

	if (!foundLetter)
	{
		++misses;
	}
}

bool isGameOver(const std::vector<char>& letters, const int& misses, const int& maxNumOfMisses)
{
	bool isWordRevealed{ true };

	for (int i = 0; i < letters.size(); ++i)
	{
		if (letters[i] == '_')
			isWordRevealed = false;
	}

	if (misses >= maxNumOfMisses && !isWordRevealed)
	{
		std::cout << "Player has lost the game!! Better luck next time!" << std::endl;
		return true;
	}

	if (misses < maxNumOfMisses && isWordRevealed)
	{
		std::cout << "PLAYER WON THE GAME!! CONGRATULATIONS!!!!" << std::endl;
		return true;
	}

	return false;
}

int main()
{

	std::string word{};
	const int maxNumOfMisses{ 5 };
	int misses{};
	std::vector<char> letters;
	bool gameOver{ false };

	// Printing some empty lines here to keep the couts and cins from jumping on the screen when the hangman is drawn.
	PrintEmptyLines();

	// initialising the secret word. TODO: put all this logic in a function
	std::string file{"wordlist.txt"};
	std::fstream stream;
	stream.open(file, stream.in);

	if(!stream.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	std::vector<std::string> words{};
	stream.seekp(0);

	while(!stream.eof())
	{
		std::string line;
		std::getline(stream, line);
		words.emplace_back(line);
	}

	while(word.size() < 3)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int>range(0, words.size() - 1);


		word = words[range(rng)];
	}

	std::cout << "The secret word has " << word.size() << " letters in it!" << std::endl;

	// Initialize the letters vector with "_" marks. This is the vector that diplays the correctly guesses letters in their correct places in the word.
	for (int i = 0; i < word.size(); ++i)
	{
		letters.push_back('_');
	}

	while (!gameOver)
	{
		std::string guess{};

		// Printing some empty lines here to keep the couts and cins form jumping on the screen when the hangman is drawn.
		if (misses == 0)
		{
			PrintEmptyLines();
		}

		std::cout << "Player, guess a letter or word: ";
		std::cin >> guess;
		system("clear");

		// The function returns true if a letter if found, otherwise returns false
		ProcessLetterInput(word, letters, misses, gameOver, guess);

		// display the word with undiscovered letters marked with "_"
		DisplayWord(letters);

		PrintHangman(misses, maxNumOfMisses);
		
		gameOver = isGameOver(letters, misses, maxNumOfMisses);
	}

	std::cout << "The secret word was " << word << std::endl;

	return 0;
}	