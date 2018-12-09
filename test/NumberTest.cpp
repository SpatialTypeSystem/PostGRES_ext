#include "Number.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NumberTest
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(init_out)
{
    boost::test_tools::output_test_stream out;
    Number a;
    out << a;
    BOOST_REQUIRE(out.is_equal("0"));
}

BOOST_AUTO_TEST_CASE(init_string)
{
    boost::test_tools::output_test_stream out;
    Number a("500");
    out << a;
    BOOST_REQUIRE(out.is_equal("500"));
}

BOOST_AUTO_TEST_CASE(init_negative)
{
    boost::test_tools::output_test_stream out;
    Number a("-400");
    out << a;
    BOOST_REQUIRE(out.is_equal("-400"));
}

BOOST_AUTO_TEST_CASE(init_to_string)
{
    Number a("500.7293203823820");
    BOOST_REQUIRE(a.to_string(13) == "500.7293203823820");
}

BOOST_AUTO_TEST_CASE(to_string_truncate)
{
    Number a("500.7293203823820");
    BOOST_CHECK_EQUAL(a.to_string(10), "500.7293203823");
}

BOOST_AUTO_TEST_CASE(to_string_expand)
{
    Number a("500.7293203823820");
    BOOST_CHECK_EQUAL(a.to_string(15), "500.729320382382000");
}

BOOST_AUTO_TEST_CASE(init_negative_decimal)
{
    Number a("-4.87654");
    BOOST_CHECK_EQUAL(a.to_string(5), "-4.87654");
}

