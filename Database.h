//
// Created by dmytro on 19/04/2020.
//

#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <vector>
#include <typeinfo>
#include <fstream>
#include "json.hpp"
#include "Manager.h"

class Database {

public:
    Database();
    ~Database() {};//no need in destructor
    nlohmann::json Buffer_to_JSON(Person* p);
    nlohmann::json All_Buffer_to_JSON();
    bool LoadFromJSON(std::string file);
    bool UpdateJSON(std::string file);
    //arranges "flat" database after loading from the file
    void ArrangeSubordinates();
    //hire a new employee
    bool HireEmployee(Person* p);
    nlohmann::json Srch_by_id(unsigned int _id);
    //fire the employee
    bool FireEmployee(unsigned int id);
    //void DisplayAll();
    Person* FindManager(std::string _department);

private:
    std::vector<Person*> employees;
};

#endif //DATABASE_DATABASE_H
