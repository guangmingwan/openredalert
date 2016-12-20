// Projectille.h
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

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <string>
#include <vector>

class ProjectileData;
class ProjectileDataList;
class SHPImage;

/**
 * Projectille in game
 */
class Projectile {
 public:
  Projectile(std::string pname, ProjectileDataList* weapini, std::vector<SHPImage*>*imagePool);
  ~Projectile();
  uint32_t getImageNum();
  //uint8_t getSpeed(){return speed;}
  bool doesRotate();
  bool AntiAir();
  bool AntiGround();
  bool AntiSubmarine();
  bool getInaccurate();

 private:
  uint32_t imagenum;
  uint8_t rotationimgs;

  /** @link aggregation */
  ProjectileData* lnkProjectileData;
};


#endif //PROJECTILE_H
