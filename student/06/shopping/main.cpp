#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>

// constant for representing unavailability of a product as double
const double SOLDOUT = -1;

// Struct for storing product info
struct Product {
         std::string product_name;
         double price;
     };

bool operator <(const Product& pro1, const Product& pro2) {
    return pro1.product_name < pro2.product_name;
}

// help function
bool is_cheaper (const Product& pro1, const Product& pro2) {
    return pro1.price < pro2.price;
}

// Struct for storing products of a single store
struct storeSt {
        std::set < Product > proSet;

        // Method for inserting products to product list
        void insert_pro ( Product nPro ) {
            // old values are overwritten with new ones
            if ( proSet.find(nPro) != proSet.end()) {
                proSet.erase(nPro);
            }
            proSet.insert(nPro);
        }
    };

// help function
bool search_product (std::set < Product > targetSet, std::string searchName)
{
    for (Product pro : targetSet) {
        if (pro.product_name == searchName) { return true; }
    }
    return false;
}

// Function for saving data read from file to programs data structure
void data_handler(std::map < std::string, std::map < std::string, storeSt > >& shopsData, const std::string& stoChain, const std::string& stoName, const std::string& proName, const double& proPrice )
{

    Product newPro = {proName, proPrice};

    if (shopsData.find(stoChain) == shopsData.end()) {
        shopsData.insert( {stoChain, {}} );
    }

    std::map<std::string, storeSt> &storesInChain = shopsData.at(stoChain);
    if ( storesInChain.find(stoName) == storesInChain.end() ) {
        storeSt newStore = {{newPro}};
        storesInChain.insert({stoName, newStore});

    } else {
        //std::set < storeInfo >::iterator storeIter = cStores.begin();
        storesInChain.at(stoName).insert_pro(newPro);
    }
}

// Function for reading file and passing its contents forward
bool reader( const std::string& fileName, std::map < std::string, std::map < std::string, storeSt > >& shopsData )
{
    std::ifstream inptFile(fileName);
    if (not inptFile) {
        return false;
    }
    std::string inputString;

    while (getline(inptFile, inputString)) {
        // process single line as a stream
        std::stringstream lineStream(inputString);

        // vector for storing read contents
        std::vector <std::string> tempVec = {};

        while (getline(lineStream, inputString, ';')) {
            tempVec.push_back(inputString);
        }
        // check file formating
        if (tempVec.size() != 4) {
            return false;
        }
        // sort read contents
        std::string stoChain = tempVec.at(0);
        std::string stoName = tempVec.at(1);
        std::string proName = tempVec.at(2);

        double proPrice;
        // converting read string to aproppriate double value
        if (tempVec.at(3) == "out-of-stock") { proPrice = SOLDOUT;} else { proPrice = stod(tempVec.at(3));}

        // call to store data to program
        data_handler(shopsData, stoChain, stoName, proName, proPrice);

    }

    inptFile.close();

    return true;
}

// Function for handling set 'cheapStores', condition 'r' clears set before inserting new value
void addCheapStore(std::set <std::string>& cheapStores, std::string newStore, char condition = ' ')
{
    if (condition == 'r') {
        cheapStores.clear();
    }
    cheapStores.insert(newStore);
}

