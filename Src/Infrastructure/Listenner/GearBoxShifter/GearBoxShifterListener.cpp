#include "KeyboardListener.h"
#include "../../Device/DeviceManager.h"
#include "../../../Core/Command/Keyboard/CommandA.h"
#include "../../../Core/Command/Keyboard/CommandB.h"
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
                if (event == "GEAR_1") {
                    std::cout << "Marcha 1 metida" << std::endl;
                }
                else if (event == "GEAR_2") {
                    std::cout << "Marcha 2 metida" << std::endl;
                }
                else if (event == "GEAR_3") {
                    std::cout << "Marcha 3 metida" << std::endl;
                }
                else if (event == "GEAR_4") {
                    std::cout << "Marcha 4 metida" << std::endl;
                }
                else if (event == "GEAR_5") {
                    std::cout << "Marcha 5 metida" << std::endl;
                }
                else if (event == "GEAR_R") {
                    std::cout << "Marcha atrás metida" << std::endl;
                }
                else {
                    std::cout << "Evento desconocido: " << event << std::endl;
                }
            }
            });
    }

}
