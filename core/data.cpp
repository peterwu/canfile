#include <cmath>

#include "data.h"

Data& Data::instance() {
  static Data d;
  return d;
}

void Data::set(int key, double dollars) {
  values_[key] = static_cast<int64_t>(std::round(dollars * 100));
  notify_dependents(key);
}

double Data::get(int key) const {
  auto it = values_.find(key);
  return it != values_.end() ? it->second / 100.0 : 0.0;
}

void Data::set_formula(int key,
                       std::function<double()> formula,
                       const std::vector<int>& deps) {
  formulas_[key] = formula;
  for (int dep : deps)
    dependents_[dep].push_back(key);
  recompute(key);
}

void Data::recompute(int key) {
  if (formulas_.count(key)) {
    set(key, formulas_[key]());
  }
}

void Data::notify_dependents(int key) {
  if (dependents_.count(key)) {
    for (int dep : dependents_[key])
      recompute(dep);
  }
}

Data::Proxy& Data::Proxy::operator=(double val) {
  data->set(key, val);
  return *this;
}

Data::Proxy::operator double() const {
  return data->get(key);
}

Data::Proxy Data::operator[](int key) {
  return Proxy{this, key};
}