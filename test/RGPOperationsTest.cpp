#include "Number.h"
#include "RGPHalfSegment2D.h"
#include "RGPOperations2D.h"
#include "RGPPoint2D.h"
#include "RGPSegment2D.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RGPSegment2DTest
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(operations_intersection_null)
{
    RGPSegment2D s1("(2,4),(3,2)"), s2("(1,9),(4,8)");
    optional<RGPPoint2D> intersectionPoint = RGPOperations2D::intersectionOf(s1, s2);
    BOOST_REQUIRE(intersectionPoint.has_value() == false);
}

BOOST_AUTO_TEST_CASE(operations_intersection)
{
    RGPSegment2D s1("(2,4),(3,2)"), s2("(1,1),(4,3)");
    optional<RGPPoint2D> intersectionPoint = RGPOperations2D::intersectionOf(s1, s2);
    BOOST_REQUIRE(intersectionPoint.has_value() == true);
    boost::test_tools::output_test_stream out;
    out << *intersectionPoint;
    BOOST_REQUIRE(out.is_equal("(2.875,2.25)"));
}