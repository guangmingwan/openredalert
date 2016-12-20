// Dune2Header.h
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

#ifndef DUNE2HEADER_H
#define DUNE2HEADER_H

#include <cstdint>

class Dune2Header {
 public:
  uint16_t compression;
  uint8_t  cy;
  uint16_t cx;
  uint8_t  cy2;
  uint16_t size_in;
  uint16_t size_out;
};

#endif //DUNE2HEADER_H
