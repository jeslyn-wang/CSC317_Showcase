#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Set ray.origin to the camera position.
  ray.origin = camera.e;

  // pixel (i,j) on the image plane.
  // pixel center in normalized device coords for different resolutions
  const double px_ndc = (static_cast<double>(j) + 0.5) / static_cast<double>(width);
  const double py_ndc = (static_cast<double>(i) + 0.5) / static_cast<double>(height);

  // map to image plane coordinates (centered at 0)
  const double x = (px_ndc - 0.5) * camera.width;
  const double y = (0.5 - py_ndc) * camera.height; // flip Y because i grows downward
  const double z = -camera.d; // positive forward

  // world-space direction (offset from camera position)
  Eigen::Vector3d dir = camera.u * x + camera.v * y + camera.w * z;

  ray.direction = dir.normalized();
  ////////////////////////////////////////////////////////////////////////////
}
