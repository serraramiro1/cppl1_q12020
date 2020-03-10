#pragma once

#include <cmath>
#include <iomanip> // std::setprecision
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
  Matrix3 operator=(const Matrix3 &rhs) { return Matrix3(rhs); };
  Matrix3 operator=(const Matrix3 &&rhs) { return Matrix3(rhs); };
  Vector3 &operator[](const int row_n) { return row(row_n); };
  Vector3 operator[](const int row_n) const { return row(row_n); };

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

class Vector4 {
public:
  Vector4(const std::initializer_list<double> &rhs);
  Vector4(const Vector3 &rhs) {
    vec_[0] = rhs.x();
    vec_[1] = rhs.y();
    vec_[2] = rhs.z();
    vec_[3] = 1;
  }
  Vector4(const double &first = 0.0, const double &second = 0.0,
          const double &third = 0.0, const double &fourth = 0.0) {
    vec_[0] = first;
    vec_[1] = second;
    vec_[2] = third;
    vec_[3] = fourth;
  }
  double &operator[](const int index) { return vec_[index]; }
  double operator*(const Vector4 rhs) const {
    double output = 0;
    for (int i = 0; i < 4; i++) {
      output += (vec_[i] * rhs.vec_[i]);
    }
    return output;
  }
  bool operator==(const Vector4 &rhs) const {
    return ((vec_[0] == rhs.vec_[0]) && (vec_[1] == rhs.vec_[1]) &&
            (vec_[2] == rhs.vec_[2]) && (vec_[3] == rhs.vec_[3]));
  }
  const double &operator[](const int index) const { return vec_[index]; }
  static const Vector4 kUnit1;
  static const Vector4 kUnit2;
  static const Vector4 kUnit3;
  static const Vector4 kUnit4;
  static const Vector4 kZero;
  static const Vector4 kOnes;

private:
  double vec_[4];
};

inline std::ostream &operator<<(std::ostream &ss,
                                const cppcourse::Vector4 &vec) {
  return ss << "[ " << vec[0] << ", " << vec[1] << ", " << vec[2] << ", "
            << vec[3] << "]";
}

class Matrix4 {
public:
  Matrix4() {
    rows_[0] = Vector4();
    rows_[1] = Vector4();
    rows_[2] = Vector4();
    rows_[3] = Vector4();
  };
  Matrix4(const std::initializer_list<double> &rhs);
  Matrix4(const Matrix3 &rhs);
  Matrix4(const Vector4 &first, const Vector4 &second, const Vector4 &third,
          const Vector4 &fourth) {
    rows_[0] = first;
    rows_[1] = second;
    rows_[2] = third;
    rows_[3] = fourth;
  }
  Matrix4 operator*(const Matrix4 &rhs) const;
  const Vector4 &row(const int index) const { return rows_[index]; }
  Vector4 &row(const int index) { return rows_[index]; }
  Vector4 &operator[](const int row_n) { return row(row_n); };
  Vector4 operator[](const int row_n) const { return row(row_n); };
  bool operator==(const Matrix4 &rhs) const {
    return ((rows_[0] == rhs.rows_[0]) && (rows_[1] == rhs.rows_[1]) &&
            (rows_[2] == rhs.rows_[2]) && (rows_[3] == rhs.rows_[3]));
  };

  Vector4 col(const int index) const {
    return (Vector4(rows_[0][index], rows_[1][index], rows_[2][index],
                    rows_[3][index]));
  }
  Vector4 operator*(const Vector4 &rhs) const {
    Vector4 output;
    for (int i = 0; i < 4; i++) {
      output[i] = rows_[i] * rhs;
    }
    return output;
  }
  static const Matrix4 kZero;
  static const Matrix4 kIdentity;

private:
  Vector4 rows_[4];
};

inline std::ostream &operator<<(std::ostream &ss,
                                const cppcourse::Matrix4 &mat) {
  return ss << "[ " << mat[0] << "/n " << mat[1] << "/n " << mat[2] << "/n "
            << mat[3] << "]";
}

class Isometry {
public:
  Isometry() {
    isometry_matrix_ = Matrix4::kIdentity;
    rotation_ = Matrix4::kIdentity;
    translation_ = Vector3::kZero;
  }
  Isometry(const Vector3 &trans, const Matrix3 &rot) {
    *this = FromTranslation(trans);
    rotation_ = Mat4FromMat3(rot);
    isometry_matrix_ = (isometry_matrix_ * rotation_);
  }

  static Matrix4 Mat4FromMat3(const Matrix3 &mat3) {
    Matrix4 output = Matrix4::kIdentity;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        output[i][j] = mat3[i][j];
      }
    }
    return output;
  }
  static const Isometry FromTranslation(const Vector3 &vec);

  static Matrix3 Mat3FromMat4(const Matrix4 &mat4) {
    Matrix3 output;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        output[i][j] = mat4[i][j];
      }
    }
    return output;
  }
  Vector3 operator*(const Vector3 &rhs) const {
    Vector4 output = isometry_matrix_ * Vector4{rhs};
    return (Vector3{output[0], output[1], output[2]});
  }
  Isometry operator*(const Isometry &rhs) const {
    return (Isometry{translation_ + rhs.translation_,
                     Mat3FromMat4(rotation_ * rhs.rotation_)});
  }
  Isometry inverse() const {
    // Only does inverse of translation (do we need inverse of rotation?)
    return (Isometry::FromTranslation(translation_ * -1));
  }
  Isometry compose(const Isometry &rhs) const { return (*this * rhs); }
  Vector3 transform(const Vector3 &rhs) const { return (*this * rhs); }
  bool operator==(const Isometry &rhs) const {
    return (isometry_matrix_ == rhs.isometry_matrix_);
  }
  const Matrix3 rotation() const { return Mat3FromMat4(rotation_); }
  const Vector3 &translation() const { return translation_; }
  static Isometry RotateAround(const Vector3 &direction, const double &value);
  static Isometry FromEulerAngles(const double &roll, const double &pitch,
                                  const double &yaw);
  Matrix4 get_iso() const { return isometry_matrix_; };

private:
  Matrix4 isometry_matrix_;
  Matrix4 rotation_;
  Vector3 translation_;
};

inline std::ostream &operator<<(std::ostream &ss,
                                const cppcourse::Isometry &iso) {
  ss << std::setprecision(9);
  return ss << "[T: " << iso.translation() << ", R:" << iso.rotation() << "]";
}
} // namespace cppcourse
