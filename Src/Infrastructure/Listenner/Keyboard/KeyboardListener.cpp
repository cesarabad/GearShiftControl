#include "KeyboardListener.h"
#include "../../Device/DeviceManager.h"
#include "../../../Core/Command/Keyboard/CommandA.h"
#include "../../../Core/Command/Keyboard/CommandB.h"
#include <thread>
#include <iostream>

namespace Infrastructure::Listener {

    void KeyboardListener::listen(const std::string& event) const {
        if (listening_) return;
        stopFlag_.store(false);
        listening_ = true;

        listenerThread_ = std::thread([this]() {
            auto& device = Infrastructure::Device::DeviceManager::get_instance("").get_keyboard(); // Ajusta jsonContent según corresponda
            while (!stopFlag_.load()) {
                std::string input = device.read();
                if (input.empty()) break; // EOF o error

                if (input == "a") {
                    std::thread([]() {
                        Core::Commands::CommandA::get_instance().execute();
                        }).detach();
                }
                else if (input == "b") {
                    std::thread([]() {
                        Core::Commands::CommandB::get_instance().execute();
                        }).detach();
                }
            }
            });
    }

}
