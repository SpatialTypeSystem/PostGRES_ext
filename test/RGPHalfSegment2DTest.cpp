#include "RGPHalfSegment2D.h"
#include "Number.h"
#include "RGPPoint2D.h"
#include "RGPSegment2D.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RGPSegment2DTest
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(halfsegment_isleft)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2);
    BOOST_REQUIRE(hf1.isLeft() == true);
    BOOST_REQUIRE(hf2.isLeft() == false);
}

BOOST_AUTO_TEST_CASE(halfsegment_equality)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p1);
    BOOST_REQUIRE(hf1 == hf2);
}

BOOST_AUTO_TEST_CASE(halfsegment_notequal)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2);
    BOOST_REQUIRE(hf1 != hf2);
}

BOOST_AUTO_TEST_CASE(halfsegment_lessthan)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)"), p3("(1,4)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2), hf3(s3, p3), hf4(s4, p3);
    BOOST_REQUIRE(hf1 < hf2);
    BOOST_REQUIRE(hf4 < hf3);
}

BOOST_AUTO_TEST_CASE(halfsegment_lessthanequals)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)"), p3("(1,4)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p1), hf3(s3, p3), hf4(s4, p3);
    BOOST_REQUIRE(hf1 <= hf2);
    BOOST_REQUIRE(hf4 <= hf3);
}

BOOST_AUTO_TEST_CASE(halfsegment_greaterthan)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p2);
    BOOST_REQUIRE(hf2 > hf1);
}

BOOST_AUTO_TEST_CASE(halfsegment_greaterthanequals)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)"), p3("(1,4)");
    RGPHalfSegment2D hf1(s1, p1), hf2(s2, p1), hf3(s3, p3), hf4(s4, p3);
    BOOST_REQUIRE(hf2 >= hf1);
    BOOST_REQUIRE(hf3 >= hf4);
}

BOOST_AUTO_TEST_CASE(halfsegment_point_equality)
{
    RGPSegment2D s1("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)");
    RGPHalfSegment2D hf1(s1, p1);
    BOOST_REQUIRE(hf1 == p1);
}

BOOST_AUTO_TEST_CASE(halfsegment_point_notequal)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1);
    BOOST_REQUIRE(hf1 != p2);
}

BOOST_AUTO_TEST_CASE(halfsegment_point_lessthan)
{
    RGPSegment2D s1("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1);
    BOOST_REQUIRE(hf1 < p2);
}

BOOST_AUTO_TEST_CASE(halfsegment_point_lessthanequals)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)"), s3("(1,4),(1,10)"), s4("(1,4),(2,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf1(s1, p1);
    BOOST_REQUIRE(hf1 <= p2);
    BOOST_REQUIRE(hf1 == p1);
}

BOOST_AUTO_TEST_CASE(halfsegment_point_greaterthan)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf2(s2, p2);
    BOOST_REQUIRE(hf2 > p1);
}

BOOST_AUTO_TEST_CASE(halfsegment_point_greaterthanequals)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPHalfSegment2D hf2(s2, p2);
    BOOST_REQUIRE(hf2 >= p1);
    BOOST_REQUIRE(hf2 == p2);
}

BOOST_AUTO_TEST_CASE(annotated_halfsegment)
{
    RGPSegment2D s1("(1,5),(4,3)"), s2("(1,5),(4,3)");
    RGPPoint2D p1("(1,5)"), p2("(4,3)");
    RGPAnnotatedHalfSegment2D hf2(s2, p2, true);
    BOOST_REQUIRE(hf2 >= p1);
    BOOST_REQUIRE(hf2 == p2);
}