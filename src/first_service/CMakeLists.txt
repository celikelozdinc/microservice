find_package(cpprestsdk REQUIRED) #requires sudo apt-get install libcpprest-dev
#find_package(OpenSSL REQUIRED)

message(OPENSSL LIBRARIES  " => ${OPENSSL_LIBRARIES}")

set(This first_service)

add_library(${This} service.cpp) #static lib

target_link_libraries(${This} PRIVATE
        cpprestsdk::cpprest
        ${OPENSSL_LIBRARIES}
        #OpenSSL::OpenSSL
)

