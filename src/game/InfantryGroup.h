// InfantryGroup.h
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

#ifndef INFANTRYGROUP_H
#define INFANTRYGROUP_H

#include <cstdint>

class Unit;

/**
 * This should be a member of unit for infantry. When an infantry unit walks
 * into a previously empty cell a new group is created, otherwise the existing group is used.
 * We need one more bit in the unit/structure matrix to tell if infantry is in that cell.
 * @todo: Implement group reuse, or just scrap this in favour of something that
 * won't cause lots of allocations and deallocations whilst moving infantry.
 */
class InfantryGroup {
 public:
  InfantryGroup();
  ~InfantryGroup();
  bool AddInfantry(Unit* inf, uint8_t subpos);
  bool RemoveInfantry(unsigned int subpos);
  bool IsClear(uint8_t subpos);
  uint8_t GetNumInfantry() const;
  bool IsAvailable() const;
  uint8_t GetFreePos() const;
  Unit * UnitAt(uint8_t subpos);

  uint8_t GetImageNums(uint32_t **inums, int8_t **xoffsets, int8_t **yoffsets);
  void GetSubposOffsets(uint8_t oldsp, uint8_t newsp, int8_t *xoffs, int8_t *yoffs);
  static const int8_t *GetUnitOffsets();
  Unit *GetNearest(uint8_t subpos);
 private:
  Unit* positions[5];
  uint8_t numinfantry;
  static const int8_t unitoffsets[];
};

#endif //INFANTRYGROUP_H
