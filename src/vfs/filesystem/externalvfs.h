// ExternalFiles.h
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

#ifndef EXTERNALVFS_H
#define EXTERNALVFS_H

#include <string>
#include <vector>

#include "vfs/archive.h"

/**
 * Object that provide methodes to load/read/write external files (not in original archives of the game
 */
class ExternalFiles : public Archive {
 public:
  ExternalFiles(const char *defpath);
  ~ExternalFiles();

  const char *getArchiveType() const;
  bool loadArchive(const char *fname);
  /**
   * Can't use default argument as we need exact type signature for inheritence.
   * try to load a file. if not found, return -1 else return the filedescriptor(?)
   */
  uintptr_t getFile(const char* fname);
  ///see other overload for details
  uintptr_t getFile(const char *fname, const char* mode);
  void releaseFile(uintptr_t file);

  uint32_t readByte(uintptr_t file, uint8_t *databuf, uint32_t numBytes);
  uint32_t readWord(uintptr_t file, uint16_t *databuf, uint32_t numWords);
  uint32_t readDWord(uintptr_t file, uint32_t *databuf, uint32_t numDWords);
	 /**
    * Read a line of file.
    */
  char* readLine(uintptr_t file, char *databuf, uint32_t buflen);

  uint32_t writeByte(uintptr_t file, const uint8_t *databuf, uint32_t numBytes);
  uint32_t writeWord(uintptr_t file, const uint16_t *databuf, uint32_t numWords);
  uint32_t writeDWord(uintptr_t file, const uint32_t *databuf, uint32_t numDWords);
  void writeLine(uintptr_t file, const char *databuf);
  int vfs_printf(uintptr_t file, const char* fmt, va_list ap);
  void flush(uintptr_t file);

  void seekSet(uintptr_t file, uint32_t pos);
  void seekCur(uintptr_t file, int32_t pos);

  uint32_t getPos(uintptr_t file) const;
  uint32_t getSize(uintptr_t file) const;
  const char* getPath(uintptr_t file) const;

  static const uintptr_t ErrorLoadingFile = (uintptr_t)-1;			///<returned in case file could not be loaded

 private:
  std::string defpath;
  std::vector<std::string> path;
};

#endif //EXTERNALVFS_H
