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
        static CommandManualShift get_instance(const input_event& event) {
            return CommandManualShift(event);
        }

        void execute() {


			Services::Data::ConcurrentData& concurrentData = Services::Data::ConcurrentData::get_instance();
			Infrastructure::Device::DeviceManager& deviceManager = Infrastructure::Device::DeviceManager::get_instance("");

            if (event_.value == 0) {
                if (concurrentData.get_current_gear() != 0) {
                    concurrentData.set_current_gear(0); // Poner en punto muerto
                }
                return;
            }

            using namespace Core::Model::Event;
            switch ((GearBoxManualShiftEventCode)event_.code) {

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
                std::cout << "Código de evento no reconocido: " << event_.code << std::endl;
                break;
            }
        }

    private:
        // Guardamos copia de la cadena, no referencia
        CommandManualShift(const input_event& event) : event_(event) {};
        CommandManualShift(const CommandManualShift&) = delete;
        CommandManualShift& operator=(const CommandManualShift&) = delete;

        input_event event_;

    };

}
