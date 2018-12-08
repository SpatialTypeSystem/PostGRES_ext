#include "RGPSegment2D.h"
#include "Number.h"
#include "RGPPoint2D.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RGPSegment2DTest
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(segment_output)
{
    RGPPoint2D p1(Number("3"), Number("5")), p2(Number("1"), Number("3"));
    RGPSegment2D s(p1, p2);
    boost::test_tools::output_test_stream out;
    out << s;
    BOOST_REQUIRE(out.is_equal("(1,3),(3,5)"));
}

BOOST_AUTO_TEST_CASE(segment_input)
{
    RGPSegment2D s;
    std::stringstream ss;
    ss << "(65,7),(10,4)";
    ss >> s;
    BOOST_REQUIRE(s.point1.x == Number("10"));
    BOOST_REQUIRE(s.point1.y == Number("4"));
    BOOST_REQUIRE(s.point2.x == Number("65"));
    BOOST_REQUIRE(s.point2.y == Number("7"));
}

BOOST_AUTO_TEST_CASE(segment_contains)
{
    RGPSegment2D s("(0,0),(5,10)");
    BOOST_REQUIRE(s.contains(RGPPoint2D("(3,6)")) == true);
}

BOOST_AUTO_TEST_CASE(segment_ispointabove)
{
    RGPSegment2D s("(0,1),(5,10)");
    BOOST_REQUIRE(s.isPointAbove(RGPPoint2D("(6,7)")) == true);
    BOOST_REQUIRE(s.isPointAbove(RGPPoint2D("(0,4)")) == false);
}

BOOST_AUTO_TEST_CASE(segment_ispointbelow)
{
    RGPSegment2D s("(0,1),(5,10)");
    BOOST_REQUIRE(s.isPointBelow(RGPPoint2D("(6,7)")) == false);
    BOOST_REQUIRE(s.isPointBelow(RGPPoint2D("(0,4)")) == true);
}

BOOST_AUTO_TEST_CASE(segment_ispointonsegment)
{
    RGPSegment2D s("(0,0),(5,10)");
    BOOST_REQUIRE(s.isPointOnSegment(RGPPoint2D("(3,6)")) == true);
}

BOOST_AUTO_TEST_CASE(segment_equality)
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(2,3),(50,22)");
    BOOST_REQUIRE(segment1 == segment2);
}

BOOST_AUTO_TEST_CASE(segment_notequals)
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(50,22)");
    BOOST_REQUIRE(segment1 != segment2);
}

BOOST_AUTO_TEST_CASE(segment_lessthan)
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,2)");
    BOOST_REQUIRE(segment2 < segment1);
}

BOOST_AUTO_TEST_CASE(segment_lessthanequals)
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,2)"), segment3(RGPPoint2D("(2,3)"), RGPPoint2D("(50,22)"));
    BOOST_REQUIRE(segment2 <= segment1);
    BOOST_REQUIRE(segment1 <= segment3);
}

BOOST_AUTO_TEST_CASE(segment_greaterthan)
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,4)");
    RGPSegment2D segment3("(2,3),(50,22)"), segment4("(1,3),(2,2)");
    BOOST_REQUIRE(segment1 > segment2);
    BOOST_REQUIRE(segment3 > segment4);
}

BOOST_AUTO_TEST_CASE(segment_greaterthanequals)
{
    RGPSegment2D segment1("(2,3),(50,22)"), segment2("(1,3),(2,4)"), segment3(RGPPoint2D("(1,3)"), RGPPoint2D("(2,4)"));
    BOOST_REQUIRE(segment1 >= segment2);
    BOOST_REQUIRE(segment3 >= segment2);
}
