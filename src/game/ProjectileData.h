// ProjectileData.h
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

#ifndef PROJECTILEDATA_H
#define PROJECTILEDATA_H

#include <string>

#include "misc/INIFile.h"

class ProjectileData {
 public:
  ProjectileData();

  uint32_t getAA();

  void setAA(uint32_t AA);

  uint32_t getAG();

  void setAG(uint32_t AG);

  int getASW();

  void setASW(int ASW);

  int getAnimates();

  void setAnimates(int animates);

  int getArcing();

  void setArcing(int arcing);

  int getArm();

  void setArm(int arm);

  int getDegenerates();

  void setDegenerates(int degenerates);

  int getDropping();

  void setDropping(int dropping);

  int getFrames();

  void setFrames(int frames);

  int getGigundo();

  void setGigundo(int gigundo);

  int getHigh();

  void setHigh(int high);

  std::string getImage();

  void setImage(std::string image);

  int getInaccurate();

  void setInaccurate(int inaccurate);

  int getInviso();

  void setInviso(int inviso);

  int getProximity();

  void setProximity(int proximity);

  int getROT();

  void setROT(int ROT);

  int getRanged();

  void setRanged(int ranged);

  int getRotates();

  void setRotates(int rotates);

  int getShadow();

  void setShadow(int shadow);

  int getTranslucent();

  void setTranslucent(int translucent);

  int getParachuted();

  void setParachuted(int parachuted);

  int getUnderWater();

  void setUnderWater(int underWater);

  static ProjectileData* loadProjectileData(INIFile * file, std::string name);
  void print();

 private:
  uint32_t AA;
  uint32_t AG;
  int ASW;
  int animates;
  int arcing;
  int arm;
  int degenerates;
  int dropping;
  int frames;
  int gigundo;
  int high;
  std::string image;
  int inaccurate;
  int inviso;
  int proximity;
  int ROT;
  int ranged;
  int rotates;
  int shadow;
  int translucent;
  int parachuted;
  int underWater;
};

#endif //PROJECTILEDATA_H
