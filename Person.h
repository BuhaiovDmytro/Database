//
// Created by dmytro on 20/04/2020.
//

#ifndef DATABASE_PERSON_H
#define DATABASE_PERSON_H

#include <string>

//An abstract class
class Person {
public:
    Person() {
        f_name = "";
        l_name = "";
        age = 0;
    };
    Person(std::string _f_name, std::string _l_name, int _age) : age(_age), f_name(_f_name), l_name(_l_name) {
        f_name = _f_name;
        l_name = _l_name;
        age = _age;
    };
    virtual void Display(bool ismanager) = 0;
    int GetAge();
    std::string Get_f_name();
    std::string Get_l_name();
protected:
    std::string f_name;//first name
    std::string l_name;//last name
    int age;
};

#endif //DATABASE_PERSON_H
