#pragma once
#include <vector>
#include "tpp_interface.h"

class Triangulation {
public:
  Triangulation(std::vector<double>);
  ~Triangulation();
  std::vector<double> vertices();
  std::vector<int> triangles();
private:
	// there is no default constructor, so I have to postpone the construction to this' constructor, so I have to hold a pointer here.
	std::unique_ptr<tpp::Delaunay> d;
};
