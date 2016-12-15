// Blowfish.h
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

#ifndef BLOWFISH_H
#define BLOWFISH_H

#include <cstdint>

typedef uint32_t t_bf_p[18];
typedef uint32_t t_bf_s[4][256];

/**
 * Object to encipher/decipher data with BlowFish algorythm
 *
 * Modified slightly for FreeCNC use by Kareem Dana
 * Special Thanks to Olaf van der Spek (xcc.ra2mods.com) for the original
 *
 * this is needed so we can read the MIX files
 */
class Cblowfish {
 public:
  void set_key(const uint8_t* key, uint32_t cb_key);
  void encipher(uint32_t& xl, uint32_t& xr) const;
  void encipher(const void* s, void* d, uint32_t size) const;
  void decipher(uint32_t& xl, uint32_t& xr) const;
  void decipher(const void* s, void* d, int size) const;

 private:
  inline uint32_t S(uint32_t x, int i) const;
  inline uint32_t bf_f(uint32_t x) const;
  inline void ROUND(uint32_t& a, uint32_t b, int n) const;

  t_bf_p m_p;
  t_bf_s m_s;
};

#endif //BLOWFISH_H
