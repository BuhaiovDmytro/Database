cmake_minimum_required(VERSION 3.16)
project(Database)

set(CMAKE_CXX_STANDARD 17)

add_executable(Database Client.cpp Database.cpp Database.h Person.cpp Person.h Employee.cpp Employee.h Manager.cpp Manager.h Server.cpp Server.h)