#include "Number.h"

// Constructors
// Default number value is 0
Number::Number() {}

// The string will be converted to a rational number
Number::Number(std::string number) {}

// Fraction of the form n/1
Number::Number(int n) {}

// Fraction of the form n/d
Number::Number(int n, int d) {}

// Destructor
Number::~Number() {}


// Override arithmetic operators
Number& Number::operator+ (const Number& n) const {}
Number& Number::operator+= (const Number& n) {}
Number& Number::operator- (const Number& n) const {}
Number& Number::operator-= (const Number& n) {}
Number& Number::operator* (const Number& n) const {}
Number& Number::operator*= (const Number& n) {}
Number& Number::operator/ (const Number& n) const {}
Number& Number::operator/= (const Number& n) {}
Number& Number::operator^ (const int n) const {}

// Override comparison operators
bool Number::operator< (const Number& n) const {}
bool Number::operator<= (const Number& n) const {}
bool Number::operator> (const Number& n) const {}
bool Number::operator>= (const Number& n) const {}
bool Number::operator== (const Number& n) const {}

Number& Number::sqrt() const {}

// Overriding the output and input operator
std::ostream& Number::operator<<(std::ostream& os, const Number& n) {}
std::istream& Number::operator>>(std::istream& is, Number& n) {}
