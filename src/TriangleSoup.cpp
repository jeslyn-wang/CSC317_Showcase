#include "TriangleSoup.h"
#include "Triangle.h"
#include "first_hit.h"
bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  bool hit = false;
  double closest_t = std::numeric_limits<double>::infinity();
  Eigen::Vector3d temp_n; // temporary normal
  for (const auto & triangle : triangles)
  {
    double temp_t;
    if (triangle->intersect(ray, min_t, temp_t, temp_n))
    {
      if (temp_t < closest_t)
      {
        hit = true;
        closest_t = temp_t;
        n = temp_n;
      }
    }
  }
  if (hit)
  {
    t = closest_t;
  }
  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
