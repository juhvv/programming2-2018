#include <iostream>
#include <string>

bool palindrome_recursive(std::string word)
{
    std::string::size_type size = word.length();
    if (size == 1 or size == 0) {
        return true;
    }

    if (word.at(0) == word.at(size - 1)) {
        word.erase(0,1);
        word.erase(size - 2);
        return palindrome_recursive(word);

    } else {
        return false;
    }
}


int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
