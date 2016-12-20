// StructureType.h
// 1.5
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

#ifndef STRUCTURETYPE_H
#define STRUCTURETYPE_H

#include <string>
#include <vector>

#include "UnitOrStructureType.h"
#include "PowerInfo.h"

#include "armour_t.h"
#include "animinfo_t.h"

class INIFile;
class Weapon;

/**
 * Base class for structure in game
 */
class StructureType : public UnitOrStructureType {
 public:
  /** Constructor */
  StructureType(const std::string& typeName, INIFile* structini, INIFile* artini,
                const std::string& thext);
  ~StructureType();

  uint16_t *getSHPNums();

  uint16_t *getSHPTNum();

  std::vector<std::string> getDeployWith() const;

  std::vector<std::string> getOwners() const;

  uint8_t getNumLayers() const;

  uint16_t getMakeImg() const;

  /** Only applicable to structures.  UnitType always returns false. */
  bool isWall() const;

  bool isWaterBound() const;

  bool hasAirBoundUnits() const;

  uint8_t getXsize() const;

  uint8_t getYsize() const;

  uint8_t isBlocked(uint16_t tile) const;

  int8_t getXoffset() const;

  int8_t getYoffset() const;

  uint8_t getOffset() const;

  uint8_t getTurnspeed() const;

  /**
   * Surcharge speed with 0 (because it's a building).
   */
  uint8_t getSpeed() const;

  armor_t getArmor() const;

  animinfo_t getAnimInfo() const;

  PowerInfo getPowerInfo() const;

  bool isPowered();

  bool hasTurret() const;

  uint16_t getBlckOff() const;

  bool isInfantry() const;

  uint8_t getNumWallLevels() const;

  uint8_t getDefaultFace() const;

  uint8_t getBuildlevel() const;

  bool primarySettable() const;

  bool Charges();

  uint8_t getPQueue() const;

  bool isStructure() const;

  uint32_t getAdjacent() const;

 private:
  StructureType(const StructureType& orig);

  /** Index in the ImagePool of the first MAKE image */
  uint16_t makeimg;
  uint16_t blckoff;
  int8_t xoffset;
  int8_t yoffset;
  uint8_t turnspeed;
  uint8_t xsize;
  uint8_t ysize;
  uint8_t numshps;
  uint8_t numwalllevels;
  uint8_t defaultface;
  uint8_t buildlevel;
  uint8_t * blocked;

  std::vector<std::string> owners;
  std::vector<std::string> deploywith;
  PowerInfo powerinfo;

  bool is_wall;
  bool turret;
  bool primarysettable;
  bool charges;
  bool WaterBound;
  bool AirBoundUnits;
  uint16_t* shptnum;
  uint16_t* shpnums;
  
  /** Adjacent = distance allowed to place from other buildings (def=1) */
  uint32_t adjacent;
};

#endif
