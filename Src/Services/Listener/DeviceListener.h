#pragma once
#include <string>

namespace Services::Listener {
	class DeviceListener {
	public:
		virtual ~DeviceListener() = default;
		virtual void listen(const std::string& event) const = 0;
		virtual void stop_listening() = 0;

	protected: 
		bool listening_{ false };
	};
}
