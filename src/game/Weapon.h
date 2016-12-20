// Weapon.h
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

#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>
#include <map>

#include "armour_t.h"

class Projectile;
class Warhead;
class UnitOrStructure;

/**
 * Weapon in the game
 */
class Weapon {
 public:
  Weapon(const char * wname);
  ~Weapon();

  uint8_t getReloadTime() const;
  uint8_t getRange() const;
  uint8_t getSpeed() const;
  int16_t getDamage() const;
  bool getWall() const;
  Projectile* getProjectile();

  Warhead* getWarhead();

  const std::string getChargingSound() const;

  void fire(UnitOrStructure* owner, uint16_t target, uint8_t subtarget);

  //Uint32 tmppif;

  bool isHeatseek() const;

  bool isInaccurate() const;

  double getVersus(armor_t armour) const;

  uint8_t getFuel() const;

  uint8_t getSeekFuel() const;

  const char* getName() const;

  void Reload();

 private:
  Projectile* projectile;
  Warhead* whead;
  uint8_t speed;
  uint8_t range;
  uint8_t reloadtime;
  int16_t damage;
  uint8_t burst;

  /** how many ticks this projectile can move for until being removed. */
  uint8_t fuel;

  /**
   * How many ticks can this projectile change course to track its target before falling back to flying
   * in a straight line.
   */
  uint8_t seekfuel;
  bool heatseek;
  bool charges;

  // @todo Implemente Anim in [Weapon]
  //Uint32 fireimage;
  //Uint32* fireimages;
  //Uint8 numfireimages;
  //Uint8 numfiredirections;

  std::string report;
  std::string reloadsound;
  std::string chargingsound;
  std::string name;
};

#endif
