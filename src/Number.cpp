#include "../include/Number.h"
#include "gmpxx.h"

struct Number::NumberImpl {
mpq_class num;
};

// Constructors
// Default number value is 0
Number::Number() {
    p = new NumberImpl;
    mpq_class temp;
    p->num = temp;
}

// The string will be converted to a rational number
Number::Number(std::string number) {
    p = new NumberImpl;
    mpq_class temp(number, 10);
    p->num = temp;
}

// Destructor
Number::~Number() {
    delete p;
}

// Override arithmetic operators
Number &Number::operator=(const Number &n) {
    p->num = n.p->num;
    return *this;
}

Number &Number::operator+(const Number &n) const {
    Number *ret = new Number();
    ret->p->num = p->num + n.p->num;
    return *ret;
}

Number &Number::operator+=(const Number &n) {
    p->num = p->num + n.p->num;
    return *this;
}

Number &Number::operator-(const Number &n) const {
    Number *ret = new Number();
    ret->p->num = p->num - n.p->num;
    return *ret;
}

Number &Number::operator-=(const Number &n) {
    p->num = p->num - n.p->num;
    return *this;
}

Number &Number::operator*(const Number &n) const {
    Number *ret = new Number();
    ret->p->num = p->num * n.p->num;
    return *ret;
}

Number &Number::operator*=(const Number &n) {
    p->num = p->num *= n.p->num;
    return *this;
}

Number &Number::operator/(const Number &n) const {
    Number *ret = new Number();
    ret->p->num = p->num / n.p->num;
    return *ret;
}

Number &Number::operator/=(const Number &n) {
    p->num = p->num /= n.p->num;
    return *this;
}

Number &Number::operator^(const int n) const {
    Number *ret = new Number();
    mpz_pow_ui(ret->p->num.get_num_mpz_t(), p->num.get_num_mpz_t(), (unsigned long) n);
    mpz_pow_ui(ret->p->num.get_den_mpz_t(), p->num.get_den_mpz_t(), (unsigned long) n);
    ret->p->num.canonicalize();
    return *ret;
}

// Override comparison operators
bool Number::operator<(const Number &n) const {
    return p->num < n.p->num;
}

bool Number::operator<=(const Number &n) const {
    return p->num <= n.p->num;
}

bool Number::operator>(const Number &n) const {
    return p->num > n.p->num;
}

bool Number::operator>=(const Number &n) const {
    return p->num >= n.p->num;
}

bool Number::operator==(const Number &n) const {
    return p->num == n.p->num;
}

bool Number::operator!=(const Number &n) const {
    return p->num != n.p->num;
}

Number &Number::sqrt() const {
    // TODO: Temporary implementation, limited precision
    Number *ret = new Number();
    mpf_class float_num(p->num);
    mpf_sqrt(float_num.get_mpf_t(), float_num.get_mpf_t());
    ret->p->num = mpq_class(float_num);
    return *ret;
}

// Overriding the output and input operator
std::ostream &operator<<(std::ostream &os, const Number &n) {
    // TODO: Support arbitrary precision
    os << n.p->num.get_d();
    return os;
}
std::istream &operator>>(std::istream &is, Number &n) {
    is >> n.p->num;
    return is;
}
