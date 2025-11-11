#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>
#include <vector>

class Data {
 public:
  static Data& instance();

  // Assign a value in dollars
  void set(int key, double dollars);

  // Read a value in dollars
  double get(int key) const;

  // Set a formula (in dollars)
  void set_formula(int key,
                   std::function<double()> formula,
                   const std::vector<int>& deps);

  struct Proxy {
    Data* data;
    int key;
    Proxy& operator=(double val);
    operator double() const;
  };

  Proxy operator[](int key);

 private:
  std::unordered_map<int, int64_t> values_;  // stored in cents
  std::unordered_map<int, std::function<double()>> formulas_;
  std::unordered_map<int, std::vector<int>> dependents_;

  void recompute(int key);
  void notify_dependents(int key);
};