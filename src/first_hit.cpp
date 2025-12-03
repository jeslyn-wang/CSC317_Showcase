#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  bool hit = false;
  double closest_t = std::numeric_limits<double>::infinity();
  Eigen::Vector3d temp_n;

  for (int i = 0; i < objects.size(); ++i)
  {
    double temp_t;
    if (objects[i]->intersect(ray, min_t, temp_t, temp_n))
    {
      if (temp_t < closest_t)
      {
        hit = true;
        closest_t = temp_t;
        hit_id = i;
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
