#pragma once
#include "../../Services/Security/SafetyChecker.h"
#include "../../Services/Data/ConcurrentData.h"
#include <iostream>

namespace Infrastructure::Security {
	class ShiftGearChecker : Services::Security::SafetyChecker {
	public:
		ShiftGearChecker() = default;

		static ShiftGearChecker& get_instance(int gear_checking) {
			static ShiftGearChecker instance;
			instance.gear_checking_ = gear_checking;
			return instance;
		}

		// Prohibimos copias
		ShiftGearChecker(const ShiftGearChecker&) = delete;
		ShiftGearChecker& operator=(const ShiftGearChecker&) = delete;

		virtual ~ShiftGearChecker() = default;

		bool check() const override {
			Services::Data::ConcurrentData& concurrentData = Services::Data::ConcurrentData::get_instance();

			if (!concurrentData.get_gear_map().contains(gear_checking_)) {
				std::cout << "La marcha " << gear_checking_ << " no está definida en el mapa de marchas." << std::endl;
				return false;
			}

			if (concurrentData.get_configuration().Security.CheckClutchPressed &&
				!concurrentData.is_clutch_pressed()) {
				std::cout << "El embrague no está presionado, no se puede cambiar de marcha." << std::endl;
				return false;
			}

			if (concurrentData.get_configuration().Security.CheckSpeedRange &&
				concurrentData.get_current_speed() >= concurrentData.get_gear_map()[gear_checking_].speedLimit.max ||
				concurrentData.get_current_speed() <= concurrentData.get_gear_map()[gear_checking_].speedLimit.min) {
				std::cout << "La velocidad actual (" << concurrentData.get_current_speed() << " km/h) no está en el rango permitido para la marcha " << gear_checking_ << " ("
					<< concurrentData.get_gear_map()[gear_checking_].speedLimit.min << " - "
					<< concurrentData.get_gear_map()[gear_checking_].speedLimit.max << " km/h)." << std::endl;
				return false;
			}

			return true;//Services::Data::ConcurrentData::get_instance().is_clutch_pressed();
		}

	private:
		int gear_checking_;
	};
}