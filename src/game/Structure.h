// Structure.h
// 1.2
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

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <string>

#include "UnitOrStructure.h"

class StructureType;
class UnitType;
class BuildingAnimEvent;
class BAttackAnimEvent;
class BRepairUnitAnimEvent;
class DoorAnimEvent;

/**
 * Building in game
 */
class Structure : public UnitOrStructure {
 public:
  friend class BuildingAnimEvent;
  friend class BAttackAnimEvent;
  friend class BRepairUnitAnimEvent;
  friend class DoorAnimEvent;

  Structure(StructureType *type, uint16_t cellpos, unsigned int owner, uint16_t rhealth,
            uint8_t facing, std::string trigger_name);
  ~Structure();

  uint8_t getImageNums(uint32_t **inums, int8_t **xoffsets, int8_t **yoffsets);
  uint16_t* getImageNums() const;
  void changeImage(uint8_t layer, int16_t imagechange);
  /** Return the actual current image number (without side color etc)*/
  uint32_t getRealImageNum(uint8_t layer);
  uint32_t getImageNum(uint8_t layer) const;
  uint16_t getNumbImages(uint8_t layer);
  void setImageNum(uint32_t num, uint8_t layer);
  UnitOrStructureType* getType();
  void setStructnum(uint32_t stn);
  uint32_t getNum() const;
  uint16_t getBPos(uint16_t curpos) const;
  uint16_t getFreePos(uint8_t* subpos, bool findsubpos);
  void remove();

  unsigned int getPos() const;
  unsigned int getSubpos() const;

  void applyDamage(int16_t amount, Weapon* weap, UnitOrStructure* attacker);
  void runAnim(uint32_t mode);
  void runSecAnim(uint32_t param, bool extraParam = false);
  void stopAnim();
  void stop();
  uint8_t getOwner() const;
  void setOwner(uint8_t newowner);
  bool canAttack() const;

  bool IsAttacking();
  bool IsBuilding();

  void attack(UnitOrStructure* target);

  uint16_t getHealth() const;
  void ChangeHealth(int16_t amount);

  int8_t getXoffset() const;
  int8_t getYoffset() const;

  bool isPowered();

  bool isRefinery(void);

  bool CreateUnitAnimation(UnitType* UnType, uint8_t owner);

  double getRatio() const;
  bool isPrimary() const;
  void setPrimary(bool pri);
  bool RepairUnint(Unit *Un);

  uint32_t getExitCell() const;
  void resetLoadState(bool runsec, uint32_t param);
  bool checkdamage();
  uint16_t getTargetCell() const;

  bool is(std::string Name);

  void sell();

  void repair();
  bool isRepairing();
  void repairDone();

  /** Use to bomb a structure */
  void bomb();
  /** Get if the C4 is here :( */
  bool isBombing();
  /** */
  void bombingDone();

  bool underAttack();
  uint16_t getAttackerPosition();

  std::string getTriggerName();

  static bool valid_pos(StructureType *type, uint8_t PlayerNr, uint16_t pos,
                        uint8_t*);
  static bool valid_possubpos(StructureType *type, uint8_t PlayerNr,
                              uint16_t pos, uint8_t* subpos);

 private:
  std::string TriggerName;
  StructureType *type;
  uint32_t structnum;
  uint16_t *imagenumbers;

  unsigned int cellpos;
  uint16_t bcellpos;
  uint16_t health;

  unsigned int owner;

  bool damaged;
  bool animating;
  bool usemakeimgs;
  bool exploding;
  bool primary;

  /** health/maxhealth */
  double ratio;
  /** If we stop a loop animation because of a repair animation
   we use this var to start the loop animation again */
  uint8_t backup_anim_mode;

  bool retry_sell;
  bool retry_repair;
  bool retry_bombing;
  bool repairing;
  bool bombing;

  UnitType* CreateUnitType;
  unsigned int CreateUnitOwner;
  uint32_t UnitToRepairPos;
  uint32_t LastAttackTick;
  
  BuildingAnimEvent* buildAnim;
  BAttackAnimEvent* attackAnim;
  BRepairUnitAnimEvent* repairunitAnim;
};

#endif //STRUCTURE_H
