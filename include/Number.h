#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <string>


class Number
{
public:
  // Constructors
  // Default number value is 0
  Number();

  // The string will be converted to a rational number
  Number(std::string number);

  // Destructor
  ~Number();

  // Override arithmetic operators
  Number& operator+(const Number& n) const;
  Number& operator+=(const Number& n);
  Number& operator-(const Number& n) const;
  Number& operator-=(const Number& n);
  Number& operator*(const Number& n) const;
  Number& operator*=(const Number& n);
  Number& operator/(const Number& n) const;
  Number& operator/=(const Number& n);
  Number& operator^(const int n) const;

  // Override comparison operators
  bool operator<(const Number& n) const;
  bool operator<=(const Number& n) const;
  bool operator>(const Number& n) const;
  bool operator>=(const Number& n) const;
  bool operator==(const Number& n) const;
  bool operator!=(const Number& n) const;

  Number& sqrt() const;

  // Overriding the output and input operator
  friend std::ostream& operator<<(std::ostream& os, const Number& n);
  friend std::istream& operator>>(std::istream& is, Number& n);

private:
  NumberImpl* p;
  struct NumberImpl;
};

#endif // NUMBER_H
