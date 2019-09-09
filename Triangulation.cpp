#include "Triangulation.h"

Triangulation::Triangulation(std::vector<double> polygon) {
  std::vector<tpp::Delaunay::Point> dInput;
  dInput.reserve(polygon.size() / 2);
  for (auto pi = polygon.begin(); pi != polygon.end();) {
    double x = *pi++;
    double y = *pi++;
    dInput.push_back(tpp::Delaunay::Point(x, y));
  }
  this->d = std::unique_ptr<tpp::Delaunay>(new tpp::Delaunay(dInput));
  this->d->Triangulate(true);
}

Triangulation::~Triangulation()
{
}

std::vector<double> Triangulation::vertices()
{
	return this->d->vertices();
}

std::vector<int> Triangulation::triangles()
{
	return this->d->triangles();
}
