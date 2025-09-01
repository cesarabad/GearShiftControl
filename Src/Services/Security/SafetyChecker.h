#pragma once

namespace Services::Security {

class SafetyChecker {

public:
	
	virtual ~SafetyChecker() = default;
	virtual bool check() const = 0;
};

}