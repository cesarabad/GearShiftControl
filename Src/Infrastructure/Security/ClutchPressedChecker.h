#pragma once
#include "../../Services/Security/safetyChecker.h"
#include "../../Services/Data/ConcurrentData.h"

namespace Infrastructure::Security {
	class ClutchPressedChecker : Services::Security::SafetyChecker {
	public:
		ClutchPressedChecker() = default;

        static ClutchPressedChecker& getInstance() {
            static ClutchPressedChecker instance;
            return instance;
        }

        // Prohibimos copias
        ClutchPressedChecker(const ClutchPressedChecker&) = delete;
        ClutchPressedChecker& operator=(const ClutchPressedChecker&) = delete;

		virtual ~ClutchPressedChecker() = default;

		bool check() const override {
			return Services::Data::ConcurrentData::get_instance().is_clutch_pressed();
		}
	};
}