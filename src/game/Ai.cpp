// Ai.cpp
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

#include "Ai.h"

#include <stdexcept>
#include <cmath>
#include <sstream>

#include "Logger.h"
#include "ActionEventQueue.h"
#include "CnCMap.h"
#include "PlayerPool.h"
#include "UnitAndStructurePool.h"
#include "Dispatcher.h"
#include "GameMode.h"
#include "UnitOrStructure.h"
#include "Structure.h"
#include "pside.h"
#include "Player.h"
#include "AiRules.h"
#include "Unit.h"
#include "misc/INIFile.h"
#include "audio/SoundEngine.h"
#include "UnitType.h"
#include "StructureType.h"

#define DEBUG_AI

namespace p {
  extern CnCMap* ccmap;
  extern UnitAndStructurePool* uspool;
  extern Dispatcher* dispatcher;
}

/**
 *  AI constructor
 */
Ai::Ai() {
  this->Difficulty = 1;
  LplayerBasePos = 0;
  guide = false;

  NumbPlayers = p::ccmap->getPlayerPool()->getNumPlayers();

  for (unsigned int i = 0; i < (unsigned)NumbPlayers; i++) {
    LastGuideTickCount.push_back(SDL_GetTicks());
    LastBuildTickCount.push_back(SDL_GetTicks());
    LastAttackTickCount.push_back(SDL_GetTicks());
    LastDefendTickCount.push_back(SDL_GetTicks());
    LastHarvestTickCount.push_back(SDL_GetTicks());
    LastGuideGatherTickCount.push_back(SDL_GetTicks());
    RetryDeploy.push_back(false);
    player_targets.push_back(0);
    UnitBuildMultiplexer.push_back(0);
  }
  //  AiDifficultyTimer.Start();

  // Create Rules
  Rules = new AiRules();


  /// Load the sounds ini file
  INIFile *rules_ini = new INIFile("rules.ini");
  if (rules_ini != 0) {
    Rules->AttackInterval = rules_ini->readInt("AI", "AttackInterval", 3);
    Rules->AttackDelay = rules_ini->readInt("AI", "AttackDelay", 5);
    Rules->PatrolScan = rules_ini->readFloat("AI", "PatrolScan", .016f);
    Rules->CreditReserve = rules_ini->readInt("AI", "CreditReserve", 100);
    Rules->PathDelay = rules_ini->readFloat("AI", "PathDelay", .01f);
    Rules->OreNearScan = rules_ini->readInt("AI", "OreNearScan", 6);
    Rules->OreFarScan = rules_ini->readInt("AI", "OreFarScan", 48);
    Rules->AutocreateTime    = rules_ini->readInt("AI", "AutocreateTime", 5);
    Rules->InfantryReserve    = rules_ini->readInt("AI", "InfantryReserve", 3000);
    Rules->InfantryBaseMult    = rules_ini->readInt("AI", "InfantryBaseMult", 1);
    Rules->PowerSurplus    = rules_ini->readInt("AI", "PowerSurplus", 50);
    Rules->BaseSizeAdd    = rules_ini->readInt("AI", "BaseSizeAdd", 3);
    Rules->RefineryRatio    = rules_ini->readFloat("AI", "RefineryRatio", .16f);
    Rules->RefineryLimit    = rules_ini->readInt("AI", "RefineryLimit", 4);
    Rules->BarracksRatio    = rules_ini->readFloat("AI", "BarracksRatio", .16f);
    Rules->BarracksLimit    = rules_ini->readInt("AI", "BarracksLimit", 2);
    Rules->WarRatio        = rules_ini->readFloat("AI", "WarRatio", .1f);
    Rules->WarLimit        = rules_ini->readInt("AI", "WarLimit", 2);
    Rules->DefenseRatio    = rules_ini->readFloat("AI", "DefenseRatio", .4f);
    Rules->DefenseLimit    = rules_ini->readInt("AI", "DefenseLimit", 40);
    Rules->AARatio        = rules_ini->readFloat("AI", "AARatio", .14f);
    Rules->AALimit        = rules_ini->readInt("AI", "AALimit", 10);
    Rules->TeslaRatio    = rules_ini->readFloat("AI", "TeslaRatio", .16f);
    Rules->TeslaLimit    = rules_ini->readInt("AI", "TeslaLimit", 10);
    Rules->HelipadRatio    = rules_ini->readFloat("AI", "HelipadRatio", .12f);
    Rules->HelipadLimit    = rules_ini->readInt("AI", "HelipadLimit", 5);
    Rules->AirstripRatio    = rules_ini->readFloat("AI", "AirstripRatio", .12f);
    Rules->AirstripLimit    = rules_ini->readInt("AI", "AirstripLimit", 5);
    //        Rules->CompEasyBonus    = rules_ini->readInt("AI", "CompEasyBonus", true);
    //        Rules->Paranoid        = rules_ini->readInt("AI", "Paranoid", true);
    Rules->CompEasyBonus    = true; // @todo read this value from the config file
    Rules->Paranoid        = true; // @todo read this value from the config file
    Rules->PowerEmergency    = rules_ini->readInt    ("AI", "PowerEmergency", 75);
  } else {
    Rules->AttackInterval    = 3;
    Rules->AttackDelay    = 5;
    Rules->PatrolScan    =.016f;
    Rules->CreditReserve    =100;
    Rules->PathDelay        =.01f;
    Rules->OreNearScan    = 6;
    Rules->OreFarScan    = 48;
    Rules->AutocreateTime    =5;
    Rules->InfantryReserve    =3000;
    Rules->InfantryBaseMult    = 1;
    Rules->PowerSurplus    = 50;
    Rules->BaseSizeAdd    = 3;
    Rules->RefineryRatio    = .16f;
    Rules->RefineryLimit    = 4;
    Rules->BarracksRatio    = .16f;
    Rules->BarracksLimit    = 2;
    Rules->WarRatio        =.1f;
    Rules->WarLimit        = 2;
    Rules->DefenseRatio    = .4f;
    Rules->DefenseLimit    = 40;
    Rules->AARatio        =.14f;
    Rules->AALimit        = 10;
    Rules->TeslaRatio    = .16f;
    Rules->TeslaLimit = 10;
    Rules->HelipadRatio = .12f;
    Rules->HelipadLimit = 5;
    Rules->AirstripRatio = .12f;
    Rules->AirstripLimit = 5;
    Rules->CompEasyBonus = true;
    Rules->Paranoid = true;
    Rules->PowerEmergency = 75;
  }

  Rules->AlwaysAlly = true;
}

