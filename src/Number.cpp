#include "../include/Number.h"
#include <gmpxx.h>
#include <memory>
#include <regex>

struct Number::NumberImpl
{
  mpq_class num;
};

// Constructors
// Default number value is 0
Number::Number()
{
  p = new NumberImpl;
  mpq_class temp;
  p->num = temp;
}

// Copy constructor
Number::Number(const Number &n)
{
  p = new NumberImpl;
  p->num = n.p->num;
}

// The string will be converted to a rational number
Number::Number(std::string number)
{
  std::string denom = "/1";
  std::regex decimal("^-?[0-9]+(\\.[0-9]+)?$");

  if (!std::regex_match(number, decimal))
  {
    throw std::invalid_argument("Argument should be a decimal number!");
  }

  size_t dec_point_pos = number.find('.');
  if (dec_point_pos != std::string::npos)
  {
    denom.append(number.length() - dec_point_pos - 1, '0');
    number.replace(dec_point_pos, 1, "");
  }

  p = new NumberImpl;
  mpq_class temp(number + denom, 10);
  p->num = temp;
}

// Destructor
Number::~Number()
{
  delete p;
}

// Override arithmetic operators
Number Number::operator=(const Number &n)
{
  p->num = n.p->num;
  return *this;
}

Number Number::operator+(const Number &n) const
{
  Number ret;
  ret.p->num = p->num + n.p->num;
  return ret;
}

Number Number::operator+=(const Number &n)
{
  p->num = p->num + n.p->num;
  return *this;
}

Number Number::operator-(const Number &n) const
{
  Number ret;
  ret.p->num = p->num - n.p->num;
  return ret;
}

Number Number::operator-=(const Number &n)
{
  p->num = p->num - n.p->num;
  return *this;
}

Number Number::operator*(const Number &n) const
{
  Number ret;
  ret.p->num = p->num * n.p->num;
  return ret;
}

Number Number::operator*=(const Number &n)
{
  p->num = p->num *= n.p->num;
  return *this;
}

Number Number::operator/(const Number &n) const
{
  Number ret;
  ret.p->num = p->num / n.p->num;
  return ret;
}

Number Number::operator/=(const Number &n)
{
  p->num = p->num /= n.p->num;
  return *this;
}

Number Number::operator^(const int n) const
{
  Number ret;
  mpz_pow_ui(ret.p->num.get_num_mpz_t(), p->num.get_num_mpz_t(),
             (unsigned long)n);
  mpz_pow_ui(ret.p->num.get_den_mpz_t(), p->num.get_den_mpz_t(),
             (unsigned long)n);
  ret.p->num.canonicalize();
  return ret;
}

// Override comparison operators
bool Number::operator<(const Number &n) const
{
  return p->num < n.p->num;
}

bool Number::operator<=(const Number &n) const
{
  return p->num <= n.p->num;
}

bool Number::operator>(const Number &n) const
{
  return p->num > n.p->num;
}

bool Number::operator>=(const Number &n) const
{
  return p->num >= n.p->num;
}

bool Number::operator==(const Number &n) const
{
  return p->num == n.p->num;
}

bool Number::operator!=(const Number &n) const
{
  return p->num != n.p->num;
}

Number Number::sqrt() const
{
  Number ret;
  mpf_class float_num(p->num);
  mpf_sqrt(float_num.get_mpf_t(), float_num.get_mpf_t());
  ret.p->num = mpq_class(float_num);
  return ret;
}

Number Number::sqrt(size_t digits) const
{
  std::string quotient = to_string(digits * 2);
  if (quotient[0] == '-')
  {
    throw std::runtime_error("Square root of a negative number is not supported!");
  }

  std::string full_divisor(quotient);
  size_t quot_int_len = quotient.find('.');
  full_divisor.replace(quot_int_len, 1, "");

  if (quot_int_len == std::string::npos)
  {
    quot_int_len = quotient.length();
  }

  mpz_class curr_divisor;
  std::string curr_dividend;
  std::string square_root;
  if (quot_int_len % 2 != 0)
  {
    full_divisor = '0' + full_divisor;
    quot_int_len++;
  }

  for (int i = 0; i < digits + quot_int_len / 2; i++)
  {
    curr_dividend += full_divisor.substr(i * 2, 2);
    for (int j = 0; j < 10; j++)
    {
      mpz_class curr_dividend_mpz(curr_dividend);
      mpz_class temp_divisor = curr_divisor * 10 + j + 1;
      if (temp_divisor * (j + 1) > curr_dividend_mpz)
      {
        curr_dividend_mpz -= (curr_divisor * 10 + j) * j;
        curr_divisor = curr_divisor * 10 + 2 * j;
        curr_dividend = curr_dividend_mpz.get_str();
        square_root += std::to_string(j);
        break;
      }
    }
  }

  square_root.insert(quot_int_len / 2, ".");
  Number ret(square_root);
  return ret;
}

std::string Number::to_string(size_t digits) const
{
  mpz_class den_mpz = p->num.get_den();
  std::string num = p->num.get_num().get_str();
  std::string den = p->num.get_den().get_str();
  bool is_negative = num[0] == '-';
  if (is_negative)
  {
    num.erase(0, 1);
  }

  size_t num_int_len = num.find('.');
  if (num_int_len == std::string::npos)
  {
    num_int_len = num.length();
  }

  std::string curr_div;
  std::string quotient;
  for (int i = 0; i < num_int_len; i++)
  {
    curr_div += num.at(i);
    mpz_class curr_div_mpz(curr_div);
    if (curr_div_mpz > den_mpz)
    {
      mpz_class quotient_digit = curr_div_mpz / den_mpz;
      mpz_class remainder = curr_div_mpz % den_mpz;
      quotient += quotient_digit.get_str();
      curr_div = remainder.get_str();
    }
    else
    {
      quotient += '0';
    }
  }

  quotient += '.';

  while (digits > 0)
  {
    curr_div += '0';
    mpz_class curr_div_mpz(curr_div);
    if (curr_div_mpz > den_mpz)
    {
      mpz_class quotient_digit = curr_div_mpz / den_mpz;
      mpz_class remainder = curr_div_mpz % den_mpz;
      quotient += quotient_digit.get_str();
      curr_div = remainder.get_str();
    }
    else
    {
      quotient += '0';
    }
    digits--;
  }

  size_t non_zero_idx = quotient.find_first_not_of('0');
  if (quotient[non_zero_idx] == '.')
  {
    non_zero_idx--;
  }

  quotient.erase(0, non_zero_idx);

  if (is_negative)
  {
    quotient.insert(0, 1, '-');
  }

  return quotient;
}

// Overriding the output and input operator
std::ostream &operator<<(std::ostream &os, const Number &n)
{
  os << n.p->num.get_d();
  return os;
}
std::istream &operator>>(std::istream &is, Number &n)
{
  std::string input;
  getline(is, input);
  Number temp(input);
  n.p->num = temp.p->num;
  return is;
}
