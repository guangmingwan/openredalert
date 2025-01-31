// L2Overlay.h
// 1.0
//    This file is part of OpenRedAlert.
//
//    OpenRedAlert is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, version 2 of the License.
//
//    OpenRedAlert is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with OpenRedAlert.  If not, see <http://www.gnu.org/licenses/>.

#ifndef L2OVERLAY_H
#define L2OVERLAY_H

#include <vector>
#include <cstdint>
/**
 */
class L2Overlay {
 public:
  /** Create and size an overlay with a fixed number of images */
  L2Overlay(uint8_t numimages);
  /** Get all images in the overlay */
  uint8_t getImages(uint32_t** images, int8_t** xoffs, int8_t** yoffs);

  uint16_t cellpos;
  std::vector<uint32_t> imagenums;
  std::vector<int8_t> xoffsets;
  std::vector<int8_t> yoffsets;
  uint8_t numimages;
};

#endif //L2OVERLAY_H
