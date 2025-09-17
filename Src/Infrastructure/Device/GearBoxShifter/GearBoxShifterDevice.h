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

    class GearBoxShifterDevice : public Services::Device::InputDevice {
    public:

        explicit GearBoxShifterDevice(int fd)
            : Services::Device::Device(fd),
            Services::Device::InputDevice(fd,
                std::make_unique<Infrastructure::Listener::GearBoxShifterListener>()) {
        }

        std::string read() const override {
            struct input_event ev;
            std::stringstream ss;

            // Lee un evento
            ssize_t n = ::read(device_serial_fd_, &ev, sizeof(ev));
            if (n != sizeof(ev)) {
                return {};
            }

            // Solo nos interesan eventos de tipo "key" o "absolute" (según el dispositivo)
            if (ev.type == EV_KEY) {
                ss << "KEY_CODE:" << ev.code << " VALUE:" << ev.value;
            }
            else if (ev.type == EV_ABS) {
                ss << "ABS_CODE:" << ev.code << " VALUE:" << ev.value;
            }

            return ss.str();
        }
    };

}
