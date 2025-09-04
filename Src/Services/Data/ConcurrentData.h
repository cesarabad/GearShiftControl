#pragma once
#include <unordered_map>
#include <memory>
#include "../../Core/Model/Gear.h"

namespace Services::Data {

    class ConcurrentData {
    private:
        int current_gear_{ 0 };
        std::unordered_map<int, Core::Model::GearModel::Gear> gear_map_;

        ConcurrentData() = default;

        static std::unique_ptr<ConcurrentData> instance_;

    public:
        ConcurrentData(const ConcurrentData&) = delete;
        ConcurrentData& operator=(const ConcurrentData&) = delete;

        static ConcurrentData& get_instance() {
            if (!instance_) {
                instance_ = std::unique_ptr<ConcurrentData>(new ConcurrentData());
            }
            return *instance_;
        }

        void set_gear_map(const std::unordered_map<int, Core::Model::GearModel::Gear>& map) {
            gear_map_ = map;
        }

        const std::unordered_map<int, Core::Model::GearModel::Gear>& get_gear_map() const {
            return gear_map_;
        }

        void set_current_gear(int gear) { current_gear_ = gear; }
        int get_current_gear() const { return current_gear_; }
    };

    std::unique_ptr<ConcurrentData> ConcurrentData::instance_ = nullptr;

}
