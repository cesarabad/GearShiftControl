#pragma once
#include "../Device.h"

namespace Services::Device {

    template <typename T>
    class OutputDevice : public virtual Device {
    public:
        OutputDevice(int device_serial_fd, const std::string& device_function)
            : Device(device_serial_fd, device_function) {
        }
        ~OutputDevice() override = default;

        virtual void write(const T& data) const = 0;
    };

}
