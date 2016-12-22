// UnitAndStructurePool.h
// 1.3
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

#ifndef UNITANDSTRUCTUREPOOL_H
#define UNITANDSTRUCTUREPOOL_H


#define US_IS_UNIT				0x40000000
#define US_IS_STRUCTURE			0x20000000
#define US_IS_WALL				0x10000000
#define US_HAS_L2OVERLAY		0x08000000
#define US_MOVING_HERE			0x07000000
#define US_UNIT_LOWER_RIGHT		0x00800000
#define US_STR_LOWER_RIGHT		0x00400000
#define US_HIGH_COST			0x00200000	// This indicates one can drive over this place but agains high cost ;)
#define US_IS_AIRUNIT			0x00100000
#define US_AIR_MOVING_HERE		0x00040000
#define US_AIRUNIT_LOWER_RIGHT	0x00020000
#define US_CELL_HAS_TRIGGER		0x00010000

//#define US_HAS_PROJECTILE 0x00800000
//#define US_HAS_HIGHPROJ   0x00400000
//#define US_HAS_EXPLOTION  0x00200000

//#define US_HAS_AIRUNIT

#include <set>
#include <string>
#include <map>
#include <vector>

#include "UnitOrStructure.h"

class RA_Teamtype;
class UnitAndStructureMat;
class UnitOrStructure;
class UnitOrStructureType;
class INIFile;
class L2Overlay;
class Unit;
class UnitType;
class Player;
class Structure;
class StructureType;
class InfantryGroup;
class Talkback;
class CnCMap;
class AiCommand;

/**
 * Stores all units and structures.
 *
 * Handles level two overlays.
 */
class UnitAndStructurePool {
 public:
  /** The constructor needs theater because many structures graphics depends of theater */
  UnitAndStructurePool(const char* theTheater);
  ~UnitAndStructurePool();

  uint8_t getStructureNum(uint16_t cellpos, uint32_t **inumbers, int8_t **xoffsets, int8_t **yoffsets);
  uint8_t getUnitNum(uint16_t cellpos, uint32_t **inumbers, int8_t **xoffsets, int8_t **yoffsets);
  uint8_t getFlyingUnitNum(uint16_t cellpos, uint32_t **inumbers, int8_t **xoffsets, int8_t **yoffsets);

  /** Retrieve a limited amount of information from the cell.*/
  bool getUnitOrStructureLimAt(uint32_t curpos, float* width, float* height,
                               uint32_t* cellpos, uint8_t* igroup, uint8_t* owner,
                               uint8_t* pcol, bool* blocked);
  bool hasL2overlay(uint16_t cellpos) const ;
  uint8_t getL2overlays(uint16_t cellpos, uint32_t **inumbers, int8_t **xoddset, int8_t **yoffset);

  /** Add an overlay */
  std::multimap<uint16_t, L2Overlay*>::iterator addL2overlay(uint16_t cellpos, L2Overlay* overlay);
  /** Remove an overlay */
  void removeL2overlay(std::multimap<uint16_t, L2Overlay*>::iterator entry);

  bool createReinforcements(RA_Teamtype* Team);

  /** Create a structure in a map with this pool */
  bool createStructure(const char* typen, uint16_t cellpos, unsigned int owner,
                       uint16_t health, uint8_t facing, bool makeanim, std::string trigger_name);

  /** Create a structure in a map with this pool */
  bool createStructure(StructureType* type, uint16_t cellpos, unsigned int owner,
                       uint16_t health, uint8_t facing, bool makeanim, std::string trigger_name);


  /** Create a Unit and return it or return NULL */
  Unit* createUnit(const char* typen, uint16_t cellpos, uint8_t subpos,
                   unsigned int owner, uint16_t health, uint8_t facing, uint8_t action, std::string trigger_name);
  /** Create a Unit and return it or return NULL */
  Unit* createUnit(UnitType* type, uint16_t cellpos, uint8_t subpos,
                   unsigned int owner, uint16_t health, uint8_t facing, uint8_t action, std::string trigger_name);


  /** Create a trigger on a cell */
  bool createCellTrigger(uint32_t cellpos);

  bool spawnUnit(const char* typen, uint8_t owner);
  bool spawnUnit(UnitType* type, uint8_t owner);

  Unit* getUnitAt(uint32_t cell, uint8_t subcell);
  Unit *getUnitAt(uint32_t cell);
  size_t getNumbUnits(void) ;
  Unit* getUnit(uint32_t num);
  //    Structure* getStructureAt(Uint32 cell);
  Structure* getStructureAt(uint32_t cell, bool wall);
  Structure* getStructure(uint32_t num);
  size_t getNumbStructures (void);

