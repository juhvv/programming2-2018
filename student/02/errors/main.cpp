#include <iostream>
#include <string>

const int MAX_GUESSES = 10;

// Prints empty lines at the beginning of execution
void clean_screen();

// Checks if all the letters include in the list of guessed letters
bool is_word_already_guessed(std::string secret, std::string guessed);

// Prints string using '_' in the places of letters not guessed
void print_game_status(std::string secret, std::string guessed);


int main()
{
    std::string secret_word = "";
    std::cout << "Give a word to be guessed: ";
    getline(std::cin, secret_word);

    clean_screen();

    std::string guessed_letters = "";
    int guesses_used = 0;

    while (not is_word_already_guessed(secret_word, guessed_letters)
              and guesses_used < MAX_GUESSES)
    {

        std::cout << std::endl
             << "Game status: ";
        print_game_status(secret_word, guessed_letters);

        if (guessed_letters.size() > 0)
        {
            std::cout << "You have used " << guesses_used
                 << " guesses!"
                 << std::endl
                 << "You have guessed letters: " << guessed_letters
                 << std::endl;
        }

        std::string guess = "";
        std::cout << "Guess a letter: ";
        getline(std::cin, guess);

        if (guess.size() != 1)
        {
            std::cout << "You failed: give exactly one letter!"
                 << std::endl;
            continue;
        }
        else if (guessed_letters.find(guess) != std::string::npos)
        {

            std::cout << "You failed: you had already guessed the letter " << guess << "!"
                 << std::endl;
            continue;
        }

        guessed_letters += guess;

        if (secret_word.find(guess) == std::string::npos)
        {
            std::cout << "Guessed letter does not include the word!" << std::endl;
        }

        ++guesses_used;
    }

    if (not is_word_already_guessed(secret_word, guessed_letters))
    {
        std::cout << std::endl
             << "Guesses expired!"
             << std::endl;
    }
    else
    {
        std::cout << std::endl
             << "Right guess. You used " << guesses_used
             << " guesses!"
             << std::endl;
    }
}

void clean_screen()
{
    // Cleaning screen by printing 100 empty lines.
    for (int i = 0; i < 100; ++i)
    {
        std::cout << std::endl;
    }
}


bool is_word_already_guessed(std::string secret, std::string guessed)
{
    // Going through all the characters in secret string.
    for (std::string::size_type index = 0; index < secret.size(); ++index)
    {
        // If such a character in secret string is met that is not in
        // guessed letters, it can be immediately concluded that
        // the whole secret word has not yet guessed.
        if (guessed.find(secret.at(index)) == std::string::npos)
        {
            return false;
        }
    }

    // When all the secret string has been gone through, and each character
    // was found from guessed string, it must hold that the whole
    // secret word has been guessed.
    return true;
}


void print_game_status(std::string secret, std::string guessed)
{
    // The characters of a string can be gone through also with such a for loop
    // that looks like "for x in y" structure in Python.
    // This is an alternative for the for loop with index variable
    // used in previous function.
    for (char secret_char: secret)
    {
        if (guessed.find(secret_char) == std::string::npos)
        {
            std::cout << "_";
        }
        else
        {
            std::cout << secret_char;
        }
    }

    std::cout << std::endl;
}
