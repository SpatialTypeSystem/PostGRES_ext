#include "Evaluate.h"
#include "PredicateEnum.h"

Evaluate::Evaluate() {}

Evaluate::~Evaluate() {}

// ------------ Validate -----------------

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, Predicate predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

// ------------ Determine -----------------

Predicate Evaluate::determine( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	enum VectorFlag {poi_shared, poi_disjoint};

	if ( featureVectorF[poi_disjoint] ) { // A0B-
		if ( featureVectorF[poi_shared] ) { // A0B0, moved right
			if ( featureVectorG[poi_disjoint] ) { // A-B0
				return Predicate::overlap; // 5
			} else {
				return Predicate::contains; // 4
			}
		} else {
			return Predicate::disjoint; // 1
		}
	} else { // A-B0, moved left
		if ( featureVectorG[poi_disjoint] ) { // vg[poi_disjoint]
			return Predicate::inside; // 3
		} else {
			return Predicate::equal; // 2
		}

	}
}

Predicate Evaluate::determine( Point2DImpl  &spatialObj_F, Line2DImpl &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

	if( featureVectorF[poi_on_interior] ) { // A0B0
		if( featureVectorF[poi_on_bound] ) { // A0&B (boundary B) 
			if( featureVectorF[poi_disjoint] ) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::overlap; // 14
				} else {
					return Predicate::overlap; //13
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::inside; // 12
				} else {
					return Predicate::inside; // 11
				}
			}
		} else {
			if (  featureVectorF[poi_disjoint]) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::overlap; // 9
				} else {
					return Predicate::overlap; // 10
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::inside; // 7
				} else {
					return Predicate::inside; // 8
				}
			}
		}
	} else {
		if( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_disjoint] ) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::meet; // 6
				} else {
					return Predicate::meet; // 5
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::meet; // 4
				} else {
					return Predicate::meet; // 3
				}
			}
		} else { // A-&B
			if ( featureVectorG[bound_poi_disjoint] ) {
				return Predicate::disjoint; // 2
			} else {
				return Predicate::disjoint; // 1
			}
		}
	}
}

Predicate Evaluate::determine( Point2DImpl  &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF)
{
	enum VectorFlag {poi_inside, poi_on_bound, poi_outside};
	
	if ( featureVectorF[poi_inside] ) { // A0B0
		if ( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_outside] ) { // A0B-
				return Predicate::overlap; // 7
			} else {
				return Predicate::inside; // 6
			}
		} else {
			if ( featureVectorF[poi_outside] ) { // A0B-
				return Predicate::inside; // 4
			} else {
				return Predicate::overlap; // 5
			}
		}
	} else {
		if ( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_outside] ) { //A0B-
				return Predicate::meet; // 3
			} else {
				return Predicate::meet; // 2
			}
		} else {
			return Predicate::disjoint; // 1
		}
	}
}

Predicate Evaluate::determine( Line2DImpl   &spatialObj_F, Line2DImpl &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

	if (featureVectorF[bound_shared])
	{
		if (featureVectorG[bound_on_interior])
		{
			if (featureVectorF[bound_on_interior])
			{
				if (featureVectorF[bound_disjoint])
				{
					if (featureVectorF[seg_unshared])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::equal;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::inside;
							}
							else
							{
								return Predicate::inside;
							}
						}
					}
					else
					{
						if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::disjoint;
							}
							else
							{
								return Predicate::disjoint;
							}
						}
						else
						{
							if (featureVectorG[seg_unshared])
							{
								return Predicate::contains;
							}
							else
							{
								if (featureVectorG[bound_disjoint])
								{
									return Predicate::overlap;
								}
								else
								{
									return Predicate::overlap;
								}
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::disjoint;
						}
						else
						{
							return Predicate::disjoint;
						}
					}
					else
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::contains;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
				}
			}
			else
			{
				if (featureVectorG[bound_disjoint])
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorF[seg_unshared])
						{
							return Predicate::inside;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorF[seg_unshared])
						{
							return Predicate::inside;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
				}
			}
		}
		else
		{
			if (featureVectorF[bound_disjoint])
			{
				if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
				}
				else
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::contains;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
				}
				else
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::contains;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
		}
	}
	else
	{
		if (featureVectorG[bound_on_interior])
		{
			if (featureVectorF[bound_on_interior])
			{
				if (featureVectorF[bound_disjoint])
				{
					if (featureVectorF[seg_unshared])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::equal;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::coveredBy;
							}
							else
							{
								return Predicate::coveredBy;
							}
						}
					}
					else
					{
						if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::meet;
							}
							else
							{
								return Predicate::meet;
							}
						}
						else
						{
							if (featureVectorG[seg_unshared])
							{
								return Predicate::covers;
							}
							else
							{
								if (featureVectorG[bound_disjoint])
								{
									return Predicate::overlap;
								}
								else
								{
									return Predicate::overlap;
								}
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::covers;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
				}
			}
			else
			{
				if (featureVectorG[bound_disjoint])
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorF[seg_unshared])
						{
							return Predicate::coveredBy;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorF[seg_unshared])
						{
							return Predicate::coveredBy;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
				}
			}
		}
		else
		{
			if (featureVectorF[bound_disjoint])
			{
				if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
				}
				else
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::covers;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
				}
				else
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::covers;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
		}
	}
}

