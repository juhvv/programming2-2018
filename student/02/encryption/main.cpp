#include <iostream>
#include <string>
#include <cctype>

bool input_chk( std::string en_input );
bool letterchk( std::string c_string );
void encrypter( std::string& en_str, std::string en_key);

int main()
{
    std::cout << "Enter the encryption key: ";
    std::string en_key = "";
    std::cin >> en_key;

    if ( input_chk( en_key) ) {
        std::cout << "Enter the text to be encrypted: ";
        std::string en_str = "";
        std::cin >> en_str;

        encrypter( en_str, en_key );
        std::cout << "Encrypted text: " + en_str << std::endl;

    } else {
        return EXIT_FAILURE;
    }
}


bool input_chk( std::string en_input ) {
    if ( en_input.length() != 26 ) {
        std::cout << "Error! The encryption key must contain 26 characters." << std::endl;
        return 0;

    } else if ( not letterchk( en_input ) ) {
        return 0;

    } else {
        return 1;
    }
}

bool letterchk( std::string c_string ) {

    for ( char letter:c_string ) {
        if ( isupper(letter) or not ('a' <= letter and letter <= 'z')) {
            std::cout << "Error! The encryption key must contain only lower case characters." << std::endl;
            return 0;
        }
    }

    for ( char letter = 'a'; letter < 'z'; ++letter) {
        if ( c_string.find(letter) == std::string::npos ) {
            std::cout << "Error! The encryption key must contain all alphabets a-z." << std::endl;
            return 0;
        }
    }
    return 1;
}

void encrypter( std::string& en_str, std::string en_key) {
    std::string en_text = "";
    for ( char letter:en_str ) {
        int alpha_pos = letter - 97;
        en_text += en_key.at(alpha_pos);
    }
    en_str = en_text;
}
