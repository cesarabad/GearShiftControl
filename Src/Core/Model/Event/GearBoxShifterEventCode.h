#pragma once

namespace Core::Model::Event {
	enum class GearBoxManualShiftEventCode {
		Neutral = 0,
		FirstGear = 295,
		FirstGear2 = 293,
		SecondGear = 294,
		SecondGear2 = 292,
		ThirdGear = 291,
		FourthGear = 290,
		FifthGear = 289,
		Reverse = 288
	};

	enum class GearBoxSecuentialShiftEventCode {
		UpShift = 291,
		DownShift = 290
	};
}