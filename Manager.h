//
// Created by dmytro on 20/04/2020.
//

#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Employee.h"
#include <list>

class Manager : public Employee {
public:
    Manager() {
        f_name = "";
        l_name = "";
        age = 0;
        department = "";
        salary = 0;
        id = 0;
        subordinates;
    };
    Manager(std::string _f_name, std::string _l_name, int _age, int _id) : Employee(_f_name, _l_name, _age, _id) {
        subordinates;
    };
    Manager(const Manager& m);
    Manager& operator=(const Manager& m);
    //add an employee to the subordinates list
    Person* AddSubordinate(Person* p);
    void FireSubordinates(Person* p);
    std::list<Person*> GetSubordinates();
private:
    std::list<Person*> subordinates;
};

#endif //DATABASE_MANAGER_H
