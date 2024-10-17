#include "decision_problem.h"

// Constructor to initialize with two curves and epsilon
DecisionProblem::DecisionProblem(const PolygonalCurve& P,
                                 const PolygonalCurve& Q, double epsilon)
    : P(P),
      Q(Q),
      epsilon(epsilon),
      freeSpace(P, Q, epsilon),
      monotoneCurveExists(false) {
  checkMonotoneCurve();
}

// Getter for the result
bool DecisionProblem::doesMonotoneCurveExist() const {
  return monotoneCurveExists;
}

// Getter for polygonal curve P
const PolygonalCurve& DecisionProblem::getCurveP() const { return P; }

// Getter for polygonal curve Q
const PolygonalCurve& DecisionProblem::getCurveQ() const { return Q; }

// Getter for epsilon
double DecisionProblem::getEpsilon() const { return epsilon; }

// Setter for epsilon and recompute monotone curve existence
void DecisionProblem::setEpsilon(double newEpsilon) {
  epsilon = newEpsilon;
  freeSpace.setEpsilon(newEpsilon);  // Update FreeSpace with new epsilon
  checkMonotoneCurve();              // Recheck if a monotone curve exists
}

// Function to check if there is a monotone curve
void DecisionProblem::checkMonotoneCurve() {
  // Step 1: Check start and end conditions
  if (!checkStartAndEndConditions()) {
    monotoneCurveExists = false;
    return;
  }

  // Step 2: Check if a monotone curve exists
  monotoneCurveExists = checkIfMonotoneCurveExists();
}

// Helper function to check if (0,0) exists in the first element and (q-1, p-1)
// in the last element
bool DecisionProblem::checkStartAndEndConditions() {
  const PointPairVector& L = freeSpace.getL();
  const PointPairVector& B = freeSpace.getB();

  // Check for (0,0) in the first elements of L or B
  Point_2 startPoint(0, 0);
  bool startCondition =
      (L[0].first == startPoint || L[0].second == startPoint ||
       B[0].first == startPoint || B[0].second == startPoint);

  int p = P.numPoints();
  int q = Q.numPoints();
  Point_2 endPoint(q - 1, p - 1);

  // Check for (q-1, p-1) in the last elements of L or B
  bool endCondition =
      (L.back().first == endPoint || L.back().second == endPoint ||
       B.back().first == endPoint || B.back().second == endPoint);

  // If both conditions are satisfied, we can proceed
  return startCondition && endCondition;
}

// Function to check if a monotone curve exists
bool DecisionProblem::checkIfMonotoneCurveExists() {
  // This will check if there is a valid monotone curve
  return true;  // Placeholder return, logic will be added later
}
