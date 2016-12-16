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

#include "RealFile.h"

RealFile::RealFile(const std::string &path, FILE *file) {
  this->path = path;
  this->file = file;
}

RealFile::~RealFile() {
}

size_t RealFile::read(void *buffer, size_t buflen) {
  return fread(buffer, 1, buflen, file);
}

std::string RealFile::readLine() {
  char data[1024 * 4];
  if (fgets(data, 1024 * 4, file) == nullptr) {
    return std::string();
  }
  return data;
}

size_t RealFile::write(void *buffer, size_t buflen) {
  return fwrite(buffer, 1, buflen, file);
}

void RealFile::writeLine(const std::string &string) {
  fputs(string.c_str(), file);
}

void RealFile::flush() {
  fflush(file);
}

void RealFile::seekSet(size_t pos) {
  fseek(file, pos, SEEK_SET);
}

void RealFile::seekCur(ptrdiff_t offset) {
  long current_pos = ftell(file);
  long new_pos = current_pos + offset;
  if (new_pos >= 0 && new_pos < fileSize()) {
    fseek(file, new_pos, SEEK_SET);
  }
}

size_t RealFile::fileSize() {
  long current_pos = ftell(file);
  fseek(file, 0, SEEK_END);
  size_t result = ftell(file);
  fseek(file, current_pos, SEEK_SET);
  return result;
}

size_t RealFile::tell() {
  return ftell(file);
}

std::string RealFile::getPath() {
  return path;
}






ContainedFile::ContainedFile(const std::string &path, VFileBase *file, size_t pos, size_t size) {
  this->path = path;
  this->file = file;
  this->pos = pos;
  this->size = size;
  this->current_pos = 0;
}

ContainedFile::~ContainedFile() {
}

size_t ContainedFile::read(void *buffer, size_t buflen) {
  file->seekSet(pos + current_pos);
  size_t result = file->read(buffer, buflen);
  current_pos += result;
  return result;
}

std::string ContainedFile::readLine() {
  file->seekSet(pos + current_pos);
  size_t start_pos = pos + current_pos;
  std::string result = file->readLine();
  current_pos += file->tell() - start_pos;
  return result;
}

size_t ContainedFile::write(void *buffer, size_t buflen) {
  file->seekSet(pos + current_pos);
  size_t result = file->write(buffer, buflen);
  current_pos += result;
  return result;
}

void ContainedFile::writeLine(const std::string &string) {
  file->seekSet(pos + current_pos);
  size_t start_pos = pos + current_pos;
  file->writeLine(string);
  current_pos += file->tell() - start_pos;
}

void ContainedFile::flush() {
  file->flush();
}

void ContainedFile::seekSet(size_t pos) {
  current_pos = pos;
}

void ContainedFile::seekCur(ptrdiff_t offset) {
  current_pos += offset;
}

size_t ContainedFile::fileSize() {
  return size;
}

size_t ContainedFile::tell() {
  return current_pos;
}

std::string ContainedFile::getPath() {
  return path;
}





MIXFolder::MIXFolder(VFileBase *file) {
}

MIXFolder::~MIXFolder() {
}

VFileBase *MIXFolder::openFile(const std::string &name) {
  return nullptr;
}

bool MIXFolder::append(VFolder *folder) {
  return false;
}

