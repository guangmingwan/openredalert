// VQAHeader.h
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

#ifndef VQAHEADER_H
#define VQAHEADER_H

#include <cstdint>
#include <cstddef>

namespace VQA {

  // Copied from XCC Mixer (xcc.ra2.mods) by Olaf van der Spek

  /// @todo Fix/verify this for Big Endian
  inline uint8_t VQA_HI_BYTE(uint32_t x) {
    return (x & 0xff000000) >> 24;
  }

  const uint32_t vqa_t_mask = 0x00ffffff;

  // Each of these constants is derived from e.g. *(Uint32*)"CBF\0" etc.
  // We can't have these in the above form if we want to use them as switch
  // labels, even though they're consts.....
  const uint32_t vqa_cbf_id = 0x464243;
  const uint32_t vqa_cbp_id = 0x504243;
  const uint32_t vqa_cpl_id = 0x4C5043;
  const uint32_t vqa_snd_id = 0x444E53;
  const uint32_t vqa_vpt_id = 0x545056;
  const uint32_t vqa_vpr_id = 0x525056;
  const uint32_t vqa_vqfl_id = 0x4C465156;
  const uint32_t vqa_vqfr_id = 0x52465156;

  /** size of vqa header - so i know how many bytes to read in the file */
  const size_t header_size = sizeof(uint8_t) * 28 + sizeof(uint16_t) * 9
		+ sizeof(uint32_t) * 2;

  /**
   * Header of Movie in .VQA format
   *
   * @see VQAMovie
   */
  class VQAHeader {
   public:
    /** Always "WVQAVQHD" */
    uint8_t Signature[8];
    /** Size of header minus Signature (always 42 bytes) big endian */
    uint32_t RStartPos;
    /** VQA Version. 2 = C&C TD and C&C RA, 3 = C&C TS */
    uint16_t Version;
    /** VQA Flags. If bit 1 is set, VQA has sound */
    uint16_t Flags;
    /** Number of frames */
    uint16_t NumFrames;
    /** Width of each frame */
    uint16_t Width;
    /** Height of each frame */
    uint16_t Height;
    /** Width of each image block (usually 4) */
    uint8_t BlockW;
    /** Height of each image block (usually 2) */
    uint8_t BlockH;
    /** Number of frames per second? */
    uint8_t FrameRate;
    /** Number of frames that use the same lookup table (always 8 in TD and RA) */
    uint8_t CBParts;
    /** Number of colors used in Palette */
    uint16_t Colors;
    /** Maximum number of image blocks?? */
    uint16_t MaxBlocks;
    /** Unknown information */
    uint16_t Unknown1;
    /** Unknown information */
    uint32_t Unknown2;
    /** Sound frequency */
    uint16_t Freq;
    /** 1 = mono; 2 = stereo (TD and RA always 1) (TS is always 2) */
    uint8_t Channels;
    /** 8 or 16 bit sound */
    uint8_t Bits;
    /** Unknown information */
    uint8_t Unknown3[14];
  };
  
}

#endif //VQAHEADER_H
