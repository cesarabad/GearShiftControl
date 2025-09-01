#pragma once
#include <unistd.h>

namespace Services::Device {

    class Device {
    protected:
        int device_serial_fd_{ -1 };

    public:
        explicit Device(int device_serial_fd)
            : device_serial_fd_(device_serial_fd) {
        }

        // No copiable (evita double-close)
        Device(const Device&) = delete;
        Device& operator=(const Device&) = delete;

        // Movible
        Device(Device&&) noexcept = default;
        Device& operator=(Device&&) noexcept = default;

        virtual ~Device() {
            if (device_serial_fd_ >= 0) {
                ::close(device_serial_fd_);
            }
        }
    };

}
