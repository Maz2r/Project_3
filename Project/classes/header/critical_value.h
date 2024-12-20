#ifndef CRITICAL_VALUE_H
#define CRITICAL_VALUE_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <vector>

#include "polygonal_curve.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;

class CriticalValue {
 public:
  // Constructor to initialize the polygonal curves P and Q
  CriticalValue(const PolygonalCurve& P, const PolygonalCurve& Q);

  // Destructor
  ~CriticalValue();

  // Functions to compute the distances for each type
  void computeTypeA();
  void computeTypeB();
  void computeTypeC();
  void computeAndSortAllTypes();

  // Getters for the computed values
  const std::vector<double>& getTypeAValues() const;
  const std::vector<double>& getTypeBValues() const;
  const std::vector<double>& getTypeCValues() const;
  const std::vector<double>& getCriticalValues() const;

 private:
  PolygonalCurve P;  // Polygonal curve P
  PolygonalCurve Q;  // Polygonal curve Q

  // Vectors to store each type of distance
  std::vector<double> typeAValues;
  std::vector<double> typeBValues;
  std::vector<double> typeCValues;
  std::vector<double> critical_values;

  // Helper functions for repeated calculations
  double distance(const Point_2& p1, const Point_2& p2) const;
  double closestPointOnEdge(const Point_2& p, const Point_2& start,
                            const Point_2& end) const;
  Point_2 findIntersectionWithPerpendicularBisector(const Point_2& p1,
                                                    const Point_2& p2,
                                                    const Point_2& start,
                                                    const Point_2& end) const;
};

#endif  // CRITICAL_VALUE_H
