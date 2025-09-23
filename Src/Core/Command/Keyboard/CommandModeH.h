#pragma once
#include "../Command.h"
#include "../../../Core/Model/Configuration/ShiftMode.h"
#include "../../../Services/Data/ConcurrentData.h"
#include <iostream>
#include <memory>

namespace Core::Commands::Keyboard {

    class CommandModeH : public Command {
    public:
        static CommandModeH& get_instance() {
            static CommandModeH instance;
            return instance;
        }

        void execute() override {
			if (Services::Data::ConcurrentData::get_instance().get_configuration().ShiftMode_.load() == Core::Model::Configuration::ShiftMode::Manual) {
				std::cout << "Ya está en modo manual\n";
				return;
			}
            else if (Services::Data::ConcurrentData::get_instance().get_current_gear() != 0) {
				std::cout << "Hay que poner en punto muerto antes de cambiar a modo manual\n";
                return;
            }
            std::cout << "Usando cambio en H\n";
			Services::Data::ConcurrentData::get_instance().get_configuration().ShiftMode_.store(Core::Model::Configuration::ShiftMode::Manual);
        }

    private:
        CommandModeH() = default;
    };

}
