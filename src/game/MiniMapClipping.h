// MiniMapClipping.h
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

#ifndef MINIMAPCLIPPING_H
#define MINIMAPCLIPPING_H

/**  */
class MiniMapClipping {
 public:
  uint16_t x;
  uint16_t y;
  uint16_t w;
  uint16_t h;
  uint16_t sidew;
  uint16_t sideh;
  uint8_t tilew;
  uint8_t tileh;
  uint8_t pixsize;
};

#endif //MINIMAPCLIPPING_H
