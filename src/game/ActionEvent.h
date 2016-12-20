// ActionEvent.h
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

#ifndef ACTIONEVENT_H
#define ACTIONEVENT_H

#include <cstdint>

/**
 * An abstract class which all actionevents must extend.
 *
 * The run must be implemented.
 */
class ActionEvent {
 public:
  ActionEvent(uint32_t p);

  void addCurtick(uint32_t curtick);
  virtual void run();

  void setDelay(uint32_t p);

  uint32_t getPrio();

  virtual ~ActionEvent();
  virtual void stop();

 private:
  uint32_t prio;
  uint32_t delay;
};

#endif //ACTIONEVENT_H
