#include "Relationship.h"

#include <iostream>
#include <vector>
#include <string>

void printResultMessage( std::string testname, bool result) {
	std::cout << std::boolalpha;
	std::cout << testname << result;
}

void point_disjoint_false()
{
	// Check if we lines are disjoint
	bool result = disjoint(Point2D("((1,2),(2,3))"), Point2D("((1,2),(2,3))") );
	printResultMessage("point_disjoint_false", result == false);
}

void point_disjoint_true()
{
	// Check if we lines are disjoint
	bool result = disjoint(Point2D("((1,2),(2,3))"), Point2D("((2,2),(3,3))"));
	printResultMessage("point_disjoint_false", result == true);
}

void regions_overlap_true()
{
	// Check if 2 regions overlap
	bool result = disjoint( Region2D("[WCR((2 2,2 4,4 4,4 2,2 2))]"), Region2D("[WCR((1 1,1 3,3 3,3 1,1 1))]") );
	printResultMessage("region_covers", result == true);
}

void line_equal_true()
{
	bool result = equal( Line2D("( (3,4),(2,2) )"), Line2D("( (3,4),(2,2) )"));
	printResultMessage("region_covers", result == true);
}

void line_equal_false()
{
	bool result = equal( Line2D("( (3,4),(2,2) )"), Line2D("( (4,5),(2,2) )"));
	printResultMessage("region_covers", result == false);
}

void region_covers_true()
{
	// Check if 2 regions cover
	bool result = covers( Region2D("[WCR((0 0,0 6,6 6,6 0,0 0))]"), Region2D("[WCR((1 1,1 2,2 2,2 1,1 1))]") );
	printResultMessage("region_covers", result == true);
}

void region_covers_false()
{
	// Check if 2 regions cover
	bool result = covers( Region2D("[WCR((1 1,1 2,2 2,2 1,1 1))]"), Region2D("[WCR((0 0,0 6,6 6,6 0,0 0))]") );
	printResultMessage("region_covers", result == false);
}

void determine_overlap_true()
{
	PREDICATE result = determine( Region2D("[WCR((2 2,2 4,4 4,4 2,2 2))]"), Region2D("[WCR((1 1,1 3,3 3,3 1,1 1))]") );
	printResultMessage("region_covers", PREDICATE.determine == result);
}