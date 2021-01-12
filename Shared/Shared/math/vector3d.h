#pragma once

#include <cmath>
#include <math.h>

#include <corecrt_math.h>
#include <corecrt_math_defines.h>

namespace math
{
	class vector3D
	{
	public:
		float x, y, z;
	};

	using qAngle = vector3D;
}