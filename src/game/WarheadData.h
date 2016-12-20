// WarheadData.h
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

#ifndef WARHEADDATA_H
#define WARHEADDATA_H

#include <string>

#include "misc/INIFile.h"

/**
 * This is what gives the "rock, paper, scissors" character to the game. It describes how the damage is to be applied to the target. The values should take into consideration the 'area of effect'.; example: Although an armor piercing tank round would instantly kill a soldier IF it hit, the anti-infantry rating is still very low because the tank round has such a limited area of effect, lacks pinpoint accuracy, and acknowledges the fact that tanks pose little threat to infantry that take cover.
 */
class WarheadData {
 public:
  uint32_t getSpread();

  void setSpread(uint32_t spread);

  uint32_t getWall();

  void setWall(uint32_t wall);

  uint32_t getWood();

  void setWood(uint32_t wood);

  uint32_t getOre();

  void setOre(uint32_t ore);

  uint32_t getVersusNone();

  void setVersusNone(uint32_t versusNone);

  uint32_t getVersusWood();

  void setVersusWood(uint32_t versusWood);

  uint32_t getVersusLight();

  void setVersusLight(uint32_t versusLight);

  uint32_t getVersusHeavy();

  void setVersusHeavy(uint32_t versusHeavy);

  uint32_t getVersusConcrete();

  void setVersusConcrete(uint32_t versusConcrete);

  uint32_t getExplosion();

  void setExplosion(uint32_t explosion);

  uint32_t getInfDeath();

  void setInfDeath(uint32_t infDeath);

  static WarheadData* loadWarheadData(INIFile * file, std::string name);
  void print();

private:
  uint32_t spread;
  uint32_t wall;
  uint32_t wood;
  uint32_t ore;
  uint32_t versusNone;
  uint32_t versusWood;
  uint32_t versusLight;
  uint32_t versusHeavy;
  uint32_t versusConcrete;
  uint32_t explosion;
  uint32_t infDeath;
};
#endif //WARHEADDATA_H
