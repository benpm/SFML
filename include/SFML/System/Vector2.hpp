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

#ifndef SFML_VECTOR2_HPP
#define SFML_VECTOR2_HPP

#include <SFML/System/Angle.hpp>
#include <cassert>
#include <cmath>
#include <type_traits>


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility template class for manipulating
///        2-dimensional vectors
///
////////////////////////////////////////////////////////////
template <typename T>
class Vector2
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates a Vector2(0, 0).
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from its coordinates
    ///
    /// \param X X coordinate
    /// \param Y Y coordinate
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2(T X, T Y);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from another type of vector
    ///
    /// This constructor doesn't replace the copy constructor,
    /// it's called only when U != T.
    /// A call to this constructor will fail to compile if U
    /// is not convertible to T.
    ///
    /// \param vector Vector to convert
    ///
    ////////////////////////////////////////////////////////////
    template <typename U>
    constexpr explicit Vector2(const Vector2<U>& vector);
    
    ////////////////////////////////////////////////////////////
    /// \brief Length of the vector <i>(floating point only)</i>.
    ///
    /// If you are not interested in the actual length, but only in comparisons, consider using lengthSq().
    ///
    ////////////////////////////////////////////////////////////
    T length() const;

    ////////////////////////////////////////////////////////////
    /// \brief Square of vector's length <i>(floating point only)</i>.
    /// 
    /// Suitable for comparisons, more efficient than length().
    ///
    ////////////////////////////////////////////////////////////
    T lengthSq() const;

    ////////////////////////////////////////////////////////////
    /// \brief Scales \c *this to have length <tt>|newLength|</tt> <i>(floating point only)</i>.
    /// 
    /// If \c newLength is less than zero, the vector's direction changes.
    /// 
    /// \pre \c vector is no zero vector.
    ///
    ////////////////////////////////////////////////////////////
    Vector2 withLength(T newLength) const;

    ////////////////////////////////////////////////////////////
    /// \brief Vector with same direction but length 1 <i>(floating point only)</i>.
    /// 
    /// \pre \c vector is no zero vector.
    ///
    ////////////////////////////////////////////////////////////
    Vector2 normalized() const;

    ////////////////////////////////////////////////////////////
    /// \brief Signed angle from \c *this to \c rhs <i>(floating point only)</i>.
    /// 
    /// \return Angle in degrees in the interval [-180,180].
    /// The angle determines how much you have to rotate \c *this
    ///  until it points to the same direction as \c rhs.
    /// \pre Neither \c *this nor \c rhs is a zero vector.
    ///
    ////////////////////////////////////////////////////////////
    Angle signedAngleTo(const Vector2& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Angle from +X or (1,0) vector <i>(floating point only)</i>.
    /// 
    /// The vector (1,0) corresponds to 0 degrees, (0,1) corresponds to 90 degrees.
    /// 
    /// \return Angle in degrees in the interval [-180,180].
    /// \pre \c vector is no zero vector.
    ///
    ////////////////////////////////////////////////////////////
    Angle polarAngle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns a vector with same length, but given polar angle <i>(floating point only)</i>.
    /// 
    /// The vector (1,0) corresponds 0 degrees, (0,1) corresponds 90 degrees.
    ///
    ////////////////////////////////////////////////////////////
    Vector2 withPolarAngle(Angle newAngle) const;

    ////////////////////////////////////////////////////////////
    /// \brief Rotate by given angle <i>(floating point only)</i>.
    /// 
    /// The vector (1,0) corresponds 0 degrees, (0,1) corresponds 90 degrees.
    ///
    ////////////////////////////////////////////////////////////
    Vector2 rotatedBy(Angle angle) const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns a perpendicular vector <i>(floating point only)</i>.
    /// 
    /// Returns \c vector rotated by 90 degrees counter clockwise; (x,y) becomes (-y,x).
    /// For example, the vector (1,0) is transformed to (0,1).
    ///
    ////////////////////////////////////////////////////////////
    Vector2 perpendicular() const;

    ////////////////////////////////////////////////////////////
    /// \brief Projection of \c vector onto \c axis <i>(floating point only)</i>.
    /// 
    /// \param vector Vector to project.
    /// \param axis Vector being projected onto. Need not be a unit vector, but must not have length zero.
    ///
    ////////////////////////////////////////////////////////////
    Vector2 projectedOnto(const Vector2& axis) const;

    ////////////////////////////////////////////////////////////
    /// \brief Computes the dot product of two 2D vectors <i>(floating point only)</i>.
    ///
    ////////////////////////////////////////////////////////////
    T dot(const Vector2& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Cross product's Z component <i>(floating point only)</i>.
    /// 
    /// Treats the operands as 3D vectors, computes their cross product and returns the result's Z component
    ///  (X and Y components are always zero).
    ///
    ////////////////////////////////////////////////////////////
    T cross(const Vector2& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Component-wise multiplication of \c *this and \c rhs <i>(floating point only)</i>.
    /// 
    /// Computes <tt>(lhs.x*rhs.x, lhs.y*rhs.y)</tt>. Main use case are scales.
    ///
    ////////////////////////////////////////////////////////////
    Vector2 cwiseMul(const Vector2& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Component-wise quotient of \c *this and \c rhs <i>(floating point only)</i>.
    /// 
    /// Computes <tt>(lhs.x/rhs.x, lhs.y/rhs.y)</tt>. Main use case are scales.
    /// 
    /// \pre Neither component of \c rhs is zero.
    ///
    ////////////////////////////////////////////////////////////
    Vector2 cwiseDiv(const Vector2& rhs) const;


    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    T x; //!< X coordinate of the vector
    T y; //!< Y coordinate of the vector
};

// Define the most common types
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;
using Vector2f = Vector2<float>;

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of unary operator -
///
/// \param right Vector to negate
///
/// \return Memberwise opposite of the vector
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator -(const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator +=
///
/// This operator performs a memberwise addition of both vectors,
/// and assigns the result to \c left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \c left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator -=
///
/// This operator performs a memberwise subtraction of both vectors,
/// and assigns the result to \c left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \c left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator +
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise addition of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator -
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise subtraction of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise multiplication by \c right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator *(const Vector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a scalar value)
/// \param right Right operand (a vector)
///
/// \return Memberwise multiplication by \c left
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator *(T left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator *=
///
/// This operator performs a memberwise multiplication by \c right,
/// and assigns the result to \c left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \c left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator *=(Vector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator /
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise division by \c right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator /(const Vector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator /=
///
/// This operator performs a memberwise division by \c right,
/// and assigns the result to \c left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \c left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator /=(Vector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator ==
///
/// This operator compares strict equality between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \c left is equal to \c right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator !=
///
/// This operator compares strict difference between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \c left is not equal to \c right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator !=(const Vector2<T>& left, const Vector2<T>& right);

#include <SFML/System/Vector2.inl>

} // namespace sf


#endif // SFML_VECTOR2_HPP


////////////////////////////////////////////////////////////
/// \class sf::Vector2
/// \ingroup system
///
/// sf::Vector2 is a simple class that defines a mathematical
/// vector with two coordinates (x and y). It can be used to
/// represent anything that has two dimensions: a size, a point,
/// a velocity, etc.
///
/// The template parameter T is the type of the coordinates. It
/// can be any type that supports arithmetic operations (+, -, /, *)
/// and comparisons (==, !=), for example int or float.
///
/// You generally don't have to care about the templated form (sf::Vector2<T>),
/// the most common specializations have special type aliases:
/// \li sf::Vector2<float> is sf::Vector2f
/// \li sf::Vector2<int> is sf::Vector2i
/// \li sf::Vector2<unsigned int> is sf::Vector2u
///
/// The sf::Vector2 class has a small and simple interface, its x and y members
/// can be accessed directly (there are no accessors like setX(), getX()) and it
/// contains no mathematical function like dot product, cross product, length, etc.
///
/// Usage example:
/// \code
/// sf::Vector2f v1(16.5f, 24.f);
/// v1.x = 18.2f;
/// float y = v1.y;
///
/// sf::Vector2f v2 = v1 * 5.f;
/// sf::Vector2f v3;
/// v3 = v1 + v2;
///
/// bool different = (v2 != v3);
/// \endcode
///
/// Note: for 3-dimensional vectors, see sf::Vector3.
///
////////////////////////////////////////////////////////////
