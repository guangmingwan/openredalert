// Player.h
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

#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <map>
#include <vector>

#include "ConStatus.h"
#include "UnitOrStructureType.h"

class MoneyCounter;
class Structure;
class StructureType;
class BQueue;
class INIFile;
class Unit;

/**
 * Player in game
 */
class Player {
 public:
  explicit Player(const std::string& pname);
  ~Player();

  /** Load information from ini file */
  void LoadIni(INIFile* mapini);

  /*bool isLPlayer();*/
  void setPlayerNum(uint8_t num);
  void setMultiColour(const char* colour);
  void setMultiColour(const int colour);
  uint8_t getMultiColour (void) ;
  //void setSettings(const char* nick, const char* colour, const char* mside);
  //void setSettings(const char* nick, const int colour, const char* mside);

  unsigned int getPlayerNum() const ;

  /** Return the name of the player */
  const std::string& getName() const ;

  uint8_t getSide() const ;
  bool setSide(uint8_t Side);
  uint8_t getMSide() const ;

  bool changeMoney(int32_t change);
  void setMoney(int32_t NewMoney);
  int32_t getMoney() const ;

  bool startBuilding(UnitOrStructureType * type);
  ConStatus stopBuilding(UnitOrStructureType* type);
  void pauseBuilding(void);
  void resumeBuilding(void);
  void placed(UnitOrStructureType* type);
  ConStatus getStatus(UnitOrStructureType* type, uint8_t* quantity, uint8_t* progress);
  BQueue* getQueue(uint8_t ptype);

  void builtUnit(Unit* un);
  void lostUnit(Unit* un, bool wasDeployed);
  void movedUnit(uint32_t oldpos, uint32_t newpos, uint8_t sight);
  void builtStruct(Structure* str);
  void lostStruct(Structure* str);

  size_t getNumUnits() ;
  size_t getNumStructs() const ;
  const std::vector<Unit*>& getUnits() const ;
  const std::vector<Structure*>* getStructures() const ;

  uint8_t getStructpalNum() const ;
  uint8_t getUnitpalNum() const ;

  uint32_t getPower() const ;
  uint32_t getPowerUsed() const ;

  uint16_t getPlayerStart() const ;

  void updateOwner(unsigned int newnum);

  bool isDefeated() const;

  bool isAllied(Player* pl) const;
  size_t getNumAllies() const ;
  bool allyWithPlayer(Player* pl);
  void didAlly(Player* pl);
  bool unallyWithPlayer(Player* pl);
  void didUnally(Player* pl);
  void setAlliances(INIFile* mapini);
  void clearAlliances();

  void addUnitKill() ;
  void addStructureKill() ;
  uint32_t getUnitKills() const ;
  uint32_t getUnitLosses() const ;
  uint32_t getStructureKills() const ;
  uint16_t getStructureLosses() const ;

  size_t ownsStructure(StructureType* stype) ;
  Structure*& getPrimary(const UnitOrStructureType* uostype) ;
  Structure*& getPrimary(uint32_t ptype) ;
  void setPrimary(Structure* str);

  // SOB == Sight or Build.
  void revealAroundWaypoint(uint32_t Waypoint);
  enum SOB_update { SOB_SIGHT = 1, SOB_BUILD = 2 };
  void setVisBuild(SOB_update mode, bool val);
  std::vector<bool>* getMapVis() ;
  std::vector<bool>* getMapBuildable() ;

  /** Turns on a block of cells in either the sight or buildable matrix */
  void addSoB(uint32_t pos, uint8_t width, uint8_t height, uint8_t sight, SOB_update mode);
  /** Turns on cells around one cell depending on sight */
  void addSoB(uint32_t pos, uint8_t sight, SOB_update mode);

  /** Turns off a block of cells in either the sight or buildable matrix */
  void removeSoB(uint32_t pos, uint8_t width, uint8_t height, uint8_t sight, SOB_update mode);

  bool canBuildAll() const;
  bool canBuildAny() const;
  bool canSeeAll() const;
  bool hasInfMoney() const;
  void enableBuildAll();
  void enableInfMoney();

  int32_t getTechLevel();
  /** Return number of radar of the player */
  uint32_t getNumberRadars();

  /** Set if the player is victorious */
  void setVictorious(bool victorious);
  /** Return if the player is victorious */
  bool isVictorious();

 private:
  /** Do not want player being constructed using default constructor*/
  Player() ;
  Player(const Player&) ;

  /** This instead of a vector as we don't have to check ranges before operations*/
  std::map<uint8_t, BQueue*> queues;

  bool defeated;
  std::string playername;
  std::string nickname;
  uint8_t playerside;
  uint8_t multiside;
  uint8_t playernum;
  uint8_t unitpalnum;
  uint8_t structpalnum;

  /** TechLevel of the player in the map */
  int32_t techLevel;

  /** See the alliance code in the .cpp file*/
  uint8_t unallycalls;

  int32_t money;
  uint32_t powerGenerated;
  uint32_t powerUsed;

  uint32_t unitkills;
  uint32_t unitlosses;
  uint32_t structurekills;
  uint32_t structurelosses;

  uint16_t playerstart;

  // All of these pointers are owned elsewhere.
  std::vector<Unit*> unitpool;
  std::vector<Structure*>* structurepool;
  std::map<StructureType*, std::list<Structure*> > structures_owned;
  std::map<uint32_t, std::list<Structure*> > production_groups;
  std::map<uint32_t, Structure*> primary_structure;

  std::vector<Player*> allies;

  /**
   * players that have allied with this player, but this player
   * has not allied in return.  Used to force an unally when player
   * is defeated.
   */
  std::vector<Player*> non_reciproc_allies;

  std::vector<uint8_t>* sightMatrix;
  std::vector<uint8_t>* buildMatrix;

  /** List of location that is visible by player */
  std::vector<bool>* mapVisible;
  /** List of location that is buildable by player */
  std::vector<bool>* mapBuildable;

  /** cheat/debug flags: allmap (reveal all map) */
  bool allmap;
  /** cheat/debug flags: buildany (remove proximity check) */
  bool buildany;
  /** cheat/debug flags: buildall (disable prerequisites) */
  bool buildall;
  /** cheat/debug flags: infmoney (doesn't care if money goes negative).*/
  bool infmoney;

  /** Event that manage Money variations */
  MoneyCounter* counter;

  /** Number of radars structures */
  uint32_t numberRadars;
  
  /** buildable_radius */
  uint8_t brad;
  /** @todo : REMOVE THAT  Map Width */
  uint16_t mwid;
  
  /** Is true if the player is victorious */
  bool victorious;
};

#endif //PLAYER_H
