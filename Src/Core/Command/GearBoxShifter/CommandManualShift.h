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

    class CommandManualShift : public Command {
    public:
        // Cada llamada recibe un mensaje y devuelve un objeto con su propia copia
        static CommandManualShift get_instance(const std::string& message) {
            return CommandManualShift(message);
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

			Services::Data::ConcurrentData& concurrentData = Services::Data::ConcurrentData::get_instance();
			Infrastructure::Device::DeviceManager& deviceManager = Infrastructure::Device::DeviceManager::get_instance("");

            if (eventValue == 0) {
                if (concurrentData.get_current_gear() != 0) {
                    concurrentData.set_current_gear(0); // Poner en punto muerto
                }
                return;
            }

            using namespace Core::Model::Event;
            switch ((GearBoxManualShiftEventCode)eventCode) {

            case GearBoxManualShiftEventCode::FirstGear:
            case GearBoxManualShiftEventCode::FirstGear2:
                if (concurrentData.get_current_gear() != 1 &&
                    Infrastructure::Security::ShiftGearChecker::get_instance(1).check()) {
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[0]); // Ponemos N
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[1]);
                    concurrentData.set_current_gear(1);
                }
                break;

            case GearBoxManualShiftEventCode::SecondGear:
            case GearBoxManualShiftEventCode::SecondGear2:
                if (concurrentData.get_current_gear() != 2 &&
                    Infrastructure::Security::ShiftGearChecker::get_instance(2).check()) {
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[0]); // Ponemos N
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[2]);
                    concurrentData.set_current_gear(2);
                }
                break;

            case GearBoxManualShiftEventCode::ThirdGear:
                if (concurrentData.get_current_gear() != 3 &&
                    Infrastructure::Security::ShiftGearChecker::get_instance(3).check()) {
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[0]); // Ponemos N
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[3]);
                    concurrentData.set_current_gear(3);
                }
                break;

            case GearBoxManualShiftEventCode::FourthGear:
                if (concurrentData.get_current_gear() != 4 &&
                    Infrastructure::Security::ShiftGearChecker::get_instance(4).check()) {
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[0]); // Ponemos N
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[4]);
                    concurrentData.set_current_gear(4);
                }
                break;

            case GearBoxManualShiftEventCode::FifthGear:
                if (concurrentData.get_current_gear() != 5 &&
                    Infrastructure::Security::ShiftGearChecker::get_instance(5).check()) {
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[0]); // Ponemos N
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[5]);
                    concurrentData.set_current_gear(5);
                }
                break;

            case GearBoxManualShiftEventCode::Reverse:
                if (concurrentData.get_current_gear() != -1 &&
                    Infrastructure::Security::ShiftGearChecker::get_instance(-1).check()) {
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[0]); // Ponemos N
                    deviceManager.get_gearbox().write(concurrentData.get_gear_map()[-1]);
                    concurrentData.set_current_gear(-1);
                }
                break;

            default:
                std::cout << "Código de evento no reconocido: " << eventCode << std::endl;
                break;
            }
        }

    private:
        // Guardamos copia de la cadena, no referencia
        CommandManualShift(const std::string& message) : message_(message) {};
        CommandManualShift(const CommandManualShift&) = delete;
        CommandManualShift& operator=(const CommandManualShift&) = delete;

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