Predicate Evaluate::determine( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	enum VectorFlag {seg_unshared, seg_inside, seg_shared, seg_outside, poi_shared, bound_inside, bound_shared, bound_disjoint};

	if (featureVectorF[bound_shared])
	{
		if (featureVectorF[bound_inside])
		{
			if (featureVectorF[seg_inside])
			{
				if (featureVectorF[bound_disjoint])
				{
					if (featureVectorF[seg_outside])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
					else
					{
						if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
						{
							return Predicate::disjoint;
						}
						else
						{
							if (featureVectorG[seg_unshared])
							{
								return Predicate::meet;
							}
							else
							{
								return Predicate::meet;
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
					{
						return Predicate::disjoint;
					}
					else
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::meet;
						}
						else
						{
							return Predicate::meet;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::inside;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
				else
				{
					if (featureVectorG[seg_unshared])
					{
						if (featureVectorF[seg_outside])
						{
							return Predicate::inside;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
					else
					{
						if (featureVectorF[seg_outside])
						{
							return Predicate::inside;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::overlap;
							}
							else
							{
								return Predicate::overlap;
							}
						}
					}
				}
			}
		}
		else
		{
			if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
			{
				if (featureVectorF[seg_outside])
				{
					return Predicate::inside;
				}
				else
				{
					if (featureVectorF[bound_disjoint])
					{
						return Predicate::overlap;
					}
					else
					{
						return Predicate::overlap;
					}
				}
			}
			else
			{
				if (featureVectorG[seg_unshared])
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::inside;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
				else
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::inside;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
		}
	}
	else
	{
		if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
		{
			if (featureVectorF[bound_inside])
			{
				if (featureVectorF[seg_inside])
				{
					if (featureVectorF[bound_disjoint])
					{
						return Predicate::meet;
					}
					else
					{
						return Predicate::meet;
					}
				}
				else
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::coveredBy;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[seg_outside])
				{
					return Predicate::coveredBy;
				}
				else
				{
					if (featureVectorF[bound_disjoint])
					{
						return Predicate::overlap;
					}
					else
					{
						return Predicate::overlap;
					}
				}
			}
		}
		else
		{
			if (featureVectorF[seg_inside])
			{
				if (featureVectorF[seg_outside])
				{
					return Predicate::meet;
				}
				else
				{
					if (featureVectorF[bound_disjoint])
					{
						return Predicate::meet;
					}
					else
					{
						return Predicate::meet;
					}
				}
			}
			else
			{
				if (featureVectorF[bound_inside])
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::coveredBy;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
				else
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::coveredBy;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
		}
	}
}

Predicate Evaluate::determine( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

	if (featureVectorG[one_two] || featureVectorG[two_one])
	{
		if (featureVectorF[zero_one] || featureVectorF[one_zero])
		{
			if (featureVectorF[zero_one] || featureVectorF[one_zero] || featureVectorF[one_one] || featureVectorG[one_two] || featureVectorG[two_one])
			{
				if (featureVectorF[one_two] || featureVectorF[two_one])
				{
					if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::equal;
					}
					else
					{
						return Predicate::coveredBy;
					}
				}
				else
				{
					if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
					{
						return Predicate::inside;
					}
					else
					{
						if (featureVectorG[zero_one] || featureVectorG[one_zero])
						{
							return Predicate::coveredBy;
						}
						else
						{
							return Predicate::coveredBy;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[one_two] || featureVectorF[two_one])
				{
					if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_two] || featureVectorF[two_one] || featureVectorG[one_two] || featureVectorG[two_one])
					{
						return Predicate::meet;
					}
					else
					{
						return Predicate::overlap;
					}
				}
				else
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::overlap;
					}
					else
					{
						return Predicate::overlap;
					}
				}
			}
		}
		else
		{
			if (featureVectorG[zero_one] || featureVectorG[one_zero])
			{
				if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_two] || featureVectorF[two_one] || featureVectorG[one_two] || featureVectorG[two_one])
				{
					return Predicate::meet;
				}
				else
				{
					if (featureVectorF[one_two] || featureVectorF[two_one])
					{
						if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
						{
							return Predicate::covers;
						}
						else
						{
							return Predicate::overlap;
						}
					}
					else
					{
						return Predicate::overlap;
					}
				}
			}
			else
			{
				if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_two] || featureVectorF[two_one] || featureVectorG[one_two] || featureVectorG[two_one])
				{
					if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
					{
						return Predicate::disjoint;
					}
					else
					{
						return Predicate::meet;
					}
				}
				else
				{
					if (featureVectorF[one_two] || featureVectorF[two_one])
					{
						return Predicate::overlap;
					}
					else
					{
						if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
		}
	}
	else
	{
		if (featureVectorF[one_two] || featureVectorF[two_one])
		{
			if (featureVectorF[zero_one] || featureVectorF[one_zero])
			{
				if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
				{
					return Predicate::covers;
				}
				else
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::overlap;
					}
					else
					{
						return Predicate::overlap;
					}
				}
			}
			else
			{
				if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
				{
					if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::contains;
					}
					else
					{
						return Predicate::overlap;
					}
				}
				else
				{
					if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::covers;
					}
					else
					{
						if (featureVectorG[zero_one] || featureVectorG[one_zero])
						{
							return Predicate::overlap;
						}
						else
						{
							return Predicate::overlap;
						}
					}
				}
			}
		}
		else
		{
			if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
			{
				if (featureVectorF[zero_one] || featureVectorF[one_zero])
				{
					return Predicate::overlap;
				}
				else
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::overlap;
					}
					else
					{
						return Predicate::overlap;
					}
				}
			}
			else
			{
				if (featureVectorF[zero_one] || featureVectorF[one_zero])
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::overlap;
					}
					else
					{
						return Predicate::overlap;
					}
				}
				else
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::overlap;
					}
					else
					{
						return Predicate::overlap;
					}
				}
			}
		}
	}
}
