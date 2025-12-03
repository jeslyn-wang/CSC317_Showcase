#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d oc = ray.origin - center;
  double a = ray.direction.dot(ray.direction); // should be 1 if normalized
  double b = 2.0 * oc.dot(ray.direction);
  double c = oc.dot(oc) - radius * radius;
  double discriminant = b*b - 4*a*c;

  if (discriminant < 0) return false;
  
  double sqrt_d = std::sqrt(discriminant);
  double t1 = (-b - sqrt_d) / (2.0*a);
  double t2 = (-b + sqrt_d) / (2.0*a);
  // printf("t1: %f, t2: %f\n", t1, t2);

  double t_candidate = (t1 >= min_t) ? t1 : (t2 >= min_t ? t2 : -1);

  if (t_candidate < 0) return false;
  // printf("t_candidate: %f\n", t_candidate);

  t = t_candidate;
  Eigen::Vector3d p = ray.origin + t*ray.direction;
  n = (p - center).normalized();
  if (n.dot(ray.direction) > 0) n = -n; // optional flip
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

