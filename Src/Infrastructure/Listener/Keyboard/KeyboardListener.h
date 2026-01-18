#pragma once
#include "../../../../../DeviceDomain/include/Listener/DeviceListener.h"
#include <string>

namespace Infrastructure::Listener {

    class KeyboardListener : public Services::Listener::DeviceListener {
    public:
        void listen() const override;
    };

}
