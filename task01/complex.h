#include <iostream>
#include <iostream>

class Complex
{
public:
    Complex();
    Complex(float re, float im = 0.0);
    Complex(const Complex &copy);
    ~Complex();

    float Re() const;

    float &Re();

    float Im() const;

    float &Im();

    float abs();
    Complex conj();

    Complex& operator=(const Complex &c);
    Complex& operator+=(const Complex &c);

    // overload this operators:
    // +, -, *(Complex), /(Complex), *(float)
    // >>, <<
private:
    float re;
    float im;
};

Complex operator+(const Complex &one, const Complex &other);

Complex operator+(const Complex &one, float other);

Complex operator+(float other, const Complex &one);

Complex operator-(const Complex &one, const Complex &other);

Complex operator-(const Complex &one, float other);

Complex operator-(float other, const Complex &one);

Complex operator*(const Complex &one, const Complex &other);

Complex operator*(const Complex &one, float other);

Complex operator*(float other, const Complex &one);

Complex operator/(const Complex &one, float other);

Complex operator/(const Complex &one, const Complex &other);

Complex operator/(float other, const Complex &one);

bool operator==(const Complex &one, const Complex &other);

bool operator!=(const Complex &one, const Complex &other);

std::ostream &operator<<(std::ostream &out, const Complex &z) {
    out << z.Re() << " " << z.Im() << "i";
    return out;
}

std::istream &operator>>(std::istream &in, Complex &z) {
    in >> z.Re() >> z.Im();
    return in;
}