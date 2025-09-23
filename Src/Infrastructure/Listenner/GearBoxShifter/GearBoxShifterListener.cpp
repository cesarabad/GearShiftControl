#include "GearBoxShifterListener.h"
#include "../../Device/DeviceManager.h"
#include "../../../Services/Data/ConcurrentData.h"
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

                // Cuando value es 0 significa que estamos en N (solo lo tendremos en cuenta cuando estemos en cambio en H.
                //

                // Aquí interpretas el evento
                if (event == "KEY_CODE:291 VALUE:1") {

                    if (Services::Data::ConcurrentData::get_instance().is_clutch_pressed()) {
                        std::cout << "Subir de marcha" << std::endl;
                    }
                    else {
                        std::cout << "No se puede subir de marcha, el embrague no está presionado" << std::endl;
                    }
                    
                }
                else if (event == "KEY_CODE:290 VALUE:1") {
					if (Services::Data::ConcurrentData::get_instance().is_clutch_pressed()) {
						std::cout << "Bajar de marcha" << std::endl;
					}
					else {
						std::cout << "No se puede bajar de marcha, el embrague no está presionado" << std::endl;
					}
                }
            }
            });
    }

}
