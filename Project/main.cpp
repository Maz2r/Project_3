#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_set_3.h>

#include <fstream>
#include <limits>

#include "dummy.h"
#include "free_space.h"
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
  // Define polygonal curve P (a more complex polygonal line)
  vector<Point_2> pointsP = {Point_2(0.0, 0.0), Point_2(2.0, 1.0),
                             Point_2(4.0, 0.0), Point_2(6.0, 1.0),
                             Point_2(8.0, 0.0)};

  PolygonalCurve curveP(pointsP);

  // Define polygonal curve Q (a zigzag line pattern)
  vector<Point_2> pointsQ = {Point_2(1.0, 0.5), Point_2(3.0, 1.5),
                             Point_2(5.0, 0.5), Point_2(7.0, 1.5),
                             Point_2(9.0, 0.5)};

  PolygonalCurve curveQ(pointsQ);

  // Set epsilon value (e.g., 0.5)
  double epsilon = 1.0;

  // Create the FreeSpace object
  FreeSpace freeSpace(curveP, curveQ, epsilon);

  // Compute the free space
  freeSpace.computeFreeSpace();

  // Get and display the results for L (for curve P)
  cout << "Results for L (curve P):" << endl;
  const PointPairVector& L = freeSpace.getL();
  for (size_t i = 0; i < L.size(); ++i) {
    cout << "L[" << i << "]: ((" << L[i].first.x() << ", " << L[i].first.y()
         << "), (" << L[i].second.x() << ", " << L[i].second.y() << "))"
         << endl;
  }

  // Get and display the results for B (for curve Q)
  cout << "Results for B (curve Q):" << endl;
  const PointPairVector& B = freeSpace.getB();
  for (size_t i = 0; i < B.size(); ++i) {
    cout << "B[" << i << "]: ((" << B[i].first.x() << ", " << B[i].first.y()
         << "), (" << B[i].second.x() << ", " << B[i].second.y() << "))"
         << endl;
  }

  return 0;
}