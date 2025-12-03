#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d v0 = std::get<0>(corners);
  Eigen::Vector3d v1 = std::get<1>(corners);
  Eigen::Vector3d v2 = std::get<2>(corners);

  Eigen::Vector3d e1 = v1 - v0;
  Eigen::Vector3d e2 = v2 - v0;

  Eigen::Vector3d h = ray.direction.cross(e2);
  double a = e1.dot(h);

  if (fabs(a) < 1e-8) return false; // parallel

  double f = 1.0 / a;
  Eigen::Vector3d s = ray.origin - v0;
  double u = f * s.dot(h);
  if (u < 0.0 || u > 1.0) return false;

  Eigen::Vector3d q = s.cross(e1);
  double v = f * ray.direction.dot(q);
  if (v < 0.0 || u + v > 1.0) return false;

  double t_temp = f * e2.dot(q);
  if (t_temp > min_t)
  {
    t = t_temp;
    n = e1.cross(e2).normalized();
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}


