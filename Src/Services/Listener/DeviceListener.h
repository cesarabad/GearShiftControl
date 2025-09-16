#pragma once
#include <string>
#include <thread>
#include <atomic>

namespace Services::Listener {

    class DeviceListener {
    public:
        virtual ~DeviceListener() {
            stop_listening();
        }

        virtual void listen(const std::string& event = "") const = 0;

        virtual void stop_listening() {
            stopFlag_.store(true);
            listening_ = false;
            if (listenerThread_.joinable()) {
                listenerThread_.join();
            }
        }

    protected:
        mutable std::thread listenerThread_;
        mutable std::atomic<bool> stopFlag_{ false };
        mutable bool listening_{ false };
    };

}
