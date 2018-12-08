#include "iostream"
#include "sstream"

#include "Number.h"
#include "RGPHalfSegment2D.h"
#include "RGPOperations2D.h"
#include "RGPPoint2D.h"
#include "RGPSegment2D.h"

int main(void)
{
    Number n;
    Number a("5");
    std::cout << "All includes successfull!" << std::endl;
    return 0;
}

bool init_out()
{
    std::ostringstream out;
    Number a;
    out << a;
    return out.is_equal("0");
}

bool init_string()
{
    std::ostringstream out;
    Number a("500");
    out << a;
    return out.is_equal("500");
}

bool init_negative()
{
    std::ostringstream out;
    Number a("-400");
    out << a;
    return out.is_equal("-400");
}

bool init_to_string()
{
    Number a("500.7293203823820");
    return a.to_string(13) == "500.7293203823820";
}

bool to_string_truncate()
{
    Number a("500.7293203823820");
    return a.to_string(10) == "500.7293203823";
}

bool to_string_expand()
{
    Number a("500.7293203823820");
    return a.to_string(15) == "500.729320382382000";
}

bool init_negative_decimal()
{
    Number a("-4.87654");
    return a.to_string(5) == "-4.87654";
}

bool malformed_number()
{
    BOOST_CHECK_THROW(Number a("7 - 99"), std::invalid_argument);
    BOOST_CHECK_THROW(Number a("5/3"), std::invalid_argument);
    BOOST_CHECK_THROW(Number a("1.45e+14"), std::invalid_argument);
    BOOST_CHECK_THROW(Number a("500.729.789"), std::invalid_argument);
    BOOST_CHECK_THROW(Number a("500.729abc"), std::invalid_argument);
}

bool assignment()
{
    Number a("65.378");
    Number b;
    b = a;
    return b.to_string(3) == "65.378";
}

bool addition()
{
    Number a("678.56");
    Number b("0.678965");
    Number c;
    c = a + b;
    return c.to_string(6) == "679.238965";
}

bool add_assign()
{
    Number a("678.56");
    Number b("0.678965");
    a += b;
    return a.to_string(6) == "679.238965";
}

bool subtraction()
{
    Number a("678.56");
    Number b("0.678965");
    Number c;
    c = a - b;
    return c.to_string(6) == "677.881035";
}

bool sub_assign()
{
    Number a("678.56");
    Number b("0.678965");
    a -= b;
    return a.to_string(6) == "677.881035";
}

bool multiplication()
{
    Number a("78.563");
    Number b("25.87601");
    Number c;
    c = a * b;
    return c.to_string(8) == "2032.89697363";
}

bool mult_assign()
{
    Number a("78.563");
    Number b("25.87601");
    a *= b;
    return a.to_string(8) == "2032.89697363";
}

bool division()
{
    Number a("78.563");
    Number b("25.87601");
    Number c;
    c = a / b;
    return c.to_string(20) == "3.03613269588317518813";
}

bool div_assign()
{
    Number a("78.563");
    Number b("25.87601");
    a /= b;
    return a.to_string(20) == "3.03613269588317518813";
}

bool exponentiation()
{
    Number a("78.563");
    int b = 3;
    Number c;
    c = a ^ b;
    return c.to_string(4) == "484902.2251";
}

bool less_than()
{
    Number a("56.78");
    Number b("67.78");
    Number c("45.78");
    Number d("56.78");
    return a < b == true;
    return a < c == false;
    return a < d == false;
}

bool less_than_equal()
{
    Number a("56.78");
    Number b("67.78");
    Number c("45.78");
    Number d("56.78");
    return a <= b == true;
    return a <= c == false;
    return a <= d == true;
}

bool greater_than()
{
    Number a("56.78");
    Number b("67.78");
    Number c("45.78");
    Number d("56.78");
    return a > b == false;
    return a > c == true;
    return a > d == false;
}

bool greater_than_equal()
{
    Number a("56.78");
    Number b("67.78");
    Number c("45.78");
    Number d("56.78");
    return a >= b == false;
    return a >= c == true;
    return a >= d == true;
}

bool equal()
{
    Number a("56.78");
    Number b("67.78");
    Number c("56.78");
    return a == a == true;
    return a == b == false;
    return a == c == true;
}

bool not_equal()
{
    Number a("56.78");
    Number b("67.78");
    Number c("56.78");
    return a != a == false;
    return a != b == true;
    return a != c == false;
}

bool sqrt_approx()
{
    Number a("5");
    a = a.sqrt();
    double sqrt5 = 2.236068;
    double result = std::stod(a.to_string(6));
    BOOST_CHECK_CLOSE(result, sqrt5, 0.0001);
}

bool sqrt_digits()
{
    Number a("5");
    a = a.sqrt(98);
    std::string oeis_a002163 = "2.23606797749978969640917366873127623544"
                               "0618359611525724270897245410520925637804"
                               "89941441440837878227";
    return a.to_string(98) == oeis_a002163;
}

bool sqrt_digits_neg()
{
    Number a("-5");
    BOOST_CHECK_THROW(a.sqrt(2), std::runtime_error);
}

bool input_stream()
{
    Number a;
    std::stringstream ss;
    ss << "5.6789";
    ss >> a;
    return a.to_string(4) == "5.6789";
}

bool malformed_input()
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

bool halfsegment_isleft()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2);
    return hf1.isLeft() == true;
    return hf2.isLeft() == false;
}

bool halfsegment_equality()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p1);
    return hf1 == hf2;
}

bool halfsegment_notequal()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2);
    return hf1 != hf2;
}

