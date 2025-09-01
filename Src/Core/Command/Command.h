#pragma once
#include <unordered_map>
#include <memory>
#include "../../Services/Security/SafetyChecker.h"
#include "../../Services/Data/ConcurrentData.h"
namespace Core::Commands {
	class Command {
	protected:
		std::unordered_map<int, std::shared_ptr<SafetyChecker>> safetyCheckers_;
		std::shared_ptr<ConcurrentData> data_;

	public:
		
		Command(std::shared_ptr<ConcurrentData> data,
			std::unordered_map<int, std::shared_ptr<SafetyChecker>> safetyCheckers = {})
			: safetyCheckers_(std::move(safetyCheckers)), data_(std::move(data)) {}


		virtual ~Command() = default;
		virtual void execute() = 0;
	};
}
