#ifndef FREE_SPACE_H
#define FREE_SPACE_H

#include "polygonal_curve.h"  // Include the class for PolygonalCurve

using namespace std;

class FreeSpace {
 public:
  // Constructor to initialize with two polygonal curves and an epsilon value
  FreeSpace(const PolygonalCurve& P, const PolygonalCurve& Q, double epsilon);

  // Destructor
  ~FreeSpace();

  // Getters for polygonal curves and epsilon
  const PolygonalCurve& getCurveP() const;
  const PolygonalCurve& getCurveQ() const;
  double getEpsilon() const;

  // Additional member functions will be added here step by step

 private:
  PolygonalCurve P;  // Polygonal curve P
  PolygonalCurve Q;  // Polygonal curve Q
  double epsilon;    // Epsilon value
};

#endif  // FREE_SPACE_H
