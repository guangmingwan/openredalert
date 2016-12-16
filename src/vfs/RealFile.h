// RealFile.h
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

#ifndef REALFILE_H
#define REALFILE_H

#include "VFile.h"

class RealFile : public VFileBase {
 public:
  RealFile(const std::string &path, FILE *file);
  virtual ~RealFile();

  virtual size_t read(void *buffer, size_t buflen);
  virtual std::string readLine();

  virtual size_t write(void *buffer, size_t buflen);
  virtual void writeLine(const std::string &string);

  virtual void flush();

  virtual void seekSet(size_t pos);
  virtual void seekCur(ptrdiff_t offset);
  virtual size_t fileSize();
  virtual size_t tell();

  virtual std::string getPath();

 protected:
  std::string path;
  FILE *file;
};

class ContainedFile : public VFileBase {
 public:
  ContainedFile(const std::string &path, VFileBase *file, size_t pos, size_t size);
  virtual ~ContainedFile();

  virtual size_t read(void *buffer, size_t buflen);
  virtual std::string readLine();

  virtual size_t write(void *buffer, size_t buflen);
  virtual void writeLine(const std::string &string);

  virtual void flush();

  virtual void seekSet(size_t pos);
  virtual void seekCur(ptrdiff_t offset);
  virtual size_t fileSize();
  virtual size_t tell();

  virtual std::string getPath();

 protected:
  std::string path;
  VFileBase *file;
  size_t pos;
  size_t size;
  size_t current_pos;
};

class MIXFolder : public VFolder {
 public:
  MIXFolder(VFileBase *file);
  virtual ~MIXFolder();

  virtual VFileBase *openFile(const std::string &name);
  virtual bool append(VFolder *folder);

 protected:
  VFileBase *file;
};

#endif  // REALFILE_H