/**
 */
Ai::~Ai() {
  // Free ai rules
  delete Rules;
}

/**
 * @param diff Difficulty
 */
void Ai::SetDifficulty(int diff) {
  if (diff > 0 && diff <= 4) {
    this->Difficulty = diff;
  }
}

/**
 *
 */
void Ai::DefendUnits(Player* pPlayer, int pPlayerNumb) {
  // For each unit from this player
  for (Unit *lUnit : pPlayer->getUnits()) {
    // Check that the unit can attack and that the unit doens't have other thing to do
    if (!lUnit->canAttack() || lUnit->IsAttacking() || lUnit->IsMoving ()){
      continue;
    }

    Unit *lEnemyUnit = EnemyUnitInRange(pPlayerNumb, lUnit);

    if (lEnemyUnit != NULL && lUnit->canAttack()) {
      // Don't distract units on a AI mission (only abort the mission if we see a harvester)
      if (!lUnit->UnderAttack () && lUnit->AI_Mission != 1) {
        // Abort the ai mission if we 'see' a harvester
        if (lEnemyUnit->getType()->getName() == "HARV") {
          lUnit->AI_Mission = 1;
        } else {
          continue;
        }
      }

      //            Enemy  = p::uspool->getUnitOrStructureAt(EnemyUnit->getPos(), EnemyUnit->getSubpos());
      UnitOrStructure* lEnemy = (UnitOrStructure*)p::uspool->getGroundUnitAt(lEnemyUnit->getPos(), lEnemyUnit->getSubpos());

      if (lEnemy == nullptr) {
        lEnemy  = (UnitOrStructure*)p::uspool->getFlyingAt(lEnemyUnit->getPos(), lEnemyUnit->getSubpos());
      }

      if (lEnemy == nullptr) {
        lEnemy  = (UnitOrStructure*)p::uspool->getStructureAt(lEnemyUnit->getPos(), lEnemyUnit->getSubpos(), false);
      }

      if (lEnemy != nullptr){
        lUnit->attack(lEnemy);
        return;
      }
    }

    Structure *lEnemyStructure = EnemyStructureInRange(pPlayerNumb, lUnit);
    if ((lEnemyStructure != nullptr) && lUnit->canAttack()) {
      //Enemy  = p::uspool->getUnitOrStructureAt(EnemyStructure->getPos(), EnemyStructure->getSubpos());

      //            if ( Enemy != NULL ){
      //                Unit->attack(Enemy);
      lUnit->attack(lEnemyStructure);
      return;
      //            }
    }
  }
}

void Ai::DefendComputerPlayerBaseUnderAttack(Player *Player,
                                             int PlayerNumb,
                                             UnitOrStructure *Enemy,
                                             Structure *StructureUnderAttack) {
  if (Enemy == nullptr || StructureUnderAttack == nullptr){
    return;
  }

  if (Enemy->getOwner() == StructureUnderAttack->getOwner()){
    return;
  }
  //
  // don't try to build for the human player
  // We should actually check if building is allowed and only build when allowed (by triggers)
  //
  if (PlayerNumb == this->HumanPlayerNumb){
    return;
  }

  int StructureUnderAttackPos = StructureUnderAttack->getPos();

  // Repair the structure (if needed)
  if (StructureUnderAttack->getType()->getMaxHealth() > StructureUnderAttack->getHealth()){
    if (!StructureUnderAttack->isRepairing()) {
      StructureUnderAttack->repair();
    }
  }

  for (Unit *Unit : Player->getUnits()) {
    if (/*Unit->IsAttacking () ||*/ !Unit->canAttack()) {
      continue;
    }

    int Distance = Unit->getDist(StructureUnderAttackPos);
    int SightRange = Unit->getType()->getSight();

    if (Distance < (SightRange * 3) /*&& !Unit->IsAttacking ()*/){
      Unit->attack(Enemy);
    }
  }
}

void Ai::DefendComputerPlayerUnitUnderAttack(Player *Player,
                                             int PlayerNumb,
                                             UnitOrStructure *Enemy,
                                             Unit *UnitUnderAttack) {
  if (Enemy == nullptr || UnitUnderAttack == nullptr) {
    return;
  }

  if (Enemy->getOwner() == UnitUnderAttack->getOwner())
    return;

  // don't try to defend for the human player
  if (PlayerNumb == this->HumanPlayerNumb){
    return;
  }

  // Start with shooting back
  if (UnitUnderAttack->canAttack())
    UnitUnderAttack->attack (Enemy);


  int UnitUnderAttackPos = UnitUnderAttack->getPos();

  for (Unit *lUnit : Player->getUnits()){
    if (/*lUnit->IsAttacking () ||*/ !lUnit->canAttack()) {
      continue;
    }

    int Distance    = lUnit->getDist(UnitUnderAttackPos);
    int SightRange    = lUnit->getType()->getSight();

    // If I can see my comrade under attack
    if (Distance < SightRange){
      lUnit->attack ((UnitOrStructure*)Enemy);
    }
  }
}


/**
 * This is a beginning, for now this function only deploy's the starting MCV
 */
