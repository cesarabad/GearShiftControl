#pragma once
namespace Core::Model::GearModel {
	struct Rotation {
		float x;
		float y;
	};
	struct SpeedLimit {
		float min;
		float max;
		float maxToReduce;
	};
	struct Gear {
		int number;
		Rotation rotation;
		SpeedLimit speedLimit;
	};
};