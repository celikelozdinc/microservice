#include "room_service.h"

#include <iostream>

Status RoomServiceImpl::CreateRoom(ServerContext* context, const roompackage::RoomRequest* request, roompackage::RoomResponse* response) {
    std::cout << "[ROOM_SERVICE]" << "[CreateRoom]" << '\n';
    //response->set_sum(request->addend_1() + request->addend_2())
    
    return Status::OK;
}

void RoomServiceImpl::Run() {
    is_room_service_running.test_and_set(); // sets to True
    ServerBuilder builder;
    builder.AddListeningPort(_address, grpc::InsecureServerCredentials());
    builder.RegisterService(this);
    _server = builder.BuildAndStart();

    // Run server
    std::cout << "[ROOM_SERVICE]" << " listening on " << _address << '\n';
    //_server->Wait();
    HandleRpcs();
}

void RoomServiceImpl::HandleRpcs() {
    std::cout << "[ROOM_SERVICE]" << "[HandleRpcs]" << "[START]" <<'\n';
    while(is_room_service_running.test_and_set()) {
        ;
    }
    std::cout << "[ROOM_SERVICE]" << "[HandleRpcs]" << "[END]" <<'\n';
}

RoomServiceImpl::~RoomServiceImpl() {
    std::cout << "[ROOM_SERVICE]" << " is being destroyed!\n";
    _server->Shutdown();
    is_room_service_running.clear();
    std::cout << "[ROOM_SERVICE]" << " is being shutted down!\n";
}