#pragma once

namespace EGE
{
	class Vector2
	{
	public:
		float X, Y;

		constexpr Vector2() : X(0), Y(0) {}
		constexpr Vector2(float Value) : X(Value), Y(Value) {}
		constexpr Vector2(float X_, float Y_) : X(X_), Y(Y_) {}

		constexpr static Vector2 Up()    {return Vector2(0.0f, 1.0f);}
		constexpr static Vector2 Down()  {return Vector2(0.0f, -1.0f);}
		constexpr static Vector2 Left()  {return Vector2(-1.0f, 0.0f);}
		constexpr static Vector2 Right() {return Vector2(1.0f, 0.0f);}
	};
}