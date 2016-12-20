// MoneyCounter.h
// 1.4
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

#ifndef MONEYCOUNTER_H
#define MONEYCOUNTER_H

#include "ActionEvent.h"

class Player;

/**
 *
 */
class MoneyCounter : public ActionEvent {
 public:
  MoneyCounter(int32_t* money, Player* player, MoneyCounter * * backref);
  ~MoneyCounter();
  void run();

  uint16_t getDebt() const { return debtleft; }

  void addCredit(uint16_t amount, uint8_t PlayerNumb);
  void addDebt(uint16_t amount, uint8_t PlayerNumb);

  bool isScheduled() const { return queued; }

 private:
  static const uint8_t delta = 5;

  int32_t& money;
  Player * player;
  bool queued;
  // Seperate because we want both credit and debit sounds being played
  uint16_t creditleft;
  uint16_t debtleft;
  int32_t creditsound;
  int32_t debitsound;

  uint8_t step(uint16_t & value);
  bool sound;

  MoneyCounter **backref;

  void reshedule();
};

#endif //MONEYCOUNTER_H
