// UHarvestEvent.h
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

#ifndef UHARVESTEVENT_H
#define UHARVESTEVENT_H

#include "UnitAnimEvent.h"

#define HARVEST_RETURN_STEP_1	1
#define HARVEST_RETURN_STEP_2	2
#define HARVEST_RETURN_STEP_3	3
#define HARVEST_RETURN_STEP_4	4

class Unit;
class UnitOrStructure;

/**
 * Animation played when harvester is harvesting
 */
class UHarvestEvent : public UnitAnimEvent {
 public:
  UHarvestEvent(uint32_t p, Unit * un);
  virtual ~UHarvestEvent();

  void stop();
  void setHarvestingPos(uint32_t pos);
  virtual void update();
  virtual void run();

 private:
  int GetBaseRefineryPos();

  uint16_t RetryMoveCounter;
  /** this is used to empty the truck when it is not full jet. */
  bool ForceEmpty;
  uint8_t ReturnStep;
  bool new_orgimage;
  Unit* un;
  bool stopping;
  bool manual_pauze;
  UnitOrStructure * target;
  int index;
  int delay;
  int facing;
  uint32_t MoveTargePos;
  uint32_t OrgImage;
  /** Number of pieces resource in harvester */
  uint8_t NumbResources;
  /** Resource type in harvester */
  uint8_t ResourceTypes[10];
};

#endif //UHARVESTEVENT_H
