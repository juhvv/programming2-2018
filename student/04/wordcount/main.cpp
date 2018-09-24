#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

bool reader(std::string inputNam, std::map< std::string, std::vector< int > >& wordMap)
{
    std::ifstream inptFile(inputNam);

    if (not inptFile) {
        return false;
    }

    std::string inLine;
    std::vector< int > tempVec;
    int lineNum = 1;

    while (getline(inptFile, inLine)) {
        std::stringstream sLine(inLine);

        while (getline(sLine, inLine, ' ')) {
            if (wordMap.find(inLine) == wordMap.end()) {
                tempVec = { lineNum };
                wordMap.insert( {inLine, tempVec} );

            } else {
                wordMap.at(inLine).push_back(lineNum);
            }
        }

        ++lineNum;
    }

    inptFile.close();

    return true;
}

void printer(std::map< std::string, std::vector< int > >& wordMap)
{
    for ( auto data_pair : wordMap ) {
          std::cout << data_pair.first << " " << data_pair.second.size() << ": ";

          bool first = true;
          for ( int const lNum : data_pair.second) {
              if (first) { first = false; } else { std::cout << ", ";}
              std::cout << lNum;
          }
          std::cout << std::endl;
    }
}

int main()
{
    std::map< std::string, std::vector< int > > wordMap;
    std::string inputNam;

    std::cout << "Input file: ";
    std::cin >> inputNam;

    if (reader(inputNam, wordMap)) {
        printer(wordMap);
        return EXIT_SUCCESS;

    } else {
        std::cout << "Error! The file " << inputNam << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
}