// Function for printing cheapest price and store(s) for a product
void cheapest_printer(const std::map < std::string, std::map < std::string, storeSt > >& shopsData, const std::string& product)
{
    std::set <std::string> cheapStores = {};
    // start value for lowest price is set to something absurd that is easy to compare
    double lowestPrice = -2;

    // go through all chains, their stores and products
    for ( auto stoChain : shopsData) {
        for ( auto store : stoChain.second ) {
            for ( Product sPro : store.second.proSet ) {

                // check if current product is the searched product
                if (sPro.product_name == product)  {
                    // save current chain and store
                    std::string curChainStore = stoChain.first + " " + store.first;
                    // lowest price is < 0 -> lowestPrice has its start value -> always change that value
                    if (lowestPrice < 0) {
                        lowestPrice = sPro.price;
                        addCheapStore(cheapStores, curChainStore);

                    // current price non-negative and less than current lowest price:
                    } else if (sPro.price > 0 and sPro.price < lowestPrice) {
                        // set new lowest price
                        lowestPrice = sPro.price;
                        // clear current store set before applying the new store
                        addCheapStore(cheapStores, curChainStore, 'r');

                    // current price is the cheapest price -> append this store to store set
                    } else if (not (sPro.price < lowestPrice) and not (sPro.price > lowestPrice)) {
                        addCheapStore(cheapStores, curChainStore);
                    }
                }
            }
        }
    }
    // lowest price has its start value; no products found
    if (lowestPrice < -1) {
        std::cout << "Product is not part of product selection."<< std::endl;

    // lowest price is -1; product out of stock everywhere
    } else if (lowestPrice < 0 and lowestPrice > -2) {
        std::cout << "The product is temporarily out of stock everywhere." << std::endl;

    // print cheapest price and stores
    } else {
        std::cout << std::fixed << std::setprecision(2) << lowestPrice << "e" << std::endl;
        for (auto store : cheapStores) { std::cout << store << std::endl; }
    }
}

// Function for printing all products in all stores
void product_printer(const std::map < std::string, std::map < std::string, storeSt > >& shopsData)
{
    // set for storing product names
    std::set <std::string> printSet = {};

    // go through all products in all stores
    for ( auto stoChain : shopsData) {
        for ( auto store : stoChain.second ) {
            for ( Product sPro : store.second.proSet ) {
                printSet.insert(sPro.product_name);
            }
        }
    }
    // print out collected list
    for ( std::string proNam : printSet) {std::cout << proNam << std::endl;}
}

// prints error messages of desired type
void error_printer(std::string errorType = "", std::string command = "")
{
    std::string errorMsg = "unknown ";

    if (errorType == "cmd") {
        errorMsg = "error in command " + command;

    } else if ( errorType == "ch" ) {
        errorMsg += "chain";
    } else if ( errorType == "st" ) {
        errorMsg += "store";
    } else {
        errorMsg += "command";
    }

    std::cout << "Error: " << errorMsg << std::endl;
}

// main
int main()
{
    std::map < std::string, std::map < std::string, storeSt > > shopsData;

    std::string fileName;
    std::cout << "Input file: ";
    getline(std::cin, fileName);

    if (not reader(fileName, shopsData)) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    }

    while(true){

        std::string line = "";
        std::cout << "> ";

        getline(std::cin, line);

        std::stringstream lineStream(line);
        std::vector<std::string> parts = {};

        while (getline(lineStream, line, ' ')) { parts.push_back(line); }
        std::string command = parts.at(0);

        if (command == "chains") {
            for ( auto chain : shopsData ) { std::cout << chain.first << std::endl;}

        } else if (command == "stores") {
            if (parts.size() == 2) {
                std::string inptChain = parts.at(1);
                if (shopsData.find(inptChain) != shopsData.end()){
                    for ( auto store : shopsData.at(inptChain) ) { std::cout << store.first << std::endl; }
                } else { error_printer("ch"); }

            } else {
                error_printer("cmd", command);
            }

        } else if (command == "selection") {
            if (parts.size() == 3) {
                std::string inptChain = parts.at(1);
                std::string store = parts.at(2);

            } else {
                error_printer("cmd", command);
            }

        } else if (command == "cheapest") {
            if (parts.size() == 2) {
                std::string product = parts.at(1);
                cheapest_printer(shopsData, product);

            } else {
                error_printer("cmd", command);
            }

        } else if (command == "products") {
            product_printer(shopsData);
        }

        else if (command == "debug" or command == "dd") {
            for ( auto store : shopsData) {
                std::cout << store.first << std::endl;
                for ( auto sstore : store.second ) {
                    std::cout << "--" << sstore.first << std::endl;
                    for ( Product sPro : sstore.second.proSet ) {
                        std::cout << "---" << sPro.product_name << " " << sPro.price << std::endl;
                    }
                }
            }

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            error_printer();
        }
    }


}
