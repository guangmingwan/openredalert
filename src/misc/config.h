#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "misc/common.h"
#include "misc/gametypes.h"

#include "SDL.h"
#include "SDL.h"

namespace {
  const Uint8 NUMBINDABLE = 3;
}

enum KEY_TYPE {
  KEY_SIDEBAR = 0,
  KEY_STOP,
  KEY_ALLY
};

typedef struct _ConfigType {
  Uint32 videoflags;
  Uint32 startMoney;

  Uint16 width,
  height,
  bpp,
  serverport;

  Uint8 intro;
  /* Game mode */
  Uint8 gamemode;
  Uint8 totalplayers,
  playernum,
  scrollstep,
  scrolltime,
  maxscroll,
  finaldelay,
  dispatch_mode;

  bool nosound;
  bool pause;
  bool quit_mission;
  bool playvqa,
  allowsandbagging,
  debug,
  demo;
  /** Enable/disable the fog of war */
  bool UseFogOfWar;

  gametypes gamenum;

  SDL_GrabMode grabmode;

  SDLKey bindablekeys[NUMBINDABLE];

  Uint8 bindablemods[NUMBINDABLE];

  Uint8 buildable_radius;

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
  std::string BattleControlTerm,
  BuildingCanceled,
  BuildingOnHold,
  Newoptions,
  NoDeploy,
  NoFunds,
  Nopower,
  Reinforcements,
  RadarUp,
  RadarDown,
  MissionWon,
  MissionLost;
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
