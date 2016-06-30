#ifndef ROBOTICS_H
#define ROBOTICS_H
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/SVD>

using namespace Eigen;

#define PI (3.1415926)
#define eps (2.2204e-16)

Matrix3f hat(Vector3f w);
Vector3f unhat(Matrix3f w_hat);
Matrix3f expr(Vector3f w, float theta);
VectorXf logr(Matrix3f R);
Matrix4f expg(MatrixXf xi, float theta);
Matrix4f fwd_kin(MatrixXf xi, VectorXf theta, MatrixXf g0);
Matrix4f g(MatrixXf xi, VectorXf theta);
VectorXf logg(MatrixXf g);
MatrixXf Adjoint(MatrixXf g);
MatrixXf pinv(MatrixXf MatIn);
#endif // ROBOTICS_H

