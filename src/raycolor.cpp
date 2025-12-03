#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  double t;
  Eigen::Vector3d n;
  int hit_id;

  if (first_hit(ray, min_t, objects, hit_id, t, n))
  {
    std::shared_ptr<Object> hit_object = objects[hit_id];
    Eigen::Vector3d hit_point = ray.origin + t * ray.direction;

    rgb = Eigen::Vector3d::Zero();

    // Call the correct Blinn-Phong function
    rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);

    // Reflection
    if (num_recursive_calls < 5 && hit_object->material->km.norm() > 1e-6)
    {
      Eigen::Vector3d reflected_dir = reflect(ray.direction, n).normalized();
      Ray reflected_ray;
      reflected_ray.origin = hit_point + 1e-6 * n;
      reflected_ray.direction = reflected_dir;

      Eigen::Vector3d reflected_color;
      if (raycolor(reflected_ray, 1e-6, objects, lights,
                   num_recursive_calls + 1, reflected_color))
      {
        rgb += hit_object->material->km.cwiseProduct(reflected_color);
      }
    }

    rgb = rgb.cwiseMax(0.0).cwiseMin(1.0);
    return true;
  }

  rgb = Eigen::Vector3d::Zero();
  return false;
}