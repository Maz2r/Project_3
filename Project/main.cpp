#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_set_3.h>

#include <fstream>
#include <limits>

#include "dummy.h"
#include "polygonal_curve.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::FT FT;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;

typedef CGAL::Point_set_3<Point> Point_set;

void print_point_set(const Point_set& point_set) {
  std::cerr << "Content of point set:" << std::endl;
  for (Point_set::const_iterator it = point_set.begin(); it != point_set.end();
       ++it)
    std::cerr << "* Point " << *it << ": "
              << point_set.point(*it)  // or point_set[it]
              << " with normal " << point_set.normal(*it) << std::endl;
}

int main(int, char**) {
  vector<Point_2> points = {Point_2(0.02, 0.02), Point_2(1.03, 1.11),
                            Point_2(2.54, 4.52)};

  PolygonalCurve curve(points);

  // Adding a point
  curve.addPoint(Point_2(3.92, 10.11));

  // Print the curve points
  curve.printCurve();

  // Get and print curve length
  cout << "Curve Length: " << curve.curveLength() << endl;

  return 0;
}