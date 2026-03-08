#pragma once  
#include "SecurityConfiguration.h"  
#include "ShiftMode.h"
#include <atomic>  

namespace Core::Model::Configuration {  

   

   struct Configuration {  
       SecurityConfiguration Security_;  
       std::atomic<ShiftMode> ShiftMode_ { ShiftMode::Undefined };  
   };  
}