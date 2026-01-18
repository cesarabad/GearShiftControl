#pragma once
#include "../../../../../DeviceDomain/include/Device/Input/InputDevice.h"
#include "../../../../../DeviceDomain/include/Listener/DeviceListener.h"
#include "../../Listener/GearBoxShifter/GearBoxShifterListener.h"
#include <memory>
#include <iostream>
#include <linux/input.h>
#include <unistd.h>
#include <sstream>

namespace Infrastructure::Device {

    class GearBoxShifterDevice : public ::Device::InputDevice<input_event> {
    public:

        explicit GearBoxShifterDevice(int fd)
            : ::Device::Device(fd),
            ::Device::InputDevice<input_event>(fd,
                std::make_unique<Infrastructure::Listener::GearBoxShifterListener>()) {
        }

        input_event read() const override {
            struct input_event ev;

            // Bloquea hasta que haya un evento
            ssize_t n = ::read(device_serial_fd_, &ev, sizeof(ev));
            if (n != sizeof(ev)) {
                // Esto solo ocurrirá si hay error
                std::cerr << "Error leyendo el dispositivo" << std::endl;
                ev.value = -1;
            }

            return ev;
        }
    };

}
