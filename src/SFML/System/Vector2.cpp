////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2022 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <cmath>


namespace sf
{
////////////////////////////////////////////////////////////
float length(const Vector2f& vector)
{
	return std::sqrt(lengthSquared(vector));
}

////////////////////////////////////////////////////////////
float lengthSquared(const Vector2f& vector)
{
	return dot(vector, vector);
}

////////////////////////////////////////////////////////////
void setLength(Vector2f& vector, float newLength)
{
	assert(vector != Vector2f());
	vector *= newLength / length(vector);
}

////////////////////////////////////////////////////////////
Vector2f normalized(const Vector2f& vector)
{
	assert(vector != Vector2f());
	return vector / length(vector);
}

////////////////////////////////////////////////////////////
float signedAngle(const Vector2f& lhs, const Vector2f& rhs)
{
	assert(lhs != Vector2f() && rhs != Vector2f());
	return std::atan2(cross(lhs, rhs), dot(lhs, rhs));
}

////////////////////////////////////////////////////////////
float polarAngle(const Vector2f& vector)
{
	assert(vector != Vector2f());
	return std::atan2(vector.y, vector.x);
}

////////////////////////////////////////////////////////////
void setPolarAngle(Vector2f& vector, float newAngle)
{
	// No assert here, because turning a zero vector is well-defined (yields always zero vector)

	float vecLength = length(vector);

	vector.x = vecLength * std::cos(newAngle);
	vector.y = vecLength * std::sin(newAngle);
}

////////////////////////////////////////////////////////////
void rotate(Vector2f& vector, float angle)
{
	// No assert here, because turning a zero vector is well-defined (yields always zero vector)

	float cos = std::cos(angle);
	float sin = std::sin(angle);

	// Don'float manipulate x and y separately, otherwise they're overwritten too early
	vector = Vector2f(
		cos * vector.x - sin * vector.y,
		sin * vector.x + cos * vector.y);
}

////////////////////////////////////////////////////////////
Vector2f rotatedVector(const Vector2f& vector, float angle)
{
	// No assert here, because turning a zero vector is well-defined (yields always zero vector)

	Vector2f copy = vector;
	rotate(copy, angle);
	return copy;
}

////////////////////////////////////////////////////////////
Vector2f perpendicularVector(const Vector2f& vector)
{
	return Vector2f(-vector.y, vector.x);
}

////////////////////////////////////////////////////////////
Vector2f projectedVector(const Vector2f& vector, const Vector2f& axis)
{
	assert(axis != Vector2f());
	return dot(vector, axis) / lengthSquared(axis) * axis;
}

////////////////////////////////////////////////////////////
float dot(const Vector2f& lhs, const Vector2f& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

////////////////////////////////////////////////////////////
float cross(const Vector2f& lhs, const Vector2f& rhs)
{
	return lhs.x * rhs.y - lhs.y * rhs.x;
}

////////////////////////////////////////////////////////////
Vector2f cwiseProduct(const Vector2f& lhs, const Vector2f& rhs)
{
	return Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
}

////////////////////////////////////////////////////////////
Vector2f cwiseQuotient(const Vector2f& lhs, const Vector2f& rhs)
{
	assert(rhs.x != 0 && rhs.y != 0);
	return Vector2f(lhs.x / rhs.x, lhs.y / rhs.y);
}

} // namespace sf
