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
  if (rhs.size() != 3) {
    throw;
  }
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

Matrix3::Matrix3(const std::initializer_list<double> &rhs) {
  if (rhs.size() != 9) {
    throw;
  }
  auto begin_vec = rhs.begin();
  rows_[0] = Vector3{begin_vec[0], begin_vec[1], begin_vec[2]};
  rows_[1] = Vector3{begin_vec[3], begin_vec[4], begin_vec[5]};
  rows_[2] = Vector3{begin_vec[6], begin_vec[7], begin_vec[8]};
}

Matrix3::Matrix3(const Matrix3 &rhs) {
  rows_[0] = rhs.rows_[0];
  rows_[1] = rhs.rows_[1];
  rows_[2] = rhs.rows_[2];
}

Matrix3 Matrix3::inverse() const{
  Matrix3 output;
  output[0][0] = rows_[1][1] * rows_[2][2] - rows_[1][2] * rows_[2][1];
  output[0][1] = rows_[0][2] * rows_[2][1] - rows_[0][1] * rows_[2][2];
  output[0][2] = rows_[0][1] * rows_[1][2] - rows_[0][2] * rows_[1][1];

  output[1][0] = rows_[1][2] * rows_[2][0] - rows_[1][0] * rows_[2][2];
  output[1][1] = rows_[0][0] * rows_[2][2] - rows_[0][2] * rows_[2][0];
  output[1][2] = rows_[0][2] * rows_[1][0] - rows_[0][0] * rows_[1][2];

  output[2][0] = rows_[1][0] * rows_[2][1] - rows_[1][1] * rows_[1][2];
  output[2][1] = rows_[0][1] * rows_[2][0] - rows_[0][0] * rows_[2][1];
  output[2][2] = rows_[0][0] * rows_[1][1] - rows_[0][1] * rows_[1][0];
  return (output * (1 / det()));
}

bool Matrix3::operator==(const Matrix3 &other) const {
  return ((rows_[0] == other.rows_[0]) && (rows_[1] == rows_[1]) &&
          (rows_[2] == other.rows_[2]));
}

Matrix3 &Matrix3::operator+=(const Matrix3 &rhs) {
  rows_[0] = rows_[0] + rhs.rows_[0];
  rows_[1] = rows_[1] + rhs.rows_[1];
  rows_[2] = rows_[2] + rhs.rows_[2];

  return *this;
}

Matrix3 &Matrix3::operator-=(const Matrix3 &rhs) {
  rows_[0] = rows_[0] - rhs.rows_[0];
  rows_[1] = rows_[1] - rhs.rows_[1];
  rows_[2] = rows_[2] - rhs.rows_[2];

  return *this;
}

Matrix3 Matrix3::operator-(const Matrix3 &other) const {
  return (Matrix3(*this) -= other);
}

Matrix3 Matrix3::operator+(const Matrix3 &other) const {
  Matrix3 aux{*this};
  aux += other;
  return aux;
}

Matrix3 Matrix3::operator*(const double &other) const {
  return (Matrix3(rows_[0] * other, rows_[1] * other, rows_[2] * other));
}

Matrix3 Matrix3::operator*(const Matrix3 &other) const {
  Matrix3 output;
  for (int i = 0; i < 3; ++i) {
    output[i] = rows_[i] * other.rows_[i];
  }
  return output;
}

Matrix3 Matrix3::operator*(const Vector3 &other) const {
  Matrix3 output;
  for (int i = 0; i < 3; ++i) {
    output[i] = rows_[i] * other[i];
  }
  return output;
}

Matrix3 Matrix3::operator/(const Matrix3 &other) const {
  Matrix3 output;
  for (int i = 0; i < 3; i++) {
    output[i] = rows_[i] / other.rows_[i];
  }
  return output;
}

double Matrix3::det() const {
  return (
      rows_[0][0] * (rows_[1][1] * rows_[2][2] - rows_[1][2] * rows_[2][1]) -
      rows_[0][1] * (rows_[1][0] * rows_[2][2] - rows_[1][2] * rows_[2][0]) +
      rows_[0][2] * (rows_[1][0] * rows_[2][1] - rows_[1][1] * rows_[2][0]));
}

Matrix3 Matrix3::product(const Matrix3 &rhs) const {
  Matrix3 output;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      output[i][j] = row(i).dot(rhs.col(j));
    }
  }
  return output;
}

Vector3 Matrix3::product(const Vector3 &rhs) const {
  Vector3 output;
  for (int i = 0; i < 3; ++i) {
    output[i] = row(i).dot(rhs);
  }
  return output;
}

const Matrix3 Matrix3::kIdentity = {1., 0., 0., 0., 1., 0., 0., 0., 1.};
const Matrix3 Matrix3::kOnes = {1., 1., 1., 1., 1., 1., 1., 1., 1.};
const Matrix3 Matrix3::kZero = {0., 0., 0., 0., 0., 0., 0., 0., 0.};

Isometry Isometry::FromTranslation(const Vector3 &vec) {
  return Isometry{vec, Matrix3::kIdentity};
}

Isometry Isometry::RotateAround(const Vector3 &direction, const double &value) {
  Isometry output;

  output.rotation_[0][0] = std::cos(value) + (direction.x() * direction.x()) * (1 - std::cos(value));
  output.rotation_[0][1] = direction.x() * direction.y() * (1 - std::cos(value)) - direction.z() * std::sin(value);
  output.rotation_[0][2] = direction.x() * direction.z() * (1 - std::cos(value)) + direction.y() * std::sin(value);
  output.rotation_[1][0] = direction.y() * direction.x() * (1 - std::cos(value)) + direction.z() * std::sin(value);
  output.rotation_[1][1] = std::cos(value) + (direction.y() * direction.y()) * (1 - std::cos(value));
  output.rotation_[1][2] = direction.y() * direction.z() * (1 - std::cos(value)) - direction.x() * std::sin(value);
  output.rotation_[2][0] = direction.z() * direction.x() * (1 - std::cos(value)) + direction.y() * std::sin(value);
  output.rotation_[2][1] = direction.z() * direction.y() * (1 - std::cos(value)) + direction.x() * std::sin(value);
  output.rotation_[2][2] = std::cos(value) + (direction.z() * direction.z()) * (1 - std::cos(value));

  return output;
}

Isometry Isometry::FromEulerAngles(const double &roll, const double &pitch,
                                   const double &yaw) {
  return (Isometry::RotateAround(Vector3::kUnitX, roll) *
          Isometry::RotateAround(Vector3::kUnitY, pitch) *
          Isometry::RotateAround(Vector3::kUnitZ, yaw));
}
} // namespace cppcourse
