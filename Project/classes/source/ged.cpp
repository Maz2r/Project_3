#include "ged.h"

namespace GED {

// Computes O(n^(1/2))-approximation of GED
double computeSquareRootApproxGED(const PolygonalCurve& P,
                                  const PolygonalCurve& Q) {
  size_t n = min(P.numPoints(), Q.numPoints());

  // Step 1: Check the sum of distances between corresponding points
  double totalDistance = 0.0;
  for (size_t i = 0; i < n; ++i) {
    double dx = P.getPoint(i).x() - Q.getPoint(i).x();
    double dy = P.getPoint(i).y() - Q.getPoint(i).y();
    totalDistance += sqrt(dx * dx + dy * dy);
  }

  // If sum of distances is less or equal to 1
  if (totalDistance <= 1.0) {
    // Construct a matching [(0, 0), (1, 1), ..., (n-1, n-1)]
    Matching approximationMatching;
    for (size_t i = 0; i < n; ++i) {
      approximationMatching.emplace_back(i, i);
    }
    return computeCost(P, Q, approximationMatching);
  }

  // Step 2: Approximation
  for (int i = 0; i <= ceil(log2(n)); ++i) {
    int g = static_cast<int>(pow(2, i));
    int maxJ = static_cast<int>(ceil(9.0 * log(n)));  // Assuming c=9

    for (int j = 0; j <= maxJ; ++j) {
      // Transform curves into strings
      CurveStringPair transformedStrings = transformCurvesToStrings(P, Q, g);

      // Compute String Edit Distance (SED)
      Matching approximationMatching =
          SED(transformedStrings.first, transformedStrings.second,
              (8 * sqrt(2) + 2) * g);

      // If a matching is found, return the cost(which is
      // O(n^(1/2))-approximation of GED)
      if (!approximationMatching.empty()) {
        return computeCost(P, Q, approximationMatching);
      }
    }
  }

  // Step 3: Return cost for empty matching if no matching found during the
  // iteration
  Matching emptyMatching;
  return computeCost(P, Q, emptyMatching);
}

// Computes the GED cost for given matching for two polygonal curves P, Q
double computeCost(const PolygonalCurve& P, const PolygonalCurve& Q,
                   const Matching& matching) {
  return 0.0;
}

// Transfroms the curves into string by randomly shifted grid
CurveStringPair transformCurvesToStrings(const PolygonalCurve& P,
                                         const PolygonalCurve& Q, int g) {
  return {{}, {}};
}

// Computes the String Edit Distance (SED)
Matching SED(const CurveString& S, const CurveString& T, double threshold) {
  return {};
}

}  // namespace GED
