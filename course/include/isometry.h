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

class Matrix3 {
public:
  Matrix3() {}
  Matrix3(const std::initializer_list<double> &rhs);
  Matrix3(const Matrix3 &rhs);
  Matrix3(const Vector3 &first, const Vector3 &second, const Vector3 &third) {
    rows_[0] = first;
    rows_[1] = second;
    rows_[2] = third;
  }
  Matrix3(Matrix3 &&rhs) {
    rows_[0] = std::move(rhs.rows_[0]);
    rows_[1] = std::move(rhs.rows_[1]);
    rows_[2] = std::move(rhs.rows_[2]);
  }
  Matrix3 operator-(const Matrix3 &other) const;
  Matrix3 operator+(const Matrix3 &other) const;
  Matrix3 operator*(const double &other) const;
  Matrix3 operator*(const Matrix3 &other) const;
  Matrix3 operator*(const Vector3 &other) const;
  Matrix3 operator/(const Matrix3 &other) const;
  Matrix3 &operator-=(const Matrix3 &rhs);
  Matrix3 &operator+=(const Matrix3 &rhs);
  Matrix3 &operator=(const Matrix3 &rhs) {
    this->rows_[0] = rhs.row(0);
    this->rows_[1] = rhs.row(1);
    this->rows_[2] = rhs.row(2);
    return *this;
  };
  Matrix3 &operator=(const Matrix3 &&rhs) {
    this->rows_[0] = rhs.row(0);
    this->rows_[1] = rhs.row(1);
    this->rows_[2] = rhs.row(2);
    return *this;
  };
  Vector3 &operator[](const int row_n) { return row(row_n); };
  const Vector3 &operator[](const int row_n) const { return row(row_n); };

  const Vector3 &row(int index) const { return rows_[index]; }
  Vector3 &row(int index) { return rows_[index]; }
  Vector3 col(int index) const {
    return Vector3(rows_[0][index], rows_[1][index], rows_[2][index]);
  }
  bool operator==(const Matrix3 &other) const;
  static const Matrix3 kIdentity;
  static const Matrix3 kZero;
  static const Matrix3 kOnes;
  double det() const;

private:
  Vector3 rows_[3];
};

inline Matrix3 operator*(const double &lhs, const Matrix3 &rhs) {
  return (rhs * lhs);
}

inline std::ostream &operator<<(std::ostream &ss, const Matrix3 &vec) {
  return ss << "[[" << vec.row(0)[0] << ", " << vec.row(0)[1] << ", "
            << vec.row(0)[2] << "],"
            << " [" << vec.row(1)[0] << ", " << vec.row(1)[1] << ", "
            << vec.row(1)[2] << "],"
            << " [" << vec.row(2)[0] << ", " << vec.row(2)[1] << ", "
            << vec.row(2)[2] << "]]";
}

} // namespace cppcourse
