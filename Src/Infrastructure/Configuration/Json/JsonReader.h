#pragma once
#include <string>
#include "../DataReader.h"

namespace Infrastructure::Configuration {

	class JsonReader : public DataReader<std::string> {

	protected:
		std::string file_path_;

	public:
		explicit JsonReader(const std::string& filePath) : file_path_(filePath) {}

		~JsonReader() override = default;

		std::string read() const override;

		void set_path(const std::string& newPath) {
			file_path_ = newPath;
		}
	};
}