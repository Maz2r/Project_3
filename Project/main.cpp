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
  vector<Point_2> pointsP = {Point_2(0.0, 0.0), Point_2(2.0, 1.0),
                             Point_2(4.0, 0.0), Point_2(6.0, 1.0)};
  PolygonalCurve curveP(pointsP);

  // Define a polygonal curve Q with multiple points
  vector<Point_2> pointsQ = {Point_2(1.0, 2.0), Point_2(3.0, 3.0),
                             Point_2(5.0, 2.0), Point_2(7.0, 3.0)};
  PolygonalCurve curveQ(pointsQ);

  // Create the CriticalValue object and compute the distances
  CriticalValue criticalValue(curveP, curveQ);

  // Display the critical values (all type a, b, c combined and sorted)
  const vector<double>& criticalValues = criticalValue.getCriticalValues();
  cout << "Critical Values (sorted):" << endl;
  for (size_t i = 0; i < criticalValues.size(); ++i) {
    cout << criticalValues[i] << endl;
  }

  // Display Type A, B, and C values separately
  const vector<double>& typeAValues = criticalValue.getTypeAValues();
  const vector<double>& typeBValues = criticalValue.getTypeBValues();
  const vector<double>& typeCValues = criticalValue.getTypeCValues();

  cout << "\nType A Values:" << endl;
  for (double value : typeAValues) {
    cout << value << endl;
  }

  cout << "\nType B Values:" << endl;
  for (double value : typeBValues) {
    cout << value << endl;
  }

  cout << "\nType C Values:" << endl;
  for (double value : typeCValues) {
    cout << value << endl;
  }

  return 0;
}