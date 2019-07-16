// Selection.h
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

#ifndef SELECTION_H
#define SELECTION_H

#include <list>
#include <cstdint>
class Structure;
class Unit;

/**
 * Selection of Units and structure in the game
 *
 * @todo Some stuff still uses the "for (i = begin; i != end; ++i)" pattern.
 * @todo Some of the functions in the namespace can be replaced by further STL magic.
 * @todo Rename function names.
 * @todo (Later) Rewrite Selection to be as close to the STL Container concept as useful
 */
class Selection {
 public:
  Selection();
  ~Selection();

  bool addUnit(Unit *selunit, bool enemy);
  void removeUnit(Unit *selunit);
  bool addStructure(Structure *selstruct, bool enemy);
  void removeStructure(Structure *selstruct);

  bool saveSelection(uint8_t savepos);
  bool loadSelection(uint8_t loadpos);
  bool mergeSelection(uint8_t loadpos);

  void clearSelection();

  void purge(Unit* sel);
  void purge(Structure* sel);

  uint32_t numbUnits() const ;
  Unit* getUnit(uint32_t UnitNumb) ;
  /** Return a ref to a selected structure */
  Structure* getStructure(uint32_t structureNumber);

  bool canAttack() const ;
  bool canMove() const ;
  bool areWaterBound ();
  bool isEnemy() const ;
  bool empty() const ;
  /** Returns the number of the player who owns all things selected */
  uint8_t getOwner() const;
  void moveUnits(uint32_t pos);
  void attackUnit(Unit* target);
  void attackStructure(Structure* target);
  void checkSelection();
  Unit* getRandomUnit();
  bool getWall() const;
  void stop();

 private:
  std::list<Unit*> sel_units;
  std::list<Structure*> sel_structs;

  uint32_t numattacking;
  bool enemy_selected;
  std::list<Unit*>saved_unitsel[10];
  std::list<Structure*>saved_structsel[10];
};

#endif //SELECTION_H
