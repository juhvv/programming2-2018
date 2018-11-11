#include "company.hh"

// constructor of class Company
Company::Company()
{

}

// destructor of class Company
Company::~Company()
{
    // delete manually allocated data
    for (auto idPair : employeeMainMap_) {
        delete idPair.second;
    }
}

/* Description: Adds a new Employee to the datastructure.
 * Parameters:
 *  Param1: Employee's ID string
 *  Param2: Employee's department
 *  Param3: Employee's time in service
 *  Param4: Output-stream for error-printing
 * Errormessages:
 *  If employees's ID is already in datastructure:
 *      "Error. Employee already added."
 */
void Company::addNewEmployee(const std::string &id, const std::string &dep, const double &time, std::ostream &output)
{
    // check if employee already excists in data structure
    if (employeeMainMap_.find(id) == employeeMainMap_.end()) {
        // create new employee struct and store the pointer to 'employeeMainMap'
        Employee* newEmployee = new Employee{};
        employeeMainMap_.insert({id, newEmployee});

        // assign values to fields of the new struct
        newEmployee->id_ = id;
        newEmployee->department_ = dep;
        newEmployee->time_in_service_ = time;

    } else {
        // error message
        output << "Error. Employee already added." << std::endl;
    }

}

/* Description: Prints all stored Employees: ID, department and time in service
 * Parameters:
 *  Param1: Output-stream for printing
 * Errormessages:
 *  None.
 */
void Company::printEmployees(std::ostream &output) const
{
    for (auto idPair : employeeMainMap_) {
        auto curEmp = idPair.second;

        output << curEmp->id_ << ", " << curEmp->department_ << ", "
               << curEmp->time_in_service_ << std::endl;
    }
}

void Company::addRelation(const std::string &subordinate, const std::string &boss, std::ostream &output)
{

}

void Company::printSubordinates(const std::string &id, std::ostream &output) const
{

}

void Company::printBoss(const std::string &id, std::ostream &output) const
{

}

void Company::printColleagues(const std::string &id, std::ostream &output) const
{

}

void Company::printDepartment(const std::string &id, std::ostream &output) const
{

}

void Company::printLongestTimeInLineManagement(const std::string &id, std::ostream &output) const
{

}

void Company::printShortestTimeInLineManagement(const std::string &id, std::ostream &output) const
{

}

void Company::printSubordinatesN(const std::string &id, const int n, std::ostream &output) const
{

}

void Company::printBossesN(const std::string &id, const int n, std::ostream &output) const
{

}

