#include <iostream>
#include <string>
#include <vector>


// Do not change main function
void delNone(std::vector< std::string >& inptVec) {
   std::vector< int > delVec;

   int iter = 0;
   for (std::string vStr : inptVec) {
       if (vStr == "") {
           delVec.push_back(iter);
       }
       ++iter;
   }
   if (delVec.size() != 0) {
       int delOffset = 0;

       for (int posVal : delVec) {
           posVal -= delOffset;
           inptVec.erase(inptVec.begin() + posVal);
           ++delOffset;
       }
   }
}


std::vector< std::string > split(std::string inputStr, char sep, bool ignEmpStr = false)
{
    std::vector< std::string > retVec;
    std::string apStr = "";

    if (inputStr.find(sep) != std::string::npos) {
        for (char sChar : inputStr) {
            if (sChar != sep) {
                apStr += sChar;

             } else {
                retVec.push_back(apStr);
                apStr.erase(0);
            }

        }
        retVec.push_back(apStr);

        if (ignEmpStr) {
            delNone(retVec);
        }
        return retVec;

    } else {
        retVec.push_back(inputStr);
        return retVec;
    }

}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto o : parts ) {
        std::cout << o << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto o : parts_no_empty ) {
        std::cout << o << std::endl;
    }
}