void Ai::handle() {
  static bool DelayAttack = true;

  // Don't burn our fingers on multi player mode...
  if (p::ccmap->getGameMode() == GAME_MODE_MULTI_PLAYER){
    return;
  }

  switch (Difficulty) {
    case 1:
      //            if (AiDifficultyTimer.Elapsed () < 2)
      //                return;
      break;

    case 2:
      //            if (AiDifficultyTimer.Elapsed () < 1)
      //                return;
      break;

    case 3:
      //            if (AiDifficultyTimer.Elapsed () < 0.5)
      //                return;
      break;

    case 4:
      // Don't wait
      break;
  }


  this->HumanPlayerNumb = p::ccmap->getPlayerPool()->getLPlayerNum();

  // This part of the AI takes care of the computer player attacking a enemy within range
  // and of the human player fighting back when attacked.
  for (unsigned int PlayerNumb = 0; PlayerNumb < NumbPlayers; PlayerNumb++) {
    Player *CurPlayer = p::ccmap->getPlayerPool()->getPlayer(PlayerNumb);

    // Don't try to control defeated players
    if (CurPlayer->isDefeated()) {
      continue;
    }

    if ((SDL_GetTicks() - LastDefendTickCount[PlayerNumb]) > 100){
      LastDefendTickCount[PlayerNumb] = SDL_GetTicks();
      // Let the units defend themselfes
      DefendUnits(CurPlayer, PlayerNumb);
      // Let the structures with weapons defend themselfes
      DefendStructures(CurPlayer, PlayerNumb);
    }

    //The next part is only for computer players
    if (PlayerNumb == HumanPlayerNumb){
      continue;
    }

    if ((SDL_GetTicks() - LastHarvestTickCount[PlayerNumb]) > 1000){
      LastHarvestTickCount[PlayerNumb] = SDL_GetTicks();
      this->Harvest (CurPlayer, PlayerNumb);
    }

    // Retry moving when the path was blocked (maybe we should add some code so tanks will wait for infantry (move in steps to the target)
    if ((SDL_GetTicks() - LastGuideTickCount[PlayerNumb]) > Rules->PathDelay * 60 * 1000 ){
      LastGuideTickCount[PlayerNumb] = SDL_GetTicks();
      this->guideAttack (CurPlayer, PlayerNumb);
    }

    if ((SDL_GetTicks() - LastBuildTickCount[PlayerNumb]) > 24000 || RetryDeploy[PlayerNumb]){
      LastBuildTickCount[PlayerNumb] = SDL_GetTicks();
      RetryDeploy[PlayerNumb] = false;
      this->Build (CurPlayer, PlayerNumb);
    }

    // The first attack is delayed, all other attacks use the attack interval
    if (DelayAttack){
      if ((SDL_GetTicks() - LastAttackTickCount[PlayerNumb]) > (unsigned)(Rules->AttackDelay * 60 * 1000)){
        LastAttackTickCount[PlayerNumb] = SDL_GetTicks();
        this->patrolAndAttack (CurPlayer, PlayerNumb);
      }
      DelayAttack = false;
    }else{
      if ((SDL_GetTicks() - LastAttackTickCount[PlayerNumb]) > (unsigned)(Rules->AttackInterval * 60 * 1000)){
        LastAttackTickCount[PlayerNumb] = SDL_GetTicks();
        this->patrolAndAttack (CurPlayer, PlayerNumb);
      }
    }
  }
}

