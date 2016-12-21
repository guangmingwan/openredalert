// Game.h
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

#ifndef GAME_H
#define GAME_H

#include <string>

#include "misc/config.h"

/**
 * This object represent a game session
 */
class Game {
 public:
  Game();
  ~Game();

  void InitializeMap(std::string MapName);
  /** Initialize some object of the game */
  void InitializeGameClasses();
  void FreeMemory();
  void play();
  void HandleTiming();
  void dumpstats();

 private:
  void handleAiCommands();

  uint8_t MissionNr;
  uint32_t OldUptime;
  ConfigType config;
  uint8_t gamemode;
  bool BattleControlTerminated;
};

#endif //GAME_H
