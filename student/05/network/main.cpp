#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void netPrinter( const std::string& id, const std::map< std::string, std::vector< std::string > >& netMap, std::string& indent)
{
    // print current id with current indent
    std::cout << indent << id << std::endl;

    // if current id excists in netMap:
    // -> it has sub-value(s) to be printed
    // -> therefore indentation needs to increase by 2 chars
    if (netMap.find(id) != netMap.end()) {
        indent += "..";

        // start going through sub-values of this id
        for (std::string val : netMap.at(id)) {

            // recursive call with current indent
            netPrinter(val, netMap, indent);
        }
        // after sub-values of this id are printed, delete two chars from indentation
        // -> indentation becomes the same it was before sub-value printing
        indent.erase(0, 2);
    }
    // if current id does not excist in netMap, do nothing else
}

void netCounter( const std::string& id, const std::map< std::string, std::vector< std::string > >& netMap, int& count )
{
    ++count;
    if (netMap.find(id) != netMap.end()) {
        // start going through sub-values of this id
        for (std::string val : netMap.at(id)) {

            // recursive call with current count
            netCounter(val, netMap, count);
        }
    }
    // if current id does not excist in netMap, do nothing else
}

void depthCounter( const std::string& id, const std::map< std::string, std::vector< std::string > >& netMap, int& dCount)
{

    ++dCount;
    if (netMap.find(id) != netMap.end()) {


        // start going through sub-values of this id
        for (std::string val : netMap.at(id)) {

            // recursive call with current indent
            depthCounter(val, netMap, dCount);
            //dCount -= 1;
        }

        dCount -= 1;

    }
    // if current id does not excist in netMap, do nothing else
}


int main()
{
    // TODO: Implement the datastructure here
    std::map< std::string, std::vector< std::string > > netMap;


    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!  << Done!
            if (netMap.find(id1) == netMap.end()) {
                std::vector< std::string > tempVec = {id2};
                netMap.insert( {id1, tempVec} );

            } else {
                netMap.at(id1).push_back(id2);
            }

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!  << Done!

            std::string indent;
            netPrinter(id, netMap, indent);


        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!  << Done!
            int count = -1;
            netCounter(id, netMap, count);
            std::cout << count << std::endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!  << Done!

            int dCount = 1;
            if (netMap.find(id) != netMap.end()) {
                depthCounter(id, netMap, dCount);

            } else { dCount = 1; }
            std::cout << dCount << std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
