// Dispatcher.h
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

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <cstdint>

#include "DispatchLogState.h"
#include "ConStatus.h"

class UnitType;
class Unit;
class Structure;
class StructureType;
class UnitOrStructure;
class UnitOrStructureType;

/**
 * Dispatcher a the game
 *
 * Use to future client/server architecture
 */
class Dispatcher {
 public:
  Dispatcher();
  ~Dispatcher();

  void unitMove(Unit* un, uint32_t dest);
  void unitAttack(Unit* un, UnitOrStructure* target, bool tisunit);
  void unitDeploy(Unit* un);

  void structureAttack(Structure* st, UnitOrStructure* target, bool tisunit);

  /// @todo Implement these
  bool constructionStart(const UnitOrStructureType* type);
  void constructionPause(const UnitOrStructureType* type);
  void constructionPause(uint8_t ptype);
  void constructionResume(const UnitOrStructureType* type);
  void constructionResume(uint8_t ptype);
  void constructionCancel(const UnitOrStructureType* type);
  void constructionCancel(uint8_t ptype);

  ConStatus constructionQuery(const UnitOrStructureType* type);
  ConStatus constructionQuery(uint8_t ptype);

  /** @return true if structure was placed at given location. */
  bool structurePlace(const StructureType* type, uint32_t pos, uint8_t owner);
  bool structurePlace(const char* typen, uint32_t pos, uint8_t owner);
  /** Spawns a unit at the player's appropriate primary building */
  bool unitSpawn(UnitType* type, uint8_t owner);
  bool unitSpawn(const char* tname, uint8_t owner);
  /** Temporary function to place a unit directly on the map */
  bool unitCreate(const char* tname, uint32_t pos, uint8_t subpos, unsigned int owner);

  uint16_t getExitCell(const UnitOrStructureType* type);
  uint16_t getExitCell(uint8_t ptype);

 private:
  DispatchLogState logstate;
  uint8_t localPlayer;
};

#endif //DISPATCHER_H
