#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include "reflect.h"
#include "raycolor.h"
#include <algorithm> 

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  //add code implementation here:
  std::shared_ptr<Object> hit_object = objects[hit_id];
    Eigen::Vector3d hit_point = ray.origin + t * ray.direction;
    Eigen::Vector3d rgb = Eigen::Vector3d::Zero();

    // Ambient 
    rgb += 0.1 * hit_object->material->ka;

    // Direct illuminatio  
    for (const auto &light : lights)
    {
        Eigen::Vector3d light_dir;
        double max_t;
        light->direction(hit_point, light_dir, max_t);
        light_dir.normalize(); // just in case

        // Shadow ray
        Ray shadow_ray;
        shadow_ray.origin = hit_point + 1e-6 * n;
        shadow_ray.direction = light_dir;

        int shadow_id;
        double shadow_t;
        Eigen::Vector3d shadow_n;

        bool in_light = !first_hit(shadow_ray, 1e-6, objects, shadow_id, shadow_t, shadow_n) 
                        || shadow_t > max_t;

        if (in_light)
        {
            Eigen::Vector3d light_intensity = light->I;

            // Diffuse
            double diff = std::max(0.0, n.dot(light_dir));
            Eigen::Vector3d diffuse = hit_object->material->kd.cwiseProduct(light_intensity) * diff;

            // Specular (Blinn-Phong)
            Eigen::Vector3d view_dir = -ray.direction.normalized();
            Eigen::Vector3d half_vector = (view_dir + light_dir).normalized();
            double spec_angle = std::max(0.0, n.dot(half_vector));
            Eigen::Vector3d specular = hit_object->material->ks.cwiseProduct(light_intensity) 
                                       * std::pow(spec_angle, hit_object->material->phong_exponent);

            rgb += diffuse + specular;
        }
    }

    rgb = rgb.cwiseMax(0.0).cwiseMin(1.0);

    return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
