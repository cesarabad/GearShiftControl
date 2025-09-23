#pragma once
#include "../../Services/Security/SafetyChecker.h"

namespace Infrastructure::Security {
	class ShiftGearChecker : Services::Security::SafetyChecker {
	public:
		ShiftGearChecker() = default;

		static ShiftGearChecker& getInstance() {
			static ShiftGearChecker instance;
			return instance;
		}

		// Prohibimos copias
		ShiftGearChecker(const ShiftGearChecker&) = delete;
		ShiftGearChecker& operator=(const ShiftGearChecker&) = delete;

		virtual ~ShiftGearChecker() = default;

		bool check() const override {
			// Mirar si la marcha que se intenta meter esta dentro del diccionario de marchas
			// Leer el config para ver si hay que comprobar el embrague y si esta presionado
			// Leer el config para ver si hay que leer la velocidad y si esta dentro del rango
			return true;//Services::Data::ConcurrentData::get_instance().is_clutch_pressed();
		}
	};
}