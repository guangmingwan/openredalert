// UnitOrStructureType.cpp
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

#include "UnitOrStructureType.h"

#include <string>
#include <vector>

UnitOrStructureType::UnitOrStructureType() :
ptype(0),
valid(false)
{
}

UnitOrStructureType::~UnitOrStructureType() {
}

uint8_t UnitOrStructureType::getPType() const {
  return ptype;
}

void UnitOrStructureType::setPType(uint8_t p) {
  ptype = p;
}

bool UnitOrStructureType::isValid() const {
  return valid;
}

std::vector<std::string> UnitOrStructureType::getPrereqs() const {
  return prereqs;
}

/**
 * @return Technology level
 */
int UnitOrStructureType::getTechLevel() const {
  return techLevel;
}

int UnitOrStructureType::getCost() const {
  return cost;
}

uint8_t UnitOrStructureType::getSpeed() const {
  return speed;
}

uint16_t UnitOrStructureType::getMaxHealth() const {
  return maxhealth;
}

uint8_t UnitOrStructureType::getSight() const {
  return sight;
}

std::string UnitOrStructureType::getName() const {
  return tname;
}

void UnitOrStructureType::setName(std::string pName) {
  this->tname = pName;
}

/**
 * Return the Primary weapon
 *
 * @return Reference to the primary weapon
 * @see Weapon
 */
Weapon * UnitOrStructureType::getWeapon() const {
  // Return Reference to the Primary weapon
  return getWeapon(true);
}

/**
 * Return the weapon of the structure wanted
 *
 * @param primary if true select the primary weapon else return the secondary
 * @return Reference to the selected weapon
 * @see Weapon
 */
Weapon * UnitOrStructureType::getWeapon(bool primary) const {
  if (primary) {
    return this->getPrimaryWeapon();
  } else {
    return this->getSecondaryWeapon();
  }
}

Weapon* UnitOrStructureType::getPrimaryWeapon() const {
  return this->primary_weapon;
}

Weapon* UnitOrStructureType::getSecondaryWeapon() const {
  return this->secondary_weapon;
}

void UnitOrStructureType::setPrimaryWeapon(Weapon* value) {
  if (this->tname == "WEAP") {
    //        int a = 0;
  }
  this->primary_weapon = value;
}

void UnitOrStructureType::setSecondaryWeapon(Weapon* value) {
  this->secondary_weapon = value;
}

void UnitOrStructureType::setCost(int pCost) {
  this->cost = pCost;
}
