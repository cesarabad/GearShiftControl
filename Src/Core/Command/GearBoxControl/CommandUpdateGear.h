#pragma once  
#include "../Command.h"  
#include "../../../Services/Data/ConcurrentData.h"  
#include "../../../Core/Model/Configuration/ShiftMode.h"  
#include <iostream>  
#include <memory>  
#include <utility> // Para std::pair  
#include <sstream> // Para std::istringstream  
#include <stdexcept> // Para std::invalid_argument  

namespace Core::Commands::GearBoxControl {  

  class CommandUpdateGear : public Command {  
  public:  
      static CommandUpdateGear& get_instance(std::string message) {  
          static CommandUpdateGear instance;  
          instance.message_ = message;  
          return instance;  
      }  

      void execute() override {  
          Services::Data::ConcurrentData& concurrentData = Services::Data::ConcurrentData::get_instance();  
		  std::cout << "Mensaje recibido del dispositivo de control de marchas: " << message_ << std::endl;
          if (concurrentData.get_next_gear() == nullptr) {  
              return;  
          }  
          else {  
			  if (is_correct_gear(decode_message(message_))) {
				  concurrentData.set_current_gear(concurrentData.get_next_gear()->number);
				  concurrentData.set_next_gear(nullptr);
				  std::cout << "Marcha cambiada a: " << concurrentData.get_current_gear() << std::endl;
			  }
              concurrentData.get_shift_mutex().unlock();  
          }  
      }  

  private:  
      CommandUpdateGear() = default;  
      std::string message_;  

      std::pair<float, float> decode_message(const std::string& message) const {  
          try {  
              size_t x_pos = message.find('X');  
              size_t y_pos = message.find('Y');  
              size_t comma_pos = message.find(',');  

              if (x_pos == std::string::npos || y_pos == std::string::npos || comma_pos == std::string::npos || x_pos >= comma_pos || comma_pos >= y_pos) {  
                  throw std::invalid_argument("Formato de mensaje inválido");  
              }  

              float x_value = std::stof(message.substr(x_pos + 1, comma_pos - x_pos - 1));  
              float y_value = std::stof(message.substr(y_pos + 1));  

              return std::make_pair(x_value, y_value);  
          } catch (const std::exception& e) {  
              std::cerr << "Error al decodificar el mensaje: " << e.what() << std::endl;  
              return std::make_pair(0.0f, 0.0f);  
          }  
      }

	  bool is_correct_gear(const std::pair<float, float>& position) {
		  auto* gear = Services::Data::ConcurrentData::get_instance().get_next_gear();
          if (!gear) {
              // No hay gear configurado
              return false;
          }
		  const float tolerance = 5.0f; // Tolerancia en grados
		  float deltaX = std::abs(position.first - gear->rotation.x);
		  float deltaY = std::abs(position.second - gear->rotation.y);
		  return (deltaX <= tolerance) && (deltaY <= tolerance);
	  }
  };  

}
