#include <string_view>

namespace Infrastructure::Device::DeviceConst {
    namespace Type {
        inline constexpr std::string_view INPUT = "Input";
        inline constexpr std::string_view OUTPUT = "Output";
    }

    namespace Function {
        inline constexpr std::string_view READ_KEYBOARD = "ReadKeyboard";
        inline constexpr std::string_view GEARBOX_CONTROL = "GearboxControl";
        inline constexpr std::string_view READ_GEARBOX_SHIFTER = "ReadGearBoxShifter";
    }
}
