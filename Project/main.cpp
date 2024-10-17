#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_set_3.h>

#include <fstream>
#include <limits>

#include "critical_value.h"
#include "decision_problem.h"
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
  // Define two simple polygonal curves
  std::vector<Point_2> pointsP = {Point_2(0, 0), Point_2(1, 2), Point_2(2, 3)};
  std::vector<Point_2> pointsQ = {Point_2(0, 0), Point_2(1, 1), Point_2(2, 2)};

  // Create polygonal curves P and Q
  PolygonalCurve P(pointsP);
  PolygonalCurve Q(pointsQ);

  // Set an epsilon value
  double epsilon = 1.5;

  // Create a DecisionProblem object with P, Q, and epsilon
  DecisionProblem decision(P, Q, epsilon);

  // Test if a monotone curve exists
  if (decision.doesMonotoneCurveExist()) {
    std::cout << "A monotone curve exists for epsilon = " << epsilon
              << std::endl;
  } else {
    std::cout << "No monotone curve exists for epsilon = " << epsilon
              << std::endl;
  }

  // Change epsilon value and recheck
  double newEpsilon = 0.5;
  decision.setEpsilon(newEpsilon);

  // Test again after updating epsilon
  if (decision.doesMonotoneCurveExist()) {
    std::cout << "A monotone curve exists for epsilon = " << newEpsilon
              << std::endl;
  } else {
    std::cout << "No monotone curve exists for epsilon = " << newEpsilon
              << std::endl;
  }

  return 0;
}