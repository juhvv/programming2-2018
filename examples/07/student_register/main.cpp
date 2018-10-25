#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string HELP_TEXT = "N = List ordered by student numbers\n"
                         "U = List ordered alphabetically by user ids\n"
                         "Q = Quit\n";

struct Student {
    std::string student_number;
    std::string user_id;
    std::string name;
    std::string phone_number;
    std::string email;
    std::string skype;
};

std::vector<std::string> split(const std::string& s, const char delimiter, const bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}


bool read_data(const std::string file_name, map< string, Student* >& alphabetical_order, map< string, Student* >& numerical_order) {
    ifstream file_object(file_name);
    if( !file_object ) {
        return false;
    }

    string line = "";

    while( getline( file_object, line ) ) {
        std::vector<std::string> parts = split(line, ';');
        if(parts.size() != 6) {
            return false;
        }

        Student* new_student = new Student({parts[0], parts[1], parts[2], parts[3], parts[4], parts[5]});
        numerical_order[parts[0]] = new_student;
        alphabetical_order[parts[1]] = new_student;
    }
    return true;
}


void print_data(const Student o) {
    std::cout << o.student_number << " " << o.user_id << std::endl
              << o.name << std::endl
              << o.phone_number << std::endl
              << o.email << std::endl
              << o.skype << std::endl << std::endl;
}


int main() {
    string file_name = "";
    cout << "Student file: ";
    getline(cin, file_name);

    map< std::string, Student* > user_ids;
    map< std::string, Student* > student_numbers;
    if(not read_data(file_name, user_ids, student_numbers)) {
        cout << "Error in reading file!" << std::endl;
        return EXIT_FAILURE;
    }

    while(true) {
        std::cout << HELP_TEXT << std::endl;
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        if(parts.empty()) {
            continue;
        }
        std::string command = parts.at(0);

        // Printing in alphabetical order by user ids
        if(command == "U" or command == "u") {
            if(parts.size() != 1) {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            } else {
                for(auto pair: user_ids) {
                    print_data(*(pair.second));
                }
            }

            // Printing in numerical order by student numbers
        } else if(command == "N" or command == "n") {
            if(parts.size() != 1){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            } else {
                for(auto pair: student_numbers) {
                    print_data(*(pair.second));
                }
            }

            // Modifying student data
        } else if(command == "M" or command == "m") {
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }

            string id = parts.at(1);
            // TODO: Add functionality here

        } else if(command == "Q" or command == "q") {
            // Deleting the data structure: nullifying pointers and deallocating memory
            for(auto pair: student_numbers) {
                pair.second = nullptr;
            }

            for(auto pair: user_ids) {
                delete pair.second;
                pair.second = nullptr;
            }

            return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}


