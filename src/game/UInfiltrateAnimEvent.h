// UInfiltrateAnimEvent.h
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

#ifndef UINFILTRATEANIMEVENT_H
#define UINFILTRATEANIMEVENT_H

#include "UnitAnimEvent.h"

class Unit;
class UnitOrStructure;

/**
 * Unit animation use to make an infiltration
 */
class UInfiltrateAnimEvent : public UnitAnimEvent {
 public:
  UInfiltrateAnimEvent(uint32_t p, Unit *un);
  virtual ~UInfiltrateAnimEvent();
  void stop();
  virtual void update();
  virtual void run();

 private:
  Unit* un;
  bool stopping;
  uint8_t waiting;
  UnitOrStructure* target;
};

#endif //UINFILTRATEANIMEVENT_H
