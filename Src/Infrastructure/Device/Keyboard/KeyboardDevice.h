#pragma once
#include "../../../../../DeviceDomain/include/Device/Input/InputDevice.h"
#include "../../../../../DeviceDomain/include/Listener/DeviceListener.h"
#include "../../Listener/Keyboard/KeyboardListener.h"
#include <memory>
#include <iostream>

namespace Infrastructure::Device {

    class KeyboardDevice : public ::Device::InputDevice<std::string> {
    public:
        
        explicit KeyboardDevice(int fd)
            : ::Device::Device(fd),
            ::Device::InputDevice<std::string>(fd,
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
