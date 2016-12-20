// PlayerPool.h
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

#ifndef PLAYERPOOL_H
#define PLAYERPOOL_H

#include <vector>
#include <string>

#include "misc/INIFile.h"

class Player;

/**
 * @todo Currently the player starts are shuffled randomly without
 * any way of accepting a preshuffled list.
 */
class PlayerPool {
 public:
  explicit PlayerPool();
  ~PlayerPool();

  /** Get the number of a color in string */
  const int MultiColourStringToNumb(const std::string& colour);

  /** */
  void LoadIni(INIFile *inifile);

  /** */
  void Init(uint8_t gamemode);

  uint8_t getNumPlayers() const;
  uint8_t getLPlayerNum() const;
  Player *getLPlayer();
  void setLPlayer(const std::string& pname);
  //void setLPlayer(Uint8 number, const char* nick, const char* colour, const char* mside);
  void setPlayer(uint8_t number, const char* nick, const int colour, const char* mside);
  Player* getPlayer(int player) const;
  Player* getPlayer(const std::string& playerName);

  int getPlayerNum(const std::string& pname);
  Player* getPlayerByName(const char* pname);

  int getPlayerNumByHouseNum(int House) const;
  int getHouseNumByPlayerNum(unsigned int Player) const;

  uint8_t getUnitpalNum(uint8_t player) const ;
  uint8_t getStructpalNum(uint8_t player) const ;
  std::vector<Player*> getOpponents(Player* pl);
  /*void playerDefeated(Player * pl);
   void playerUndefeated(Player * pl);*/
  // bool hasWon() const ;
  // bool hasLost() const ;
  void setAlliances(INIFile* mapini);
  //void placeMultiUnits();
  //INIFile * getMapINI();
  uint16_t getAStart();
  void setPlayerStarts(uint8_t pos, uint32_t start);

  /** Called by input to see if sidebar needs updating*/
  bool pollSidebar();

  /** Called by the local player when sidebar is to be updated*/
  void updateSidebar();

  /** Called by input to see if radar status has changed.*/
  uint8_t statRadar();

 private:
  explicit PlayerPool(INIFile *inifile, uint8_t gamemode);
  PlayerPool(const PlayerPool&);

  uint32_t playerstarts[10];

  std::vector<Player*> playerpool;
  std::vector<uint16_t> player_starts;

  uint8_t localPlayer;
  uint8_t gamemode;
  bool won;
  bool lost;
  bool updatesidebar;
  //INIFile * mapini;
};

#endif //PLAYERPOOL_H
