#include <iostream>
#include <thread>
#include <atomic>

#include "src/first_service/service.h"

std::atomic_flag isRunning = ATOMIC_FLAG_INIT;

void sig_handler(int signal) {
    std::cout << "Caught signal : " << signal << ", thread id : " << std::this_thread::get_id() << '\n';
    isRunning.clear(); //sets to False
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

int main() {
    std::cout << "Starting main thread, thread id : " << std::this_thread::get_id() << '\n';
    FirstService first{};
    std::signal(SIGINT, sig_handler); //catches Ctrl + C
    auto custom_terminate = [] {
        std::cout << "Terminating all services, thread id : " << std::this_thread::get_id() << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(5));
        isRunning.clear(); //sets to False
        //std::abort();
        //std::exit(0);
    };
    std::set_terminate(custom_terminate);
    first.start();
    isRunning.test_and_set(); //sets to True

    std::thread workerTh {worker};
    workerTh.join();

    //first.stop(); //=> its destructor will also invokes stop()
    return EXIT_SUCCESS;
}
