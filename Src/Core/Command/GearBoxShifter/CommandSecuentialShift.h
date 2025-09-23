#pragma once  
#include "../Command.h"  
#include "../../../Core/Model/Configuration/ShiftMode.h"  
#include "../../../Services/Data/ConcurrentData.h"  
#include "../../../Core/Model/Event/GearBoxShifterEventCode.h"
#include "../../../Infrastructure/Security/ShiftGearChecker.h"
#include <iostream>  
#include <sstream>  
#include <vector>  
#include <string>  

namespace Core::Commands::GearBoxShifter {

    class CommandSecuentialShift : public Command {
    public:
        static CommandSecuentialShift get_instance(const std::string& message) {
            return CommandSecuentialShift(message);
        }

        void execute() {
            auto decoded_message = decode_message();
            int eventCode;
            int eventValue;

            if (decoded_message.empty()) {
                std::cout << "Mensaje vacío o inválido" << std::endl;
                return;
            }

            eventCode = decoded_message[0];
            eventValue = decoded_message[1];

            if (eventValue == 1) {
                using namespace Core::Model::Event;
                switch ((GearBoxSecuentialShiftEventCode)eventCode) {

                case GearBoxSecuentialShiftEventCode::UpShift: {
                    int nextGear = Services::Data::ConcurrentData::get_instance().get_current_gear() + 1;
                    if (Infrastructure::Security::ShiftGearChecker::get_instance(nextGear).check()) {
                        // Escribir al arduino
                        Services::Data::ConcurrentData::get_instance().set_current_gear(nextGear);
                    }
                    break;
                }

                case GearBoxSecuentialShiftEventCode::DownShift: {
                    int prevGear = Services::Data::ConcurrentData::get_instance().get_current_gear() - 1;
                    if (Infrastructure::Security::ShiftGearChecker::get_instance(prevGear).check()) {
                        // Escribir al arduino
                        Services::Data::ConcurrentData::get_instance().set_current_gear(prevGear);
                    }
                    break;
                }

                default:
                    std::cout << "Código de evento no reconocido: " << eventCode << std::endl;
                    break;
                }
            }
        }

    private:
        // Guardamos copia de la cadena, no referencia
        CommandSecuentialShift(const std::string& message) : message_(message) {};
        CommandSecuentialShift(const CommandSecuentialShift&) = delete;
        CommandSecuentialShift& operator=(const CommandSecuentialShift&) = delete;

        std::string message_;

        std::vector<int> decode_message() {
            std::vector<int> decoded;
            std::stringstream ss(message_);
            std::string token;

            while (std::getline(ss, token, ':')) {
                try {
                    decoded.push_back(std::stoi(token));
                }
                catch (const std::invalid_argument&) {
                    std::cerr << "Token inválido: " << token << std::endl;
                }
                catch (const std::out_of_range&) {
                    std::cerr << "Número fuera de rango: " << token << std::endl;
                }
            }
            if (decoded.size() != 2) {
                decoded.clear();
                std::cerr << "Mensaje no tiene el formato esperado" << std::endl;
            }
            return decoded;
        }
    };

}