void Ai::guideAttack(Player *Player, int PlayerNumb) {
  std::vector<Structure*> EnemyTeslaCoils;
  std::vector<Structure*> EnemyPowerPlants;
  std::vector<Structure*> EnemyOreRefs;
  std::vector<Unit*> lPlayerUnitPool;
  Unit *FirstUnit = nullptr;
  Unit *ClosestUnit = nullptr;
  uint32_t MaxDist = 0;
  uint32_t TargetDist = 0;
  uint32_t NextTargetDist = 0;
  bool StillMoving = false;

  // don't try to control for the human player
  if (PlayerNumb == this->HumanPlayerNumb){
    return;
  }

  // Abort if there is no target
  if (player_targets[PlayerNumb] == nullptr) {
    return;
  }

  // Handle lPlayer vars
  const std::vector<Structure*> *lPlayerStructurePool = p::ccmap->getPlayerPool()->getLPlayer()->getStructures();
  size_t lPlayerNumbStructures = lPlayerStructurePool->size();
  lPlayerUnitPool  = p::ccmap->getPlayerPool()->getLPlayer()->getUnits();
  size_t lPlayerNumbUnits = lPlayerUnitPool.size();

  if (lPlayerNumbStructures > 0 || lPlayerNumbUnits > 0){
    // Init all units to the first unit in the pool
    for (Unit *unit : Player->getUnits()) {
      if (unit->AI_Mission == 3){
        FirstUnit = ClosestUnit = unit;
      }
    }

    // We don't need to do anything if there are no units attacking the human player
    if (FirstUnit == nullptr) {
      return;
    }

    // If the target was destroyed, find a new good target
    if (!player_targets[PlayerNumb]->isAlive()){
      player_targets[PlayerNumb] = nullptr;

      if (lPlayerStructurePool->size() > 0) {
        if ((*lPlayerStructurePool)[0]->isAlive()) {
          NextTargetDist = FirstUnit->getDist((*lPlayerStructurePool)[0]->getPos());
          player_targets[PlayerNumb] = (*lPlayerStructurePool)[0];
        } else {
          NextTargetDist = 10000;
        }

        // Find the closest target
        for (unsigned int i = 0; i < lPlayerStructurePool->size(); i++) {
          if (FirstUnit->getDist(lPlayerStructurePool->at(i)->getPos()) < NextTargetDist && lPlayerStructurePool->at(i)->isAlive()){
            NextTargetDist = FirstUnit->getDist(lPlayerStructurePool->at(i)->getPos());
            player_targets[PlayerNumb] = lPlayerStructurePool->at(i);
          }
        }

        // Find the preferred targets
        for (unsigned int i = 0; i < lPlayerStructurePool->size(); i++) {
          // Make a list of all nearby tesla's
          if ((lPlayerStructurePool->at(i)->getType()->getName() == "TSLA") && lPlayerStructurePool->at(i)->isAlive()){
            if (FirstUnit->getDist(lPlayerStructurePool->at(i)->getPos()) < 4 * NextTargetDist)
              EnemyTeslaCoils.push_back(lPlayerStructurePool->at(i));
          }

          // Make a list of all nearby advanced power plants
          if ((lPlayerStructurePool->at(i)->getType()->getName() == "APWR") && lPlayerStructurePool->at(i)->isAlive()){
            if (FirstUnit->getDist(lPlayerStructurePool->at(i)->getPos()) < 4 * NextTargetDist)
              EnemyPowerPlants.push_back(lPlayerStructurePool->at(i));
          }

          // Make a list of all nearby ore refinery's
          if ((lPlayerStructurePool->at(i)->getType()->getName() == "PROC") && lPlayerStructurePool->at(i)->isAlive()){
            if (FirstUnit->getDist(lPlayerStructurePool->at(i)->getPos()) < 4 * NextTargetDist)
              EnemyOreRefs.push_back(lPlayerStructurePool->at(i));
          }
        }

        // Prefer attacking power plants (so powered defences don't work any more
        if (EnemyPowerPlants.size() > 0){

          player_targets[PlayerNumb] = EnemyPowerPlants[0];
          NextTargetDist = FirstUnit->getDist(EnemyPowerPlants[0]->getPos());

          // find the best power plant to attack
          for (unsigned int i = 0; i < EnemyPowerPlants.size(); i++){
            if (FirstUnit->getDist(EnemyPowerPlants[i]->getPos()) < NextTargetDist){
              NextTargetDist = FirstUnit->getDist(EnemyPowerPlants[i]->getPos());
              player_targets[PlayerNumb] = EnemyPowerPlants[i];
            }
          }

          // Prefer attacking tesla coils next
        }else if (EnemyTeslaCoils.size() > 0 ){

          player_targets[PlayerNumb] = EnemyTeslaCoils[0];
          NextTargetDist = FirstUnit->getDist(EnemyTeslaCoils[0]->getPos());

          // find the best tesla coil to attack
          for (unsigned int i = 0; i < EnemyTeslaCoils.size(); i++){
            if (FirstUnit->getDist(EnemyTeslaCoils[i]->getPos()) < NextTargetDist){
              NextTargetDist = FirstUnit->getDist(EnemyTeslaCoils[i]->getPos());
              player_targets[PlayerNumb] = EnemyTeslaCoils[i];
            }
          }
          // Prefer attacking ore refinery's next
        }else if (EnemyOreRefs.size() > 0){
          player_targets[PlayerNumb] = EnemyOreRefs[0];
          NextTargetDist = FirstUnit->getDist(EnemyOreRefs[0]->getPos());

          // find the best ore refinery to attack
          for (unsigned int i = 0; i < EnemyOreRefs.size(); i++){
            if (FirstUnit->getDist(EnemyOreRefs[i]->getPos()) < NextTargetDist){
              NextTargetDist = FirstUnit->getDist(EnemyOreRefs[i]->getPos());
              player_targets[PlayerNumb] = EnemyOreRefs[i];
            }
          }
        }
      } else if (lPlayerUnitPool.size() > 0){
        ///@TDOO, fix this, it is not working jet
        if (lPlayerUnitPool[0]->isAlive()) {
          NextTargetDist = FirstUnit->getDist(lPlayerUnitPool[0]->getPos());
          player_targets[PlayerNumb] = lPlayerUnitPool[0];
        } else
          NextTargetDist = 10000;


        for (unsigned int i = 0; i < lPlayerUnitPool.size(); i++)
        {
          if (FirstUnit->getDist(lPlayerUnitPool[i]->getPos()) < NextTargetDist && lPlayerUnitPool[i]->isAlive()){
            NextTargetDist = FirstUnit->getDist(lPlayerUnitPool[i]->getPos());
            player_targets[PlayerNumb] = lPlayerUnitPool[i];
          }
        }
      }
    }

    // Get out if we can't find any more targets
    if (player_targets[PlayerNumb] == NULL)
      return;

    // Keep our attacking units close together
    for (Unit *unit : Player->getUnits()) {
      if (!unit->canAttack()) {
        continue;
      }

      if (unit->AI_Mission == 3){
        if (unit->IsMoving() && !unit->IsAttacking ())
          StillMoving = true;

        if (FirstUnit->getDist(unit->getPos()) > MaxDist){
          MaxDist = FirstUnit->getDist(unit->getPos());
          //printf ("Maxdist = %u, FirstUnitName = %s, UnitName = %s\n", MaxDist, FirstUnit->getType()->getName(), Unit->getType()->getName() );
        }

        if (ClosestUnit->getDist(player_targets[PlayerNumb]->getPos()) > unit->getDist(player_targets[PlayerNumb]->getPos())){
          ClosestUnit = unit;
          TargetDist = unit->getDist(player_targets[PlayerNumb]->getPos());
        }
      }
    }

    // Attack the target
    for (Unit *unit : Player->getUnits()) {
      if (!unit->canAttack()) {
        continue;
      }

      if (unit->AI_Mission == 3){
        if (player_targets[PlayerNumb]->isAlive()) {
          if (MaxDist > 5 && TargetDist > MaxDist) {
            //printf ("Maxdist = %u\n", MaxDist);
            unit->move(ClosestUnit->getPos());
          } else {
            if (!unit->IsAttacking()) {
              unit->attack(player_targets[PlayerNumb]);
              break;
            }
          }
        }
      }
    }
  }
}

/**
 *
 */
uint32_t Ai::getDist(uint32_t pos1, uint32_t pos2) {
  uint16_t x, y, nx, ny, xdiff, ydiff;

  p::ccmap->translateFromPos(pos1, &nx, &ny);
  p::ccmap->translateFromPos(pos2, &x, &y);

  xdiff = abs(x-nx);
  ydiff = abs(y-ny);

  return sqrt((xdiff*xdiff + ydiff*ydiff));
}


