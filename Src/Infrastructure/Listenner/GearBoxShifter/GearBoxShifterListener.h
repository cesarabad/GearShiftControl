#pragma once
#include "../../../Services/Listener/DeviceListener.h"
#include <string>

namespace Infrastructure::Listener {

    class GearBoxShifterListener : public Services::Listener::DeviceListener {
    public:
        void listen() const override;
    };

}
