//
// Created by dmytro on 21/04/2020.
//

#include "Server.h"
#include "Database.h"


nlohmann::json Handler(nlohmann::json request) {
    nlohmann::json response;
    Database Data;
    std::string path = request["path"];
    if(!Data.LoadFromJSON(path)){
        response["result"] = "error while uploading database";
    }
    else {
        if (request["method"] == "display") {
            response["result"] = Data.All_Buffer_to_JSON();
        }
        else if(request["method"] == "hireemp"){
            bool result = 0;
            if(request["ismanager"] == 0) {
                Employee *new_employee = new Employee(request["f_name"], request["l_name"], request["age"],request["id"]);
                new_employee->SetDepartment(request["department"]);
                new_employee->SetSalary(request["salary"]);
                result = Data.HireEmployee(new_employee);
            }
            else if((request["ismanager"] == 1)&&(Data.FindManager(request["department"]) == NULL)){
                Manager *new_manager = new Manager(request["f_name"], request["l_name"], request["age"],request["id"]);
                new_manager->SetDepartment(request["department"]);
                new_manager->SetSalary(request["salary"]);
                result = Data.HireEmployee(new_manager);
            }
            if(result){
                response["result"] = "The new employee hired";
            }
            else{
                response["result"] = "Error while hiring the new employee, try another id";
            }
        }
        else if(request["method"] == "fireemp"){
            bool result = Data.FireEmployee(request["id"]);
            if(result){
                response["result"] = "Employee fired";
            }
            else{
                response["result"] = "Error while firing employee";
            }
        }
        else if(request["method"] == "srch_by_id"){
            if(Data.Srch_by_id(request["id"]) != nullptr) {
                response["result"] = Data.Srch_by_id(request["id"]);
            }
            else{
                response["result"] = "Couldn't find an employee with such id";
            }
        }
    }
    Data.ArrangeSubordinates();
    Data.UpdateJSON(path);
    return response;
}
