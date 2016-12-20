// L2Overlay.cpp
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

#include "L2Overlay.h"

#include <vector>

/**
 * Create and size an overlay with a fixed number of images
 */
L2Overlay::L2Overlay(uint8_t numimages) {
  this->numimages = numimages;
  this->imagenums.resize(numimages);
  this->xoffsets.resize(numimages);
  this->yoffsets.resize(numimages);
}

/**
 * Get all images in the overlay
 */
uint8_t L2Overlay::getImages(uint32_t **images, int8_t **xoffs, int8_t **yoffs) {
  uint8_t i;
  *images = new uint32_t[numimages];
  *xoffs = new int8_t[numimages];
  *yoffs = new int8_t[numimages];
  for (i=0; i<numimages; ++i) {
    (*images)[i] = imagenums[i];
    (*xoffs)[i] = xoffsets[i];
    (*yoffs)[i] = yoffsets[i];
  }
  return numimages;
}
