#include "company.hh"

// constructor of class Company
Company::Company() {}

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
void Company::addNewEmployee(const std::string &id, const std::string &dep,
                             const double &time, std::ostream &output)
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

/* Description: Adds new boss-subordinate relation
 * Parameters:
 *  Param1: ID of the subordinate
 *  Param2: ID of the boss
 *  Param3: Output-stream for error-printing
 */
void Company::addRelation(const std::string &subordinate,
                          const std::string &boss, std::ostream &output)
{
    Employee* bossPtr = nullptr;
    Employee* subPtr = nullptr;

    // check that both employees excist in main data structure using getPointer
    if (getPointer(subordinate, subPtr, output, false) and
            getPointer(boss, bossPtr, output, false)) {

        subPtr->boss_ = bossPtr;
        bossPtr->subordinates_.push_back(subPtr);
    }
}

/* Description: Prints direct subordinates for the employee.
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */
void Company::printSubordinates(const std::string &id, std::ostream &output) const
{
    Employee* empPtr = nullptr;

    if (getPointer(id, empPtr, output)) {
        printGroup(id, "subordinates", VectorToIdSet(empPtr->subordinates_),
                   output);
    }
}

/* Description: Prints the direct boss of the employee.
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */
void Company::printBoss(const std::string &id, std::ostream &output) const
{
    Employee* empPtr = nullptr;
    IdSet printSet = {};

    if (getPointer(id, empPtr, output)) {
        if (empPtr->boss_ != nullptr) {
            printSet.insert(empPtr->boss_->id_);
        }
        // print using printGroup
        printGroup(id, "bosses", printSet, output);
    }
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

// private methods

/* Returns true if key 'id' excists in 'employeeMainMap', else false. If 'id' is
 * present, 'empPtr' is also redirected to point at the same place that value
 * of key 'id'. Else an error message is printed if parameter 'printError'
 * is 'true' (default value).
 */
bool Company::getPointer(const std::string &id, Employee *&empPtr,
                         std::ostream &output, bool printError) const
{
    // check if key 'id' excists
    if (employeeMainMap_.find(id) != employeeMainMap_.end()) {
        // redirect reference pointer
        empPtr = employeeMainMap_.at(id);
        return true;

    } else {
        // no error printing if parameter 'printError' is false
        if (printError) {
            output << "Error. " << id << " not found." << std::endl;
        }
        return false;
    }
}

// Turns a vector of employees to a set of IDs.
IdSet Company::VectorToIdSet(const std::vector<Employee *> &container) const
{
    IdSet returnSet = {};
    for (auto personPtr : container) {
        returnSet.insert(personPtr->id_);
    }

    return returnSet;
}

// Prints the the data in a container.
void Company::printGroup(const std::string &id, const std::string &group, const IdSet &container, std::ostream &output) const
{
    if (container.size() != 0) {
        output << id << " has " << container.size() << " " << group
               << ":" << std::endl;
        for (auto person : container) {
            output << person << std::endl;
        }

    } else {
        output << id << " has no " << group << "." << std::endl;
    }
}
