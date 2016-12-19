// ExternalFiles.cpp
//
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

#include "externalvfs.h"

#include <map>

// Includes specifics to plateforms
#ifdef _MSC_VER
# include <windows.h>
#else
# include <dirent.h>
#endif

inline bool isRelativePath(const char *p) {
#ifdef _WIN32
  return ((strlen(p) == 0) || p[1] != ':') && p[0] != '\\' && p[0] != '/';
#else
  return p[0] != '/';
#endif
}

namespace ExtPriv {
  struct OpenFile {
    FILE *file;
    size_t size;
    std::string path;
  };
  typedef std::map<size_t, OpenFile> openfiles_t;
  openfiles_t openfiles;
  FILE* fcaseopen(std::string* path, const char* mode, uint32_t caseoffset = 0) throw();
  bool isdir(const std::string& path);
}

using namespace ExtPriv; // XXX:  This compiles, namespace ExtPriv {...} doesn't.

#ifdef __MORPHOS__
ExternalFiles::ExternalFiles(const char *defpath) : defpath("PROGDIR:") {
}
#else
ExternalFiles::ExternalFiles(const char *defpath) : defpath(defpath) {
}
#endif

/**
 */
ExternalFiles::~ExternalFiles() {
  // printf ("%s line %i: WARING external files destructor\n", __FILE__, __LINE__);
}

/**
 * Load an archive by this filename
 *
 * @param fname file name of the archive
 * @return <code>true</code> if the loading complete successfully else <code>false</code>
 */
bool ExternalFiles::loadArchive(const char *fname) {
  std::string pth(fname);
  if ("." == pth || "./" == pth) {
#ifdef __MORPHOS__
    path.push_back("PROGDIR:");
#else
    path.push_back("./");
#endif
    return true;
  }
  if (isRelativePath(fname)) {
#ifdef __MORPHOS__
    pth = defpath + fname;
#else
    pth = defpath + "/" + fname;
#endif
  } else {
    pth = fname;
  }
  if ('/' != pth[pth.length() - 1]) {
    pth += "/";
  }
  if (!isdir(pth)) {
    return false;
  }
  path.push_back(pth);
  return true;
}

/**
 *
 */
uintptr_t ExternalFiles::getFile(const char *fname, const char* mode) {
  ExtPriv::OpenFile newFile;
  FILE *f;
  uint32_t i;
  std::string filename;
  size_t size, fnum;

  if (mode[0] != 'r') {
    filename = fname;
    //printf ("%s line %i: open file %s\n", __FILE__, __LINE__, fname);
    f = fopen(filename.c_str(), mode);
    if (f != NULL) {
      newFile.file = f;
      // We'll just ignore file sizes for files being written for now.
      newFile.size = 0;
      newFile.path = filename;
      fnum = (size_t)f;
      openfiles[fnum] = newFile;
      return fnum;
    } // Error condition hanled at end of function
  }
  for (i = 0; i < path.size(); ++i)	{			//try to load the file at several different paths
    filename = path[i] + fname;
    f = fcaseopen(&filename, mode, path[i].length());
    if (f != NULL) {
      fseek(f, 0, SEEK_END);
      size = ftell(f);
      fseek(f, 0, SEEK_SET);
      newFile.file = f;
      newFile.size = size;
      newFile.path = filename;

      fnum = (size_t)f;
      openfiles[fnum] = newFile;
      return fnum;
    }
  }

  return this->ErrorLoadingFile;
}

/**
 */
void ExternalFiles::releaseFile(uintptr_t file)
{
  fclose(openfiles[file].file);
  openfiles.erase(file);
}

size_t ExternalFiles::readByte(uintptr_t file, uint8_t *databuf, size_t numBytes)
{
  return fread(databuf, 1, numBytes, openfiles[file].file);
}

size_t ExternalFiles::readWord(uintptr_t file, uint16_t *databuf, size_t numWords)
{
  size_t numRead;

  numRead = fread(databuf, 2, numWords, openfiles[file].file);

#ifdef WORDS_BIGENDIAN
  for (uint32_t i = 0; i < numRead; i++ ) {
    databuf[i] = SDL_Swap16(databuf[i]);
  }
#endif

  return numRead;
}

size_t ExternalFiles::readDWord(uintptr_t file, uint32_t *databuf, size_t numDWords)
{
  size_t numRead = fread(databuf, 4, numDWords, openfiles[file].file);

#ifdef WORDS_BIGENDIAN
  for (uint32_t i = 0; i < numRead; i++ ) {
    databuf[i] = SDL_Swap32(databuf[i]);
  }
#endif

  return numRead;
}

char* ExternalFiles::readLine(uintptr_t file, char *databuf, size_t buflen)
{

  return fgets(databuf, buflen, openfiles[file].file);
}

size_t ExternalFiles::writeByte(uintptr_t file, const uint8_t* databuf, size_t numBytes)
{
  return fwrite(databuf, 1, numBytes, openfiles[file].file);
}

/**
 */
size_t ExternalFiles::writeWord(uintptr_t file, const uint16_t *databuf, size_t numWords)
{
  size_t numWrote;
#ifdef WORDS_BIGENDIAN
  Uint16* tmp = new Uint16[numWords];
  uint32_t i;

  for( i = 0; i < numWords; i++ ) {
    tmp[i] = SDL_Swap16(databuf[i]);
  }

  numWrote = fwrite(tmp, 2, numWords, openfiles[file].file);
  if (tmp != NULL){
    delete[] tmp;
  }
  tmp = NULL;
#else

  numWrote = fwrite(databuf, 2, numWords, openfiles[file].file);
#endif

  return numWrote;
}

