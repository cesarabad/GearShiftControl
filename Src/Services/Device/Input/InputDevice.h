#pragma once
#include "../Device.h"

namespace Services::Device {
	class InputDevice : public virtual Device {
	public:
		~InputDevice() override = default;
		virtual void read() const = 0;
	};
}