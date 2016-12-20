// MoveAnimEvent.cpp
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

#ifndef MOVEANIMEVENT_H
#define MOVEANIMEVENT_H

#include "UnitAnimEvent.h"

class Unit;
class Path;

/**
 *
 */
class MoveAnimEvent : public UnitAnimEvent {
 public:
  MoveAnimEvent(uint32_t p, Unit * un);
  virtual ~MoveAnimEvent();
  virtual void stop();
  virtual void run();
  virtual void update();
  virtual void setRange(uint32_t nr);

 private:
  uint32_t DefaultDelay;
  uint16_t BlockedCounter;
  bool stopping;
  void startMoveOne(bool wasblocked);
  void moveDone();
  uint16_t dest;
  uint16_t newpos;
  bool blocked;
  bool moved_half;
  bool pathinvalid;
  bool waiting;
  int8_t xmod;
  int8_t ymod;
  int8_t b_xmod;
  int8_t b_ymod;
  Unit* un;
  Path* path;
  uint8_t istep;
  uint8_t dir;
  uint32_t range;
};

#endif //MOVEANIMEVENT_H
