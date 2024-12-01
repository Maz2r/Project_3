#ifndef GED_H
#define GED_H

#include <cmath>
#include <utility>
#include <vector>

#include "polygonal_curve.h"

using namespace std;

typedef pair<int, int> CurveAlphabet;  // Alphabet for curve transformations
typedef vector<CurveAlphabet>
    CurveString;  // A string that was transformed from a curve
typedef pair<CurveString, CurveString>
    CurveStringPair;                      // A pair of CurveString
typedef vector<pair<int, int>> Matching;  // A matching of points that has a
                                          // pair((index, index)) as an element

namespace GED {

// Computes O(n^(1/2))-approximation of GED
double computeSquareRootApproxGED(const PolygonalCurve& P,
                                  const PolygonalCurve& Q);

// Computes the GED cost for given matching for two polygonal curves P, Q
double computeCost(const PolygonalCurve& P, const PolygonalCurve& Q,
                   const Matching& matching);

// Transfroms the curves into string by randomly shifted grid
CurveStringPair transformCurvesToStrings(const PolygonalCurve& P,
                                         const PolygonalCurve& Q, int g);

// Computes the String Edit Distance (SED) for GED
Matching SED(const CurveString& S, const CurveString& T, double threshold);

// Backtrace the DP table and return matching
Matching backtrace(const vector<vector<int>>& D);

}  // namespace GED

#endif  // GED_H
