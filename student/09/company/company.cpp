/* TIE-02207
 * Assignment 9.3 Company
 * Juho Viljamaa 275354 viljamaa@student.tut.fi
 * .cpp file for given header file
 */


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
void Company::addNewEmployee(const std::string &id, const std::string &dep,
                             const double &time, std::ostream &output)
{
    // check if employee already exists in data structure
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

    // check that both employees exist in main data structure using getPointer
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

    // getPointer check and pointer redirection
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

    // getPointer check and pointer redirection
    if (getPointer(id, empPtr, output)) {
        // check if an employee has a boss
        if (empPtr->boss_ != nullptr) {
            printSet.insert(empPtr->boss_->id_);
        }
        // print using printGroup
        printGroup(id, "boss", printSet, output);
    }
}

/* Description: Prints the colleagues for the employee.
 *  (Employees who shares their direct boss)
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */
void Company::printColleagues(const std::string &id, std::ostream &output) const
{
    Employee* empPtr = nullptr;
    std::vector<Employee *> colVec;

    // getPointer check and pointer redirection
    if (getPointer(id, empPtr, output)) {
        for (auto idPair : employeeMainMap_) {
            // person is id's colleague if they have the same boss
            if (idPair.second->boss_ == empPtr->boss_
                    and idPair.second != empPtr and empPtr->boss_ != nullptr) {
                colVec.push_back(idPair.second);
            }
        }
        // print colleagues
        printGroup(id, "colleagues", VectorToIdSet(colVec), output);
    }
}

/* Description: Prints all-level colleagues for the employee.
 *  (Employees who share their department and belong to the same hierarchy)
 * Parameters:
 *  Param1: ID of the person
 *  Param2: Output-stream for printing
 */
void Company::printDepartment(const std::string &id, std::ostream &output) const
{
    Employee* empPtr = nullptr;
    std::vector<Employee *> colVec;

    // getPointer check and pointer redirection
    if (getPointer(id, empPtr, output)) {
        // find big boss of id
        Employee* bigBoss = getBigBoss(empPtr);

        for (auto idPair : employeeMainMap_) {
            Employee* otherEmp = idPair.second;

            // make sure 'otherEmp' doesn't point to same place as 'empPtr'
            if (otherEmp != empPtr) {
                // person is id's department colleague if they have the same
                // department and same big boss
                if (otherEmp->department_ == empPtr->department_
                        and getBigBoss(otherEmp) == bigBoss) {
                    colVec.push_back(idPair.second);
                }
            }
        }
        // print colleagues
        printGroup(id, "department colleagues", VectorToIdSet(colVec), output);
    }
}

/* Description: Prints the employee with the longest time in service
 *  in the ID's line management.
 * Parameters:
 *  Param1: ID of the employee
 *  Param2: Output-stream for printing
 */
void Company::printLongestTimeInLineManagement(const std::string &id,
                                               std::ostream &output) const
{
    Employee* empPtr = nullptr;
    // pointer to person with longest time served
    Employee* longestEmpPtr = nullptr;

    // getPointer check and pointer redirection
    if (getPointer(id, empPtr, output)) {
        longestEmpPtr = empPtr;
        double longestTime = empPtr->time_in_service_;

        for (auto subordinate : empPtr->subordinates_) {
            // check if subordinate has longer served time than current longest time
            if (subordinate->time_in_service_ > longestTime) {
                // redirect longestEmpPtr
                longestEmpPtr = subordinate;
                longestTime = subordinate->time_in_service_;
            }
        }

        // determine suitable output format
        if (longestEmpPtr->id_ == id) {
            output << "With the time of " << longestTime << ", " << id
                   << " is the longest-served employee in their line management."
                   << std::endl;
        } else {
            output << "With the time of " << longestTime << ", " <<
                      longestEmpPtr->id_ << " is the longest-served employee in "
                   << id << "'s line management."
                   << std::endl;
        }

    }
}

// Bonus tasks (not implemented)
void Company::printShortestTimeInLineManagement(const std::string &id, std::ostream &output) const
{
    std::string dummyStr = id;
    if (output) {}
}

void Company::printSubordinatesN(const std::string &id, const int n, std::ostream &output) const
{
    std::string dummyStr = id;

    if (output and n == 1) {}
}

void Company::printBossesN(const std::string &id, const int n, std::ostream &output) const
{
    std::string dummyStr = id;
    if (output and n == 1) {}
}

// private methods

/* Returns true if key 'id' exists in 'employeeMainMap', else false. If 'id' is
 * present, 'empPtr' is also redirected to point at the same place that value
 * of key 'id'. Else an error message is printed if parameter 'printError'
 * is 'true' (default value).
 */
bool Company::getPointer(const std::string &id, Employee *&empPtr,
                         std::ostream &output, bool printError) const
{
    // check if key 'id' exists
    if (employeeMainMap_.find(id) != employeeMainMap_.end()) {
        // redirect input pointer
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

// Turns a vector of employees to a set of IDs ('IdSet' type).
IdSet Company::VectorToIdSet(const std::vector<Employee *> &container) const
{
    IdSet returnSet = {};
    for (auto personPtr : container) {
        returnSet.insert(personPtr->id_);
    }

    return returnSet;
}

// Prints the the data in a container of 'IdSet' type.
void Company::printGroup(const std::string &id, const std::string &group,
                         const IdSet &container, std::ostream &output) const
{
    // check if given container is empty
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

// returns pointer to boss of id's hierarchy (recursive function)
Employee *Company::getBigBoss(Employee *curEmpPtr) const
{
    if (curEmpPtr->boss_ == nullptr) {
        return curEmpPtr;

    } else {
        return getBigBoss(curEmpPtr->boss_);
    }
}

