// WarheadData.cpp
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

#include "WarheadData.h"

#include <iostream>

#include "misc/INIFile.h"
#include "misc/common.h"

#include "misc/INIFile.h"

uint32_t WarheadData::getSpread() {
  return spread;
}

void WarheadData::setSpread(uint32_t spread) {
  this->spread = spread;
}

uint32_t WarheadData::getWall() {
  return wall;
}

void WarheadData::setWall(uint32_t wall) {
  this->wall = wall;
}

uint32_t WarheadData::getWood() {
  return wood;
}

void WarheadData::setWood(uint32_t wood) {
  this->wood = wood;
}

uint32_t WarheadData::getOre() {
  return ore;
}

void WarheadData::setOre(uint32_t ore) {
  this->ore = ore;
}

uint32_t WarheadData::getVersusNone() {
  return versusNone;
}

void WarheadData::setVersusNone(uint32_t versusNone) {
  this->versusNone = versusNone;
}

uint32_t WarheadData::getVersusWood() {
  return versusWood;
}

void WarheadData::setVersusWood(uint32_t versusWood) {
  this->versusWood = versusWood;
}

uint32_t WarheadData::getVersusLight() {
  return versusLight;
}

void WarheadData::setVersusLight(uint32_t versusLight) {
  this->versusLight = versusLight;
}

uint32_t WarheadData::getVersusHeavy() {
  return versusHeavy;
}

void WarheadData::setVersusHeavy(uint32_t versusHeavy) {
  this->versusHeavy = versusHeavy;
}

uint32_t WarheadData::getVersusConcrete() {
  return versusConcrete;
}

void WarheadData::setVersusConcrete(uint32_t versusConcrete) {
  this->versusConcrete = versusConcrete;
}

uint32_t WarheadData::getExplosion() {
  return explosion;
}

void WarheadData::setExplosion(uint32_t explosion) {
  this->explosion = explosion;
}

uint32_t WarheadData::getInfDeath() {
  return infDeath;
}

void WarheadData::setInfDeath(uint32_t infDeath) {
  this->infDeath = infDeath;
}

WarheadData* WarheadData::loadWarheadData(INIFile * file, std::string name) {
  WarheadData* ptrWarheadData;

  // Create the WarheadData object
  ptrWarheadData = new WarheadData();

  // Spread = damage spread factor [larger means greater spread] (def=1)
  //  [A value of 1 means the damage is halved every pixel distant from
  // center point.
  //   a value of 2 means damage is halved every 2 pixels, etc.]
  uint32_t tmpSpread = file->readInt(name, "Spread", 1);
  ptrWarheadData->setSpread(tmpSpread);

  // Wall = Does this warhead damage concrete walls (def=no)?
  ptrWarheadData->setWall(file->readYesNo(name, "Wall", 0));

  // Ore = Does this warhead destroy ore (def=no)?
  ptrWarheadData->setOre(file->readYesNo(name, "Ore", 0));

  // Verses = damage value verses various armor types (as percentage
  // of full damage)...
  // -vs- none, wood (buildings), light armor, heavy armor, concrete
  // @todo REFACTOR THAT
  std::string tmpPtVerses = file->readString(name, "Verses", "");
  if (tmpPtVerses != "") {
    uint32_t versus[5];

    versus[0] = 100;
    versus[1] = 100;
    versus[2] = 100;
    versus[3] = 100;
    versus[4] = 100;

    std::vector<char*> toto = splitList(tmpPtVerses.c_str(), ',');

    sscanf(toto[0], "%u", &versus[0]);
    sscanf(toto[1], "%u", &versus[1]);
    sscanf(toto[2], "%u", &versus[2]);
    sscanf(toto[3], "%u", &versus[3]);
    sscanf(toto[4], "%u", &versus[4]);

    ptrWarheadData->setVersusNone(versus[0]);
    ptrWarheadData->setVersusWood(versus[1]);
    ptrWarheadData->setVersusLight(versus[2]);
    ptrWarheadData->setVersusHeavy(versus[3]);
    ptrWarheadData->setVersusConcrete(versus[4]);
  }

  // Explosion = which explosion set to use when warhead of this
  // type impacts (def=0)
  // 0=none, 1=piff, 2=piffs, 3=fire, 4=frags, 5=pops, 6=nuke
  uint32_t tmpExplosion = file->readInt(name.c_str(), "Explosion", 0);
  ptrWarheadData->setExplosion(tmpExplosion);

  // InfDeath = which infantry death animation to use (def=0)
  // 0=instant die, 1=twirl die, 2=explodes, 3=flying death,
  // 4=burn death, 5=electro
  uint32_t tmpInfDeath = file->readInt(name.c_str(), "InfDeath", 0);
  ptrWarheadData->setInfDeath(tmpInfDeath);

  // Returns the constructed object
  return ptrWarheadData;
}

/**
 * Print the Data
 */
void WarheadData::print() {
  std::cout << "Spread=" << getSpread() << std::endl;
  std::cout << "Wall=" << getWall() << std::endl;
  std::cout << "Wood=" << getWood() << std::endl;
  std::cout << "Ore=" << getOre() << std::endl;
  std::cout << "Verses=" << getVersusNone() << "%," << getVersusWood() << "%,"
  << getVersusLight() << "%," << getVersusHeavy() << "%,"
  << getVersusConcrete() << "%" << std::endl;
  std::cout << "Explosion=" << getExplosion() << std::endl;
  std::cout << "InfDeath=" << getInfDeath() << std::endl;
}

