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

   class CommandManualShift : public Command {  
   public:  
       static CommandManualShift& get_instance(const std::string& message) {  
           static CommandManualShift instance;  
           instance.message_ = message;  
           return instance;  
       }  

       void execute() {  
           auto decoded_message = decode_message();  
           int eventCode;
           int eventValue;

           if (decoded_message.empty()) {  
               std::cout << "Mensaje vacío o inválido" << std::endl;  
               return;
           }  

           if (!Infrastructure::Security::ShiftGearChecker::get_instance().check()) {
			   std::cout << "Condiciones de seguridad no cumplidas para cambiar de marcha" << std::endl;
			   return;
           }

           eventCode = decoded_message[0];  
           eventValue = decoded_message[1];

		   if (eventValue == 0) {
               if (Services::Data::ConcurrentData::get_instance().get_current_gear() != 0) {
				   Services::Data::ConcurrentData::get_instance().set_current_gear(0); // Poner en punto muerto
               }
               return;
		   }
		   using namespace Core::Model::Event;
           switch ((GearBoxManualShiftEventCode)eventCode) {

               case GearBoxManualShiftEventCode::FirstGear:
               case GearBoxManualShiftEventCode::FirstGear2:
                   if (Services::Data::ConcurrentData::get_instance().get_current_gear() != 1) {
					   // Escribir al arduino
					   Services::Data::ConcurrentData::get_instance().set_current_gear(1);
                   }
                   break;

			   case GearBoxManualShiftEventCode::SecondGear:
			   case GearBoxManualShiftEventCode::SecondGear2:
				   if (Services::Data::ConcurrentData::get_instance().get_current_gear() != 2) {
					   // Escribir al arduino
					   Services::Data::ConcurrentData::get_instance().set_current_gear(2);
				   }
                   break;

			   case GearBoxManualShiftEventCode::ThirdGear:
				   if (Services::Data::ConcurrentData::get_instance().get_current_gear() != 3) {
					   // Escribir al arduino
					   Services::Data::ConcurrentData::get_instance().set_current_gear(3);
				   }
				   break;

			   case GearBoxManualShiftEventCode::FourthGear:
				   if (Services::Data::ConcurrentData::get_instance().get_current_gear() != 4) {
					   // Escribir al arduino
					   Services::Data::ConcurrentData::get_instance().set_current_gear(4);
				   }
				   break;

			   case GearBoxManualShiftEventCode::FifthGear:
				   if (Services::Data::ConcurrentData::get_instance().get_current_gear() != 5) {
					   // Escribir al arduino
					   Services::Data::ConcurrentData::get_instance().set_current_gear(5);
				   }
				   break;

			   case GearBoxManualShiftEventCode::Reverse:
				   if (Services::Data::ConcurrentData::get_instance().get_current_gear() != -1) {
					   // Escribir al arduino
					   Services::Data::ConcurrentData::get_instance().set_current_gear(-1);
				   }
				   break;

			   default:
				   std::cout << "Código de evento no reconocido: " << eventCode << std::endl;
				   break;
           }
       }  

   private:  
       CommandManualShift() = default;  
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