bool Ai::CanBuildAt(uint8_t PlayerNumb, const std::string &structname,
                    uint32_t pos) {
  uint16_t xpos;
  uint16_t ypos;
  p::ccmap->translateFromPos(pos, &xpos, &ypos);

  StructureType* Type	= p::uspool->getStructureTypeByName(structname);

  std::vector<bool>* buildable = p::ccmap->getPlayerPool()->getPlayer(PlayerNumb)->getMapBuildable();

  // Check that we don't try to build outside the map (copied check from unitandstructurepool.cpp!!
  uint32_t br = pos + p::ccmap->getWidth()*(Type->getYsize()-1);
  if (pos > p::ccmap->getSize() || (br > p::ccmap->getSize() && 0)) {
    return false;
  }

  // Prevent wrapping around
  if (xpos + Type->getXsize() > p::ccmap->getWidth()) {
    return false;
  }

  for (uint32_t placeypos = 0; placeypos < Type->getYsize(); placeypos++) {
    for (uint32_t placexpos = 0; placexpos < Type->getXsize(); placexpos++) {
      uint32_t curpos = pos + placeypos*p::ccmap->getWidth() + placexpos;

      if (!buildable->at(curpos)) {
        return false;
      }

      if (p::uspool->getGroundUnitAt(curpos) != NULL ||
          p::uspool->getFlyingAt(curpos) != NULL ||
          p::uspool->getStructureAt(curpos) != NULL) {   //p::uspool->getUnitAt(curpos+x) != NULL
        return false;
      }

      if (!p::ccmap->isBuildableAt(PlayerNumb, curpos)) {
        return false;
      }
    }
  }

  return true;
}

/**
 *
 */
bool Ai::BuildStructure(Player *Player, int PlayerNumb, const char *structname, Uint32 ConstYardPos) {
  Uint32 pos = 0;
  Uint16 ConstYard_x;
  Uint16 ConstYard_y;

  p::ccmap->translateFromPos(ConstYardPos, &ConstYard_x, &ConstYard_y);

  // Get the structure type so we can see what the cost are for this structure
  StructureType* type = p::uspool->getStructureTypeByName(structname);
#if 0
  //Check if we can pay for this structure ;)
  if (Player->getMoney() > type->getCost())
  {
    for (Uint32 offset = 5; offset < 100; offset += 4)
    {
      // Uint32 offset = 20;
      curpos = ConstYardPos - ccmap->getWidth()*(offset/2);
      for (Uint32 pos = curpos; pos < curpos + offset; pos +=4){
        if (CanBuildAt (PlayerNumb, structname, pos) ){
          if (!p::dispatcher->structurePlace(structname, pos, PlayerNumb))
            logger->error("Failed to build, ConstYardPosition = %u, pos = %u\n", ConstYardPos, pos);
          else{
            // Succes at building
            return true;
          }
        }
      }
    }
  }
#else
  //Check if we can pay for this structure ;)
  if (Player->getMoney() > type->getCost()){
    for (Uint32 offset = 5; offset < 100; offset += 4){
      for (Uint32 x = ConstYard_x-offset; x < ConstYard_x + offset; x += 4){
        for (Uint32 y = ConstYard_y-offset; y < ConstYard_y + offset; y += 3){
          pos = p::ccmap->translateToPos (x,y);
          if (CanBuildAt (PlayerNumb, structname, pos) ){
            if (!p::dispatcher->structurePlace(structname, pos, PlayerNumb)){
              std::stringstream message;
              message << "Failed to build, ConstYardPosition = " << ConstYardPos << ", pos = " << pos;
              Logger::getInstance()->Error(message.str());
            } else {
              // Succes at building
              return true;
            }
          }
        }
      }
    }
  }

#endif

  // Log
  Logger::getInstance()->Error("Ai::BuildStructure Failed to find free pos");
  return false;
}

/**
 *
 */
unsigned int Ai::FindClosesedTiberium(Unit *Unit) {
  Uint32 tiberium = 0;
  Uint32 ClosesedPos = 0;
  Uint32 ClosesedDistance = 0;
  Uint32 Distance = 0;
  bool FirstFound = false;

  for (unsigned int pos =0; pos < p::ccmap->getSize(); pos++){
    tiberium = p::ccmap->getResourceFrame(pos);
    if (tiberium != 0) {
      // Found tiberium
      Distance = Unit->getDist(pos);
      if (Distance < ClosesedDistance || !FirstFound){
        ClosesedPos		= pos;
        ClosesedDistance	= Distance;
        FirstFound = true;
      }
    }
  }

  return ClosesedPos;
}

/**
 * Make structures defend themselves
 */
void Ai::DefendStructures(Player *player, int PlayerNumb) {
  // For each structure from this player
  for (Structure *theStructure : *player->getStructures()) {
    // We should ensure that the structurepool is always consistent,
    // in order to avoid segfaults due to the presence of NULL elements in the vector
    // Using list instead of vector would solve the problem
    if(theStructure != NULL) {
      Unit *EnemyUnit = EnemyUnitInRange(PlayerNumb, theStructure);
      StructureType *st = dynamic_cast<StructureType*>(theStructure->getType());

      // If there is no valid enemy
      // OR the structure is a building
      // OR the structure can't attack
      // OR we don't have enough power
      // OR the structure is already attacking
      if (EnemyUnit == nullptr ||
          theStructure->IsBuilding() ||
          !theStructure->canAttack() ||
          (st->getPowerInfo().powered && (player->getPower() < player->getPowerUsed())) ||
          theStructure->IsAttacking())
      {
        continue;
      }

      theStructure->attack(EnemyUnit);
    }
  }
}

