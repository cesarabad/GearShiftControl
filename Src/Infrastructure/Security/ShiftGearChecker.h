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

			if (concurrentData.get_configuration().Security_.CheckClutchPressed &&
				!concurrentData.is_clutch_pressed()) {
				std::cout << "El embrague no está presionado, no se puede cambiar de marcha." << std::endl;
				return false;
			}

			if (concurrentData.get_configuration().Security_.CheckSpeedRange &&
				(concurrentData.get_current_speed() > concurrentData.get_gear_map()[gear_checking_].speedLimit.max ||
				concurrentData.get_current_speed() < concurrentData.get_gear_map()[gear_checking_].speedLimit.min)) {


				if (concurrentData.get_configuration().ShiftMode_ == Core::Model::Configuration::ShiftMode::Secuential &&
					concurrentData.get_current_speed() < concurrentData.get_gear_map()[concurrentData.get_current_gear()].speedLimit.min &&
					concurrentData.get_current_speed() < concurrentData.get_gear_map()[gear_checking_].speedLimit.max) {
					std::cout << "La marcha " << gear_checking_ << " tambien esta fuera de rango, pero no pasa la velocidad maxima..." << std::endl;
					
					// Si se meten mas comprobaciones, no debemos retornar valor
					return true;
				}

				std::cout << "La velocidad actual (" << concurrentData.get_current_speed() << " km/h) no está en el rango permitido para la marcha " << gear_checking_ << " ("
					<< concurrentData.get_gear_map()[gear_checking_].speedLimit.min << " - "
					<< concurrentData.get_gear_map()[gear_checking_].speedLimit.max << " km/h)." << std::endl;
				return false;
			}

			return true;
		}

	private:
		int gear_checking_;
	};
}