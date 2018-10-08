#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>

const double SOLDOUT = -1;

struct Product {
         std::string product_name;
         double price;
     };

bool operator <(const Product& pro1, const Product& pro2) {
    return pro1.product_name < pro2.product_name;
}

bool is_cheaper (const Product& pro1, const Product& pro2) {
    return pro1.price < pro2.price;
}


struct storeInfo {
        std::string sLoc;
        std::set < Product > proSet;

        void insert_pro ( Product nPro ) {
            if ( proSet.find(nPro) != proSet.end()) {
                proSet.erase(nPro);
            }
            proSet.insert(nPro);
        }
    };

bool operator <(const storeInfo& pin1, const storeInfo& pin2 ) {
    return pin1.sLoc < pin2.sLoc;
}

bool search_product (std::set < Product > targetSet, std::string searchName) {
    for (Product pro : targetSet) {
        if (pro.product_name == searchName) { return true; }
    }
    return false;
}

bool search_store (const std::map < std::string, storeInfo >& targetSet, const std::string& searchName) {
    for (auto store : targetSet) {
        if (store.second.sLoc == searchName) { return true; }
    }
    return false;
}


void data_handler(std::map < std::string, std::map < std::string, storeInfo > >& shopsData, const std::string& stoChain, const std::string& stoName, const std::string& proName, const double& proPrice ) {

    Product newPro = {proName, proPrice};

    if (shopsData.find(stoChain) == shopsData.end()) {
        shopsData.insert( {stoChain, {}} );
    }

    std::map < std::string, storeInfo >& cStores = shopsData.at(stoChain);
    if ( not search_store( cStores, stoName ) ) {
        storeInfo newStore = {stoName, {newPro}};
        cStores.insert({stoName, newStore});

    } else {
        //std::set < storeInfo >::iterator storeIter = cStores.begin();
        cStores.at(stoName).insert_pro(newPro);
    }
}

bool reader( const std::string& fName, std::map < std::string, std::map < std::string, storeInfo > >& shopsData )
{
    std::ifstream inptFile(fName);

    if (not inptFile) {
        return false;
    }

    std::string inLine;

    while (getline(inptFile, inLine)) {
        std::stringstream sLine(inLine);
        std::vector < std::string > tempVec = {};

        while (getline(sLine, inLine, ';')) {
            tempVec.push_back(inLine);
        }

        if (tempVec.size() != 4) {
            return false;
        }

        std::string stoChain = tempVec.at(0);
        std::string stoName = tempVec.at(1);
        std::string proName = tempVec.at(2);

        double proPrice;
        if (tempVec.at(3) == "out-of-stock") { proPrice = SOLDOUT;} else { proPrice = stod(tempVec.at(3));}

        data_handler(shopsData, stoChain, stoName, proName, proPrice);
    }

    inptFile.close();

    return true;
}


int main()
{
    std::map < std::string, std::map < std::string, storeInfo > > shopsData;

    std::string fileName;
    std::cout << "Input file: ";
    std::cin >> fileName;

    if (not reader(fileName, shopsData)) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    }

    while(true){

        std::string command;
        std::cout << "> ";
        getline(std::cin, command);
        /*
        std::stringstream sLine(line);
        std::vector<std::string> parts;

        while (getline(sLine, line, ';')) { parts.push_back(line); }
        */
        //std::string command = parts.at(0);
        if (command == "debug" or command == "dd") {
            for ( auto store : shopsData) {
                std::cout << store.first << std::endl;
                for ( auto sstore : store.second ) {
                    std::cout << "--" << sstore.second.sLoc << std::endl;
                    for ( Product sPro : sstore.second.proSet ) {
                        std::cout << "---" << sPro.product_name << " " << sPro.price << std::endl;
                    }
                }
            }

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl;
        }
    }


}
