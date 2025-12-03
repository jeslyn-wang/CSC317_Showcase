#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Implement ray-plane intersection.
  // Return true if there is an intersection and update t and n.
  // Return false if there is no intersection.
  double denom = normal.dot(ray.direction);
  if (denom == 0) {
    return false; // Ray is parallel to the plane
  }
  double numer = normal.dot(point - ray.origin);
  double t_temp = numer / denom;
  if (t_temp >= min_t) {
    t = t_temp;
    n = normal.normalized(); // Ensure the normal is unit length
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