BOOST_AUTO_TEST_CASE(malformed_number)
{
    BOOST_CHECK_THROW(Number a("7 - 99"), std::invalid_argument);
    BOOST_CHECK_THROW(Number a("5/3"), std::invalid_argument);
    BOOST_CHECK_THROW(Number a("1.45e+14"), std::invalid_argument);
    BOOST_CHECK_THROW(Number a("500.729.789"), std::invalid_argument);
    BOOST_CHECK_THROW(Number a("500.729abc"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(assignment)
{
    Number a("65.378");
    Number b;
    b = a;
    BOOST_CHECK_EQUAL(b.to_string(3), "65.378");
}

BOOST_AUTO_TEST_CASE(addition)
{
    Number a("678.56");
    Number b("0.678965");
    Number c;
    c = a + b;
    BOOST_CHECK_EQUAL(c.to_string(6), "679.238965");
}

BOOST_AUTO_TEST_CASE(add_assign)
{
    Number a("678.56");
    Number b("0.678965");
    a += b;
    BOOST_CHECK_EQUAL(a.to_string(6), "679.238965");
}

BOOST_AUTO_TEST_CASE(subtraction)
{
    Number a("678.56");
    Number b("0.678965");
    Number c;
    c = a - b;
    BOOST_CHECK_EQUAL(c.to_string(6), "677.881035");
}

BOOST_AUTO_TEST_CASE(sub_assign)
{
    Number a("678.56");
    Number b("0.678965");
    a -= b;
    BOOST_CHECK_EQUAL(a.to_string(6), "677.881035");
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    Number a("78.563");
    Number b("25.87601");
    Number c;
    c = a * b;
    BOOST_CHECK_EQUAL(c.to_string(8), "2032.89697363");
}

BOOST_AUTO_TEST_CASE(mult_assign)
{
    Number a("78.563");
    Number b("25.87601");
    a *= b;
    BOOST_CHECK_EQUAL(a.to_string(8), "2032.89697363");
}

BOOST_AUTO_TEST_CASE(division)
{
    Number a("78.563");
    Number b("25.87601");
    Number c;
    c = a / b;
    BOOST_CHECK_EQUAL(c.to_string(20), "3.03613269588317518813");
}

BOOST_AUTO_TEST_CASE(div_assign)
{
    Number a("78.563");
    Number b("25.87601");
    a /= b;
    BOOST_CHECK_EQUAL(a.to_string(20), "3.03613269588317518813");
}

BOOST_AUTO_TEST_CASE(exponentiation)
{
    Number a("78.563");
    int b = 3;
    Number c;
    c = a ^ b;
    BOOST_CHECK_EQUAL(c.to_string(4), "484902.2251");
}

BOOST_AUTO_TEST_CASE(less_than)
{
    Number a("56.78");
    Number b("67.78");
    Number c("45.78");
    Number d("56.78");
    BOOST_CHECK_EQUAL(a < b, true);
    BOOST_CHECK_EQUAL(a < c, false);
    BOOST_CHECK_EQUAL(a < d, false);
}

BOOST_AUTO_TEST_CASE(less_than_equal)
{
    Number a("56.78");
    Number b("67.78");
    Number c("45.78");
    Number d("56.78");
    BOOST_CHECK_EQUAL(a <= b, true);
    BOOST_CHECK_EQUAL(a <= c, false);
    BOOST_CHECK_EQUAL(a <= d, true);
}

BOOST_AUTO_TEST_CASE(greater_than)
{
    Number a("56.78");
    Number b("67.78");
    Number c("45.78");
    Number d("56.78");
    BOOST_CHECK_EQUAL(a > b, false);
    BOOST_CHECK_EQUAL(a > c, true);
    BOOST_CHECK_EQUAL(a > d, false);
}

BOOST_AUTO_TEST_CASE(greater_than_equal)
{
    Number a("56.78");
    Number b("67.78");
    Number c("45.78");
    Number d("56.78");
    BOOST_CHECK_EQUAL(a >= b, false);
    BOOST_CHECK_EQUAL(a >= c, true);
    BOOST_CHECK_EQUAL(a >= d, true);
}

BOOST_AUTO_TEST_CASE(equal)
{
    Number a("56.78");
    Number b("67.78");
    Number c("56.78");
    BOOST_CHECK_EQUAL(a == a, true);
    BOOST_CHECK_EQUAL(a == b, false);
    BOOST_CHECK_EQUAL(a == c, true);
}

BOOST_AUTO_TEST_CASE(not_equal)
{
    Number a("56.78");
    Number b("67.78");
    Number c("56.78");
    BOOST_CHECK_EQUAL(a != a, false);
    BOOST_CHECK_EQUAL(a != b, true);
    BOOST_CHECK_EQUAL(a != c, false);
}

BOOST_AUTO_TEST_CASE(sqrt_approx)
{
    Number a("5");
    a = a.sqrt();
    double sqrt5 = 2.236068;
    double result = std::stod(a.to_string(6));
    BOOST_CHECK_CLOSE(result, sqrt5, 0.0001);
}

BOOST_AUTO_TEST_CASE(sqrt_digits)
{
    Number a("5");
    a = a.sqrt(98);
    std::string oeis_a002163 = "2.23606797749978969640917366873127623544"
                               "0618359611525724270897245410520925637804"
                               "89941441440837878227";
    BOOST_CHECK_EQUAL(a.to_string(98), oeis_a002163);
}

BOOST_AUTO_TEST_CASE(sqrt_digits_neg)
{
    Number a("-5");
    BOOST_CHECK_THROW(a.sqrt(2), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(input_stream)
{
    Number a;
    std::stringstream ss;
    ss << "5.6789";
    ss >> a;
    BOOST_CHECK_EQUAL(a.to_string(4), "5.6789");
}

BOOST_AUTO_TEST_CASE(malformed_input)
{
    Number a;
    std::stringstream ss;
    ss << "7 - 99\n";
    BOOST_CHECK_THROW(ss >> a, std::invalid_argument);
    ss << "5/3\n";
    BOOST_CHECK_THROW(ss >> a, std::invalid_argument);
    ss << "1.45e+14\n ";
    BOOST_CHECK_THROW(ss >> a, std::invalid_argument);
    ss << "500.729.789\n";
    BOOST_CHECK_THROW(ss >> a, std::invalid_argument);
    ss << "500.729abc\n";
    BOOST_CHECK_THROW(ss >> a, std::invalid_argument);
}