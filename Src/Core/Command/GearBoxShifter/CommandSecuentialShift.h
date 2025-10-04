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
        static CommandSecuentialShift get_instance(const input_event& event) {
            return CommandSecuentialShift(event);
        }

        void execute() {


            if (event_.value == 1) {
                using namespace Core::Model::Event;
                Services::Data::ConcurrentData& concurrentData = Services::Data::ConcurrentData::get_instance();
				Infrastructure::Device::DeviceManager& deviceManager = Infrastructure::Device::DeviceManager::get_instance("");
                switch ((GearBoxSecuentialShiftEventCode)event_.code) {

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
        CommandSecuentialShift(const input_event& event) : event_(event) {};
        CommandSecuentialShift(const CommandSecuentialShift&) = delete;
        CommandSecuentialShift& operator=(const CommandSecuentialShift&) = delete;

        input_event event_;

    };

}
