#pragma once
#include <iostream>
#include <cmath>
#include <type_traits>

template<typename T>

class Vector2D{
public:
    T x;
    T y;
    Vector2D() : x(0), y(0){}
    Vector2D(T x_, T y_) : x(x_), y(y_){}
    template<typename U>
    Vector2D(const Vector2D<U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)){}
    template<typename U>
    auto operator+(const Vector2D<U>& v) const -> Vector2D<std::common_type_t<T, U> >{
        return Vector2D<std::common_type_t<T, U> >(x + v.x, y + v.y);
    }
    template<typename U>
    auto operator-(const Vector2D<U>& v) const -> Vector2D<std::common_type_t<T, U> >{
        return Vector2D<std::common_type_t<T, U> >(x - v.x, y - v.y);
    }
    Vector2D operator*(float scalar){
        return Vector2D(x * scalar, y * scalar);
    }
    template<typename U>
    auto operator*(const Vector2D<U>& v) const -> Vector2D<std::common_type_t<T, U> >{
        return Vector2D<std::common_type_t<T, U> >(x * v.x, y * v.y);
    }
    Vector2D operator/(float scalar){
        return Vector2D(x / scalar, y / scalar);
    }
    template<typename U>
    auto operator/(const Vector2D<U>& v) const -> Vector2D<std::common_type_t<T, U> >{
        return Vector2D<std::common_type_t<T, U> >(x / v.x, y / v.y);
    }
    template<typename U>
    Vector2D<T>& operator=(const Vector2D<U>& v){
        x = static_cast<T>(v.x);
        y = static_cast<T>(v.y);
        return *this;
    }
    template<typename U>
    bool operator==(const Vector2D<U>& v){
        return x == v.x && y == v.y;
    }
    auto normalized() const -> Vector2D<T>{
        T length = std::sqrt(x * x + y * y);
        if(length == 0) return Vector2D(0, 0);
        return Vector2D<T>(x / length, y / length);
    }
    void ceil(){
        x = std::round(x);
        y = std::round(y);
    }
    void clamp(const Vector2D& min, const Vector2D& max){
        if(x < min.x) x = min.x;
        if(x > max.x) x = max.x;
        if(y < min.y) y = min.y;
        if(y > max.y) y = max.y;
    }
    void clampLenght(float min, float max){
        T len = length();
        if(len < min) {
            *this = normalized() * min;
        } else if(len > max){
            *this = normalized() * max;
        }
    }
    void clampScalar(float min, float max){
        if(x < min) x = min;
        if(x > max) x = max;
        if(y < min) y = min;
        if(y > max) y = max;
    }
    Vector2D clone(){
        return Vector2D(x, y);
    }
    template<typename U>
    auto distanceTo(const Vector2D<U>& v) const -> std::common_type_t<T, U>{
        return std::sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
    }
    T length(){
        return std::sqrt(x * x + y * y);
    }
};
