// WalkAnimEvent.h
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

#ifndef WALKANIMEVENT_H
#define WALKANIMEVENT_H

#include "UnitAnimEvent.h"
#include "Unit.h"

class WalkAnimEvent : public UnitAnimEvent {
 public:
  WalkAnimEvent(uint32_t p, Unit * un, uint8_t dir, uint8_t layer);
  virtual ~WalkAnimEvent();
  virtual void stop();
  virtual void run();
  virtual void changedir(uint8_t ndir);
  void update();

 private:
  bool stopping;
  void calcbaseimage(void);
  Unit * un;
  uint8_t dir;
  uint8_t istep;
  uint8_t layer;
  uint8_t baseimage;
};

#endif //WALKANIMEVENT_H
