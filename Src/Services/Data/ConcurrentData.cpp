#include "ConcurrentData.h"
#include <iostream>

namespace Services::Data {

    // Definición de variables estáticas
    std::unique_ptr<ConcurrentData> ConcurrentData::instance_ = nullptr;
    std::once_flag ConcurrentData::init_flag_;

    ConcurrentData& ConcurrentData::get_instance() {
        std::call_once(init_flag_, []() {
            instance_.reset(new ConcurrentData());
            });
        return *instance_;
    }

    // Current gear
    void ConcurrentData::set_current_gear(int gear) {
        current_gear_.store(gear);
        std::cout << "Se ha puesto la marcha " << gear << std::endl;
    }

    int ConcurrentData::get_current_gear() const {
        return current_gear_.load();
    }

	// Clutch state
	void ConcurrentData::set_clutch_pressed(bool pressed) {
        if (is_clutch_pressed() != pressed) {
		    clutch_pressed_.store(pressed);
			std::cout << "Embrague " << (pressed ? "presionado" : "liberado") << std::endl;
        }
	}

	bool ConcurrentData::is_clutch_pressed() const {
		return clutch_pressed_.load();
	}

	// Current speed
	void ConcurrentData::set_current_speed(float speed) {
		current_speed_ = speed;
		std::cout << "Velocidad actual: " << speed << " km/h" << std::endl;
	}
	float ConcurrentData::get_current_speed() const {
		return current_speed_;
	}

    // Gear map
    void ConcurrentData::set_gear_map(const std::unordered_map<int, Core::Model::GearModel::Gear>& map) {
        std::lock_guard<std::mutex> lock(gear_map_mutex_);
        gear_map_ = map;
    }

    std::unordered_map<int, Core::Model::GearModel::Gear> ConcurrentData::get_gear_map() const {
        std::lock_guard<std::mutex> lock(gear_map_mutex_);
        return gear_map_;
    }

	// Configuration
	Core::Model::Configuration::Configuration ConcurrentData::get_configuration() const {
		return configuration_;
	}

} // namespace Services::Data
