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
    }

    int ConcurrentData::get_current_gear() const {
        return current_gear_.load();
    }

	// Clutch state
	void ConcurrentData::set_clutch_pressed(bool pressed) {
		clutch_pressed_.store(pressed);
	}

	bool ConcurrentData::is_clutch_pressed() const {
		return clutch_pressed_.load();
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
