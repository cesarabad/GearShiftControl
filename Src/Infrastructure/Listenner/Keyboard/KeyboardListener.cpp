#include "KeyboardListener.h"
#include "../../Device/DeviceManager.h"
#include "../../../Core/Command/Keyboard/CommandModeH.h"
#include "../../../Core/Command/Keyboard/CommandModeSecuential.h"
#include <thread>
#include <algorithm>
#include <iostream>

namespace Infrastructure::Listener {

    void KeyboardListener::listen() const {
        if (listening_) return;
        stopFlag_.store(false);
        listening_ = true;

        listenerThread_ = std::thread([this]() {
            auto& device = Infrastructure::Device::DeviceManager::get_instance("").get_keyboard(); // Ajusta jsonContent según corresponda
            while (!stopFlag_.load()) {
                std::string input = device.read();
                if (input.empty()) break; // EOF o error

                if (input == "h") {
                    std::thread([]() {
                        Core::Commands::Keyboard::CommandModeH::get_instance().execute();
                        }).detach();
                }
                else if (input == "s") {
                    std::thread([]() {
                        Core::Commands::Keyboard::CommandModeSecuential::get_instance().execute();
                        }).detach();
                }
                else if (std::all_of(input.begin(), input.end(), [](unsigned char c) { return std::isdigit(c) || c == '.'; })) {
                    try {
                        float value = std::stof(input);
						Services::Data::ConcurrentData::get_instance().set_current_speed(value);
                    } catch (const std::exception& e) {
                        std::cerr << "Error parsing float: " << e.what() << std::endl;
                    }
                }
            }
            });
    }

}
