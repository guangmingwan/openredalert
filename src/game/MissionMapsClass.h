// MissionMapsClass.h
// 1.2
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

#ifndef MISSIONMAPSCLASS_H
#define MISSIONMAPSCLASS_H

#include <string>
#include <vector>

/**
 *  Mission map class
 *  reads out the missions from ____
 */
class MissionMapsClass {
 public:
  MissionMapsClass();

  std::string getGdiMissionMap(uint32_t missionNumber);
  std::string getNodMissionMap(uint32_t missionNumber);

 private:
  void readMissionData();

  std::vector<std::string> Mapdata;
  std::vector<std::string> NodMissionMaps;
  std::vector<std::string> GdiMissionMaps;
  std::vector<std::string> MissionBriefing;
  std::vector<std::string> MultiPlayerMapNames;
};

#endif //MISSIONMAPSCLASS_H
