include(FetchContent)

## START PROTOBUF ##
FetchContent_Declare(
        protobuf
        GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
        GIT_TAG        v27.0
        SOURCE_SUBDIR  cmake
        GIT_PROGRESS TRUE
)
## END PROTOBUF ##

## START gRPC ##
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG        v1.64.0
        GIT_PROGRESS TRUE
)
## END gRPC ##


set(ABSL_ENABLE_INSTALL ON)
#set(protobuf_INSTALL OFF)
#set(utf8_range_ENABLE_INSTALL OFF)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(protobuf gRPC)

include_directories(${GRPC_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS})

set(GENERATED_CODE_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_CODE_DIR})

#set(PROTOC /usr/bin/protoc)
#set(PROTOC ${protobuf_BINARY_DIR}/protoc)
set(PROTOC $<TARGET_FILE:protoc>)

set(GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)

set(GENERATED_SRCS ${GENERATED_CODE_DIR}/room.pb.cc ${GENERATED_CODE_DIR}/room.grpc.pb.cc)
set(GENERATED_HDRS ${GENERATED_CODE_DIR}/room.pb.h ${GENERATED_CODE_DIR}/room.grpc.pb.h)

#
# Protobuf/Grpc source files
#
set(PROTO_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROTO_FILES ${PROTO_FILE_DIR}/room.proto)


message(GENERATED_CODE_DIR                  " => ${GENERATED_CODE_DIR}")
message(PROTOCOMPILER                       " => ${PROTOC}")
message(GRPC_CPP_PLUGIN_EXECUTABLE          " => ${GRPC_CPP_PLUGIN_EXECUTABLE}")
message(PROTO_FILE_DIR                      " => ${PROTO_FILE_DIR}")
message(PROTOBUF_INCLUDE_DIRS               " => ${PROTOBUF_INCLUDE_DIRS}")
message(GRPC_INCLUDE_DIRS                   " => ${GRPC_INCLUDE_DIRS}")
message(CURRENT_SOURCE_DIR                  " => ${CMAKE_CURRENT_SOURCE_DIR}")
message(CURRENT_BINARY_DIR                  " => ${CMAKE_CURRENT_BINARY_DIR}")


# Add custom command to generate source files
add_custom_command(
    OUTPUT ${GENERATED_SRCS} ${GENERATED_HDRS}
    COMMAND ${PROTOC}
    ARGS --grpc_out=${GENERATED_CODE_DIR} --cpp_out=${GENERATED_CODE_DIR}
         --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
         -I ${PROTO_FILE_DIR} ${PROTO_FILES}
    DEPENDS ${PROTO_FILES}
)

# Add custom target for proto files
#add_custom_target(generate_proto_files ALL DEPENDS ${GENERATED_SRCS} ${GENERATED_HDRS})
#include_directories(${CMAKE_CURRENT_BINARY_DIR})
#include_directories(${GENERATED_CODE_DIR})

#[===[
block comment
]===]


#
# Add Library target with protobuf sources
#
add_library(protodatabase ${GENERATED_SRCS} ${GENERATED_HDRS})
target_link_libraries(protodatabase
    PUBLIC
        libprotobuf
        grpc
        grpc++
)