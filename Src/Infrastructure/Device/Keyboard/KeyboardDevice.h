#pragma once
#include "../../../Services/Device/Input/InputDevice.h"
#include "../../Listenner/Keyboard/KeyboardListener.h"
#include "../DeviceManager.h"
#include <memory>
#include <iostream>

namespace Infrastructure::Device {

    class KeyboardDevice : public InputDevice<Services::Listener::KeyboardListener> {
    public:
        std::string read() const override {
            std::string input;
            if (!std::getline(std::cin, input)) {
                return {};
            }
            return input;
        }
        explicit KeyboardDevice(int fd)
            : InputDevice(fd, Services::Device::DeviceConst::Function::ReadKeyboard) {
        }
    };

}
