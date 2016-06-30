#include "robotics.h"
#include <iostream>
#include <math.h>

using namespace std;

Matrix3f hat(Vector3f w)
{
    Matrix3f w_hat;
    w_hat.setZero();
    w_hat(0,1) = -w(2);
    w_hat(0,2) = w(1);
    w_hat(1,0) = w(2);
    w_hat(1,2) = -w(0);
    w_hat(2,0) = -w(1);
    w_hat(2,1) = w(0);
    return w_hat;
}

Vector3f unhat(Matrix3f w_hat)
{
    Vector3f w;
    w(0)=-w_hat(1,2);
    w(1)=w(0,2);
    w(2)=-w(0,1);
    return w;
}

Matrix3f expr(Vector3f w, float theta)
{
    float n = w.norm();
    Matrix3f R;
    if(n<eps)
    {
        R = MatrixXf::Identity(3,3);
    }
    else
    {
        theta = theta*n;
        w = w/n;
        R = MatrixXf::Identity(3,3) + hat(w)*sin(theta) + hat(w)*hat(w)*(1-cos(theta));
    }
    return R;
}
/*
 * return [w,theta]'
*/
VectorXf logr(Matrix3f R)
{
    int t = R.trace();
    float theta;
    Vector3f w;
    if(t>=3)
    {
        /* no rotation */
        w<<0,0,0;
        theta = 0;
    }
    else if(t<=-1)
    {
        /* 180 deg */
        theta = PI;
        w<<sqrt((R(0,0)+1)/2),sqrt((R(1,1)+1)/2),sqrt((R(2,2)+1)/2);
    }
    else
    {
        /* non-trivial case */
        theta = acos((t-1)/2);
        w<<R(2,1)-R(1,2),R(0,2)-R(2,0),R(1,0)-R(0,1);
        w=w/(2*sin(theta));
    }
    VectorXf out;
    out.resize(4);
    out<<w,theta;
    return out;
}

Matrix4f expg(MatrixXf xi, float theta)
{
    Vector3f v(xi(0),xi(1),xi(2));
    Vector3f w(xi(3),xi(4),xi(5));
    float n = w.norm();
    Matrix3f R;
    Vector3f P;

    if(n<eps)
    {
        R.setIdentity(3,3);
        P = v*theta;
    }
    else
    {
        theta = theta*n;
        w=w/n;
        v=v/n;
        R=expr(w,theta);
        P=(MatrixXf::Identity(3,3)-R)*hat(w)*v + w*w.transpose()*theta*v;
    }
    MatrixXf g(4,4);
    g<<R(0,0),R(0,1),R(0,2),P(0),
            R(1,0),R(1,1),R(1,2),P(1),
            R(2,0),R(2,1),R(2,2),P(2),
            0,0,0,1;
    return g;
}

Matrix4f fwd_kin(MatrixXf xi, VectorXf theta, MatrixXf g0)
{
    int n = theta.size();
    Matrix4f g;
    g.setIdentity();
    for(int i=0;i<n;i++)
    {
        g = g*expg(xi.col(i),theta(i));
    }
    g = g*g0;
    return g;
}

Matrix4f g(MatrixXf xi, VectorXf theta)
{
    int n = theta.size();
    Matrix4f g;
    g.setIdentity();
    for(int i=0;i<n;i++)
    {
        g = g*expg(xi.col(i),theta(i));
    }
    return g;
}

VectorXf logg(MatrixXf g)
{
    Matrix3f R = g.block<3,3>(0,0);
    Vector3f P = g.block<3,1>(0,3);
    VectorXf w_theta;
    w_theta.resize(4);
    w_theta = logr(R);
    float theta = w_theta(3);
    Vector3f w = w_theta.head(3);
    Vector3f v;
    if(theta<eps)
    {
        theta = P.norm();
        if(theta < eps)
            v<<0,0,0;
        else
            v=P/theta;
    }
    else
    {
        Matrix3f invA = MatrixXf::Identity(3,3)/theta - hat(w)/2 + hat(w)*hat(w)*(2*sin(theta)-theta*(1+cos(theta)))/(2*theta*sin(theta));
        v = invA*P;
    }
    VectorXf xi;
    xi.resize(6);
    xi<<v,w;
    VectorXf output;
    output.resize(7);
    output<<xi,theta;
    return output;
}

MatrixXf Adjoint(MatrixXf g)
{
    Matrix3f R = g.block<3,3>(0,0);
    Vector3f P = g.block<3,1>(0,3);
    MatrixXf Adg;
    Adg.resize(6,6);
    Adg<<R,hat(P)*R,MatrixXf::Zero(3,3),R;
    return Adg;
}



