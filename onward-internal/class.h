#pragma once

namespace unity {
	class color {
	public:
		float r;
		float g;
		float b;
		float a;
	};
	class vector {
	public:
		float x;
		float y;
		float z;
		vector(float x, float y, float z) {
			this->x = x; this->y = y; this->z = z;
		}
	};
};