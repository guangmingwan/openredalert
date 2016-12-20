// Ai.h
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

#ifndef AI_H
#define AI_H

#include <vector>

#define DIFFICUTY_EASY		1
#define DIFFICUTY_MEDIUM	2
#define DIFFICUTY_HARD		3
#define DIFFICUTY_VERYHARD	4


#define AI_MISSION_NONE			1	// No mission
#define AI_MISSION_GUARD		2	// Guard a area
#define AI_MISSION_ATTACK_BASE	3	// Attack the base of the human user

class Player;
class Structure;
class AiRules;
class Unit;
class UnitOrStructure;

/**
 * Artificial Intelligence that manage Units of a Player during game
 */
class Ai {
 public:
  Ai();
  ~Ai();

  /** Set the difficulty of the AI */
  void SetDifficulty(int Diff);
  void DefendUnits(Player* Player, int PlayerNumb);
  void DefendComputerPlayerBaseUnderAttack(Player* Player, int PlayerNumb, UnitOrStructure * Enimy, Structure* StructureUnderAttack);
  void DefendComputerPlayerUnitUnderAttack(Player* Player, int PlayerNumb, UnitOrStructure * Enimy, Unit* UnitUnderAttack);
  void handle();

 private:
  std::vector<uint32_t> LastHarvestTickCount;
  std::vector<uint32_t> LastDefendTickCount;
  std::vector<uint32_t> LastAttackTickCount;
  std::vector<uint32_t> LastBuildTickCount;
  std::vector<uint32_t> LastGuideGatherTickCount;
  unsigned int NumbPlayers;
  int HumanPlayerNumb;
  int Difficulty;
  std::vector<uint32_t> LastGuideTickCount;
  std::vector<uint32_t> RetryDeploy;
  uint32_t LplayerBasePos;
  std::vector<uint16_t> UnitBuildMultiplexer;
  bool guide;
  AiRules * Rules;
  std::vector<UnitOrStructure*> player_targets;

  // Uint16 getDist(Uint16 pos1, Uint16 pos2);
  void guideAttack(Player * Player, int PlayerNumb);
  uint32_t getDist(uint32_t pos1, uint32_t pos2);
  bool CanBuildAt(uint8_t PlayerNumb, const char * structname, uint32_t pos);
  bool BuildStructure(Player * Player, int PlayerNumb, const char * structname, uint32_t ConstYardPos);
  unsigned int FindClosesedTiberium(Unit * Unit);
  void DefendStructures(Player * Player, int PlayerNumb);
  void Build(Player * Player, int PlayerNumb);
  Unit* EnemyUnitInRange(int MyPlayerNumb, Unit* MyUnit, int AttackRange = -1);
  Unit* EnemyUnitInRange(int MyPlayerNumb, Structure* MyStructure, int AttackRange = -1);
  Structure * EnemyStructureInRange(int MyPlayerNumb, Unit * MyUnit, int AttackRange = -1);
  void Harvest(Player * Player, int PlayerNumb);

  void patrolAndAttack(Player * Player, int PlayerNumb);
};

#endif //AI_H
