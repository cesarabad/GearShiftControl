#pragma once
#include "../../../Services/Listener/DeviceListener.h"
#include <string>

namespace Infrastructure::Listener {

    class KeyboardListener : public Services::Listener::DeviceListener {
    public:
        void listen(const std::string& event = "") const override;
    };

}
