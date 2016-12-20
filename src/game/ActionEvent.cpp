// ActionEvent.cpp
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

#include "ActionEvent.h"

void ActionEvent::stop() {
}

ActionEvent::ActionEvent(uint32_t p) {
  delay = p;
}

void ActionEvent::addCurtick(uint32_t curtick) {
  prio = delay + curtick;
}

void ActionEvent::run() {
}

ActionEvent::~ActionEvent() {
}

void ActionEvent::setDelay(uint32_t p) {
  delay = p;
}

uint32_t ActionEvent::getPrio() {
  return prio;
}
