#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  std::ofstream ofs(filename);
    if (!ofs) {
        return false;
    }

    if (num_channels == 1) {
        // Grayscale → P2
        ofs << "P2\n" << width << " " << height << "\n255\n";
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int idx = (y * width + x);
                ofs << (int)data[idx] << " ";
            }
            ofs << "\n";
        }
    } 
    else if (num_channels >= 3) {
        // RGB → P3
        ofs << "P3\n" << width << " " << height << "\n255\n";
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int idx = (y * width + x) * num_channels;
                ofs << (int)data[idx + 0] << " "
                    << (int)data[idx + 1] << " "
                    << (int)data[idx + 2] << " ";
            }
            ofs << "\n";
        }
    } 
    else {
        return false; // unsupported channel count
    }

    return true;
  ////////////////////////////////////////////////////////////////////////////
}
