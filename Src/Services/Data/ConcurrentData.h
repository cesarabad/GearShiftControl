#pragma once
#include <unordered_map>
#include <memory>
#include <mutex>
#include <atomic>
#include "../../Core/Model/Gear.h"

namespace Services::Data {

    class ConcurrentData {
    private:
        std::atomic<int> current_gear_{ 0 };
        std::atomic<bool> clutch_pressed_{ false };
        std::unordered_map<int, Core::Model::GearModel::Gear> gear_map_;
        mutable std::mutex gear_map_mutex_; // protege gear_map_

        ConcurrentData() = default;

        static std::unique_ptr<ConcurrentData> instance_;
        static std::once_flag init_flag_; // asegura creación thread-safe

    public:
        ConcurrentData(const ConcurrentData&) = delete;
        ConcurrentData& operator=(const ConcurrentData&) = delete;

        static ConcurrentData& get_instance() {
            std::call_once(init_flag_, []() {
                instance_.reset(new ConcurrentData());
                });
            return *instance_;
        }

        // Current gear
        void set_current_gear(int gear) { current_gear_.store(gear); }
        int get_current_gear() const { return current_gear_.load(); }

        // Clutch pressed
        void set_clutch_pressed(bool pressed) { clutch_pressed_.store(pressed); }
        bool is_clutch_pressed() const { return clutch_pressed_.load(); }

        // Gear map
        void set_gear_map(const std::unordered_map<int, Core::Model::GearModel::Gear>& map) {
            std::lock_guard<std::mutex> lock(gear_map_mutex_);
            gear_map_ = map;
        }

        std::unordered_map<int, Core::Model::GearModel::Gear> get_gear_map() const {
            std::lock_guard<std::mutex> lock(gear_map_mutex_);
            return gear_map_;
        }
    };

    // Inicialización de variables estáticas
    std::unique_ptr<ConcurrentData> ConcurrentData::instance_ = nullptr;
    std::once_flag ConcurrentData::init_flag_;

} // namespace Services::Data