  //    UnitOrStructure* getSelectedUnitOrStructureAt(Uint32 cell, Uint8 subcell, bool wall = false);
  //    UnitOrStructure* getSelectedUnitOrStructureAt(Uint32 cell);
  //    UnitOrStructure* getUnitOrStructureAt(Uint32 cell, Uint8 subcell, bool wall = false);
  //    UnitOrStructure* getUnitOrStructureAt(Uint32 cell);



  bool cellOccupied(uint32_t cell);
  Unit* getGroundUnitAt(unsigned int cell, uint8_t subcell = 0);
  Unit* getFlyingAt(uint32_t cell, uint8_t subcell = 0);
  Structure* getStructureAt(uint32_t cell, uint8_t subcell = 0, bool wall = false);



  InfantryGroup* getInfantryGroupAt(uint32_t cell);
  uint16_t getSelected(uint32_t pos);
  uint16_t preMove(Unit *un, uint8_t dir, int8_t *xmod, int8_t *ymod, Unit **BlockingUnit);
  uint8_t postMove(Unit *un, uint16_t newpos);
  void abortMove(Unit* un, uint32_t pos);

  /** Return the UnitType with the specified name */
  UnitType* getUnitTypeByName(const std::string& unitname);

  /** Return the StructureType with the specified name */
  StructureType* getStructureTypeByName(const std::string& structname);

  UnitOrStructureType* getTypeByName(const char* typen);
  bool freeTile(uint16_t pos) const ;
  uint16_t getTileCost(uint16_t pos, Unit* excpUn) const;
  uint16_t getTileCost(uint16_t pos) const;
  bool tileAboutToBeUsed(uint16_t pos) const;
  void setCostCalcOwnerAndType(uint8_t owner, uint8_t type);
  void removeUnit(Unit *un);
  void removeStructure(Structure *st);
  bool hasDeleted() ;
  void showMoves();

  /** techtree code */
  void addPrerequisites(UnitType* unittype);
  /** techtree code */
  void addPrerequisites(StructureType* structtype);

  /** scans both inifiles for things with techlevel <= that of the parameter
   * then retrives those types.*/
  void preloadUnitAndStructures(uint8_t techlevel);

  /** Generate reverse dependency information from what units we have loaded.*/
  void generateProductionGroups();

  /** Used by the sidebar to know units */
  std::vector<std::string> getBuildableUnits(Player* pl);
  /** Used by the sidebar to know structures */
  std::vector<std::string> getBuildableStructures(Player* pl);

  // unit is removed from map (to be stored in transport)
  void hideUnit(Unit* un);
  uint8_t unhideUnit(Unit* un, uint16_t newpos, bool unload);

  Talkback *getTalkback(const char* talkback);

 private:
  /** simple constructor is private to avoid creation by default */
  UnitAndStructurePool();

  /** Update the ovrlay of walls ???? */
  void updateWalls(Structure* st, bool add, CnCMap* theMap);

  /** String which keep 5 lettres of the theater. Many Graphics depends of theater */
  std::string theaterext;

  std::vector<UnitAndStructureMat> unitandstructmat;

  std::vector<Structure *> structurepool;
  //vector<StructureType *> structuretypepool;
  //map<string, Uint16> structname2typenum;
  std::map<std::string, StructureType *> structuretypepool;

  std::vector<Unit *> unitpool;
  std::vector<UnitType *> unittypepool;
  std::map<std::string, uint16_t> unitname2typenum;

  std::multimap<uint16_t, L2Overlay*> l2pool;
  std::map<uint16_t, uint16_t> numl2images;

  std::multimap<StructureType*, std::vector<StructureType*>* > struct_prereqs;
  std::multimap<UnitType*, std::vector<StructureType*>* > unit_prereqs;
  void splitORPreReqs(const std::string& prereqs, std::vector<StructureType*> * type_prereqs);

  std::map<std::string, Talkback*> talkbackpool;

  INIFile* structini;
  INIFile* unitini;
  INIFile* tbackini;
  INIFile* artini;

  uint8_t costcalcowner;
  uint8_t costcalctype;

  /** Image cache numbers for worn down ground  for the small one */
  uint32_t bib1;
  /** Image cache numbers for worn down ground  for the normal one */
  uint32_t bib2;
  /** Image cache numbers for worn down ground  for the big one */
  uint32_t bib3;

  bool deleted_unitorstruct;
  uint16_t numdeletedunit;
  uint16_t numdeletedstruct;
};

#endif //UNITANDSTRUCTUREPOOL_H
