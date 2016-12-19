// VFile.cpp
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

#include "VFile.h"

#include "archive.h"

VFile::VFile(uintptr_t filenum, Archive *arch) {
  this->filenum = filenum;
  this->archive = arch;
}

VFile::~VFile() {
  archive->releaseFile(filenum);
}

size_t VFile::readByte(uint8_t * databuf, size_t numBytes) {
  return archive->readByte(filenum, databuf, numBytes);
}

size_t VFile::readWord(uint16_t * databuf, size_t numWords) {
  return archive->readWord(filenum, databuf, numWords);
}

size_t VFile::readDWord(uint32_t * databuf, size_t numDWords) {
  return archive->readDWord(filenum, databuf, numDWords);
}

char * VFile::readLine(char * string, size_t buflen) {
  return archive->readLine(filenum, string, buflen);
}

size_t VFile::writeByte(uint8_t * databuf, size_t numBytes) {
  return archive->writeByte(filenum, databuf, numBytes);
}

size_t VFile::writeWord(uint16_t * databuf, size_t numWords) {
  return archive->writeWord(filenum, databuf, numWords);
}

size_t VFile::writeDWord(uint32_t * databuf, size_t numDWords) {
  return archive->writeDWord(filenum, databuf, numDWords);
}

void VFile::writeLine(const char * string) {
  archive->writeLine(filenum, string);
}

void VFile::flush() {
  archive->flush(filenum);
}

void VFile::seekSet(size_t pos) {
  archive->seekSet(filenum, pos);
}

void VFile::seekCur(ptrdiff_t offset) {
  archive->seekCur(filenum, offset);
}

size_t VFile::fileSize() {
  return archive->getSize(filenum);
}

size_t VFile::tell() {
  return archive->getPos(filenum);
}

const char * VFile::getPath() {
  return archive->getPath(filenum);
}
