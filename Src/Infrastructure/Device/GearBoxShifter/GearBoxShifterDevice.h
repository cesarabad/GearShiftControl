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
            : Services::Device::InputDevice(fd,
                std::make_unique<Infrastructure::Listener::GearBoxShifterListener>()) {
        }

        std::string read() const override {
            struct input_event ev;
            std::stringstream ss;
            ssize_t n = 0;

            // Lee un evento completo
            do {
                n = ::read(device_serial_fd_, &ev, sizeof(ev));
                if (n == -1) {
                    perror("Error leyendo el dispositivo");
                    return "";
                }
            } while (n != sizeof(ev));

            // Solo nos interesan eventos de tipo "key" o "absolute"
            if (ev.type == EV_KEY || ev.type == EV_ABS) {
                ss << ev.code << ":" << ev.value;
            }

            return ss.str();
        }
    };

} // namespace Infrastructure::Device
