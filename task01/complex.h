#include <iostream>
#include <iostream>
#include <math.h>

class Complex {
public:
    Complex()
            : re(.0),
              im(.0) {}

    Complex(float a, float b = .0)
            : re(a),
              im(b) {}

    Complex(const Complex &other) {
        re = other.re;
        im = other.im;
    }

    ~Complex() = default;

    float Re() const {
        return re;
    }

    float &Re() {
        return re;
    }

    float Im() const {
        return im;
    }

    float &Im() {
        return im;
    }

    float abs() {
        return sqrt(Re() * Re() + Im() * Im());
    }

    Complex conj() const {
        return Complex(re, -im);
    }

    Complex operator=(const Complex &other) {
        re = other.re;
        im = other.im;
    }

    Complex &operator+=(const Complex &c) {
        re += c.re;
        im += c.im;
        return *this;
    }

    // overload this operators:
    // +, -, *(Complex), /(Complex), *(float)
    // >>, <<
private:
    float re;
    float im;
};

float abs(const Complex &z) {
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
            inv = other.conj() / (denom_abs * denom_abs);
    return one * inv;
}

Complex operator/(float other, const Complex &one) {
    float denom_abs = abs(one);
    Complex
            inv = one.conj() / (denom_abs * denom_abs);
    return other * inv;
}

bool operator==(const Complex &one, const Complex &other) {
    return one.Re() == other.Re() && one.Im() == other.Im();
}

bool operator!=(const Complex &one, const Complex &other) {
    return one.Re() != other.Re() || one.Im() != other.Im();
}

std::ostream &operator<<(std::ostream &out, const Complex &z) {
    out << z.Re();
    if (z.Im() == 1) {
        out << " + i";
    } else if (z.Im() == -1) {
        out << " - i";
    } else if (z.Im() != 0) {
        out << z.Im() << "i";
    }
    return out;
}

std::istream &operator>>(std::istream &in, Complex &z) {
    in >> z.Re() >> z.Im();
    return in;
}