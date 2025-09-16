#pragma once
#include "../../../Services/Device/Input/InputDevice.h"
#include "../../../Services/Listener/DeviceListener.h"
#include "../../Listenner/Keyboard/KeyboardListener.h"
#include <memory>
#include <iostream>

namespace Infrastructure::Device {

    class KeyboardDevice : public Services::Device::InputDevice {
    public:
        
        explicit KeyboardDevice(int fd)
            : Services::Device::Device(fd, "ReadKeyboard"),
            Services::Device::InputDevice(fd, "ReadKeyboard",
                std::make_unique<Infrastructure::Listener::KeyboardListener>()) {
        }

        std::string read() const override {
            std::string input;
            if (!std::getline(std::cin, input)) {
                return {};
            }
            return input;
        }
    };

}
