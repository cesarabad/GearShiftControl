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
            std::cout << "Usando cambio secuencial\n";
			Services::Data::ConcurrentData::get_instance().get_configuration().ShiftMode.store(Core::Model::Configuration::ShiftMode::Secuential);
        }

    private:
        CommandModeSecuential() = default;
    };

}
