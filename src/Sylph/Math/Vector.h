/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 */

#ifndef SYLPH_MATH_VECTOR_H_
#define SYLPH_MATH_VECTOR_H_

#include "internal_base.h"
#include "Angle.h"

SYLPH_BEGIN_MATHNS
    template<class Number>
    class Vector2 {
    public:
        static Vector2<Number> zero;
        static Vector2<Number> unitX;
        static Vector2<Number> unitY;
        static Vector2<Number> unitXY;
    public:
        Vector() : x(0), y(0) {}
        Vector(Number _x, Number _y) : x(_x), y(_y) {}

        auto mag() const -> decltype(sqrt(normSq)) {
            return std::sqrt(normSq);
        }

        Number magSq() const {
            return x*x + y*y;
        }

        Vector2<Number> normalize() const {
            Vector2<Number> toReturn;
            toReturn.x = x*x/magSq();
            toReturn.y = y*y/magSq();
            return toReturn;
        }

        bool multipleOf(const Vector& v2) const {
            return x*v2.y == y * v2.x;
        }

        bool isUnitVector() const {
            return normSq == 1.0f;
        }

        Vector2<Number> operator-() const {
            Vector2<Number> toReturn;
            toReturn.x = -x;
            toReturn.y = -y;
            return toReturn;
        }

    public:
        Number x, y;
    };

    template<class Number>
    auto mag(const Vector2<Number>& v) -> decltype(v.mag()) {
        return v.mag();
    }

    template<class Number>
    Number magSq(const Vector2<Number>& v) {
        return v.magSq();
    }

    template<class Number>
    auto dist(const Vector2<Number>& v1, const Vector2<Number>& v2) -> 
            decltype((v2-v1).mag()) {
        return (v2-v1).mag();
    }

    template<class Number>
    Number distSq(const Vector2<Number>& v1, const Vector2<Number>& v2) {
        return (v2-v1).magSq();
    }

    template<class Number>
    Vector2<Number>& operator+=(Vector2<Number>& v1, const Vector2<Number>& v2) {
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
    }

    template<class Number>
    Vector2<Number> operator+(const Vector2<Number>& v1,
            const Vector2<Number>& v2) {
        return Vector2<Number>(v1) += v2;
    }

    template<class Number>
    Vector2<Number>& operator-=(Vector2<Number>& v1, const Vector2<Number>& v2) {
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }

    template<class Number>
    Vector2<Number> operator-(const Vector2<Number>& v1,
            const Vector2<Number>& v2) {
        return Vector2<Number>(v1) -= v2;
    }

    template<class Number>
    Number operator*(const Vector2<Number>& v1, const Vector2<Number>& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template<class Number>
    Vector2<Number>& operator*=(Vector2<Number>& v, Number n) {
        v.x *= n; v.y *= n;
        return v;
    }

    template<class Number>
    Vector2<Number> operator*(const Vector2<Number>& v, Number n) {
        return Vector2<Number>(v) *= n;
    }

    template<class Number>
    Vector2<Number> operator*(Number n, const Vector2<Number>& v) {
        return Vector2<Number>(v) *= n;
    }

    template<class Number>
    Vector2<Number>& operator/=(Vector2<Number>& v, Number n) {
        v.x /= n; v.y /= n;
        return v;
    }

    template<class Number>
    Vector2<Number> operator/(const Vector2<Number>& v, Number n) {
        return Vector2<Number>(v) /= n;
    }
    template<class Number>
    Number operator^(const Vector2<Number>& v1, const Vector2<Number>& v2) {
        return std::acos((v1*v2)/(norm(v1)*norm(v2)));
    }

    template<class Number>
    class Vector3 {
    public:
        Vector() : x(0), y(0) {}
        Vector(Number _x, Number _y, Number _z) : x(_x), y(_y), z(_z) {}

        Number norm() {
            return std::sqrt(x*x + y*y + z*z);
        }
    public:
        Number x, y, z;
    };

    inline anglef atan2(const vec2f& a) {
        return atan2(a.y,a.x);
    }

    inline angled atan2(const vec2d& a) {
        return atan2(a.y,a.x);
    }

    typedef Vector2f Vector2<float>;
    typedef Vector2d Vector2<double>;
    typedef Vector3f Vector3<float>;
    typedef Vector3d Vector3<double>;

    typedef vec2f Vector2f;
    typedef vec2d Vector2d;
    typedef vec3f Vector3f;
    typedef vec3d Vector3d;


    typedef Point2f Vector2f;
    typedef Point2d Vector2d;
    typedef Point3f Vector2f;
    typedef Point3d Vector3d;

    typedef pt2f Point2f;
    typedef pt2d Point2d;
    typedef pt3f Point3f;
    typedef pt3d Point3d;

    typedef Size2f Vector2f;
    typedef Size3f Vector3f;
    typedef Size2d Vector2d;
    typedef Size3d Vector3d;

    typedef size2f Size2f;
    typedef size3f Size3f;
    typedef size3d Size3d;
    typedef size2d Size2d;
SYLPH_END_MATHNS

#endif /* SYLPH_MATH_VECTOR_H_ */
