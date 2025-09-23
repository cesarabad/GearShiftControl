#pragma once  
#include "SecurityConfiguration.h"  
#include "ShiftMode.h"
#include <atomic>  

namespace Core::Model::Configuration {  

   

   struct Configuration {  
       SecurityConfiguration Security;  
       std::atomic<ShiftMode> ShiftMode { ShiftMode::Undefined };  
   };  
}