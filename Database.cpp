//
// Created by dmytro on 19/04/2020.
//

#include "Database.h"

Database::Database() {
    employees.reserve(1);
}

bool Database::LoadFromJSON(std::string file) {
    std::ifstream inputfile(file);
    if(!inputfile.is_open()){
        return false;
    }
    nlohmann::json json_input;
    inputfile >> json_input;
    nlohmann::json tmp;
    for (nlohmann::json::iterator it = json_input.begin(); it != json_input.end(); ++it) {
        tmp = *it;
        if (tmp["ismanager"] == 0) {
            Employee* tmp_employee = new Employee(tmp["f_name"], tmp["l_name"], tmp["age"], tmp["id"]);
            tmp_employee->SetDepartment(tmp["department"]);
            tmp_employee->SetSalary(tmp["salary"]);
            employees.push_back(tmp_employee);
        }
        else {
            Manager *tmp_manager = new Manager(tmp["f_name"], tmp["l_name"], tmp["age"], tmp["id"]);
            tmp_manager->SetDepartment(tmp["department"]);
            tmp_manager->SetSalary(tmp["salary"]);

            //adding subordinates
            const nlohmann::json &subordinates = tmp["subordinates"];
            for (unsigned int i = 0; i < subordinates.size(); i++) {
                Employee *tmp_sub = new Employee(subordinates[i]["f_name"], subordinates[i]["l_name"], subordinates[i]["age"], subordinates[i]["id"]);
                tmp_sub->SetDepartment(subordinates[i]["department"]);
                tmp_sub->SetSalary(subordinates[i]["salary"]);
                tmp_manager->AddSubordinate(tmp_sub);
        }
            employees.push_back(tmp_manager);
        }
    }
    inputfile.close();
    if(inputfile.is_open()){
        return false;
    }
    return true;
}

nlohmann::json Database::Buffer_to_JSON(Person* p) {
    nlohmann::json json_output, json_tmp, json_subs, json_subs_tmp;
        if(typeid(*p) == typeid(Employee)){
            json_tmp = {
                    {"ismanager",0},
                    {"id",dynamic_cast<Employee*>(p)->GetId()},
                    {"f_name",dynamic_cast<Employee*>(p)->Get_f_name()},
                    {"l_name",dynamic_cast<Employee*>(p)->Get_l_name()},
                    {"age",dynamic_cast<Employee*>(p)->GetAge()},
                    {"department",dynamic_cast<Employee*>(p)->GetDepartment()},
                    {"salary",dynamic_cast<Employee*>(p)->GetSalary()}
            };
        }
        else if(typeid(*p) == typeid(Manager)){
            json_tmp = {
                    {"ismanager",1},
                    {"id",dynamic_cast<Manager*>(p)->GetId()},
                    {"f_name",dynamic_cast<Manager*>(p)->Get_f_name()},
                    {"l_name",dynamic_cast<Manager*>(p)->Get_l_name()},
                    {"age",dynamic_cast<Manager*>(p)->GetAge()},
                    {"department",dynamic_cast<Manager*>(p)->GetDepartment()},
                    {"salary",dynamic_cast<Manager*>(p)->GetSalary()},
                    //{"subordinates"}
            };
            //adding subordinates
            std::list<Person*> subslist = dynamic_cast<Manager*>(p)->GetSubordinates();
            for (std::list<Person*>::iterator i = subslist.begin(); i != subslist.end(); i++) {
                Person *sub = *i;
                json_subs_tmp = {
                        {"ismanager",0},
                        {"id",dynamic_cast<Employee*>(sub)->GetId()},
                        {"f_name",dynamic_cast<Employee*>(sub)->Get_f_name()},
                        {"l_name",dynamic_cast<Employee*>(sub)->Get_l_name()},
                        {"age",dynamic_cast<Employee*>(sub)->GetAge()},
                        {"department",dynamic_cast<Employee*>(sub)->GetDepartment()},
                        {"salary",dynamic_cast<Employee*>(sub)->GetSalary()}
                };
                json_subs.push_back(json_subs_tmp);
                json_subs_tmp.clear();
            }
            json_tmp["subordinates"] = json_subs;
            json_subs.clear();
        }
    return json_tmp;
}

bool Database::UpdateJSON(std::string file) {
    std::ofstream outputfile(file);
    if(!outputfile.is_open()){
        return false;
    }
    outputfile << std::setw(4) << All_Buffer_to_JSON() << std::endl;
    outputfile.close();
    if(outputfile.is_open()){
        return false;
    }
    return true;
}


Person* Database::FindManager(std::string _department) {
    for (std::vector<Person*>::iterator i = employees.begin(); i != employees.end(); i++) {
        Person* p = *i;
        if ((typeid(*p) == typeid(Manager))&&((dynamic_cast<Manager*>(p)->GetDepartment()) == _department)) {
            return p;
        }
    }
    return NULL;
}

void Database::ArrangeSubordinates() {
    //cleaning place for updated list
    for (std::vector<Person*>::iterator i = employees.begin(); i != employees.end(); i++) {
        Person* p = *i;
        if (typeid(*p) == typeid(Manager)) {
            dynamic_cast<Manager*>(p)->FireSubordinates(p);
        }
    }
    //filling updated list of subordinates
    for (std::vector<Person*>::iterator i = employees.begin(); i != employees.end(); i++) {
        Person* p = *i;
        if ((typeid(*p) == typeid(Employee))&&(dynamic_cast<Manager*>(FindManager(dynamic_cast<Employee*>(p)->GetDepartment())) != NULL)) {
            dynamic_cast<Manager*>(FindManager(dynamic_cast<Employee*>(p)->GetDepartment()))->AddSubordinate(p);
        }
    }
}

bool Database::HireEmployee(Person* p) {
    const unsigned int old_size = employees.size();
    employees.push_back(p);
    if (old_size < employees.size()) {
        return true;
    }
    else return false;
}

nlohmann::json Database::Srch_by_id(unsigned int _id) {
    for (std::vector<Person*>::iterator i = employees.begin(); i != employees.end(); i++) {
        Person* p = *i;
        if (((typeid(*p) == typeid(Manager)) && ((dynamic_cast<Manager*>(p)->GetId()) == _id))||((typeid(*p) == typeid(Employee)) && ((dynamic_cast<Employee*>(p)->GetId()) == _id))) {
            return Buffer_to_JSON(p);
        }
    }
    return nullptr;
}

bool Database::FireEmployee(unsigned int id) {
    const unsigned int old_size = employees.size();
    for (std::vector<Person*>::iterator i = employees.begin(); i != employees.end(); i++) {
        Person* p = *i;
        if (((typeid(*p) == typeid(Manager)) && ((dynamic_cast<Manager*>(p)->GetId()) == id)) || ((typeid(*p) == typeid(Employee)) && ((dynamic_cast<Employee*>(p)->GetId()) == id))) {
            employees.erase(i);
        }
    }
    if (old_size > employees.size()) {
        return true;
    }
    else return false;
}

nlohmann::json Database::All_Buffer_to_JSON() {
    nlohmann::json result;
    for (std::vector<Person*>::iterator i = employees.begin(); i != employees.end(); i++) {
        Person* p = *i;
        result.push_back(Buffer_to_JSON(p));
    }
    return result;
}


