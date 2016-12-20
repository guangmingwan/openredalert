// PowerInfo.h
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

#ifndef POWERINFO_H
#define POWERINFO_H

/**
 * Power information of a structure
 */
class PowerInfo {
 public:
  /** How much power the structure provide */
  uint16_t power;
  /** How much power the structure drain */
  uint16_t drain;
  /** Does this structure needs power to works ? (if yes the structure doesn't works when there are not enought power) */
  bool powered;
};

#endif //POWERINFO_H
