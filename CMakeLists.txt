cmake_minimum_required(VERSION 3.21)
project(microservice
        DESCRIPTION "using microservice arch"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(This microservice)

add_subdirectory(src)
add_subdirectory(proto)

add_executable(${This} main.cpp)

target_include_directories(${This}
    PRIVATE
        ${CMAKE_BINARY_DIR}/generated
)

target_link_libraries(${This} 
        PRIVATE
                proxy_service
                room_service
                #customer_service
                protolibrary
)

add_custom_target(exec DEPENDS ${This})
