#ifndef MICROSERVICE_SRC_ROOM_SERVICE_ROOM_SERVICE_H
#define MICROSERVICE_SRC_ROOM_SERVICE_ROOM_SERVICE_H

#include "room.grpc.pb.h"
#include <grpc++/grpc++.h>

#include <unordered_map>
#include <tuple>
#include <memory>
#include <string>

using namespace grpc;
//using namespace roompackage;

using RoomData = std::tuple<std::string, int, int>;
using RoomDatabase = std::unordered_map<uint64_t, RoomData>;

class RoomServiceImpl : public roompackage::RoomService::Service {
public:
    static inline std::atomic_flag is_room_service_running = ATOMIC_FLAG_INIT;
    Status CreateRoom(ServerContext*, const roompackage::RoomRequest*, roompackage::RoomResponse*);
    void Run();
    void HandleRpcs(); // from https://github.com/grpc/grpc/blob/v1.64.0/examples/cpp/helloworld/greeter_async_server.cc
    ~RoomServiceImpl();
private:
    RoomDatabase _rooms{};
    std::string _address{"localhost:4141"};
    std::unique_ptr<Server> _server;
};


#endif

