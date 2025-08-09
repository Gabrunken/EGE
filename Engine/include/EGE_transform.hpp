#pragma once
#include <EGE_vector2.hpp>

namespace EGE
{
	class Transform
	{
	public:
		Vector2 Position;
		Vector2 Scale;
		float Rotation;

		constexpr Transform() {}
		constexpr Transform(const Vector2& _Position, const Vector2& _Scale, float _Rotation)
			: Position(_Position), Scale(_Scale), Rotation(_Rotation) {}
	}
}