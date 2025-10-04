#pragma once
#include "../../../Services/Device/Input/InputDevice.h"
#include "../../../Services/Listener/DeviceListener.h"
#include "../../Listenner/GearBoxShifter/GearBoxShifterListener.h"
#include <memory>
#include <iostream>
#include <linux/input.h>
#include <unistd.h>
#include <sstream>

namespace Infrastructure::Device {

    class GearBoxShifterDevice : public Services::Device::InputDevice<std::string> {
    public:

        explicit GearBoxShifterDevice(int fd)
            : Services::Device::Device(fd),
            Services::Device::InputDevice<std::string>(fd,
                std::make_unique<Infrastructure::Listener::GearBoxShifterListener>()) {
        }

        std::string read() const override {
            struct input_event ev;
            std::stringstream ss;

            // Bloquea hasta que haya un evento
            ssize_t n = ::read(device_serial_fd_, &ev, sizeof(ev));
            if (n != sizeof(ev)) {
                // Esto solo ocurrirá si hay error
                std::cerr << "Error leyendo el dispositivo" << std::endl;
                return "";
            }

            // Solo nos interesan eventos de tipo "key" o "absolute"
            if (ev.type == EV_KEY || ev.type == EV_ABS) {
                ss << ev.code << ":" << ev.value;
            }

            return ss.str();
        }
    };

}
