//
// Created by dmytro on 20/04/2020.
//

#include "Manager.h"


Manager::Manager(const Manager& m) {
    f_name = m.f_name;
    l_name = m.l_name;
    age = m.age;
    department = m.department;
    salary = m.salary;
    id = m.id;
    subordinates = m.subordinates;
}

Manager& Manager::operator=(const Manager& m) {
    this->f_name = m.f_name;
    this->l_name = m.l_name;
    this->age = m.age;
    this->department = m.department;
    this->salary = m.salary;
    this->id = m.id;
    this->subordinates = m.subordinates;
    return *this;
}

Person* Manager::AddSubordinate(Person* p) {
    subordinates.push_back(p);
    return p;
}

void Manager::FireSubordinates(Person* p) {
    dynamic_cast<Manager*>(p)->subordinates.clear();
}

std::list<Person *> Manager::GetSubordinates() {
    return subordinates;
}

