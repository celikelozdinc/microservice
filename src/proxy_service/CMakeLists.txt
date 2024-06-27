find_package(cpprestsdk REQUIRED) # requires sudo apt-get install libcpprest-dev
#find_package(OpenSSL REQUIRED)

message(OPENSSL_LIBRARIES  " => ${OPENSSL_LIBRARIES}")

set(This proxy_service)

add_library(${This} STATIC service.cpp) #static lib

target_include_directories(${This}
    PRIVATE
        ${CMAKE_BINARY_DIR}/generated
)

target_link_libraries(${This} 
        PRIVATE
                cpprestsdk::cpprest
                ${OPENSSL_LIBRARIES}
                #OpenSSL::OpenSSL
                protolibrary
)

add_custom_target(proxyservice DEPENDS ${This})