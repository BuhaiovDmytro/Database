#include "Server.h"

int main() {
    std::cout << "Please, input path to \"input.json\"(Example: /home/user/Database/input.json): ";
    std::string path;
    std::cin >> path;
    while(1) {
        std::cout << "\n\nMain menu:";
        std::cout << "\n1. Display the database";
        std::cout << "\n2. Add an employee";
        std::cout << "\n3. Delete an employee";
        std::cout << "\n4. Search employee by id";
        std::cout << "\n5. Quit";
        std::cout << "\n>> ";
        char mainmenu;
        std::cin >> mainmenu;
        switch (mainmenu) {
            case '1': {
                std::cout << "\nDisplay the database:\n";
                nlohmann::json request;
                request["path"] = path;
                request["method"] = "display";
                nlohmann::json response = Handler(request);
                std::cout << response["result"];
                break;
            }
            case '2': {
                std::cout << "\nAdd an employee:\n";
                nlohmann::json request;
                request["path"] = path;
                request["method"] = "hireemp";
                std::cout << "\nManager or subordinate?(1 - Manager, 0 - Subordinate): ";
                unsigned int tmp;
                std::cin >> tmp;
                request["ismanager"] = tmp;
                std::cout << "\nId: ";
                std::cin >> tmp;
                request["id"] = tmp;
                std::cout << "\nFirst name: ";
                std::string tmpstring;
                std::cin >> tmpstring;
                request["f_name"] = tmpstring;
                std::cout << "\nLast name: ";
                std::cin >> tmpstring;
                request["l_name"] = tmpstring;
                std::cout << "\nAge: ";
                std::cin >> tmp;
                request["age"] = tmp;
                std::cout << "\nDepartment: ";
                std::cin >> tmpstring;
                request["department"] = tmpstring;
                std::cout << "\nSalary: ";
                double tmpdouble;
                std::cin >> tmpdouble;
                request["salary"] = tmpdouble;
                nlohmann::json response = Handler(request);
                std::cout << response["result"];
                break;
            }
            case '3': {
                std::cout << "\nDelete an employee:\n";
                nlohmann::json request;
                request["path"] = path;
                request["method"] = "fireemp";
                std::cout << "\nId: ";
                int tmp;
                std::cin >> tmp;
                request["id"] = tmp;
                nlohmann::json response = Handler(request);
                std::cout << response["result"];
                break;
            }
            case '4': {
                std::cout << "\nSearch employee by id:\n";
                nlohmann::json request;
                request["path"] = path;
                request["method"] = "srch_by_id";
                int tmp;
                std::cout << "\nId: ";
                std::cin >> tmp;
                request["id"] = tmp;
                nlohmann::json response = Handler(request);
                std::cout << response["result"];
                break;
            }
            case '5': {
                return 0;
            }
            default:
                std::cout << "\nWrong input";
                break;
        }
    }
}
