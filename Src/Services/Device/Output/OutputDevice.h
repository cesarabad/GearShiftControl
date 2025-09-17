#pragma once
#include "../Device.h"

namespace Services::Device {

    template <typename T>
    class OutputDevice : public virtual Device {
    public:
        OutputDevice(int device_serial_fd)
            : Device(device_serial_fd) {
        }

        ~OutputDevice() override = default;

        virtual void write(const T& data) const = 0;
    };

}
