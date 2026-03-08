#include "GearBoxShifterListener.h"  
#include "../../Device/DeviceManager.h"  
#include "../../../Services/Data/ConcurrentData.h"  
#include "../../../Core/Command/GearBoxShifter/CommandManualShift.h"  
#include "../../../Core/Command/GearBoxShifter/CommandSecuentialShift.h"
#include "../../../Core/Model//Event/GearBoxShifterEventCode.h"
#include <thread>  
#include <iostream>  

namespace Infrastructure::Listener {  

   void GearBoxShifterListener::listen() const {  
       if (listening_) return;  
       stopFlag_.store(false);  
       listening_ = true;  

       listenerThread_ = std::thread([this]() {  
           auto& device = Infrastructure::Device::DeviceManager::get_instance("").get_gearbox_shifter();  

           while (!stopFlag_.load()) {  
               input_event event = device.read(); // lee la marcha o el evento del shifter  

               if (event.value == -1) {
				   std::cerr << "Error leyendo el dispositivo de cambio de marchas" << std::endl;
				   continue; // Si hay error, continuar al siguiente ciclo
               }

               if ((Core::Model::Event::GearBoxGenericEventCode)event.code == Core::Model::Event::GearBoxGenericEventCode::SuccessShift) {
                   can_shift = true;
				   continue;
               }

               if (!can_shift) {
				   continue;
               }

               if (Services::Data::ConcurrentData::get_instance().get_configuration().ShiftMode_.load() == Core::Model::Configuration::ShiftMode::Manual) {  
                   // Capture 'event' explicitly in the lambda to fix the error  
                   std::thread([event]() {  
                       Core::Commands::GearBoxShifter::CommandManualShift::get_instance(event).execute();  
                       }).detach();  
				   can_shift = false;
               }  
               else if (Services::Data::ConcurrentData::get_instance().get_configuration().ShiftMode_.load() == Core::Model::Configuration::ShiftMode::Secuential) {  
				   std::thread([event]() {
					   Core::Commands::GearBoxShifter::CommandSecuentialShift::get_instance(event).execute();
					   }).detach();
				   can_shift = false;
               }  
           }  
       });  

   }  

}
