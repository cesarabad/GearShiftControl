#pragma once
#include <string>
#include "../DataReader.h"

namespace Infrastructure::Configuration {

	class JsonReader : public DataReader<std::string> {

	protected:
		const std::string filePath;

	public:
		explicit JsonReader(const std::string& filePath) : filePath(filePath) {}

		~JsonReader() override = default;

		std::string read() const override;
	};
}