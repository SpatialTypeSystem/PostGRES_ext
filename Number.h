#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <iostream>

/*
 * Interface for big rational numbers
 */
class Number {
    public:
        // Constructors
        // Default number value is 0
        Number();

        // The string will be converted to a rational number
        Number(std::string number);

        // Fraction of the form n/1
        Number(int n);

        // Fraction of the form n/d
        Number(int n, int d);

        // Destructor
        ~Number();

        // Override arithmetic operators
        Number& operator+ (const Number& n) const;
        Number& operator+= (const Number& n);
        Number& operator- (const Number& n) const;
        Number& operator-= (const Number& n);
        Number& operator* (const Number& n) const;
        Number& operator*= (const Number& n);
        Number& operator/ (const Number& n) const;
        Number& operator/= (const Number& n);
        Number& operator^ (const int n) const;

        // Override comparison operators
        bool operator< (const Number& n) const;
        bool operator<= (const Number& n) const;
        bool operator> (const Number& n) const;
        bool operator>= (const Number& n) const;
        bool operator== (const Number& n) const;

        Number& sqrt() const;

        // Overriding the output and input operator
        friend std::ostream& operator<<(std::ostream& os, const Number& n);
        friend std::istream& operator>>(std::istream& is, Number& n);
};

#endif //NUMBER_H
