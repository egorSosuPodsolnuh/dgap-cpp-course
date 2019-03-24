#include <iostream>
#include <cmath>
#include "complex.h"

Complex::Complex()
        : re(.0),
          im(.0) {}

Complex::Complex(float a, float b = .0)
        : re(a),
          im(b) {}

Complex::Complex(const Complex &other) {
    re = other.re;
    im = other.im;
}

Complex::Complex operator=(const Complex &other) {
    re = other.re;
    im = other.im;
}

Complex::~Complex() = default;

float Complex::Re() const {
    return re;
}

float Complex::&Re() {
    return re;
}

float Complex::Im() const {
    return im;
}

float Complex::&Im() {
    return im;
}

Complex Complex::conj() const {
    return Complex(re, -im);
}

float Complex::abs(const Complex &z) {
    return sqrt(z.Re() * z.Re() + z.Im() * z.Im());
}

Complex operator+(const Complex &one, const Complex &other) {
    return Complex(one.Re() + other.Re(), one.Im() + other.Im());
}

Complex operator+(const Complex &one, float other) {
    return Complex(one.Re() + other, one.Im());
}

Complex operator+(float other, const Complex &one) {
    return Complex(one.Re() + other, one.Im());
}

Complex operator-(const Complex &one, const Complex &other) {
    return Complex(one.Re() - other.Re(), one.Im() - other.Im());
}

Complex operator-(const Complex &one, float other) {
    return Complex(one.Re() - other, one.Im());
}

Complex operator-(float other, const Complex &one) {
    return Complex(other - one.Re(), -one.Im());
}

Complex operator*(const Complex &one, const Complex &other) {
    return Complex(one.Re() * other.Re() - one.Im() * other.Im(),
                   one.Re() * other.Im() + one.Im() * other.Re());
}

Complex operator*(const Complex &one, float other) {
    return Complex(one.Re() * other, one.Im() * other);
}

Complex operator*(float other, const Complex &one) {
    return Complex(one.Re() * other, one.Im() * other);
}

Complex operator/(const Complex &one, float other) {
    return Complex(one.Re() / other, one.Im() / other);
}

Complex operator/(const Complex &one, const Complex &other) {
    float denom_abs = abs(other);
    Complex
            inv = other.Conj() / (denom_abs * denom_abs);
    return one * inv;
}

Complex operator/(float other, const Complex &one) {
    float denom_abs = abs(one);
    Complex
            inv = one.Conj() / (denom_abs * denom_abs);
    return other * inv;
}

bool operator==(const Complex &one, const Complex &other) {
    return one.Re() == other.Re() && one.Im() == other.Im();
}

bool operator!=(const Complex &one, const Complex &other) {
    return one.Re() != other.Re() || one.Im() != other.Im();
}