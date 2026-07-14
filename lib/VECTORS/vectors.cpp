

// OBSOLETE
/*
#include "vectors.hpp"
#include <cstddef>
#include <iostream>

template<int N>
std::ostream& operator<<(std::ostream& os, const Vector<N> &v) {
    os << "(";
    for (int i = 0; i < N; i++) {
        os << v[i];
        if (i == N - 1) {
            os << ')';

        }
        os << ", ";

    }
    return os;
}


template<int N>
Vector<N> operator+(const Vector<N> &self, const Vector<N> &other) {
    Vector<N> result;
    for (int i = 0; i < N; i++){
        result[i] = self[i] + other[i];
    }
    return result;

}

template<int N>
Vector<N> operator-(const Vector<N> &self, const Vector<N> &other) {
    Vector<N> result;
    for (int i = 0; i < N; i++) {
        result[i] = self[i] - other[i];
    }
    return result;

}

template<int N>
Vector<N> operator*(const Vector<N> &self, float value) {
    Vector<N> result;
    for (int i = 0; i < N; i++) {
        result[i] = self[i] * value;
    }
    return result;
}

template<int N>
Vector<N> operator*(float value, const Vector<N> &self) {
    return self * value;
}

template<int N>
Vector<N> operator/(const Vector<N> &self, float value) {
    Vector<N> result;
    for (int i = 0; i < N; i++) {
        result[i] = self[i] / value;
    }
    return result;
}

template<int N>
Vector<N> operator/(float value, const Vector<N> &self) {
    return self * value;
}

template<int N>
float Vector<N>::dot(const Vector<N> &other) const {
    float dot = 0.f;
    for (int i = 0; i < N; i++) {
        dot += data[i] * other[i];
    }
    return dot;
}

template<int N>
float Vector<N>::length() const {
    return std::sqrt(this->dot(*this));
}

template<int N>
Vector<N> Vector<N>::normalised() const {
    return Vector<N>(*this) / this->length();
}

template<int N>
Vector<N>& Vector<N>::operator+=(const Vector<N> &other) {
    for (int i = 0; i < N; i++) {
        data[i] += other[i];
    }
    return *this;
}

template<int N>
Vector<N>& Vector<N>::operator-=(const Vector<N> &other) {
    for (int i = 0; i < N; i++) {
        data[i] -= other[i];
    }
    return *this;
}

template<int N>
Vector<N>& Vector<N>::operator*=(float value) {
    for (int i = 0; i < N; i++) {
        data[i] *= value;
    }
    return *this;
}

template<int N>
Vector<N>& Vector<N>::operator/=(float value) {
    for (int i = 0; i < N; i++) {
        data[i] /= value;
    }
    return *this;
}

template<int N>
float& Vector<N>::operator[](size_t index) {
    return this->data[index];
}

template<int N>
const float& Vector<N>::operator[](size_t index) const {
    return this->data[index];
}

Vector Vector::fromPolar(float magnitude, float angle) {
    return {std::cos(angle) * magnitude, std::sin(angle) * magnitude};
}
*/
