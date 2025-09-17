#pragma once
#include <unistd.h>
#include <string>

namespace Services::Device {

    class Device {
    protected:
        int device_serial_fd_{ -1 };

    public:
        explicit Device(int device_serial_fd, std::string device_function)
            : device_serial_fd_(device_serial_fd) {
        }

        // Non-copyable (prevents double-close)
        Device(const Device&) = delete;
        Device& operator=(const Device&) = delete;

        // Movable
        Device(Device&&) noexcept = default;
        Device& operator=(Device&&) noexcept = default;

        virtual ~Device() {
            if (device_serial_fd_ >= 0) {
                ::close(device_serial_fd_); // POSIX close(int fd)
            }
        }
    };

}