void Ai::Build(Player *Player, int PlayerNumb) {
  std::vector<Unit*>	unitpool;
  Unit*			theUnit;
  Structure		*OreRefinery;
  uint32_t NumbOfInfantry = 0, NumbWarfactorys = 0, NumbOreRefs = 0, NumbConstYards = 0, NumbBarracks = 0, NumbOfOreTrucks = 0, NumbTanks = 0, NumbTeslaCoils = 0 , NumbOfPowerPlants = 0;
  uint32_t				ConstYardPos = 0;
  //UnitType			*BuildUnitType;
  int					cost;
  bool				StructureWasBuild = false;
  //static bool			Direction = false;
  //static Uint32			MoveToPos = 0;
  //char				UnitName[10];
  uint16_t xpos;
  uint16_t ypos;

  // Don't build in single player mode (jet).
  if (p::ccmap->getGameMode() == GAME_MODE_SINGLE_PLAYER) {
    return;
  }

  // don't try to build for the human player
  if (PlayerNumb == this->HumanPlayerNumb) {
    return;
  }

  size_t NumbUnits = Player->getNumUnits();
  unitpool = Player->getUnits();
  NumbWarfactorys = NumbOreRefs = NumbConstYards = NumbBarracks = 0;
  size_t NumbStructures = Player->getNumStructs();

  // Count structures from this computer player
  OreRefinery = NULL;
  for (Structure *structure : *Player->getStructures()) {
    if (structure->is("WEAP")) {
      NumbWarfactorys++;
    }

    if (structure->is("PROC")) {
      NumbOreRefs++;
      OreRefinery = structure;
    }

    if (structure->is("FACT")) {
      NumbConstYards++;
      ConstYardPos = structure->getPos();
    }

    if (structure->is("TSLA")) {
      NumbTeslaCoils++;
    }

    if (structure->is("APWR") || structure->is("POWR")) {
      NumbOfPowerPlants++;
    }

    if (structure->is("TENT") || structure->is ("BARR")) {
      NumbBarracks++;
    }
  }

  // Count Units from this computer player
  for (int UnitNumb = 0; UnitNumb < NumbUnits; UnitNumb++) {
    theUnit = unitpool[UnitNumb];

    if (theUnit->getType()->isInfantry()){
      NumbOfInfantry++;
    }

    if (theUnit->getType()->getName() == "HARV") {
      if (theUnit->GetBaseRefinery() == 0) {
        theUnit->SetBaseRefinery(OreRefinery);
      }
      NumbOfOreTrucks++;
    }

    if (theUnit->getType()->getName() == "1TNK") {
      NumbTanks++;
    }
  }

  // Check our units if we can deploy them (only for MCV yet)
  if (NumbConstYards == 0) {
    for (int UnitNumb = 0; UnitNumb < NumbUnits; UnitNumb++) {
      theUnit = unitpool[UnitNumb];

      if (theUnit->getType()->getName() == "MCV") {
        if (theUnit->canDeploy(p::ccmap) == true) {
          // We don't have any structures, randomly deploy
          theUnit->deploy();
        } else {
          if (!theUnit->IsMoving()) {
            p::ccmap->translateFromPos(theUnit->getPos(), &xpos, &ypos);
            if (xpos + 20 < p::ccmap->getWidth()) {
              theUnit->move(p::ccmap->translateToPos(xpos + 20, ypos));
            } else {
              theUnit->move(p::ccmap->translateToPos(xpos - 20, ypos));
            }
          }
          RetryDeploy[PlayerNumb] = true;
        }
      }
    }
  }

  if (NumbConstYards > 0) {
    // Build ore refinery
    // We should use Rules->RefineryLimit somewhere around here
    if (!StructureWasBuild &&
        (NumbOreRefs == 0 || (NumbOreRefs < NumbStructures * Rules->RefineryRatio && NumbOreRefs < Rules->RefineryLimit))) {
      cost = p::uspool->getStructureTypeByName("PROC")->getCost();
      if (Player->getMoney() > cost) {
        if (BuildStructure (Player, PlayerNumb, "PROC", ConstYardPos))
          Player->changeMoney(-1 * cost);
        StructureWasBuild = true;
      }
      // @todo sell some stuff if we can't afford a new refinery and we dont't have any refinery's anymore
    }

    // Build the weapen factory
    if (!StructureWasBuild && (NumbWarfactorys == 0 ||
                               (NumbWarfactorys < Rules->WarRatio &&
                                NumbWarfactorys < Rules->WarLimit))) {
      cost = p::uspool->getStructureTypeByName("WEAP")->getCost();
      if (Player->getMoney() > cost) {
        if (BuildStructure(Player, PlayerNumb, "WEAP", ConstYardPos)) Player->changeMoney(-1 * cost);
        NumbWarfactorys++;
        StructureWasBuild = true;
      }
    }

    // build power plant (if needed)
    //printf ("Power = %i, PowerUsed = %i, PowerSurplus = %i\n", Player->getPower(), Player->getPowerUsed(), Rules->PowerSurplus);
    if (!StructureWasBuild &&
        ((signed)(Player->getPower() - Rules->PowerSurplus) < (signed)Player->getPowerUsed())) {
      cost = p::uspool->getStructureTypeByName("APWR")->getCost();
      if (Player->getMoney() > cost) {
        if (NumbOfPowerPlants > 0) {
          if (BuildStructure (Player, PlayerNumb, "APWR", ConstYardPos))
            Player->changeMoney(-1 * cost);
        } else {
          if (BuildStructure (Player, PlayerNumb, "POWR", ConstYardPos))
            Player->changeMoney(-1 * cost);
        }
        StructureWasBuild = true;
      }
    }

    // Build the barracks
    if (!StructureWasBuild && (NumbBarracks == 0 )){
      cost = p::uspool->getStructureTypeByName("BARR")->getCost();
      if (Player->getMoney() > cost){
        if (BuildStructure (Player, PlayerNumb, "BARR", ConstYardPos))
          Player->changeMoney(-1 * cost);
        NumbBarracks++;
        StructureWasBuild = true;
      }
    }

    // Build tesla coils
    if (!StructureWasBuild &&
        (NumbTeslaCoils < NumbStructures * Rules->TeslaRatio &&
         NumbTeslaCoils < Rules->TeslaLimit)) {
      cost = p::uspool->getStructureTypeByName("TSLA")->getCost();
      if (Player->getMoney() > cost){
        if (BuildStructure(Player, PlayerNumb, "TSLA", ConstYardPos))
          Player->changeMoney(-1 * cost);
        StructureWasBuild = true;
      }
    }
  }

  if (NumbWarfactorys > 0){
    if (NumbOfOreTrucks < 1 || (NumbOfOreTrucks <3 && NumbTanks > 5)){
      // Get the structure type so we can see what the cost are for this structure
      UnitType* type = p::uspool->getUnitTypeByName("HARV");
      cost = type->getCost();
      if (Player->getMoney() > cost) {
        if (p::dispatcher->unitSpawn(type, PlayerNumb)) {
          Player->changeMoney(-1 * cost);
        }
      } else if (NumbOreRefs > 0 && NumbOfOreTrucks > 0) {
        return;
      }
    } else {
      // Build tanks
      // Get the structure type so we can see what the cost are for this structure
      // UnitType* type = p::uspool->getUnitTypeByName("1TNK"); // allied tank
      UnitType* type = p::uspool->getUnitTypeByName("3TNK");	// sovejet tank
      cost = type->getCost();
      if (Player->getMoney() > cost) {
        if (p::dispatcher->unitSpawn(type, PlayerNumb)) {
          Player->changeMoney(-1 * cost);
        }
      }
    }
  }

  // Build soldier
  if (NumbBarracks > 0 &&
      ((unsigned)Player->getMoney() > Rules->InfantryReserve ||
       (unsigned) (NumbStructures * Rules->InfantryBaseMult) > NumbOfInfantry)) {
    UnitType* type;
    switch (UnitBuildMultiplexer[PlayerNumb]) {
      case 0:
        // Rifle Infantry, cost 100
        type = p::uspool->getUnitTypeByName("E1");
        cost = type->getCost();
        if (Player->getMoney() > cost) {
          if (p::dispatcher->unitSpawn(type, PlayerNumb)) {
            Player->changeMoney(-1 * cost);
          }
        }
        break;
      case 1:
        // Grenadier, cost 160
        type = p::uspool->getUnitTypeByName("E2");
        cost = type->getCost();
        if (Player->getMoney() > cost) {
          if (p::dispatcher->unitSpawn(type, PlayerNumb)) {
            Player->changeMoney(-1 * cost);
          }
        }
        break;
      case 2:
        // Rocket Soldier, cost 300
        type = p::uspool->getUnitTypeByName("E3");
        cost = type->getCost();
        if (Player->getMoney() > cost) {
          if (p::dispatcher->unitSpawn(type, PlayerNumb)) {
            Player->changeMoney(-1 * cost);
          }
        }
        break;
      case 3:
        // Flamethrower, cost 300
        type = p::uspool->getUnitTypeByName("E4");
        cost = type->getCost();
        if (Player->getMoney() > cost) {
          if (p::dispatcher->unitSpawn(type, PlayerNumb)) {
            Player->changeMoney(-1 * cost);
          }
        }
        break;
    }

    if (UnitBuildMultiplexer[PlayerNumb] < 3) {
      UnitBuildMultiplexer[PlayerNumb]++;
    } else {
      UnitBuildMultiplexer[PlayerNumb] = 0;
    }
  }

}

