// VFile.h
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

#ifndef VFILE_H
#define VFILE_H

#include <cstddef>
#include <cstdint>
#include <string>

class VFolder;

class VFileBase {
 public:
  virtual ~VFileBase() {}

  virtual size_t read(void *buffer, size_t buflen) = 0;
  virtual std::string readLine() = 0;

  virtual size_t write(void *buffer, size_t buflen) = 0;
  virtual void writeLine(const std::string &string) = 0;

  virtual void flush() = 0;

  virtual void seekSet(size_t pos) = 0;
  virtual void seekCur(ptrdiff_t offset) = 0;
  virtual size_t fileSize() = 0;
  virtual size_t tell() = 0;

  virtual std::string getPath() = 0;
};

class VFileInfo {
 public:
  virtual ~VFileInfo() {};

  virtual std::string getName() const = 0;
  virtual size_t getSize() const = 0;

  virtual VFileBase *open() const = 0;
};

class VFolder {
 public:
  virtual ~VFolder() {}

  virtual VFileBase *openFile(const std::string &name) = 0;
  virtual bool append(VFolder *folder) = 0;
};

class Archive;

/**
 * Virtual file class.
 *
 * All virtual files can be opened for reading, but only external files
 *  can be written to since it's mostly used for loading graphics,
 *  sound, etc. data.
 */
class VFile {
 public:
  VFile(uintptr_t filenum, Archive * arch);
  virtual ~VFile();

  size_t readByte(uint8_t *databuf, size_t numBytes);
  size_t readWord(uint16_t *databuf, size_t numWords);
  size_t readDWord(uint32_t *databuf, size_t numDWords);
  char *readLine(char *string, size_t buflen);

  size_t writeByte(uint8_t *databuf, size_t numBytes);
  size_t writeWord(uint16_t *databuf, size_t numWords);
  size_t writeDWord(uint32_t *databuf, size_t numDWords);
  void writeLine(const char *string);

  void flush();

  void seekSet(uint32_t pos);
  void seekCur(int32_t offset);
  size_t fileSize();
  size_t tell();

  const char *getPath();

 private:
  uintptr_t filenum;
  Archive * archive;
};

#endif //VFILE_H
