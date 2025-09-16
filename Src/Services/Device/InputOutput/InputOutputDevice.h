#pragma once
#include <cstdint>
#include "../Input/InputDevice.h"
#include "../Output/OutputDevice.h"

namespace Services::Device {

    template <typename InputListenerType>
    class InputOutputDevice : public InputDevice<InputListenerType>, public virtual OutputDevice {
    public:
        explicit InputOutputDevice(std::int32_t fd)
            : Device(fd), InputDevice<InputListenerType>(), OutputDevice() {}

        ~InputOutputDevice() override = default;
    };

}
