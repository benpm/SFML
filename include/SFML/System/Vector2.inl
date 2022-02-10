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
template <typename T>
constexpr Vector2<T>::Vector2() :
x(0),
y(0)
{

}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>::Vector2(T X, T Y) :
x(X),
y(Y)
{

}


////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
constexpr Vector2<T>::Vector2(const Vector2<U>& vector) :
x(static_cast<T>(vector.x)),
y(static_cast<T>(vector.y))
{
}


////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::length() const
{
    using std::sqrt; // allow ADL

	return sqrt(lengthSq());
}


////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::lengthSq() const
{
	return this->dot(*this);
}


////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::withLength(T newLength) const
{
	assert(*this != Vector2<T>());

	return (*this) * newLength / length();
}


////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::normalized() const
{
	assert(*this != Vector2<T>());
	return (*this) / length();
}


////////////////////////////////////////////////////////////
template <typename T>
Angle Vector2<T>::signedAngleTo(const Vector2<T>& rhs) const
{
    using std::atan2; // allow ADL

	assert(*this != Vector2<T>());
    assert(rhs != Vector2<T>());
	return radians(atan2(lhs.cross(rhs), lhs.dot(rhs)));
}


////////////////////////////////////////////////////////////
template <typename T>
Angle Vector2<T>::polarAngle() const
{
    using std::atan2; // allow ADL

	assert(*this != Vector2<T>());
	return radians(atan2(vector.y, vector.x));
}


////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::withPolarAngle(Angle newAngle) const
{
	// No assert here, because turning a zero vector is well-defined (yields always zero vector)
    
    using std::sin; // allow ADL
    using std::cos;

	T vecLength = length(vector);

    return Vector2<T>(
	    vecLength * cos(newAngle.asRadians()),
	    vecLength * sin(newAngle.asRadians()));
}


////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::rotatedBy(Angle angle) const
{
	// No assert here, because rotating a zero vector is well-defined (yields always zero vector)
        
    using std::sin; // allow ADL
    using std::cos;

	T c = cos(angle.asRadians());
	T s = sin(angle.asRadians());

	// Don'T manipulate x and y separately, otherwise they're overwritten too early
	return Vector2<T>(
		c * vector.x - s * vector.y,
		s * vector.x + c * vector.y);
}



////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::perpendicular() const
{
	return Vector2<T>(-vector.y, vector.x);
}


////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::projectedOnto(const Vector2<T>& axis) const
{
	assert(axis != Vector2<T>());
	return this->dot(axis) / axis.lengthSq() * axis;
}


////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::dot(const Vector2<T>& rhs) const
{
	return x * rhs.x + y * rhs.y;
}


////////////////////////////////////////////////////////////
template <typename T>
T Vector2<T>::cross(const Vector2<T>& rhs) const
{
	return x * rhs.y - y * rhs.x;
}


////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::cwiseMul(const Vector2<T>& rhs) const
{
	return Vector2<T>(x * rhs.x, y * rhs.y);
}


////////////////////////////////////////////////////////////
template <typename T>
Vector2<T> Vector2<T>::cwiseDiv(const Vector2<T>& rhs) const
{
	assert(rhs.x != 0 && rhs.y != 0);
	return Vector2<T>(x / rhs.x, y / rhs.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator -(const Vector2<T>& right)
{
    return Vector2<T>(-right.x, -right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x + right.x, left.y + right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x - right.x, left.y - right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator *(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x * right, left.y * right);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator *(T left, const Vector2<T>& right)
{
    return Vector2<T>(right.x * left, right.y * left);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator *=(Vector2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator /(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x / right, left.y / right);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator /=(Vector2<T>& left, T right)
{
    left.x /= right;
    left.y /= right;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x != right.x) || (left.y != right.y);
}
