// Talkback.h
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

#ifndef TALKBACK_H
#define TALKBACK_H

#include <string>
#include <map>
#include <vector>

#include "TalkbackType.h"

class INIFile;

/**
 * Object that manage talkback
 */
class Talkback {
 public:
  Talkback();
  void load(std::string talkback, INIFile* tbini);
  const char* getRandTalk(TalkbackType type);

 private:
  Talkback(const Talkback&);
  Talkback& operator=(const Talkback&);

  static std::map<std::string, TalkbackType> talktype;
  static bool talktype_init;

  typedef std::map<TalkbackType, std::vector<std::string> > t_talkstore;
  t_talkstore talkstore;

  void merge(Talkback* mergee);
  std::vector<std::string>& getTypeVector(TalkbackType type);
  TalkbackType getTypeNum(std::string name);
};

#endif //TALKBACK_H
