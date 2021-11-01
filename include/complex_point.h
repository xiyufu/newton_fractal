#ifndef COMPLEX_POINT_H
#define COMPLEX_POINT_H

#include <cstdlib>
#include <cmath>
#include <iostream>

template<typename T>
T Unit();

template<typename T>
T Zero();

template<typename T>
double Dist(const T& p1, const T& p2);

class ComplexPoint {
  double real_{0.0};
  double img_{0.0};

 public:
  ComplexPoint(double r, double i) : real_(r), img_{i} {}
  double a() const { return real_; }
  double b() const { return img_; }
  ComplexPoint conj() const { return ComplexPoint(real_, -img_); }
  static void conj(ComplexPoint& p) { p.img_ *= -1; }
  double abs() const { return std::hypot(real_, img_); }
  static double abs(const ComplexPoint& p) { return std::hypot(p.real_, p.img_); }
  ComplexPoint operator+(const ComplexPoint& rhs) const { return ComplexPoint(real_ + rhs.a(), img_ + rhs.b()); }
  ComplexPoint operator-(const ComplexPoint& rhs) const { return ComplexPoint(real_ - rhs.a(), img_ - rhs.b()); }
  ComplexPoint operator*(const double c) const { return ComplexPoint(real_ * c, img_ * c); }
  ComplexPoint operator*(const ComplexPoint& rhs) const {
    return ComplexPoint(real_ * rhs.a() - img_ * rhs.b(), real_ * rhs.b() + img_ * rhs.a());
  }
  ComplexPoint operator/(const double den) const { return ComplexPoint(real_ / den, img_ / den); }
  ComplexPoint operator/(const ComplexPoint& rhs) const {
    double den = rhs.a() * rhs.a() + rhs.b() * rhs.b();
    return (*this) * rhs.conj() / den;
  }
  void Print() const {
    std::string op = img_ > 0 ? " + " : " - ";
    std::cout << real_ << op << std::fabs(img_) << "i ";
  }
  static void Print(const ComplexPoint& p) {
    std::string op = p.b() > 0 ? " + " : " - ";
    std::cout << p.a() << op << std::fabs(p.b()) << "i ";
  }
};

#endif