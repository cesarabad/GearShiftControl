#pragma once
#include "../Command.h"
#include <iostream>
#include <memory>

namespace Core::Commands {

    class CommandB : public Command {
    public:
        static CommandB& get_instance() {
            static CommandB instance;
            return instance;
        }

        void execute() override {
            std::cout << "CommandB ejecutado (tecla 'b')\n";
        }

    private:
        CommandB() = default;
    };

}
