cmake_minimum_required(VERSION 3.21)
project(microservice
        DESCRIPTION "using microservice arch"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(This microservice)

add_subdirectory(src)

#find_package(cpprestsdk REQUIRED) #sudo apt-get install libcpprest-dev

add_executable(${This} main.cpp)

target_link_libraries(${This} PUBLIC
        #cpprestsdk::cpprest
        proxy_service
)
