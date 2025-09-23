#pragma once  

namespace Core::Model::Configuration {  
   class SecurityConfiguration {  
   public:  
       bool ClutchPressed = false;  
       bool CheckSpeedRange = false;  

       // Default constructor  
       SecurityConfiguration() = default;  

       // Copy constructor  
       SecurityConfiguration(const SecurityConfiguration&) = default;  

       // Move constructor  
       SecurityConfiguration(SecurityConfiguration&&) noexcept = default;  

       // Copy assignment operator  
       SecurityConfiguration& operator=(const SecurityConfiguration&) = default;  

       // Move assignment operator  
       SecurityConfiguration& operator=(SecurityConfiguration&&) noexcept = default;  

       // Destructor  
       ~SecurityConfiguration() = default;  
   };  
}