#include <iostream>
#include <fstream>
#include <string>

bool fileManr(std::string input, std::string output)
{
    std::ifstream inptFile(input);

    if (not inptFile) {
        return false;
    }

    std::ofstream outFile(output);
    std::string inLine;
    while (getline(inptFile, inLine)) {
        outFile << inLine << std::endl;
    }

    inptFile.close();
    outFile.close();

    return true;
}

int main()
{
    std::string inptFilename;
    std::cout << "Input file: ";
    std::cin >> inptFilename;

    std::string outFilename;
    std::cout << "Output file: ";
    std::cin >> outFilename;

    if (fileManr(inptFilename, outFilename)) {
        return EXIT_SUCCESS;

    } else {
        std::cout << "Error! The file " << inptFilename <<  " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
}
