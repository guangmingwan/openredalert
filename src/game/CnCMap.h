// CnCMap.h
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

#ifndef CNCMAP_H
#define CNCMAP_H

#include <map>
#include <string>
#include <vector>

#include "triggers.h"
#include "MiniMapClipping.h"
#include "misc/INIFile.h"
#include "misc/gametypes.h"
#include "video/SHPImage.h"
#include "Trigger.h"

class CellTrigger;
class LoadingScreen;
class CnCMap;
class MissionData;
class TemplateImage;
class PlayerPool;
class AiCommand;
class Unit;

using OpenRedAlert::Game::Trigger;
namespace OpenRedAlert {
  namespace Game {
    class Trigger;
  }
}

/**
 * Information about terrain placement
 */
struct TerrainEntry {
  uint32_t shpnum;
  int16_t xoffset;
  int16_t yoffset;
};

struct TileList {
  uint16_t templateNum;
  uint8_t tileNum;
};


class RA_TeamUnits {
 public:
  /** type name of the unit */
  std::string	tname;
  /** Number of units of this type */
  int     numb;
};

class RA_Teamtype {
 public:
  std::string                 	tname;
  int            			country;
  int                     props;
  int                     unknown1;
  int                     unknown2;
  int                     maxteams;
  int                     waypoint;
  /** Number of the trigger to set at all unit of the group */
  int                     trigger;
  /** Number of unit in the team */
  int                     numb_teamtypes;
  std::vector<RA_TeamUnits>	Units;

  /** List of command during Ai management */
  std::vector<AiCommand*> aiCommandList;
};


struct ScrollVector {
  int8_t x;
  int8_t y;
  uint8_t t;
};

struct ScrollBookmark {
  uint16_t x;
  uint16_t y;
  uint16_t xtile;
  uint16_t ytile;
};

struct ScrollData {
  uint16_t maxx;
  uint16_t maxy;
  uint16_t curx;
  uint16_t cury;
  uint16_t maxxtileoffs;
  uint16_t maxytileoffs;
  uint16_t curxtileoffs;
  uint16_t curytileoffs;
  uint16_t tilewidth;
};


struct TemplateTilePair {
  /** Template for Theater */
  TemplateImage *theater;
  /** Tile number in this Theater */
  uint8_t tile;
};

typedef std::map<std::string, TemplateImage*> TemplateCache;
typedef std::vector<TemplateTilePair* > TemplateTileCache;

/**
 * Map in Red Alert
 */
class CnCMap {
 public:
  CnCMap();
  ~CnCMap();

  void Init(gametypes gameNumber, uint8_t gameMode);
  // old proto :: void InitCnCMap();

  // Comments with "C/S:" at the start are to do with the client/server split.
  // C/S: Members used in both client and server
  void loadMap(const std::string& mapname, LoadingScreen* lscreen);

  const MissionData& getMissionData() const;

  bool isLoading() const ;

  bool canSpawnAt(uint16_t pos) const;
  bool isBuildableAt(uint32_t PlayerNumb, uint16_t pos, bool WaterBound ) const;
  bool isBuildableAt(uint16_t pos, Unit* excpUn = NULL) const;
  bool isBuildableAt(uint32_t PlayerNumb, uint16_t pos, Unit* excpUn = NULL) const;
  uint16_t getCost(uint16_t pos, Unit* excpUn = 0) const;
  uint16_t getWidth() const ;
  uint16_t getHeight() const ;
  uint32_t getSize() const ;
  uint32_t translateToPos(uint16_t x, uint16_t y) const;
  void translateFromPos(uint32_t pos, uint16_t *x, uint16_t *y) const;

  enum TerrainType {
    t_land=0,
    t_water=1,
    t_road=2,
    t_rock=3,
    t_tree=4,
    t_water_blocked=5,
    t_other_nonpass=7
  };

  enum ScrollDirection {s_none = 0, s_up = 1, s_right = 2, s_down = 4, s_left = 8,
    s_upright = 3, s_downright = 6, s_downleft = 12, s_upleft = 9, s_all = 15};

  // C/S: Not sure about this one
  uint8_t getGameMode() const ;

  /** C/S: These functions are client only*/
  void setTerrainOverlay(uint32_t pos, uint32_t ImgNum, uint16_t Frame);

