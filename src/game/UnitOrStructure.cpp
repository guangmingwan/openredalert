// UnitOrStructure.cpp
//
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

#include "UnitOrStructure.h"

#include "Logger.hpp"

void UnitOrStructure::remove() {
  deleted = true;
  if (references == 0) {
    delete this;
  }
}

bool UnitOrStructure::isAlive() {
  return !deleted;
}

void UnitOrStructure::select() {
  selected = true;
  showorder_timer = 0;
}

void UnitOrStructure::unSelect() {
  selected = false;
  showorder_timer = 0;
}

bool UnitOrStructure::isSelected() {
  return selected;
}

void UnitOrStructure::unrefer() {
  if (references > 0) {
    --references;
    if (deleted && references == 0) {
      delete this;
    }
  } else {
    Logger::getInstance()->Error("%s line %i: Unrefer while not refered \n");
  }
}

UnitOrStructure::~UnitOrStructure() {
  if (references != 0) {
    Logger::getInstance()->Error(__FILE__ , __LINE__, "%s line %i: References is not 0 \n");
  }
}

UnitOrStructure::UnitOrStructure() :
  references(0), deleted(false), selected(false), targetcell(0),
  target(0), showorder_timer(0) {
}

UnitOrStructure * UnitOrStructure::getTarget() {
  return target;
}

void UnitOrStructure::setYoffset(int8_t yo) {
}

void UnitOrStructure::setXoffset(int8_t xo) {
}

void UnitOrStructure::referTo() {
  ++references;
}

uint32_t UnitOrStructure::getExitCell() const {
  return 0;
}

uint16_t UnitOrStructure::getTargetCell() const {
  return targetcell;
}

uint16_t UnitOrStructure::getHealth() const {
  return health;
}

void UnitOrStructure::setHealth(uint16_t health) {
  this->health = health;
}

unsigned int UnitOrStructure::getOwner() const {
  return this->owner;
}

void UnitOrStructure::setOwner(unsigned int newowner) {
  this->owner = newowner;
}
