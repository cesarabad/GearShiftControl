#pragma once
#include "../../../Services/Device/Input/InputDevice.h"
#include "../../../Services/Listener/DeviceListener.h"
#include "../../Listenner/Keyboard/KeyboardListener.h"
#include <memory>
#include <iostream>

namespace Infrastructure::Device {

    class KeyboardDevice : public Services::Device::InputDevice<std::string> {
    public:
        
        explicit KeyboardDevice(int fd)
            : Services::Device::Device(fd),
            Services::Device::InputDevice<std::string>(fd,
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