  /** C/S: These functions are client only*/
  uint32_t getTerrainOverlay(uint32_t pos) ;

  /** Return true if this map is in snow theme */
  bool SnowTheme() const;

  SDL_Surface *getMapTile(uint32_t pos);
  SDL_Surface *getShadowTile(uint8_t shadownum);

  RA_Teamtype* getTeamtypeByName(std::string TeamName);

  RA_Teamtype* getTeamtypeByNumb(unsigned int TeamNumb);

  RA_Tigger* getTriggerByName(std::string TriggerName);

  void setTriggerByName(std::string TriggerName, RA_Tigger *Trig);

  RA_Tigger* getTriggerByNumb(int TriggerNumb);

  /** Return the trigger pool */
  std::vector<Trigger*>* getTriggerPool();

  /**
   * In red alert when type is bigger the 4 it is normal ore,
   * when type is smaller or equal to 4 the resource is christal :)
   */
  bool getResource(uint32_t pos, uint8_t* type, uint8_t* amount) const ;

  void decreaseResource(uint32_t pos, uint8_t amount);

  /**
   * @return the resource data in a form best understood
   * by the imagecache/renderer
   */
  uint32_t getResourceFrame(uint32_t pos) const ;

  uint32_t getTiberium(uint32_t pos) const ;

  uint32_t getSmudge(uint32_t pos) const ;
  uint32_t setSmudge(uint32_t pos, uint8_t value) ;
  uint32_t setTiberium(uint32_t pos, uint8_t value) ;
  uint32_t getOverlay(uint32_t pos);
  uint32_t getTerrain(uint32_t pos, int16_t* xoff, int16_t* yoff);
  uint8_t getTerrainType(uint32_t pos) const ;

  /** Reloads all the tiles SDL_Images */
  void reloadTiles();

  uint8_t accScroll(uint8_t direction);
  uint8_t absScroll(int16_t dx, int16_t dy, uint8_t border);
  void doscroll();
  void setMaxScroll(uint32_t x, uint32_t y, uint32_t xtile, uint32_t ytile, uint32_t tilew);
  void setValidScroll();

  void setScrollPos(uint32_t x, uint32_t y);

  uint32_t getScrollPos() const;
  uint16_t getXScroll() const;
  uint16_t getYScroll() const;
  uint16_t getXTileScroll() const;
  uint16_t getYTileScroll() const;

  SDL_Surface* getMiniMap(uint8_t pixside);
  void prepMiniClip(uint16_t sidew, uint16_t sideh);
  const MiniMapClipping& getMiniMapClipping() const;

  bool toScroll() ;
  void storeLocation(uint8_t loc);
  void restoreLocation(uint8_t loc);

  uint32_t getWaypoint(uint8_t pointnr);

  void setWaypoint (uint8_t pointnr, uint32_t mappos);
  SHPImage* getPips();
  uint32_t getPipsNum() const;
  SHPImage* getMoveFlash();
  uint32_t getMoveFlashNum() const;
  /** X offset of viewing map
   * C/S: Client only? */
  uint16_t getX() const;
  /** Y offset of viewing map
   * C/S: Client only? */
  uint16_t getY() const;

  /** Checks the WW coord is valid */
  bool validCoord(uint16_t tx, uint16_t ty) const;
  /** Converts a WW coord into a more flexible coord */
  unsigned int normaliseCoord(unsigned int linenum) const;
  /** Converts a WW coord into a more flexible coord */
  unsigned int normaliseCoord(unsigned int tx, unsigned int ty) const;
  /** Translate coordinate */
  void translateCoord(unsigned int linenum, unsigned int* tx, unsigned int* ty) const;

  /** Return the number with string of a COMMAND */
  uint8_t UnitActionToNr(const std::string action);

  /** Return true if it's the last mission of the game */
  bool isEndOfGame();

  /** Return the PlayerPool of the map */
  PlayerPool* getPlayerPool() const;

private:
  std::vector<Trigger*>* triggerPool;

  enum {
    HAS_OVERLAY=0x100,
    HAS_TERRAIN=0x200
  };
#if _MSC_VER && _MSC_VER < 1300
#define NUMMARKS ((Uint8)5)
#else
  static const uint8_t NUMMARKS=5;
#endif
  MissionData* missionData;

  /** Load the ini part of the map */
  void loadIni(INIFile* inifile);

