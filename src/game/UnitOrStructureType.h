// UnitOrStructureType.h
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

#ifndef UNITORSTRUCTURETYPE_H
#define UNITORSTRUCTURETYPE_H

#include <string>
#include <vector>

#include "armour_t.h"
#include "animinfo_t.h"

class Weapon;

/**
 * UnitOrStructureType is used when you can't or don't need to know whether you are dealing with a unit type or a structure
 * type.
 *
 * @note This class is abstract, it is used for performing casts.
 */
class UnitOrStructureType {
 public:
  UnitOrStructureType();
  virtual ~UnitOrStructureType();

  /** Turn speed is measured in arbitrary units */
  virtual uint8_t getTurnspeed() const = 0;

  /** Returns a number corresponding to the type's armour class. See armour_t.h for the enum definition */
  virtual armor_t getArmor() const = 0;

  /**
   * Returns number of layers to render, 1 or 2
   *
   * The only CnC structure that returns 2 is the weapons factory.
   * Units with turrets (tanks, humvee, buggy, missile launchers) return 2.
   */
  virtual uint8_t getNumLayers() const = 0;


  /** Only applicable to units.  StructureType always returns false. */
  virtual bool isInfantry() const = 0;

  /** @brief Return true if this Unit or Structure is a Wall */
  virtual bool isWall() const = 0;

  /** Only applicable to units.  StructureType always returns zero. */
  virtual uint8_t getOffset() const = 0;

  /** Returns the names of the sides that can build this */
  virtual std::vector<std::string> getOwners() const = 0;

  /** Returns whether the type is valid or not (loaded fully) */
  virtual bool isValid() const;

  /** Returns which production queue the type is for */
  virtual uint8_t getPQueue() const = 0;

  /** Returns the production type of this type. */
  uint8_t getPType() const;
  void setPType(uint8_t p);

  /** Calling a virtual function is much faster than a dynamic_cast */
  virtual bool isStructure() const = 0;

  /** Returns the prerequisites. */
  std::vector<std::string> getPrereqs() const;

  /** Return the technology level required to build this [-1 means can't build] (def=-1)*/
  int getTechLevel() const;

  /** Cost to build object (in credits).*/
  int getCost() const;

  /** Speed is measured in artitrary units. */
  uint8_t getSpeed() const;

  /** Returns the maximum health for this type. */
  uint16_t getMaxHealth() const;

  /** Sight range, in cells (def=1). */
  uint8_t getSight() const;

  /** Return the internal name of the structure/unit type like 'TSLA', 'PWR' ... */
  std::string getName() const;


  /**
   * Units and structures can have at most two weapons. Currently any secondary weapons are ignored.
   * @param primary if true return the first weapon else the second
   * @todo Write a version that accepts an armour type and returns the weapon that'll cause the most damage.
   */
  Weapon* getWeapon(bool primary) const;
  /** @brief Return by default the primary weapon */
  Weapon* getWeapon() const;

  Weapon* getPrimaryWeapon() const;
  Weapon* getSecondaryWeapon() const;

 protected:
  /** Sight of the Unit (in Cell) */
  uint8_t sight;
  animinfo_t animinfo;
  /** Armor of the Unit */
  armor_t armour;
  uint16_t maxhealth;
  uint8_t speed;
  /** Technology level required to build this [-1 means can't build] (default = -1) */
  int techLevel;
  std::vector<std::string> prereqs;

  bool valid;


  void setName(std::string pName);

  void setPrimaryWeapon(Weapon* theWeapon);
  void setSecondaryWeapon(Weapon* theWeapon);
  void setCost(int pCost);

 private:
  UnitOrStructureType(const UnitOrStructureType& orig);

  uint8_t ptype;
  /** Name of the Type */
  std::string tname;

  /** Secondary weapon of the Unit */
  Weapon* secondary_weapon;

  /** Primary weapon of the Unit */
  Weapon* primary_weapon;

  /** Coest of the unit or structure */
  int cost;
};

#endif //UNITORSTRUCTURETYPE_H
