#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>

#include "complex_point.h"

template<typename T>
class Poly {
  std::vector<T> roots_;

 public:
  const std::vector<T>& GetRoots() const { return roots_; }
  void AddRoot(const T& p) { roots_.push_back(p); }
  T Eval(const T& val) const {
    T res = Unit<T>();
    for (const auto& r : roots_) {
      res = res * (val - r);
    }
    return res;
  }
  size_t GetOrder() const { return roots_.size(); }
  T EvalDerivate(const T& val) const {
    if (roots_.empty()) {
      return  Zero<T>();
    }
    if (roots_.size() == 1) {
      return Unit<T>();
    }
    Poly<T> sub_poly;
    for (size_t i = 1; i < roots_.size(); ++i) {
      sub_poly.AddRoot(roots_.at(i));
    }
    return sub_poly.Eval(val) + (val - roots_.at(0)) * sub_poly.EvalDerivate(val);
  }
};

#endif