  /** The map section of the ini */
  void simpleSections(INIFile* inifile);

  /** The advanced section of the ini*/
  void advancedSections(INIFile* inifile);

  /** Load the bin part of the map (TD)*/
  void loadBin();

  /** Load the overlay section of the map (TD)*/
  void loadOverlay(INIFile* inifile);

  /** Extract RA map data*/
  void unMapPack(INIFile* inifile);

  /** Extract RA overlay data*/
  void unOverlayPack(INIFile* inifile);

  /** Load RA TeamTypes */
  void loadTeamTypes(INIFile* fileIni);

  /**
   * load the palette
   *
   * The only thing map specific about this function is the
   *  theatre (whose palette is then loaded into SHPBase).
   */
  void loadPal(const std::string& paln, SDL_Color *palette);

  /** Parse the BIN part of the map (RA or TD)*/
  void parseBin(TileList *bindata);

  /** Parse the overlay part of the map */
  void parseOverlay(const uint32_t& linenum, const std::string& name);

  /** load a specified tile*/
  SDL_Surface *loadTile(INIFile *templini, uint16_t templ, uint8_t tile,
                        uint32_t* tiletype);

  /** width of map in tiles */
  uint16_t width;
  /** height of map in tiles */
  uint16_t height;
  /** X coordinate for the first tile (inner map) */
  uint16_t x;
  /** Y coordinate for the first tile (inner map) */
  uint16_t y;

  /** Are we loading the map?*/
  bool loading;

  /** Have we loaded the map?*/
  bool loaded;

  ScrollData scrollpos;
  /* A array of tiles and a vector containing the images for the tiles
   * The matrix used to store terrain information.*/
  std::vector<uint16_t> tilematrix;
  /* A array of tiles and a vector containing the images for the tiles
   * The matrix used to store terrain information.*/
  std::vector<uint32_t> terrainoverlay;

  // Client only
  TemplateCache templateCache; //Holds cache of TemplateImage*s

  std::vector<SDL_Surface*> tileimages; //Holds the SDL_Surfaces of the TemplateImage
  std::vector<SDL_Surface*> tileimages_backup; //Holds the SDL_Surfaces of the TemplateImage
  TemplateTileCache templateTileCache; //Stores the TemplateImage* and Tile# of each SDL_Surface in tileimages

  std::vector<SDL_Surface*> shadowimages;

  /** These come from the WAYPOINTS section of the inifile, and contain start
   * locations for multiplayer maps.*/
  uint32_t waypoints[100];

  std::vector<uint32_t> overlaymatrix;

  std::vector<RA_Tigger*> RaTriggers;

  std::vector<RA_Teamtype> RaTeamtypes;

  std::vector<CellTrigger> CellTriggers;

  std::vector<uint16_t> resourcematrix;
  std::vector<uint32_t> resourcebases;
  std::map<std::string, uint8_t> resourcenames;

  std::vector<uint8_t> terraintypes;

  std::map<uint32_t, TerrainEntry> terrains;
  std::map<uint32_t, uint16_t> overlays;

  /// @todo We get this from the game loader part, investigate if there's a better approach.
  uint8_t maptype;
  uint8_t gamemode; // 0 - single player, 1 - skirmish, 2 - multiplayer

  /** @todo These need a better (client side only) home, (ui related)*/
  SDL_Surface *minimap, *oldmmap;
  MiniMapClipping miniclip;

  /// @todo These need a better (client side only) home (ui related)
  ScrollVector scrollvec;
  bool toscroll;
  /** stores which directions can be scrolled */
  uint8_t valscroll;
  /** stores certain map locations*/
  ScrollBookmark scrollbookmarks[NUMMARKS];
  uint8_t scrollstep, maxscroll, scrolltime;

  /// @todo These need a better (client side only) home (ui/gfx related)
  uint32_t pipsnum;
  SHPImage* pips;
  uint32_t flashnum;
  SHPImage* moveflash;

  /** RA ->  translate_64 = false
   * TD -> translate_64 = true
   * When converting WW style linenum values, do we use 64 or 128
   * as our modulus/divisor? */
  bool translate_64;

  /** only used in: Uint8 CnCMap::absScroll(Sint16 dx, Sint16 dy, Uint8 border)*/
  double fmax;

  /** Pool of the player of the map */
  PlayerPool* playerPool;
};

#endif //CNCMAP_H
