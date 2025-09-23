#pragma once
#include <unordered_map>
#include <memory>
#include <mutex>
#include <atomic>
#include "../../Core/Model/Gear.h"
#include "../../Core/Model/Configuration/Configuration.h"

namespace Services::Data {

    class ConcurrentData {
    private:

        std::atomic<int> current_gear_ { 0 };
		std::atomic<bool> clutch_pressed_{ false };
		float current_speed_ { 0.0f };
        std::unordered_map<int, Core::Model::GearModel::Gear> gear_map_;
        mutable std::mutex gear_map_mutex_; // protege gear_map_
		Core::Model::Configuration::Configuration configuration_;


        ConcurrentData() = default;

        static std::unique_ptr<ConcurrentData> instance_;
        static std::once_flag init_flag_; // asegura creación thread-safe

    public:
        ConcurrentData(const ConcurrentData&) = delete;
        ConcurrentData& operator=(const ConcurrentData&) = delete;

        static ConcurrentData& get_instance();

        // Current gear
        void set_current_gear(int gear);
        int get_current_gear() const;

		// Clutch state
		void set_clutch_pressed(bool pressed);
		bool is_clutch_pressed() const;

		// Current speed
		void set_current_speed(float speed);
		float get_current_speed() const;

        // Gear map
        void set_gear_map(const std::unordered_map<int, Core::Model::GearModel::Gear>& map);
        std::unordered_map<int, Core::Model::GearModel::Gear> get_gear_map() const;

		// Configuration
		Core::Model::Configuration::Configuration get_configuration() const;
    };

} // namespace Services::Data
