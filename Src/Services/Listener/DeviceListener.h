#pragma once
#include <string>

namespace Services::Listener {
	class DeviceListener {
	public:
		virtual ~DeviceListener() = default;
		virtual void listen(const std::string& event) const = 0;
	};
}
