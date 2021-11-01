#include "complex_point.h"

template<>
double Unit<double>() {
  return 1;
}

template<>
ComplexPoint Unit<ComplexPoint>() {
  return ComplexPoint(1, 0);
}

template<>
double Zero<double>() {
  return 0;
}

template<>
ComplexPoint Zero<ComplexPoint>() {
  return ComplexPoint(0, 0);
}

template<>
double Dist<double>(const double& p1, const double& p2) {
  return std::fabs(p1 - p2);
}

template<>
double Dist<ComplexPoint>(const ComplexPoint& p1, const ComplexPoint& p2) {
  return std::hypot(p1.a() - p2.a(), p1.b() - p2.b());
}