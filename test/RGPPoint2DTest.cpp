#include "RGPPoint2D.h"
#include "Number.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RGPPoint2DTest
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(point_output)
{
    boost::test_tools::output_test_stream out1, out2;
    Number x1("5"), y1("7"), x2("5"), y2("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2);
    out1 << point1;
    out2 << point2;
    BOOST_REQUIRE(out1.is_equal("(5,7)"));
    BOOST_REQUIRE(out2.is_equal("(5,7)"));
}

BOOST_AUTO_TEST_CASE(point_input)
{
    RGPPoint2D p;
    std::stringstream ss;
    ss << "(65,7)";
    ss >> p;
    BOOST_REQUIRE(p.x == Number("65"));
    BOOST_REQUIRE(p.y == Number("7"));
}

BOOST_AUTO_TEST_CASE(point_equality)
{
    Number x1("5"), y1("7"), x2("5"), y2("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2);
    BOOST_REQUIRE(point1 == point2);
}

BOOST_AUTO_TEST_CASE(point_lessthan)
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("4"), y3("6");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    BOOST_REQUIRE(point2 < point1);
    BOOST_REQUIRE(point3 < point2);
}

BOOST_AUTO_TEST_CASE(point_greaterthan)
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("4"), y3("6");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    BOOST_REQUIRE(point1 > point2);
    BOOST_REQUIRE(point2 > point3);
}

BOOST_AUTO_TEST_CASE(point_lessthanequalto)
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("5"), y3("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    BOOST_REQUIRE(point2 <= point1);
    BOOST_REQUIRE(point3 <= point1);
}

BOOST_AUTO_TEST_CASE(point_greaterthanequalto)
{
    Number x1("5"), y1("7"), x2("4"), y2("7"), x3("5"), y3("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2), point3(x3, y3);
    BOOST_REQUIRE(point1 >= point2);
    BOOST_REQUIRE(point3 >= point1);
}

BOOST_AUTO_TEST_CASE(point_notequalto)
{
    Number x1("5"), y1("7"), x2("4"), y2("7");
    RGPPoint2D point1(x1, y1), point2(x2, y2);
    BOOST_REQUIRE(point2 != point1);
}