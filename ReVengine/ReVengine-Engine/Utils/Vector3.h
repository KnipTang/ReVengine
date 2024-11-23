#pragma once
#include <type_traits>
#include <stdexcept>
#include <cmath>

struct Vector3
{
	float x;
	float y;
	float z;

    Vector3(float xI = 0.0f, float yI = 0.0f, float zI = 0.0f)
        : x(xI), y(yI), z(zI) {}

    float Magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 Normalized() const
    {
        float mag = Magnitude();
        if (mag == 0.0f)
        {
            return Vector3(0.0f, 0.0f, 0.0f);
        }
        else
        {
            return *this / mag;
        }
    }

    template <typename T>
    Vector3 operator*(T scalar) const
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be an arithmetic type");

        using CommonType = typename std::common_type<T, float>::type;
        CommonType scaledX = static_cast<CommonType>(x) * static_cast<CommonType>(scalar);
        CommonType scaledY = static_cast<CommonType>(y) * static_cast<CommonType>(scalar);
        CommonType scaledZ = static_cast<CommonType>(z) * static_cast<CommonType>(scalar);

        return Vector3(static_cast<float>(scaledX), static_cast<float>(scaledY), static_cast<float>(scaledZ));
    }

    template <typename T>
    Vector3 operator+(T scalar) const
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be an arithmetic type");

        using CommonType = typename std::common_type<T, float>::type;
        CommonType addedX = static_cast<CommonType>(x) + static_cast<CommonType>(scalar);
        CommonType addedY = static_cast<CommonType>(y) + static_cast<CommonType>(scalar);
        CommonType addedZ = static_cast<CommonType>(z) + static_cast<CommonType>(scalar);

        return Vector3(static_cast<float>(addedX), static_cast<float>(addedY), static_cast<float>(addedZ));
    }

    template <typename T>
    Vector3 operator-(T scalar) const
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be an arithmetic type");

        using CommonType = typename std::common_type<T, float>::type;
        CommonType subtractedX = static_cast<CommonType>(x) - static_cast<CommonType>(scalar);
        CommonType subtractedY = static_cast<CommonType>(y) - static_cast<CommonType>(scalar);
        CommonType subtractedZ = static_cast<CommonType>(z) - static_cast<CommonType>(scalar);

        return Vector3(static_cast<float>(subtractedX), static_cast<float>(subtractedY), static_cast<float>(subtractedZ));
    }

    template <typename T>
    Vector3 operator/(T scalar) const
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be an arithmetic type");
        if (scalar == 0) throw std::runtime_error("Division by zero is not allowed");

        using CommonType = typename std::common_type<T, float>::type;
        CommonType dividedX = static_cast<CommonType>(x) / static_cast<CommonType>(scalar);
        CommonType dividedY = static_cast<CommonType>(y) / static_cast<CommonType>(scalar);
        CommonType dividedZ = static_cast<CommonType>(z) / static_cast<CommonType>(scalar);

        return Vector3(static_cast<float>(dividedX), static_cast<float>(dividedY), static_cast<float>(dividedZ));
    }

    template <typename T>
    Vector3& operator*=(T scalar)
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be an arithmetic type");

        using CommonType = typename std::common_type<T, float>::type;
        x = static_cast<float>(static_cast<CommonType>(x) * static_cast<CommonType>(scalar));
        y = static_cast<float>(static_cast<CommonType>(y) * static_cast<CommonType>(scalar));
        z = static_cast<float>(static_cast<CommonType>(z) * static_cast<CommonType>(scalar));

        return *this;
    }

    template <typename T>
    Vector3& operator+=(T scalar)
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be an arithmetic type");

        using CommonType = typename std::common_type<T, float>::type;
        x = static_cast<float>(static_cast<CommonType>(x) + static_cast<CommonType>(scalar));
        y = static_cast<float>(static_cast<CommonType>(y) + static_cast<CommonType>(scalar));
        z = static_cast<float>(static_cast<CommonType>(z) + static_cast<CommonType>(scalar));

        return *this;
    }

    template <typename T>
    Vector3& operator-=(T scalar)
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be an arithmetic type");

        using CommonType = typename std::common_type<T, float>::type;
        x = static_cast<float>(static_cast<CommonType>(x) - static_cast<CommonType>(scalar));
        y = static_cast<float>(static_cast<CommonType>(y) - static_cast<CommonType>(scalar));
        z = static_cast<float>(static_cast<CommonType>(z) - static_cast<CommonType>(scalar));

        return *this;
    }

    template <typename T>
    Vector3& operator/=(T scalar)
    {
        static_assert(std::is_arithmetic<T>::value, "Scalar must be an arithmetic type");
        if (scalar == 0) throw std::runtime_error("Division by zero is not allowed");

        using CommonType = typename std::common_type<T, float>::type;
        x = static_cast<float>(static_cast<CommonType>(x) / static_cast<CommonType>(scalar));
        y = static_cast<float>(static_cast<CommonType>(y) / static_cast<CommonType>(scalar));
        z = static_cast<float>(static_cast<CommonType>(z) / static_cast<CommonType>(scalar));

        return *this;
    }

    Vector3 operator*(Vector3 scalar) const
    {
        float scaledX = x * scalar.x;
        float scaledY = y * scalar.y;
        float scaledZ = z * scalar.z;

        return Vector3(scaledX, scaledY, scaledZ);
    }

    Vector3 operator+(Vector3 scalar) const
    {
        float scaledX = x + scalar.x;
        float scaledY = y + scalar.y;
        float scaledZ = z + scalar.z;

        return Vector3(scaledX, scaledY, scaledZ);
    }

    Vector3 operator-(Vector3 scalar) const
    {
        float scaledX = x - scalar.x;
        float scaledY = y - scalar.y;
        float scaledZ = z - scalar.z;

        return Vector3(scaledX, scaledY, scaledZ);
    }

    Vector3 operator/(Vector3 scalar) const
    {
        float scaledX = x / scalar.x;
        float scaledY = y / scalar.y;
        float scaledZ = z / scalar.z;

        return Vector3(scaledX, scaledY, scaledZ);
    }

    Vector3& operator*=(Vector3 scalar)
    {
        x *= scalar.x;
        y *= scalar.y;
        z *= scalar.z;

        return *this;
    }

    Vector3& operator+=(Vector3 scalar)
    {
        x += scalar.x;
        y += scalar.y;
        z += scalar.z;

        return *this;
    }

    Vector3& operator-=(Vector3 scalar)
    {
        x -= scalar.x;
        y -= scalar.y;
        z -= scalar.z;

        return *this;
    }

    Vector3& operator/=(Vector3 scalar)
    {
        x /= scalar.x;
        y /= scalar.y;
        z /= scalar.z;

        return *this;
    }
};