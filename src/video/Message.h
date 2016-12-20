// Message.h
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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

/**
 * @todo Replace this class with a std::pair<string, Uint32>
 */
class Message {
 public:
  Message(std::string msg, uint32_t deltime);

  const char* getMessage() const;
  bool expired(uint32_t time) const;

 private:
  std::string message;
  uint32_t deltime;
};

#endif //MESSAGE_H
