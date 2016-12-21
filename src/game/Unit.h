// Unit.h
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

#ifndef UNIT_H
#define UNIT_H

#define LOOPEND_TURN

#include <string>
#include <map>
#include <vector>
#include <stack>
#include <time.h>

#include "game/TalkbackType.h"
#include "UnitOrStructure.h"
#include "Weapon.h"
#include "Structure.h"
#include "TalkbackType.h"
#include "UInfiltrateAnimEvent.h"
#include "AiCommand.h"

class CnCMap;
class L2Overlay;
class WalkAnimEvent;
class MoveAnimEvent;
class URepairEvent;
class UHarvestEvent;
class UAttackAnimEvent;
class TurnAnimEvent;
class ActionEventQueue;
class INIFile;
class WeaponsPool;
class InfantryGroup;

//namespace OpenRedAlert { namespace Game { class UnitType; }}
//namespace OpenRedAlert { namespace Game { class UnitOrStructureType; }}

/**
 * Unit in game
 */
class Unit : public UnitOrStructure {
 public:
  friend class MoveAnimEvent;
  friend class UAttackAnimEvent;
  friend class TurnAnimEvent;
  friend class WalkAnimEvent;
  friend class UHarvestEvent;
  friend class URepairEvent;
  friend class UInfiltrateAnimEvent;

  Unit(UnitType *type, uint16_t cellpos, uint8_t subpos, InfantryGroup *group,
       unsigned int owner, uint16_t rhealth, uint8_t facing, uint8_t action,
       std::string trigger_name);
  ~Unit();

  uint8_t getImageNums(uint32_t **inums, int8_t **xoffsets, int8_t **yoffsets);
  InfantryGroup * getInfantryGroup();
  void setInfantryGroup(InfantryGroup *ig);
  uint32_t getImageNum(uint8_t layer) const;
  uint16_t getNumbImages(uint8_t layer);

  /** Set the number of the image in a layer */
  void setImageNum(uint32_t num, uint8_t layer);
  int8_t getXoffset() const; // return xoffset-type->getOffset();
  int8_t getYoffset() const; // return yoffset-type->getOffset();
  void setXoffset(int8_t xo);
  void setYoffset(int8_t yo);
  UnitOrStructureType * getType();

  unsigned int getPos() const;
  unsigned int getSubpos() const;

  uint16_t getBPos(uint16_t pos) const;
  uint32_t getNum() const;
  void setUnitnum(uint32_t unum);

  void ChangeHealth(int16_t amount);

  /** Command to the Unit to move at a destination */
  void move(uint16_t dest);
  void move(uint16_t dest, bool needStop);
  bool IsMoving(void);
  bool IsAttacking(void);
  bool canAttack(bool primary = true);
  bool UnderAttack(void);
  void attack(UnitOrStructure* target);
  void attack(UnitOrStructure* target, bool stop);
  void turn(uint8_t facing, uint8_t layer);
  void stop();

  void remove();
  void applyDamage(int16_t amount, Weapon* weap, UnitOrStructure* attacker);
  void updateDamaged();

  bool IsHarvester();
  bool IsHarvesting();
  uint32_t FindTiberium();
  void Harvest(uint32_t pos, Structure *Struct);
  bool Repair(Structure *str);

  void doRandTalk(TalkbackType ttype);
  /** Command deploy to Unit */
  bool deploy();
  /** Check if the unit can deploy */
  bool canDeploy(CnCMap* theMap);
  /** Check if the position in this map is ok to deploy for the unit deploy type */
  bool checkDeployTarget(CnCMap* theMap, uint32_t pos);
  uint32_t calcDeployPos() const;
  uint32_t calcDeployPos(uint32_t pos) const;
  uint32_t getExitCell() const;
  double getRatio() const;
  uint16_t getDist(uint16_t pos);
  uint16_t getTargetCell();

  Structure *GetBaseRefinery();
  void SetBaseRefinery(Structure *Bref);

  void AddResource(uint8_t ResourceType);

  void EmptyResources(void);

  uint8_t GetNumResources(void);

  bool GetResourceType(uint8_t Numb, uint8_t *Type);

  uint32_t GetFixStr(void);

  uint16_t GetFixPos(void);

  bool IsAirBound(void);

  bool IsWaterBound(void);

  // The folowing var's are used by the AI
  uint8_t AI_Mission; // This tells the AI if this unit has a mission and what mission it is...
  /** The location whitch needs garding */
  uint32_t AI_GuardLocation;
  /** List of command during Ai management */
  std::vector<AiCommand*> aiCommandList;

  std::string getTriggerName();

  /** Get the infiltrate Animation */
  UInfiltrateAnimEvent* getInfianim();
  /** Set the infiltrate Animation */
  void setInfianim(UInfiltrateAnimEvent* anim);

  /** Action to infiltrate */
  void Infiltrate(Structure* target);

 private:
  int8_t yoffset;
  std::string TriggerName;
  UnitType* type;
  uint32_t unitnum;
  /** Then structure number of fix (for repairing this unit) */
  uint32_t fix_str_num;
  uint16_t fix_str_pos;
  uint16_t *imagenumbers;
  uint16_t cellpos;
  uint16_t palettenum;

  uint8_t subpos;
  int8_t xoffset;
  bool deployed;
  double ratio;

  uint32_t LastDamageTick;

  L2Overlay* l2o;
  std::multimap<uint16_t, L2Overlay*>::iterator l2entry;

  InfantryGroup* infgrp;

  MoveAnimEvent* moveanim;
  URepairEvent* repairanim;
  UAttackAnimEvent* attackanim;
  UHarvestEvent* harvestanim;
  WalkAnimEvent* walkanim;
  TurnAnimEvent* turnanim1;
  TurnAnimEvent* turnanim2;

  UInfiltrateAnimEvent* infianim;

  Structure* BaseRefinery;

  /** Number of pieces resource in harvester */
  uint8_t NumbResources;
  /** Resource type in harvester */
  uint8_t ResourceTypes[10];

  /** The command this unit should execute */
  uint8_t Command;
  uint32_t LastAttackTick;
};

#endif //UNIT_H
