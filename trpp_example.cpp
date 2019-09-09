/*! \file trpp_example.cpp
	\brief example usage of the Triangle++ wrapper
 */

#include "tpp_interface.h"
#include <vector>

using namespace tpp;

// ---
int main()
{
	// prepare input
	std::vector<Delaunay::Point> delaunayInput;

	delaunayInput.push_back(Delaunay::Point(0, 0));
	delaunayInput.push_back(Delaunay::Point(1, 1));
	delaunayInput.push_back(Delaunay::Point(0, 2));
	delaunayInput.push_back(Delaunay::Point(3, 2));


	// 1. standard triangulation
	Delaunay trGenerator(delaunayInput);
	trGenerator.Triangulate();

	// iterate over triangles
	for (Delaunay::fIterator fit = trGenerator.fbegin(); fit != trGenerator.fend(); ++fit)
	{
		int keypointIdx1 = trGenerator.Org(fit);
		int keypointIdx2 = trGenerator.Dest(fit);
		int keypointIdx3 = trGenerator.Apex(fit);

		// access data
		double x1 = delaunayInput[keypointIdx1][0];
		double y1 = delaunayInput[keypointIdx1][1];
	}


	// 2. triangulate with constraint (default = 20�)	
	bool minAngleConstraint = true;
	trGenerator.Triangulate(minAngleConstraint);

	// iterate over triangles
	for (Delaunay::fIterator fit = trGenerator.fbegin(); fit != trGenerator.fend(); ++fit)
	{
		Delaunay::Point p1;
		Delaunay::Point p2;
		Delaunay::Point p3;

		int keypointIdx1 = trGenerator.Org(fit, &p1);
		int keypointIdx2 = trGenerator.Dest(fit, &p2);
		int keypointIdx3 = trGenerator.Apex(fit, &p3);

		// new vertices might have been added to enforce constraints!
		if (keypointIdx1 == -1)
		{
			double x1 = p1[0]; // an added vertex, it's data copied to p1
			double y1 = p1[1];
		}
		else
		{
			// point from original data
			double x1 = delaunayInput[keypointIdx1][0];
			double y1 = delaunayInput[keypointIdx1][1];

			// but that will work too!
			x1 = p1[0];
			x1 = p1[1];
		}
	}
	std::cout << "mesh has" << trGenerator.nvertices() << " vertices." << std::endl;
	trGenerator.WriteToObj("x.obj");

	// cardioid
	std::vector<Delaunay::Point> cardioidPoints;

	// mesh a cardioid boundary loop
	for (double t = 0; t < 2 * 3.1415926; t += .1) {
		double x = (1 - cos(t)) * cos(t);
		double y = (1 - cos(t)) * sin(t);
		cardioidPoints.push_back(tpp::Delaunay::Point(x, y));
	}

	tpp::Delaunay cardioid(cardioidPoints);
	cardioid.Triangulate(true);
	cardioid.writeObj2("cardioid2.obj");
}

// --- eof ---
