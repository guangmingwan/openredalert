// mixvfs.h
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

#ifndef MIXFILES_H
#define MIXFILES_H

#include <vector>
#include <map>

#include "vfs/archive.h"

namespace MIXPriv {

  template<class T>
  inline T ROL(T n) {return ((n << 1) | ((n >> 31) & 1));}

  // Magic constants
  const unsigned int TS_ID = 0x763c81dd;
  const unsigned long int mix_checksum = 0x00010000;
  const unsigned long int mix_encrypted = 0x00020000;

  /* data type for which game the specific
   * mix file is from. Different from the
   * game definitions in freecnc.h
   */
  enum game_t {game_td, game_ra, game_ts};
  // d = first 4 bytes of mix file
  inline game_t which_game(unsigned int d) {
    return (d == 0 || d == mix_checksum || d == mix_encrypted || d == (mix_encrypted | mix_checksum)) ? game_ra : game_td;
  }

  /** Information about size and hash of a packed file in mix archive */
#pragma pack(push, 1)
  struct MixHeader
  {
    /** =hash ?? =calculated id ??? */
    uint16_t c_files;
    /** Sie of the file */
    uint32_t size;
  };

  struct MixRecord {
    uint32_t id;
    uint32_t offset;
    uint32_t size;
  };

  /** only 256 mixfiles can be loaded */
  struct MIXEntry {
    uint8_t filenum;
    uint32_t offset;
    uint32_t size;
  };

  struct OpenFile {
    uint32_t id;
    size_t pos;
  };
#pragma pack(pop)

  enum tscheck_ {check_ts, nocheck_ts};

  typedef std::map<uint32_t, MIXEntry> mixheaders_t;
  typedef std::map<uintptr_t, OpenFile> openfiles_t;
}

class VFile;

class MIXFiles : public Archive {
 public:
  MIXFiles();
  ~MIXFiles();

  const char *getArchiveType() const;
  bool loadArchive(const char *fname);
  void unloadArchives();
  uintptr_t getFile(const char *fname);
  void releaseFile(uintptr_t file);

  size_t readByte(uintptr_t file, uint8_t *databuf, size_t numBytes);
  size_t readWord(uintptr_t file, uint16_t *databuf, size_t numWords);
  size_t readDWord(uintptr_t file, uint32_t *databuf, size_t numDWords);
  char *readLine(uintptr_t file, char *databuf, size_t buflen);

  void seekSet(uintptr_t file, size_t pos);
  void seekCur(uintptr_t file, ptrdiff_t pos);

  size_t getPos(uintptr_t file) const;
  size_t getSize(uintptr_t file) const;

  const char* getPath(uintptr_t file) const;

 private:
  uint32_t calcID(const std::string &name);
  void readMIXHeader(VFile* mix);
  MIXPriv::MixRecord* decodeHeader(VFile* mix, MIXPriv::MixHeader* header,
                                   MIXPriv::tscheck_ tscheck);

  std::vector<VFile*> mixfiles;
  MIXPriv::mixheaders_t mixheaders;
  
  MIXPriv::openfiles_t openfiles;
};

#endif //MIXFILES_H