size_t ExternalFiles::writeDWord(uintptr_t file, const uint32_t *databuf, size_t numDWords)
{
  size_t numWrote;

#ifdef WORDS_BIGENDIAN
  Uint32 i;
  Uint32* tmp = new Uint32[numDWords];

  for( i = 0; i < numDWords; i++ ) {
    tmp[i] = SDL_Swap32(databuf[i]);
  }
  numWrote = fwrite(tmp, 4, numDWords, openfiles[file].file);
  if (tmp != NULL){
    delete[] tmp;
  }
  tmp = NULL;
#else

  numWrote = fwrite(databuf, 4, numDWords, openfiles[file].file);
#endif

  return numWrote;
}

void ExternalFiles::writeLine(uintptr_t file, const char *databuf)
{
  fputs(databuf, openfiles[file].file);
}

int ExternalFiles::vfs_printf(uintptr_t file, const char* fmt, va_list ap)
{
  int ret;
  ret = vfprintf(openfiles[file].file, fmt, ap);
  return ret;
}

void ExternalFiles::flush(uintptr_t file)
{
  fflush(openfiles[file].file);
}

void ExternalFiles::seekSet(uintptr_t file, size_t pos)
{
  fseek(openfiles[file].file, pos, SEEK_SET);
}

void ExternalFiles::seekCur(uintptr_t file, ptrdiff_t pos)
{
  fseek(openfiles[file].file, pos, SEEK_CUR);
}

size_t ExternalFiles::getPos(uintptr_t file) const {
  // @todo Abstract this const implementation of operator[].
  openfiles_t::const_iterator i = openfiles.find(file);
  if (openfiles.end() != i) {
    return ftell(i->second.file);
  }
  // @todo Throw an exception in a later iteration of code cleanup.
  return 0;
}

size_t ExternalFiles::getSize(uintptr_t file) const {
  // @todo Abstract this const implementation of operator[].
  openfiles_t::const_iterator i = openfiles.find(file);
  if (openfiles.end() != i) {
    return i->second.size;
  }
  // @todo Throw an exception in a later iteration of code cleanup.
  return 0;
}

const char* ExternalFiles::getPath(uintptr_t file) const {
  // @todo Abstract this const implementation of operator[].
  openfiles_t::const_iterator i = openfiles.find(file);
  if (openfiles.end() != i) {
    return i->second.path.c_str();
  }
  // @todo Throw an exception in a later iteration of code cleanup.
  return 0;
}

const char *ExternalFiles::getArchiveType() const {
  return "external file";
}

uintptr_t ExternalFiles::getFile(const char* fname) {
  return getFile(fname, "rb");
}

namespace ExtPriv {

  FILE* fcaseopen(std::string* name, const char* mode, uint32_t caseoffset) throw()
  {
    FILE* ret;

    if (name == NULL || mode == NULL)
      return NULL;

    //	printf ("%s line %i: Open file %s, mode = %s\n", __FILE__, __LINE__, name->c_str(), mode);

    ret = fopen(name->c_str(), mode);
    if (NULL != ret) {
      return ret;
    }
#if defined (_MSC_VER) || defined (__MORPHOS__)
    return NULL;
#else
    std::string &fname = *name;
    // Try all other case.  Assuming uniform casing.
    uint32_t i;
    // Skip over non-alpha chars.
    // @todo These are the old style text munging routines that are a) consise
    // and b) doesn't work with UTF8 filenames.
    for (i=caseoffset;i<fname.length()&&!isalpha(fname[i]);++i) {}
    if (islower(fname[i])) {
      transform(fname.begin()+caseoffset, fname.end(), fname.begin()+caseoffset, toupper);
    } else {
      transform(fname.begin()+caseoffset, fname.end(), fname.begin()+caseoffset, tolower);
    }
    ret = fopen(fname.c_str(), mode);
    if (NULL != ret) {
      return ret;
    }
    // @todo Try other tricks like "lower.EXT" or "UPPER.ext"
    return NULL;
#endif
  }

  /**
   * @param path Path to test
   * @return true if it's a Directory
   */
  bool isdir(const std::string& path)
  {
#ifdef _MSC_VER
    DWORD length = GetCurrentDirectory(0, 0);
    LPSTR orig_path = new CHAR[length];
    GetCurrentDirectory(length, orig_path);
    /*if (!SetCurrentDirectory(path.c_str())) {
     if (orig_path != 0)
     delete[] orig_path;
     orig_path = 0;
     return false;
     }*/
    SetCurrentDirectory(orig_path);
    if (orig_path != NULL)
      delete[] orig_path;
    orig_path = 0;
    return true;

#elif defined (__MORPHOS__)
    // TODO : need to chdir in directory
    struct stat fileinfo;
    stat( path.c_str(), &fileinfo );
    return S_ISDIR( fileinfo.st_mode );

#else
    // Try to open dir
    DIR *dir = opendir(path.c_str());
    if (NULL == dir) {
      return false;
    }
    closedir(dir);
    return true;

#endif
  }

} // namespace ExtPriv