bool halfsegment_lessthan()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)"), p3("(1,4)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2), hf3(s3, p3), hf4(s4, p3);
    return hf1 < hf2;
    return hf4 < hf3;
}

bool halfsegment_lessthanequals()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)"), p3("(1,4)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p1), hf3(s3, p3), hf4(s4, p3);
    return hf1 <= hf2;
    return hf4 <= hf3;
}

bool halfsegment_greaterthan()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2);
    return hf2 > hf1;
}

bool halfsegment_greaterthanequals()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)"), p3("(1,4)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p1), hf3(s3, p3), hf4(s4, p3);
    return hf2 >= hf1;
    return hf3 >= hf4;
}

bool halfsegment_point_equality()
{
    RGPSegment2D s1("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)");
    RGPHalfSegment2D hf1(s1, p1);
    return hf1 == p1;
}

bool halfsegment_point_notequal()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1);
    return hf1 != p2;
}

bool halfsegment_point_lessthan()
{
    RGPSegment2D s1("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1);
    return hf1 < p2;
}

bool halfsegment_point_lessthanequals()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1);
    return hf1 <= p2;
    return hf1 == p1;
}

bool halfsegment_point_greaterthan()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf2(s2, p2);
    return hf2 > p1;
}

bool halfsegment_point_greaterthanequals()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf2(s2, p2);
    return hf2 >= p1;
    return hf2 == p2;
}

bool annotated_halfsegment()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPAnnotatedHalfSegment2D hf2(s2, p2, true);
    return hf2 >= p1;
    return hf2 == p2;
}

bool operations_intersection_null()
{
    RGPSegment2D s1("(2,4),(3,2)"), s2("(1,9),(4,8)");
    optional<RGPPoint2D> intersectionPoint = RGPOperations2D::intersectionOf(s1, s2);
    return intersectionPoint.has_value() == false;
}

bool operations_intersection()
{
    RGPSegment2D s1("(2,4),(3,2)"), s2("(1,1),(4,3)");
    optional<RGPPoint2D> intersectionPoint = RGPOperations2D::intersectionOf(s1, s2);
    return intersectionPoint.has_value() == true;
    return intersectionPoint.value() == RGPPoint2D("(2.875,2.25)");
}

bool point_output()
{
    std::ostringstream out1, out2;
    Number x1("5"), y1("7"), x2("5"), y2("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2);
    out1 << point1;
    out2 << point2;
    return out1.is_equal("(5,7)");
    return out2.is_equal("(5,7)");
}

bool point_input()
{
    RGPPoint2D p;
    std::stringstream ss;
    ss << "(65,7)";
    ss >> p;
    return p.x == Number("65");
    return p.y == Number("7");
}

bool point_equality()
{
    Number x1("5"), y1("7"), x2("5"), y2("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2);
    return point1 == point2;
}

bool point_lessthan()
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("4"), y3("6");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    return point2 < point1;
    return point3 < point2;
}

bool point_greaterthan()
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("4"), y3("6");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    return point1 > point2;
    return point2 > point3;
}

bool point_lessthanequalto()
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("5"), y3("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    return point2 <= point1;
    return point3 <= point1;
}

bool point_greaterthanequalto()
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("5"), y3("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    return point1 >= point2;
    return point3 >= point1;
}

bool point_notequalto()
{
    Number x1("5"), y1("7"), x2("4"), y2("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2);
    return point2 != point1;
}

bool segment_output()
{
    RGPPoint2D p1(Number("3"), Number("5")), p2(Number("1"), Number("3"));
    RGPSegment2D s(p1, p2);
    std::ostringstream out;
    out << s;
    return out.is_equal("(1,3),(3,5)");
}

bool segment_input()
{
    RGPSegment2D s;
    std::stringstream ss;
    ss << "(65,7),(10,4)";
    ss >> s;
    return s.point1.x == Number("10");
    return s.point1.y == Number("4");
    return s.point2.x == Number("65");
    return s.point2.y == Number("7");
}

bool segment_contains()
{
    RGPSegment2D s("(0,0),(5,10)");
    return s.contains(RGPPoint2D("(3,6)")) == true;
}

bool segment_ispointabove()
{
    RGPSegment2D s("(0,1),(5,10)");
    return s.isPointAbove(RGPPoint2D("(6,7)")) == true;
    return s.isPointAbove(RGPPoint2D("(0,4)")) == false;
}

bool segment_ispointbelow()
{
    RGPSegment2D s("(0,1),(5,10)");
    return s.isPointBelow(RGPPoint2D("(6,7)")) == false;
    return s.isPointBelow(RGPPoint2D("(0,4)")) == true;
}

bool segment_ispointonsegment()
{
    RGPSegment2D s("(0,0),(5,10)");
    return s.isPointOnSegment(RGPPoint2D("(3,6)")) == true;
}

bool segment_equality()
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(2,3),(50,22)");
    return segment1 == segment2;
}

bool segment_notequals()
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(50,22)");
    return segment1 != segment2;
}

bool segment_lessthan()
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,2)");
    return segment2 < segment1;
}

bool segment_lessthanequals()
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,2)"), segment3(RGPPoint2D("(2,3)"), RGPPoint2D("(50,22)"));
    return segment2 <= segment1;
    return segment1 <= segment3;
}

bool segment_greaterthan()
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,4)");
    RGPSegment2D segment3("(2,3),(50,22)"), segment4("(1,3),(2,2)");
    return segment1 > segment2;
    return segment3 > segment4;
}

bool segment_greaterthanequals()
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,4)"), segment3(RGPPoint2D("(1,3)"), RGPPoint2D("(2,4)"));
    return segment1 >= segment2;
    return segment3 >= segment2;
}
