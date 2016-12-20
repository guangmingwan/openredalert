// SoundUtils.h
// 0.4
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

#ifndef SOUNDUTILS_H
#define SOUNDUTILS_H

#include <cstdint>

/**
 *
 */
class SoundUtils {
 public:
  static uint8_t Clip(int parameter0);

  static uint8_t Clip(int, int, int);

  static void IMADecode(uint8_t *output, uint8_t *input,
                        uint16_t compressed_size, int32_t& sample,
                        int32_t& index);

  static void WSADPCM_Decode(uint8_t *output, uint8_t *input,
                             uint16_t compressed_size,
                             uint16_t uncompressed_size);
};

#endif //SOUNDUTILS_H
