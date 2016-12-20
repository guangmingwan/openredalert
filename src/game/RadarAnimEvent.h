// RadarAnimEvent.h
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

#ifndef RADARANIMEVENT_H
#define RADARANIMEVENT_H

#include "ActionEvent.h"

class SHPImage;
class Sidebar;

/**
 *
 */
class RadarAnimEvent : public ActionEvent {
 public:
  /**
   * if mode = 0 => RADAR ON
   * if mode = 1 => RADAR OFF
   */
  RadarAnimEvent(uint8_t mode, Sidebar* sidebar);
  void run();

 private:
  uint8_t mode;
  uint8_t frame;
  uint8_t framend;

  Sidebar* sidebar;

  SHPImage* animImagesBad;
  SHPImage* logoRadarBad;

  SHPImage* animImagesGood;
  SHPImage* logoRadarGood;
};

#endif //RADARANIMEVENT_H
