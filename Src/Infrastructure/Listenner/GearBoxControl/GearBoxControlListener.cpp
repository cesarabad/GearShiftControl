#include "GearBoxControlListener.h"  
#include "../../Device/DeviceManager.h"
#include "../../../Core/Command/GearBoxControl/CommandUpdateGear.h"

namespace Infrastructure::Listener {

    void GearBoxControlListener::listen() const {
        if (listening_) return;
        stopFlag_.store(false);
        listening_ = true;

        listenerThread_ = std::thread([this]() {
            auto& device = Infrastructure::Device::DeviceManager::get_instance("").get_gearbox();

            while (!stopFlag_.load()) {
                std::string message = device.read(); 

				if (message.empty()) {
					std::cerr << "Error leyendo el dispositivo de control de marchas" << std::endl;
					continue;
				}

                std::thread([message]() {
                    Core::Commands::GearBoxControl::CommandUpdateGear::get_instance(message).execute();
                    }).detach();
            }
        });
    }

}