/**
 *	Returns a enemy **unit** if one is in range of our **unit**
 */
Unit *Ai::EnemyUnitInRange(int MyPlayerNumb, Unit *MyUnit, int AttackRange) {
  // Check parameter pb
  if (MyUnit == 0) {
    return 0;
  }

  // If Unit can't attack return nothing to attack
  if (!MyUnit->canAttack()) {
    return 0;
  }

  if (AttackRange == -1) {
#if 1
    AttackRange = MyUnit->getType()->getWeapon()->getRange();
#else
    AttackRange = MyUnit->getType()->getSight();
#endif
  }

  for (unsigned int i = 0; i < NumbPlayers; i++) {
    // Don't find my own units
    if (MyPlayerNumb == i){
      continue;
    }

    Player* EnemyPlayer = p::ccmap->getPlayerPool()->getPlayer(i);
    Player* MyPlayer = p::ccmap->getPlayerPool()->getPlayer(MyPlayerNumb);
    Player* localPl = p::ccmap->getPlayerPool()->getLPlayer();

    // Check to see if these are both ai players and if ai players are allied
    if ((MyPlayer != localPl) && (EnemyPlayer != localPl) && Rules->AlwaysAlly) {
      continue;
    }

    // Check if the Enemy player is a allie ;)
    if (EnemyPlayer->isAllied(MyPlayer)) {
      continue;
    }

    // For each unit from this player
    for (Unit* EnemyUnit : EnemyPlayer->getUnits()) {
      int distance = MyUnit->getDist(EnemyUnit->getPos());
      if (distance <= AttackRange && EnemyPlayer->getSide() != PS_NEUTRAL) {
        return EnemyUnit;
      }

      // Make it easyer to attack harvesters
      if ((EnemyUnit->getType()->getName() == "HARV") && MyPlayerNumb != this->HumanPlayerNumb) {
        if (distance <= 4*AttackRange && EnemyPlayer->getSide() != PS_NEUTRAL) {
          return EnemyUnit;
        }
      }
    }
  }

  // Return NULL
  return nullptr;
}

/**
 * Returns a enemy Unit if one is in range of our Structure
 */
Unit *Ai::EnemyUnitInRange(int MyPlayerNumb, Structure *MyStructure,
                           int AttackRange) {
  if (MyStructure == nullptr) {
    return nullptr;
  }

  if (!MyStructure->canAttack()) {
    return nullptr;
  }

  if (AttackRange == -1){
    StructureType *theType = dynamic_cast<StructureType*>(MyStructure->getType());
    Weapon *theWeapon = theType->getWeapon(true);
    AttackRange = theWeapon->getRange();
  }

  for (unsigned int i = 0; i < NumbPlayers; i++) {
    // Don't defend against my own units
    if (MyPlayerNumb == i) {
      continue;
    }

    Player* enemyPlayer = p::ccmap->getPlayerPool()->getPlayer(i);
    Player* myPlayer = p::ccmap->getPlayerPool()->getPlayer(MyPlayerNumb);

    // Check if the Enemy player is a ally ;)
    if (enemyPlayer->isAllied(myPlayer)) {
      continue;
    }

    // For each unit from this player
    for (Unit *enemyUnit : enemyPlayer->getUnits()) {
      int distance = enemyUnit->getDist(MyStructure->getPos());
      if (distance <= AttackRange  && enemyPlayer->getSide() != PS_NEUTRAL){
        return enemyUnit;
      }
    }
  }

  return nullptr;
}

