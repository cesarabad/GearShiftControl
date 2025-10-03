#pragma once  
#include "../Command.h"  
#include "../../../Core/Model/Configuration/ShiftMode.h"  
#include "../../../Services/Data/ConcurrentData.h"  
#include "../../../Core/Model/Event/GearBoxShifterEventCode.h"
#include "../../../Infrastructure/Security/ShiftGearChecker.h"
#include "../../../Infrastructure/Device/DeviceManager.h"
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
                std::cout << "Mensaje vac�o o inv�lido" << std::endl;
                return;
            }

            eventCode = decoded_message[0];
            eventValue = decoded_message[1];

            if (eventValue == 1) {
                using namespace Core::Model::Event;
                Services::Data::ConcurrentData& concurrentData = Services::Data::ConcurrentData::get_instance();
				Infrastructure::Device::DeviceManager& deviceManager = Infrastructure::Device::DeviceManager::get_instance("");
                switch ((GearBoxSecuentialShiftEventCode)eventCode) {

                case GearBoxSecuentialShiftEventCode::UpShift: {
                    int nextGear = concurrentData.get_current_gear() + 1;
                    if (Infrastructure::Security::ShiftGearChecker::get_instance(nextGear).check()) {
                        // Escribir al arduino
                        deviceManager.get_gearbox().write(concurrentData.get_gear_map()[0]); // Ponemos N
                        deviceManager.get_gearbox().write(concurrentData.get_gear_map()[nextGear]);
                        concurrentData.set_current_gear(nextGear);
                    }
                    break;
                }

                case GearBoxSecuentialShiftEventCode::DownShift: {
                    int prevGear = concurrentData.get_current_gear() - 1;
                    if (Infrastructure::Security::ShiftGearChecker::get_instance(prevGear).check()) {
                        deviceManager.get_gearbox().write(concurrentData.get_gear_map()[0]); // Ponemos N
                        deviceManager.get_gearbox().write(concurrentData.get_gear_map()[prevGear]);
                        concurrentData.set_current_gear(prevGear);
                    }
                    break;
                }

                default:
                    std::cout << "Estas en modo secuencial!!" << std::endl;
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
                    std::cerr << "Token inv�lido: " << token << std::endl;
                }
                catch (const std::out_of_range&) {
                    std::cerr << "N�mero fuera de rango: " << token << std::endl;
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
