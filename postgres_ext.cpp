#include "cmath"
#include "iostream"
#include "sstream"

#include "include/Number.h"
#include "include/RGPHalfSegment2D.h"
#include "include/RGPOperations2D.h"
#include "include/RGPPoint2D.h"
#include "include/RGPSegment2D.h"

bool init_out()
{
    std::ostringstream out;
    Number a;
    out << a;
    return out.str() == "0";
}

bool init_string()
{
    std::ostringstream out;
    Number a("500");
    out << a;
    return out.str() == "500";
}

bool init_negative()
{
    std::ostringstream out;
    Number a("-400");
    out << a;
    return out.str() == "-400";
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

bool malformed_number1()
{
    try
    {
        Number a("7 - 99");
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool malformed_number2()
{
    try
    {
        Number a("5/3");
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool malformed_number3()
{
    try
    {
        Number a("1.45e+14");
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool malformed_number4()
{
    try
    {
        Number a("500.729.789");
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool malformed_number5()
{
    try
    {
        Number a("500.729abc");
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
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
    return std::abs(result - sqrt5) < 0.0000011;
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
    try
    {
        Number a("-5");
        a.sqrt(2);
    }
    catch (std::runtime_error)
    {
        return true;
    }
    return false;
}

bool input_stream()
{
    Number a;
    std::stringstream ss;
    ss << "5.6789";
    ss >> a;
    return a.to_string(4) == "5.6789";
}

bool malformed_input1()
{
    Number a;
    std::stringstream ss;
    ss << "7 - 99\n";

    try
    {
        ss >> a;
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool malformed_input2()
{
    Number a;
    std::stringstream ss;
    ss << "5/3\n";

    try
    {
        ss >> a;
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool malformed_input3()
{
    Number a;
    std::stringstream ss;
    ss << "1.45e+14\n ";

    try
    {
        ss >> a;
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool malformed_input4()
{
    Number a;
    std::stringstream ss;
    ss << "500.729.789\n";

    try
    {
        ss >> a;
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool malformed_input5()
{
    Number a;
    std::stringstream ss;
    ss << "500.729abc\n";

    try
    {
        ss >> a;
    }
    catch (std::invalid_argument)
    {
        return true;
    }
    return false;
}

bool halfsegment_isleft()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2);
    return hf2.isLeft() == false && hf1.isLeft() == true;
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
    return hf4 < hf3 && hf1 < hf2;
}

bool halfsegment_lessthanequals()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)"), p3("(1,4)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p1), hf3(s3, p3), hf4(s4, p3);
    return hf4 <= hf3 && hf1 <= hf2;
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
    return hf3 >= hf4 && hf2 >= hf1;
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
    return hf1 == p1 && hf1 <= p2;
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
    return hf2 == p2 && hf2 >= p1;
}

bool annotated_halfsegment()
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPAnnotatedHalfSegment2D hf2(s2, p2, true);
    return hf2 == p2 && hf2 >= p1;
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
    std::ostringstream out;
    out << *intersectionPoint;
    return intersectionPoint.has_value() == true && out.str().compare("(2.875,2.25)") == 0;
}

bool point_output()
{
    std::ostringstream out1, out2;
    Number x1("5"), y1("7"), x2("5"), y2("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2);
    out1 << point1;
    out2 << point2;
    return out1.str() == "(5,7)" && out2.str() == "(5,7)";
}

bool point_input()
{
    RGPPoint2D p;
    std::stringstream ss;
    ss << "(65,7)";
    ss >> p;
    return p.x == Number("65") && p.y == Number("7");
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
    return point2 < point1 && point3 < point2;
}

bool point_greaterthan()
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("4"), y3("6");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    return point1 > point2 && point2 > point3;
}

bool point_lessthanequalto()
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("5"), y3("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    return point2 <= point1 && point3 <= point1;
}

bool point_greaterthanequalto()
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("5"), y3("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    return point1 >= point2 && point3 >= point1;
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
    return out.str() == "(1,3),(3,5)";
}

bool segment_input()
{
    RGPSegment2D s;
    std::stringstream ss;
    ss << "(65,7),(10,4)";
    ss >> s;
    return s.point1.x == Number("10") && s.point1.y == Number("4") &&
           s.point2.x == Number("65") && s.point2.y == Number("7");
}

bool segment_contains()
{
    RGPSegment2D s("(0,0),(5,10)");
    return s.contains(RGPPoint2D("(3,6)")) == true;
}

bool segment_ispointabove()
{
    RGPSegment2D s("(0,1),(5,10)");
    return s.isPointAbove(RGPPoint2D("(6,7)")) == true && s.isPointAbove(RGPPoint2D("(0,4)")) == false;
}

bool segment_ispointbelow()
{
    RGPSegment2D s("(0,1),(5,10)");
    return s.isPointBelow(RGPPoint2D("(6,7)")) == false && s.isPointBelow(RGPPoint2D("(0,4)")) == true;
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
    return segment2 <= segment1 && segment1 <= segment3;
}

bool segment_greaterthan()
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,4)");
    RGPSegment2D segment3("(2,3),(50,22)"), segment4("(1,3),(2,2)");
    return segment1 > segment2 && segment3 > segment4;
}

bool segment_greaterthanequals()
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,4)"), segment3(RGPPoint2D("(1,3)"), RGPPoint2D("(2,4)"));
    return segment1 >= segment2 && segment3 >= segment2;
}

int main(void)
{
    bool result[73];
    int i, num_trues = 0, num_falses = 0;
    result[0] = init_out();
    result[1] = init_string();
    result[2] = init_negative();
    result[3] = init_to_string();
    result[4] = to_string_truncate();
    result[5] = to_string_expand();
    result[6] = init_negative_decimal();
    result[7] = malformed_number1();
    result[8] = malformed_number2();
    result[9] = malformed_number3();
    result[10] = malformed_number4();
    result[11] = malformed_number5();
    result[12] = assignment();
    result[13] = addition();
    result[14] = add_assign();
    result[15] = subtraction();
    result[16] = sub_assign();
    result[17] = multiplication();
    result[18] = mult_assign();
    result[19] = division();
    result[20] = div_assign();
    result[21] = exponentiation();
    result[22] = less_than();
    result[23] = less_than_equal();
    result[24] = greater_than();
    result[25] = greater_than_equal();
    result[26] = equal();
    result[27] = not_equal();
    result[28] = sqrt_approx();
    result[29] = sqrt_digits();
    result[30] = sqrt_digits_neg();
    result[31] = input_stream();
    result[32] = malformed_input1();
    result[33] = malformed_input2();
    result[34] = malformed_input3();
    result[35] = malformed_input4();
    result[36] = malformed_input5();
    result[37] = halfsegment_isleft();
    result[38] = halfsegment_equality();
    result[39] = halfsegment_notequal();
    result[40] = halfsegment_lessthan();
    result[41] = halfsegment_lessthanequals();
    result[42] = halfsegment_greaterthan();
    result[43] = halfsegment_greaterthanequals();
    result[44] = halfsegment_point_equality();
    result[45] = halfsegment_point_notequal();
    result[46] = halfsegment_point_lessthan();
    result[47] = halfsegment_point_lessthanequals();
    result[48] = halfsegment_point_greaterthan();
    result[49] = halfsegment_point_greaterthanequals();
    result[50] = annotated_halfsegment();
    result[51] = operations_intersection_null();
    result[52] = operations_intersection();
    result[53] = point_output();
    result[54] = point_input();
    result[55] = point_equality();
    result[56] = point_lessthan();
    result[57] = point_greaterthan();
    result[58] = point_lessthanequalto();
    result[59] = point_greaterthanequalto();
    result[60] = point_notequalto();
    result[61] = segment_output();
    result[62] = segment_input();
    result[63] = segment_contains();
    result[64] = segment_ispointabove();
    result[65] = segment_ispointbelow();
    result[66] = segment_ispointonsegment();
    result[67] = segment_equality();
    result[68] = segment_notequals();
    result[69] = segment_lessthan();
    result[70] = segment_lessthanequals();
    result[71] = segment_greaterthan();
    result[72] = segment_greaterthanequals();
    for (i = 0; i < 73; i++)
    {
        if (result[i])
        {
            num_trues++;
        }
        else
        {
            printf("Testcase %d failed!\n", i);
            num_falses++;
        }
    }
    printf("Number of Testcases passed: %d\n", num_trues);
    printf("Number of Testcases failed: %d\n", num_falses);
    return 0;
}
