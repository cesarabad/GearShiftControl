#pragma once
#include "../Command.h"
#include "../../../Services/Data/ConcurrentData.h"
#include "../../../Core/Model/Configuration/ShiftMode.h"
#include <iostream>
#include <memory>

namespace Core::Commands::Keyboard {

    class CommandModeSecuential : public Command {
    public:
        static CommandModeSecuential& get_instance() {
            static CommandModeSecuential instance;
            return instance;
        }

        void execute() override {
            if (Services::Data::ConcurrentData::get_instance().get_configuration().ShiftMode_.load() == Core::Model::Configuration::ShiftMode::Secuential) {
                std::cout << "Ya está en modo secuencial\n";
                return;
            }
            else if (Services::Data::ConcurrentData::get_instance().get_current_gear() != 0) {
                std::cout << "Hay que poner en punto muerto antes de cambiar a modo secuencial\n";
                return;
            }
            std::cout << "Usando cambio secuencial\n";
			Services::Data::ConcurrentData::get_instance().get_configuration().ShiftMode_.store(Core::Model::Configuration::ShiftMode::Secuential);
        }

    private:
        CommandModeSecuential() = default;
    };

}
