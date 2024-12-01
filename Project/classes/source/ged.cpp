#include "ged.h"

#include <cstdlib>
#include <limits>

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
              12 * sqrt(n) + 2 * g);

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
  size_t n = min(P.numPoints(), Q.numPoints());

  // Step 1: Calculate delta
  double delta = g / sqrt(n);

  // Step 2: Pick random values x_o, y_o in [0, delta]
  double x_o = static_cast<double>(rand()) / RAND_MAX * delta;
  double y_o = static_cast<double>(rand()) / RAND_MAX * delta;

  // Step 3: Copy P and Q
  PolygonalCurve convertedP = P;
  PolygonalCurve convertedQ = Q;

  // Step 4: Set the new origin for both curves
  convertedP.shiftOrigin(Point_2(x_o, y_o));
  convertedQ.shiftOrigin(Point_2(x_o, y_o));

  // Step 5: Scale the grid with delta as the scaling factor
  convertedP.scaleGrid(delta);
  convertedQ.scaleGrid(delta);

  // Step 6: Floor the coordinates of the points
  convertedP.floorCoordinates();
  convertedQ.floorCoordinates();

  // Step 7: Set CurveStrings with converted curves
  CurveString stringP, stringQ;
  for (size_t i = 0; i < convertedP.numPoints(); ++i) {
    stringP.emplace_back(static_cast<int>(convertedP.getPoint(i).x()),
                         static_cast<int>(convertedP.getPoint(i).y()));
  }
  for (size_t i = 0; i < convertedQ.numPoints(); ++i) {
    stringQ.emplace_back(static_cast<int>(convertedQ.getPoint(i).x()),
                         static_cast<int>(convertedQ.getPoint(i).y()));
  }

  // Step 8: Return the CurveStringPair
  return {stringP, stringQ};
}

// Computes the String Edit Distance (SED) for GED
Matching SED(const CurveString& S, const CurveString& T, double threshold) {
  size_t n = S.size();
  int k = static_cast<int>(floor(threshold));

  // Step 1: Initialize the (n+1) by (n+1) DP table D
  vector<vector<int>> D(n + 1, vector<int>(n + 1, -1));
  for (size_t i = 0; i <= n; ++i) {
    D[i][0] = static_cast<int>(i);
    D[0][i] = static_cast<int>(i);
  }

  // Step 2: Initialize the vector L(that saves L values for each h and e) with
  // length 2k+1
  vector<int> L(2 * k + 1, -1);

  // Step 3: Dynamic programming loop
  for (int e = 0; e <= k; ++e) {
    L[k - (e + 1)] = e;   // h < 0: L_h,|h|-2 to |h|-1
    L[k + (e + 1)] = -1;  // h >= 0: L_h,|h|-2 to -1

    for (int h = -e; h <= e; ++h) {
      // Algorithm 3(from referenced paper)
      if (h % 2 != e % 2) {
        continue;
      }

      // Check if substitution values are infinity
      if (L[k + h - 1] == numeric_limits<int>::max() ||
          L[k + h + 1] == numeric_limits<int>::max()) {
        L[k + h] = numeric_limits<int>::max();  // Set L[k + h] to infinity
        continue;
      }

      // Compute r based on L
      int r = max(L[k + h - 1], L[k + h + 1] + 1);

      // Slide
      while (r + 1 <= n && r + h + 1 <= n && (S[r] == T[r + h])) {
        D[r + 1][r + h + 1] = e;
        ++r;
      }

      // Set L_h,e
      if (r >= static_cast<int>(n) || r + h >= static_cast<int>(n)) {
        L[k + h] = numeric_limits<int>::max();  // Set to "infinity"
      } else {
        L[k + h] = r;
      }
    }
  }

  // Step 4: Check if the edit distance is within the threshold
  if (D[n][n] == -1) {
    return {};  // Return empty matching
  }

  // Step 5: Backtrace the DP table and return matching
  return backtrace(D);
}

Matching backtrace(const vector<vector<int>>& D) { return {}; }

}  // namespace GED
