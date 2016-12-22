// BarrelExplosionActionEvent.cpp
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

#include "BarrelExplosionActionEvent.h"

#include <cmath>

#include "ExplosionAnim.h"
#include "video/ImageCache.h"
#include "ActionEventQueue.h"
#include "CnCMap.h"
#include "UnitAndStructurePool.h"
#include "Structure.h"
#include "Unit.h"

namespace p {
  extern ActionEventQueue* aequeue;
  extern CnCMap* ccmap;
  extern UnitAndStructurePool* uspool;
}
namespace pc {
  extern ImageCache* imgcache;
}

/**
 * @param p  of the anim
 * @param pos Position of the animation in the map
 */
BarrelExplosionActionEvent::BarrelExplosionActionEvent(unsigned int p,
                                                       unsigned int pos) :
  ActionEvent(p)
{
  // Set a delay (0.512 sec)
  setDelay(6);

  // Save the position
  position = pos;

  // Reschedule this anim
  p::aequeue->scheduleEvent(this);
}

/**
 * @todo Add sound code
 * @todo change 3 in delay of ExploAnim
 */
void BarrelExplosionActionEvent::run() {
  // Play the flame sound #1
  //pc::sfxeng->PlaySound("firebl3.aud");

  // Play the large fire misc anim
  uint32_t numImageNapalmBarrel = pc::imgcache->loadImage("napalm3.shp");
  // 3 = delay 14 = num image in ^    -36 = height/2 in ^  -36 = width/2 in ^
  new ExplosionAnim(3, position, numImageNapalmBarrel, 14, -36, -36);

  for (uint32_t ypos = 0; ypos < p::ccmap->getHeight(); ypos++) {
    for (uint32_t xpos = 0; xpos < p::ccmap->getWidth(); xpos++) {
      uint32_t curpos = xpos + ypos * p::ccmap->getWidth();

      uint32_t xtiles = position % p::ccmap->getWidth() -
                        curpos % p::ccmap->getWidth();
      uint32_t ytiles = position / p::ccmap->getWidth() -
                        curpos / p::ccmap->getWidth();

      double distance = sqrt((double)(xtiles*xtiles + ytiles*ytiles));

      double realDamage = 256.;
      for (unsigned int m = 0; m < distance; m++) {
        realDamage = realDamage * 0.3;
      }

      int damage = (int)realDamage;
      if (damage > 1) {
        // Structure to find
        Structure* str = p::uspool->getStructureAt(curpos, false);
        // If their are a structure
        if (str != 0) {
          str->applyDamage(damage, 0, 0);
        } else {
          // Find an unit
          Unit* unitTarget = p::uspool->getGroundUnitAt(curpos, 0x80);
          if (unitTarget != 0) {
            unitTarget->applyDamage(damage, 0, 0);
          }
        }
      }
    }
  }

  // After launched anim and apply damage, destroy this animation
  delete this;
}
