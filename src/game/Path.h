// Path.h
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

#ifndef PATH_H
#define PATH_H

#include <stack>
#include<cstdint>
class Unit;

/**
 *
 */
class Path : public std::stack<uint8_t> {
 public:
  Path(Unit* unit, uint32_t crBeg, uint32_t crEnd, uint8_t max_dist);
  ~Path();
};

#endif //PATH_H
