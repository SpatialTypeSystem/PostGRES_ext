#include "Relationship.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SpatialPredicateTests
#include <boost/test/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

BOOST_AUTO_TEST_CASE(lines_disjoint)
{
	// Check if we lines are disjoint
	bool result = disjoint(  );
	BOOST_REQUIRE( result, false);
}

BOOST_AUTO_TEST_CASE(regions_overlap)
{
	// Check if 2 regions overlap
	bool result = disjoint(  );
	BOOST_REQUIRE( result, true);
}

BOOST_AUTO_TEST_CASE(line_equal)
{
	// Check if 2 lines equal
	bool result = equal(  );
	BOOST_REQUIRE( result, true);
}

BOOST_AUTO_TEST_CASE(region_covers)
{
	// Check if 2 regions cover
	bool result = covers(  );
	BOOST_REQUIRE( result, false);
}