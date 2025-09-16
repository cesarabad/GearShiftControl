#pragma once
#include "../Device.h"
#include "../../Listener/DeviceListener.h"
#include <thread>
#include <memory>
#include <concepts>
#include <atomic>
#include <mutex>

namespace Services::Device {

    template <typename T>
    concept IsListener = std::derived_from<T, Services::Listener::DeviceListener>;

    template <IsListener T>
    class InputDevice : public virtual Device {
    public:
        explicit InputDevice(int device_serial_fd)
            : Device(device_serial_fd),
            listener_(std::make_unique<T>()),
            active_(false) {
        }

        ~InputDevice() override {
            deactivate();
        }

        virtual void read() const = 0;

        void set_active(bool active) {
            std::lock_guard<std::mutex> lock(mutex_);
            active_ = active;
            if (active_) {
                listener_ -> listen();
            }
            else {
                listener_-> stop_listening();
            }
        }

        bool is_active() const {
            return active_;
        }

    protected:
        std::unique_ptr<T> listener_;
        std::atomic<bool> active_;
        std::mutex mutex_;

    };

}
