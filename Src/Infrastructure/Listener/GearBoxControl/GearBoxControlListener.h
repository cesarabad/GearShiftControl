#pragma once
#include "Listener/DeviceListener.h"
#include <string>

namespace Infrastructure::Listener {

    class GearBoxControlListener : public ::Listener::DeviceListener {
    public:
        void listen() const override;

    private:
        mutable bool can_shift = true;
    };

}
