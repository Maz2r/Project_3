#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_set_3.h>

#include <fstream>
#include <limits>

#include "critical_value.h"
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
  // Define a polygonal curve P with multiple points
  vector<Point_2> pointsP = {Point_2(0.0, 0.0), Point_2(2.0, 2.0),
                             Point_2(4.0, 0.0)};
  PolygonalCurve curveP(pointsP);

  // Define a polygonal curve Q with multiple points
  vector<Point_2> pointsQ = {Point_2(1.0, 1.0), Point_2(3.0, 3.0),
                             Point_2(5.0, 1.0)};
  PolygonalCurve curveQ(pointsQ);

  // Set the initial epsilon value
  double epsilon = 1.5;

  // Create FreeSpace object with initial epsilon
  FreeSpace freeSpace(curveP, curveQ, epsilon);

  // Compute the free space
  cout << "Computing free space with epsilon = " << epsilon << endl;
  freeSpace.computeFreeSpace();

  // Display the results for L (for curve P)
  cout << "Results for L (curve P):" << endl;
  const PointPairVector& L = freeSpace.getL();
  for (size_t i = 0; i < L.size(); ++i) {
    cout << "L[" << i << "]: ((" << L[i].first.x() << ", " << L[i].first.y()
         << "), (" << L[i].second.x() << ", " << L[i].second.y() << "))"
         << endl;
  }

  // Display the results for B (for curve Q)
  cout << "Results for B (curve Q):" << endl;
  const PointPairVector& B = freeSpace.getB();
  for (size_t i = 0; i < B.size(); ++i) {
    cout << "B[" << i << "]: ((" << B[i].first.x() << ", " << B[i].first.y()
         << "), (" << B[i].second.x() << ", " << B[i].second.y() << "))"
         << endl;
  }

  // Change the epsilon value and recompute free space
  double newEpsilon = 2.0;
  cout << "\nChanging epsilon to " << newEpsilon
       << " and recomputing free space." << endl;
  freeSpace.setEpsilon(newEpsilon);

  // Display the new results for L (for curve P)
  cout << "Results for L (curve P) with new epsilon:" << endl;
  const PointPairVector& newL = freeSpace.getL();
  for (size_t i = 0; i < newL.size(); ++i) {
    cout << "L[" << i << "]: ((" << newL[i].first.x() << ", "
         << newL[i].first.y() << "), (" << newL[i].second.x() << ", "
         << newL[i].second.y() << "))" << endl;
  }

  // Display the new results for B (for curve Q)
  cout << "Results for B (for curve Q) with new epsilon:" << endl;
  const PointPairVector& newB = freeSpace.getB();
  for (size_t i = 0; i < newB.size(); ++i) {
    cout << "B[" << i << "]: ((" << newB[i].first.x() << ", "
         << newB[i].first.y() << "), (" << newB[i].second.x() << ", "
         << newB[i].second.y() << "))" << endl;
  }

  return 0;
}