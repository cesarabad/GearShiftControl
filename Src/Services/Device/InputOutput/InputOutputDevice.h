#pragma once
#include <cstdint>
#include "../Input/InputDevice.h"
#include "../Output/OutputDevice.h"

namespace Services::Device {

    class InputOutputDevice : public virtual InputDevice, public virtual OutputDevice {
    public:
        explicit InputOutputDevice(std::int32_t fd)
            : Device(fd), InputDevice<InputListenerType>(), OutputDevice() {}

        ~InputOutputDevice() override = default;
    };

}
