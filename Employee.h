//
// Created by dmytro on 20/04/2020.
//

#ifndef DATABASE_EMPLOYEE_H
#define DATABASE_EMPLOYEE_H

#include "Person.h"
#include <iostream>

class Employee : public Person {
public:
    Employee() {
        f_name = "";
        l_name = "";
        age = 0;
        department = "";
        salary = 0;
        id = 0;
    };
    Employee(std::string _f_name, std::string _l_name, int _age, int _id) : Person(_f_name, _l_name, _age), id(_id) {
        department = "";
        salary = 0;
        id = _id;
    };
    Employee(const Employee& e);
    Employee& operator=(const Employee& e);
    void SetSalary(double s);
    void SetDepartment(std::string dept);
    void SetId(int n);
    int GetId();
    std::string GetDepartment();
    virtual void Display(bool ismanager){
        std::cout << "\n\nEmployment type: " << (ismanager ? "manager" : "employee");
        std::cout << "\nid: " << id;
        std::cout << "\n" << f_name << " " << l_name << " age: " << age;
        std::cout << " salary: " << salary;
        std::cout << "\ndepartment: " << department;
    };
    double GetSalary();

protected:
    std::string department;
    double salary;
    int id;
};

#endif //DATABASE_EMPLOYEE_H
