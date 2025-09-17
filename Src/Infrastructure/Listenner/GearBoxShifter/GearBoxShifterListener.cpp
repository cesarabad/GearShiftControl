#include "GearBoxShifterListener.h"
#include "../../Device/DeviceManager.h"
#include <thread>
#include <iostream>

namespace Infrastructure::Listener {

    void GearBoxShifterListener::listen() const {
        if (listening_) return;
        stopFlag_.store(false);
        listening_ = true;

        listenerThread_ = std::thread([this]() {
            auto& device = Infrastructure::Device::DeviceManager::get_instance("").get_gearbox_shifter();

            while (!stopFlag_.load()) {
                std::string event = device.read(); // lee la marcha o el evento del shifter
                if (event.empty()) continue;

                // Aquí interpretas el evento
                if (event == "KEY_CODE:291 VALUE:1") {
                    std::cout << "Subir de marcha" << std::endl;
                }
                else if (event == "KEY_CODE:290 VALUE:1") {
                    std::cout << "Bajar de marcha" << std::endl;
                }
            }
            });
    }

}
