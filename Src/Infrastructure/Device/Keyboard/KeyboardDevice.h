#pragma once
#include "../../../Services/Device/Input/InputDevice.h"
#include <memory>
#include <iostream>

namespace Infrastructure::Device {

    class KeyboardDevice : public Services::Device::InputDevice {
    public:
        std::string read() const override {
            std::string input;
            if (!std::getline(std::cin, input)) {
                return {};
            }
            return input;
        }
        explicit KeyboardDevice(int fd, Services::Listener::DeviceListener listener)
            : InputDevice(fd, "ReadKeyboard", listener) {
        }
    };

}
