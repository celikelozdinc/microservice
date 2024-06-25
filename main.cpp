#include <iostream>
#include <thread>
#include <atomic>

#include "src/proxy_service/service.h"
#include "src/room_service/room_service.h"

std::atomic_flag isRunning = ATOMIC_FLAG_INIT;

void sig_handler(int signal) {
    std::cout << "Caught signal : " << signal << ", on thread id : " << std::this_thread::get_id() << '\n';
    isRunning.clear(); //sets to False
    RoomServiceImpl::is_room_service_running.clear(); //sets to False
    std::this_thread::sleep_for(std::chrono::seconds(5));
    //std::terminate();
}

void worker() {
    std::cout << "Starting worker thread, thread id : " << std::this_thread::get_id() << '\n';
    while(isRunning.test_and_set()) {
        ;
    }
    std::cout << "Exiting worker thread, thread id : " << std::this_thread::get_id() << '\n';
}

void room_service_worker() {
    std::cout << "Starting room_service_worker thread, thread id : " << std::this_thread::get_id() << '\n';
    RoomServiceImpl roomService{};
    roomService.Run();
    std::cout << "Exiting room_service_worker thread, thread id : " << std::this_thread::get_id() << '\n';
}

int main() {
    auto custom_terminate = [] {
        std::cout << "Terminating all services, main thread id : " << std::this_thread::get_id() << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(5));
        isRunning.clear(); //sets to False
        RoomServiceImpl::is_room_service_running.clear(); //sets to False
        //std::abort();
        //std::exit(0);
    };

    std::cout << "Starting main thread, thread id : " << std::this_thread::get_id() << '\n';
    ProxyService proxy{};
    std::signal(SIGINT, sig_handler); //catches Ctrl + C
    std::set_terminate(custom_terminate);
    proxy.start();
    isRunning.test_and_set(); //sets to True

    std::thread room_service_worker_th {room_service_worker};
    
    std::thread workerTh {worker};
    std::cout << "main devam ediyor, thread id : " << std::this_thread::get_id() << '\n';
    workerTh.join();
    room_service_worker_th.join();

    //first.stop(); //=> its destructor will also invokes stop()
    return EXIT_SUCCESS;
}
