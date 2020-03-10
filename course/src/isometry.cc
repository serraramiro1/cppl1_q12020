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
  if (rhs.size() != 3){
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
  return (Matrix3(*this) += other);
}

Matrix3 Matrix3::operator*(const double &other) const {
  return (Matrix3(rows_[0] * other, rows_[1] * other, rows_[2] * other));
}

Matrix3 Matrix3::operator*(const Matrix3 &other) const {
  Matrix3 output;
  for (int i = 0; i < 3; i++) {
    output[i] = rows_[i] * other.rows_[i];
  }
  return output;
}

Matrix3 Matrix3::operator*(const Vector3 &other) const {
  Matrix3 output;
  for (int i = 0; i < 3; i++) {
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

const Matrix3 Matrix3::kIdentity = {1., 0., 0., 0., 1., 0., 0., 0., 1.};
const Matrix3 Matrix3::kOnes = {1., 1., 1., 1., 1., 1., 1., 1., 1.};
const Matrix3 Matrix3::kZero = {0., 0., 0., 0., 0., 0., 0., 0., 0.};

// VECTOR 4
Vector4::Vector4(const std::initializer_list<double> &rhs) {
  if (rhs.size() != 4) {
    throw;
  }
  auto begin_ptr = rhs.begin();
  vec_[0] = *(begin_ptr++);
  vec_[1] = *(begin_ptr++);
  vec_[2] = *(begin_ptr++);
  vec_[3] = *(begin_ptr);
}

Matrix4::Matrix4(const std::initializer_list<double> &rhs) {
  if (rhs.size() != 16) {
    throw;
  }
  auto begin_ptr = rhs.begin();
  for (int i = 0; i < 4; i++) {
    rows_[i] = Vector4{begin_ptr[4 * i], begin_ptr[4 * i + 1],
                       begin_ptr[4 * i + 2], begin_ptr[4 * i + 3]};
  }
}

Matrix4 Matrix4::operator*(const Matrix4 &rhs) const {
  Matrix4 output;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      output[i][j] = row(i) * rhs.col(j);
    }
  }
  return output;
}

const Vector4 Vector4::kUnit1 = {1., 0., 0., 0.};
const Vector4 Vector4::kUnit2 = {0., 1., 0., 0.};
const Vector4 Vector4::kUnit3 = {0., 0., 1., 0.};
const Vector4 Vector4::kUnit4 = {0., 0., 0., 1.};
const Vector4 Vector4::kOnes = {1., 1., 1., 1.};
const Vector4 Vector4::kZero = Vector4();

const Matrix4 Matrix4::kIdentity = {Vector4::kUnit1, Vector4::kUnit2,
                                    Vector4::kUnit3, Vector4::kUnit4};
const Matrix4 Matrix4::kZero = {Vector4::kZero, Vector4::kZero, Vector4::kZero,
                                Vector4::kZero};

const Isometry Isometry::FromTranslation(const Vector3 &vec) {
  Isometry output;
  output.isometry_matrix_ = Matrix4::kIdentity;
  for (int i = 0; i < 3; i++) {
    output.isometry_matrix_[i][3] = vec[i];
  }
  output.translation_ = vec;
  output.rotation_ = Matrix4::kIdentity;
  return output;
}

Isometry Isometry::RotateAround(const Vector3 &direction, const double &value) {
  Isometry output;
  output.isometry_matrix_ = Matrix4::kIdentity;

  if (direction == Vector3::kUnitX) {
    output.isometry_matrix_[1][1] = std::cos(value);
    output.isometry_matrix_[1][2] = -std::sin(value);
    output.isometry_matrix_[2][1] = std::sin(value);
    output.isometry_matrix_[2][2] = -std::cos(value);

  } else if (direction == Vector3::kUnitY) {
    output.isometry_matrix_[0][0] = std::cos(value);
    output.isometry_matrix_[0][2] = std::sin(value);
    output.isometry_matrix_[2][0] = -std::sin(value);
    output.isometry_matrix_[2][2] = std::cos(value);

  } else if (direction == Vector3::kUnitZ) {
    output.isometry_matrix_[0][0] = std::cos(value);
    output.isometry_matrix_[0][1] = -std::sin(value);
    output.isometry_matrix_[1][0] = std::sin(value);
    output.isometry_matrix_[1][1] = std::cos(value);
  }
  output.rotation_ = output.isometry_matrix_;
  return output;
}

Isometry Isometry::FromEulerAngles(const double &roll, const double &pitch,
                                   const double &yaw) {
  return (Isometry::RotateAround(Vector3::kUnitX, roll) *
          Isometry::RotateAround(Vector3::kUnitY, pitch) *
          Isometry::RotateAround(Vector3::kUnitZ, yaw));
}
} // namespace cppcourse
