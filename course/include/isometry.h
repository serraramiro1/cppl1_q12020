#pragma once

#include <cmath>
#include <iostream>
#include <string>

namespace cppcourse {

class Vector3 {
public:

  Vector3(const std::initializer_list<double> &rhs);
  Vector3(const double &x = 0., const double &y = 0., const double &z = 0.)
      : x_(x), y_(y), z_(z){};
  Vector3 operator+(const Vector3 &other) const;
  Vector3 operator-(const Vector3 &other) const;
  Vector3 operator/(const Vector3 &other) const;
  Vector3 operator*(const double &other) const;
  Vector3 operator*(const Vector3 &other) const;
  bool operator!=(const Vector3 &other) const { return (!(*this == other)); }
  bool operator==(const Vector3 &other) const;
  bool operator==(const std::initializer_list<double> &rhs) const;
  double &operator[](const int index);
  const double &operator[](const int index) const;

  double dot(const Vector3 &other) const;
  Vector3 cross(const Vector3 &other) const;
  double norm() const;
  double &x() { return x_; }
  const double &x() const { return x_; }
  double &y() { return y_; }
  const double &y() const { return y_; }
  double &z() { return z_; }
  const double &z() const { return z_; }

  static const Vector3 kUnitX;
  static const Vector3 kUnitY;
  static const Vector3 kUnitZ;
  static const Vector3 kZero;

private:
  double x_, y_, z_;
};

inline Vector3 operator*(const double &lhs, const Vector3 &rhs) {
  return (rhs * lhs);
}

inline std::ostream &operator<<(std::ostream &ss,
                                const cppcourse::Vector3 &vec) {
  return ss << "(x: " << vec.x() << ", y: " << vec.y() << ", z: " << vec.z()
            << ")";
}

} // namespace cppcourse
