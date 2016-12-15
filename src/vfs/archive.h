// Archive.h
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

#ifndef ARCHIVE_H
#define ARCHIVE_H

/**
 * Abstract interface to manipulate VFile in archives
 */
class Archive {
 public:
  virtual ~Archive() {}
  virtual const char *getArchiveType() const = 0;
  virtual bool loadArchive(const char *fname) = 0;
  virtual void unloadArchives() {};
  virtual uintptr_t getFile(const char *fname) = 0;
  virtual void releaseFile(uintptr_t file) = 0;

  virtual uint32_t readByte(uintptr_t file, uint8_t *databuf, uint32_t numBytes) = 0;
  virtual uint32_t readWord(uintptr_t file, uint16_t *databuf, uint32_t numWords) = 0;
  virtual uint32_t readDWord(uintptr_t file, uint32_t *databuf, uint32_t numDWords) = 0;

  /**
   * Read a line of file.
   * \param file id of the file in archive
   * \param databuf will contain the read  line
   * \param buflen size of the buffer
   */
  virtual char* readLine(uintptr_t file, char *databuf, uint32_t buflen) = 0;

  /* Since only external files can write, we provide stubs here for the other
   * plugins.
   */
  virtual uint32_t writeByte(uintptr_t file, const uint8_t* databuf, uint32_t numBytes) {return 0;}
  virtual uint32_t writeWord(uintptr_t file, const uint16_t* databuf, uint32_t numWords) {return 0;}
  virtual uint32_t writeDWord(uintptr_t file, const uint32_t* databuf, uint32_t numDWords) {return 0;}
  virtual void writeLine(uintptr_t file, const char* databuf) {}

  virtual void flush(uintptr_t file) {}

  virtual void seekSet(uintptr_t file, uint32_t pos) = 0;
  virtual void seekCur(uintptr_t file, int32_t pos) = 0;

  virtual uint32_t getPos(uintptr_t file) const = 0;
  virtual uint32_t getSize(uintptr_t file) const = 0;
  virtual const char* getPath(uintptr_t file) const = 0;
};

#endif //ARCHIVE_H
