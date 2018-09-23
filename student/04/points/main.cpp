#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

bool reader(std::string inputNam, std::map< std::string, int >& pointsMap)
{
    std::ifstream inptFile(inputNam);

    if (not inptFile) {
        return false;
    }

    std::string inLine;
    std::string::size_type sepPos;

    while (getline(inptFile, inLine)) {
        sepPos = inLine.find(":");

        if (sepPos == std::string::npos) {
            inptFile.close();
            return false;
        }

        std::string name = inLine.substr(0, sepPos);
        int points = stoi(inLine.substr(sepPos + 1));

        if ( pointsMap.find(name) == pointsMap.end() ) {
            pointsMap.insert( {name, points} );

        } else {
            pointsMap.at(name) += points;

        }

    }

    inptFile.close();

    return true;
}

void printer(std::map< std::string, int >& pointsMap)
{
    std::cout << "Final scores:" << std::endl;

    for ( auto data_pair : pointsMap ) {
            std::cout << data_pair.first << ": "
                 << data_pair.second << std::endl;
    }
}

int main()
{
    std::map< std::string, int > pointsMap;
    std::string inputNam;

    std::cout << "Input file: ";
    std::cin >> inputNam;

    if (reader(inputNam, pointsMap)) {
        printer(pointsMap);

    } else {
        std::cout << "Error! The file " << inputNam << " cannot be opened." << std::endl;
    }
}
