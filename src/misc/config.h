#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "misc/common.h"
#include "misc/gametypes.h"

namespace {
  const uint8_t NUMBINDABLE = 3;
}

enum KEY_TYPE {
  KEY_SIDEBAR = 0,
  KEY_STOP,
  KEY_ALLY
};

typedef struct _ConfigType {
  uint32_t videoflags;
  uint32_t startMoney;

  uint16_t width;
  uint16_t height;
  uint16_t bpp;
  uint16_t serverport;

  uint8_t intro;
  /* Game mode */
  uint8_t gamemode;
  uint8_t totalplayers;
  uint8_t playernum;
  uint8_t scrollstep;
  uint8_t scrolltime;
  uint8_t maxscroll;
  uint8_t finaldelay;
  uint8_t dispatch_mode;

  bool nosound;
  bool pause;
  bool quit_mission;
  bool playvqa;
  bool allowsandbagging;
  bool debug;
  bool demo;
  /** Enable/disable the fog of war */
  bool UseFogOfWar;

  gametypes gamenum;

  int grabmode;

  unsigned int bindablekeys[NUMBINDABLE];

  uint8_t bindablemods[NUMBINDABLE];

  uint8_t buildable_radius;

  std::string mapname;
  std::string vqamovie;
  std::string nick;
  std::string side_colour;
  /** side of human player */
  std::string mside;
  /** side of computer player */
  std::string cside;
  std::string serveraddr;
  /** vfs binpath */
  std::string binpath;
  double buildable_ratio;


  // Some sounds

  //
  // Structures
  //
  std::string StructureDestroyed;
  std::string StructureHalfDestroyed;
  std::string StructureSold;
  std::string StructurePlaced;
  std::string StructureStartBuild;
  std::string StructureReady;
  std::string RepairStructure;
  std::string PrimairyStructureSelected;
  // Base
  std::string CmdCentreUnderAttack;
  std::string BaseUnderAttack;
  // Unit
  std::string UnitFull;
  std::string UnitLost;
  std::string RepairUnit;
  std::string UnitRepaired;
  std::string UnitSold;
  std::string UnitReady;
  std::string UnitDeployed;
  std::string TrainUnit;
  std::string AirUnitLost;
  /** Naval unit lost */
  std::string NavalUnitLost;
  /** General */
  std::string BattleControlTerm;
  std::string BuildingCanceled;
  std::string BuildingOnHold;
  std::string Newoptions;
  std::string NoDeploy;
  std::string NoFunds;
  std::string Nopower;
  std::string Reinforcements;
  std::string RadarUp;
  std::string RadarDown;
  std::string MissionWon;
  std::string MissionLost;
  /** Money Up sound */
  std::string MoneyCountUp;
  /**
   * Money Down Sound
   */
  std::string MoneyCountDown;
} ConfigType;

/**
 *	this getConfig() is located in args.cpp
 */
const ConfigType& getConfig();

#endif //CONFIG_H