/**
 * @return a enemy Structure if one is in range of our Unit
 */
Structure *Ai::EnemyStructureInRange(int MyPlayerNumb, Unit* MyUnit,
                                     int AttackRange) {
  if (MyUnit == nullptr) {
    return nullptr;
  }

  if (!MyUnit->canAttack()) {
    return nullptr;
  }

  if (AttackRange == -1)
    AttackRange = MyUnit->getType()->getWeapon()->getRange();  //MyUnit->getType()->getSight();

  for (unsigned int i = 0; i < this->NumbPlayers; i++) {
    // Don't find my own units
    if (MyPlayerNumb == i)
      continue;

    Player *EnemyPlayer = p::ccmap->getPlayerPool()->getPlayer(i);
    Player *MyPlayer = p::ccmap->getPlayerPool()->getPlayer(MyPlayerNumb);
    Player *localPl = p::ccmap->getPlayerPool()->getLPlayer();

    // Check to see if these are both ai players and if ai players are allied
    if ((MyPlayer != localPl) && (EnemyPlayer != localPl) && Rules->AlwaysAlly)
      continue;


    // Check if the Enemy player is a allie ;)
    if (EnemyPlayer->isAllied(MyPlayer))
      continue;

    // For each unit from this player
    for (Structure *EnemyStructure : *EnemyPlayer->getStructures()){
      int distance = MyUnit->getDist(EnemyStructure->getPos());
      if (distance <= AttackRange && EnemyPlayer->getSide() != PS_NEUTRAL){
        return EnemyStructure;
      }
    }
  }

  return nullptr;
}

/**
 * Assign tasks to the units
 *
 * @param PlayerNumb number of the player
 */
void Ai::Harvest(Player *Player, int PlayerNumb) {
  // don't try to control for the human player
  if (PlayerNumb == this->HumanPlayerNumb) {
    return;
  }

  // Parse all Units to find harvester (HARV -> code for harvester)
  for (Unit* theUnit : Player->getUnits()) {
    if (theUnit->getType()->getName() == "HARV") {
      if (!theUnit->IsHarvesting()) {
        // Command the unit to harvest with no parameters (NULL, NULL)
        theUnit->Harvest(0, 0);
      }
    }
  }
}

/**
 * For now the AI assumes that all non local players are computer players
 * This means no support for multiplayer with computer players mix.
 */
void Ai::patrolAndAttack(Player *Player, int PlayerNumb) {
  size_t NumbUnits;
  size_t NumbStructures;
  size_t lPlayerNumbStructures;
  size_t lPlayerNumbUnits;

  std::vector<Structure*>* structurepool, lPlayerStructurePool;
  std::vector<Unit*> unitpool, lPlayerUnitPool;
  Unit *Unit;
  UnitOrStructure* target = NULL;
  uint16_t RndStr;

  // don't try to control for the human player
  if (PlayerNumb == this->HumanPlayerNumb){
    return;
  }

  bool PreferLastStructures = ((double)2*rand()/(RAND_MAX)) != 0;

  // Handle unit vars
  NumbUnits       = Player->getNumUnits();
  unitpool        = Player->getUnits();

  // Handle structure vars
  structurepool       = 0;//Player->getStructures();
  NumbStructures      = Player->getNumStructs();

  // Handle lPlayer vars
  //lPlayerStructurePool	= p::ccmap->getPlayerPool()->getLPlayer()->getStructures();
  lPlayerNumbStructures	= p::ccmap->getPlayerPool()->getLPlayer()->getNumStructs();
  lPlayerUnitPool		= p::ccmap->getPlayerPool()->getLPlayer()->getUnits();
  lPlayerNumbUnits	= p::ccmap->getPlayerPool()->getLPlayer()->getNumUnits();

  // First find a good target
  if (lPlayerNumbStructures > 0) {
    RndStr = (int) ((double)lPlayerNumbStructures*rand()/(RAND_MAX));

    if (PreferLastStructures){
      if (RndStr < lPlayerNumbStructures/2){
        RndStr = lPlayerNumbStructures - RndStr;
      }
    }

    if (RndStr >= lPlayerNumbStructures)
      RndStr = lPlayerNumbStructures -1;

    // printf ("%s line %i: Random structure numb = %i, Numb strucutres = %i, preferlast = %i\n", __FILE__, __LINE__, RndStr, lPlayerNumbStructures, PreferLastStructures);

    if (lPlayerStructurePool[RndStr]->isAlive()){
      target = lPlayerStructurePool[RndStr];
    }else{
      for (int str =0; str < lPlayerNumbStructures; str++){
        if (lPlayerStructurePool[str]->isAlive()){
          target = lPlayerStructurePool[str];
          break;
        }
      }
    }
  } else {
    for (int un =0; un < lPlayerNumbUnits; un++){
      if (lPlayerUnitPool[un]->isAlive()){
        target = lPlayerUnitPool[un];
        break;
      }
    }
  }

  if ((lPlayerNumbStructures > 0 || lPlayerNumbUnits > 0) && NumbUnits > 0) {
    for (int UnitNumb = 0; UnitNumb < NumbUnits; UnitNumb++) {
      Unit = unitpool[UnitNumb];
      if (!Unit->canAttack())
        continue;
      if (Unit->AI_Mission == 1 || Unit->AI_Mission == 3) {
        if (Unit->getType()->getName() == "HARV") {
          Logger::getInstance()->Error(__FILE__, __LINE__, "Error harvesters can't attack.");
        } else {
          Unit->AI_Mission = 3;
          player_targets[PlayerNumb] = target;

          // Make all our units attack the same target.
          Unit->attack(target);
        }
      }
    }
  }
}
