set(This room_service)

add_library(${This} STATIC room_service.cpp) # static lib

message(CMAKE_CURRENT_BINARY_DIRECTORY            " => ${CMAKE_CURRENT_BINARY_DIR}")
#CMAKE_CURRENT_BINARY_DIRECTORY => /home/niyazi/microservice/build/src/room_service

target_sources(${This}
    PRIVATE
        ${CMAKE_BINARY_DIR}/generated/room.pb.cc
        ${CMAKE_BINARY_DIR}/generated/room.grpc.pb.cc
)

target_include_directories(${This}
    PRIVATE
        ${CMAKE_BINARY_DIR}/generated
)

target_link_libraries(${This}
    PRIVATE
        protolibrary
)

add_custom_target(roomservice DEPENDS ${This})