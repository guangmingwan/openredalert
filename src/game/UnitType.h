// UnitType.h
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

#ifndef UNITTYPE_H
#define UNITTYPE_H

#include <vector>

#include "UnitOrStructureType.h"
#include "TalkbackType.h"

#define LOOPEND_TURN

class Weapon;
class Talkback;
class StructureType;
class WeaponsPool;
class INIFile;
class L2Overlay;

/**
 * Type of unit with stats
 */
class UnitType : public UnitOrStructureType {
 public:
  UnitType(const std::string& typeName, INIFile* unitini);
  ~UnitType();

  uint32_t *getSHPNums();
  uint8_t getNumLayers() const;
  bool isInfantry() const;
  uint8_t getType() const;
  uint16_t *getSHPTNum();

  virtual std::vector<std::string> getOwners() const;
  uint8_t getOffset() const;

  uint8_t getROT() const;
  int8_t getMoveMod() const;
  uint8_t getTurnMod() const;

  uint8_t getTurnspeed() const;

  armor_t getArmor() const;

#ifdef LOOPEND_TURN

  animinfo_t getAnimInfo() const
  {
    return animinfo;
  }
#endif

  const char* getRandTalk(TalkbackType type) const;

  bool isWall() const;
  bool canDeploy() const;
  std::string getDeployTarget() const;
  StructureType* getDeployType() const;
  uint8_t getBuildlevel() const;

  /** what colour pip should be displayed for this unit when being carried*/
  uint8_t getPipColour() const;
  uint8_t getMaxPassengers() const;
  std::vector<uint8_t> getPassengerAllow() const;
  std::vector<UnitType*> getSpecificTypeAllow() const;
  uint8_t getPQueue() const;
  bool isStructure() const;
  bool isDoubleOwned();
  /** C4 = Equipped with building sabotage explosives [presumes Infiltrate is true] (def=no)? */
  bool isC4() const;
  /** */
  bool isInfiltrate();
  /** */
  void setInfiltrate(bool infiltrate);

 private:
  uint32_t *shpnums;
  uint16_t *shptnum;
  /** In multi player both sides can use this unit */
  bool doubleowned;
  uint8_t numlayers;
  uint8_t turnspeed;
  uint8_t turnmod;
  uint8_t offset;
  uint8_t pipcolour;
  uint8_t buildlevel;
  uint8_t unittype;
  int8_t movemod;

  std::vector<std::string> owners;

  /** Talkback related members*/
  Talkback* talkback;

  /** <code>true</code> if this unit is an infantry */
  bool is_infantry;
  bool deployable;

  /** this is used to check the unit can deploy */
  StructureType* deploytype;

  /** max number of passenger */
  uint8_t maxpassengers;

  /** matches the unit's type value specified in units.ini*/
  std::vector<uint8_t> passengerAllow;

  /** matches the unit's type name.*/
  std::vector<UnitType*> specificTypeAllow;

  /**
   * C4 = Equipped with building sabotage explosives
   * [presumes Infiltrate is true] (def=no)?
   */
  bool c4;

  /**
   * Infiltrate = Can it enter a building like a spy or thief (def=no)?
   */
  bool infiltrate;
};

#endif //UNITTYPE_H
