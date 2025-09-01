#pragma once
#include <memory>
#include "../Data/ConcurrentData.h"

namespace Services::Security {

class SafetyChecker {

protected:
	std::shared_ptr<ConcurrentData> data_;

public:
	inline static const int CLUTCHED = 1;

	SafetyChecker(std::shared_ptr<ConcurrentData> data) : data_(std::move(data)) {}
	virtual ~SafetyChecker() = default;
	virtual bool check() const = 0;
	};

}