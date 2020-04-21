//
// Created by dmytro on 20/04/2020.
//

#include "Employee.h"

Employee::Employee(const Employee& e) {
    f_name = e.f_name;
    l_name = e.l_name;
    age = e.age;
    department = e.department;
    salary = e.salary;
    id = e.id;
}

Employee& Employee::operator=(const Employee& e) {
    this->f_name = e.f_name;
    this->l_name = e.l_name;
    this->age = e.age;
    this->department = e.department;
    this->salary = e.salary;
    this->id = e.id;
    return *this;
}

void Employee::SetSalary(double s) {
    salary = s;
}

void Employee::SetDepartment(std::string dept) {
    department = dept;
}

void Employee::SetId(int n) {
    id = n;
}

int Employee::GetId() {
    return id;
}

std::string Employee::GetDepartment() {
    return department;
}

double Employee::GetSalary() {
    return salary;
}

