#include "isometry.h"

namespace cppcourse {

const Vector3 Vector3::kUnitX = {1., 0., 0.};
const Vector3 Vector3::kUnitY = {0., 1., 0.};
const Vector3 Vector3::kUnitZ = {0., 0., 1.};
const Vector3 Vector3::kZero = {0., 0., 0.};

Vector3 Vector3::operator+(const Vector3 &other) const {
  return Vector3(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector3 Vector3::cross(const Vector3 &other) const {
  Vector3 output;
  output.x_ = y() * other.z() - z() * other.y();
  output.y_ = z() * other.x() - x() * other.z();
  output.z_ = x() * other.y() - y() * other.x();
  return output;
}

Vector3 Vector3::operator/(const Vector3 &other) const {
  return Vector3(x_ / other.x_, y_ / other.y_, z_ / other.z_);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
  return Vector3(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Vector3 Vector3::operator*(const Vector3 &other) const {
  return Vector3(x_ * other.x_, y_ * other.y_, z_ * other.z_);
}

Vector3 Vector3::operator*(const double &other) const {
  return Vector3(x_ * other, y_ * other, z_ * other);
}

bool Vector3::operator==(const Vector3 &other) const {
  return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
}

Vector3::Vector3(const std::initializer_list<double> &rhs) {
  auto begin_ptr = rhs.begin();
  x_ = *(begin_ptr++);
  y_ = *(begin_ptr++);
  z_ = *(begin_ptr);
}
double Vector3::norm() const { return (sqrt(x_ * x_ + y_ * y_ + z_ * z_)); }

double Vector3::dot(const Vector3 &other) const {
  return (x_ * other.x_ + y_ * other.y_ + z_ * other.z_);
}

bool Vector3::operator==(const std::initializer_list<double> &rhs) const {
  Vector3 vec{rhs};
  return *this == vec;
}

double &Vector3::operator[](const int index) {
  switch (index) {
  case 0:
    return x_;

  case 1:
    return y_;

  default:
    return z_;
  }
}

const double &Vector3::operator[](const int index) const {
  switch (index) {
  case 0:
    return x_;

  case 1:
    return y_;

  default:
    return z_;
  }
}
} // namespace cppcourse
