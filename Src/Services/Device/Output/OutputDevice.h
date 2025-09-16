#pragma once
#include "../Device.h"

namespace Services::Device {

    template <typename T>
    class OutputDevice : public virtual Device {
    public:
        ~OutputDevice() override = default;

        virtual void write(const T& data) const = 0;
    };

}
