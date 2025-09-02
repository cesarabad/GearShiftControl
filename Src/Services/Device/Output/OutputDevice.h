#pragma once
#include "../Device.h"

namespace Services::Device {
	class OutputDevice : public virtual Device {
	public:
		~OutputDevice() override = default;
		virtual void write(const char* data, size_t size) const = 0;
	};
}