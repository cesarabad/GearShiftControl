#pragma once

namespace Infrastructure::Configuration {
	
	template<typename T>
	class DataReader {
	public:
		virtual ~DataReader() = default;
		virtual T read() const = 0;
	};
}