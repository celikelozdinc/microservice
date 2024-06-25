set(This room_service)

add_library(${This} room_service.cpp) # static lib

message(CMAKE_CURRENT_BINARY_DIRECTORY            " => ${CMAKE_CURRENT_BINARY_DIR}")
#CMAKE_CURRENT_BINARY_DIRECTORY => /home/niyazi/microservice/build/src/room_service

target_sources(${This}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/../../proto/generated/room.pb.cc
        ${CMAKE_CURRENT_BINARY_DIR}/../../proto/generated/room.grpc.pb.cc
)

target_include_directories(${This}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/../../proto/generated
)

target_link_libraries(${This}
    PRIVATE
        libprotobuf
        grpc
        grpc++
)