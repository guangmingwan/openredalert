// mixvfs.cpp
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

#include "mixvfs.h"

#include <algorithm>
#include <cstring>
#include "blowfish.h"
#include "ws-key.h"
#include "include/fcnc_endian.h"
#include "vfs/vfs.h"
#include "vfs/VFile.h"

using namespace MIXPriv;

/**
 *
 */
MIXFiles::MIXFiles() {
}

MIXFiles::~MIXFiles() {
  // Unload all MIX archives
  unloadArchives();
}

/**
 * Load a specifique archive
 */
bool MIXFiles::loadArchive(const char *fname) {
  // Try to load the archive file
  VFile *file = VFSUtils::VFS_Open(fname);
  if (file == 0) {
    return false;
  }
  printf("MIX archive loaded '%s'\n", fname);
  mixfiles.push_back(file);
  readMIXHeader(file);
  return true;
}

/**
 * Unload all MIX archives
 */
void MIXFiles::unloadArchives() {
  for (size_t i = 0; i < mixfiles.size(); ++i) {
    VFSUtils::VFS_Close(mixfiles[i]);
  }
  mixfiles.resize(0);
  mixheaders.clear();
}

/**
 * Search a file from a name ???
 */
uintptr_t MIXFiles::getFile(const char *fname) {
  // Calcul ID of the string
  uint32_t id = calcID(fname);

  mixheaders_t::iterator epos = mixheaders.find(id);
  if (mixheaders.end() == epos) {
    return (uintptr_t)-1;
  }

  OpenFile newfile;
  newfile.id = id;
  newfile.pos = 0;
  openfiles[id] = newfile;

  return id;
}

/**
 * Remove a file in the archive
 */
void MIXFiles::releaseFile(uintptr_t file) {
  // Remove 'file' in the archive
  openfiles.erase(file);
}

/**
 * Function to calculate a idnumber from a filename
 *
 * @param name the filename
 * @return the id.
 */
uint32_t MIXFiles::calcID(const std::string &name) {
  size_t size = name.length();
  size = ((size_t)((size + 3) / 4)) * 4;
  char *buffer = new char[size];
  memset(buffer, 0, size);

  for (size_t i = 0; name[i] != 0 && i < size; i++){
    buffer[i]=toupper(name[i]);
  }

  uint32_t calc = 0;
  uint32_t *qbuf = (uint32_t*)buffer;
  size /= 4;
  for (size_t i = 0; i < size; i++) {
    calc = ROL(calc) + le32toh(qbuf[i]);
  }

  delete[] buffer;

  return calc;
}

/**
 * Decodes RA/TS Style MIX headers. Assumes you have already checked if
 *  header is encrypted and that mix is seeked to the start of the WSKey
 *
 * @param mix pointer to vfile for the mixfile
 * @param header pointer to header object that will store the mix's header
 * @param tscheck if equal to check_ts, will check if mix is from Tiberian Sun.
 * @return pointer to MixRecord
 */
MixRecord* MIXFiles::decodeHeader(VFile* mix, MixHeader* header, tscheck_ tscheck) {
  uint8_t WSKey[80];        // 80-byte Westwood key
  uint8_t BFKey[56];        // 56-byte blow fish key
  uint8_t Block[8];         // 8-byte block to store blowfish stuff in
  Cblowfish bf;
  uint8_t *e;
  MixRecord* mindex;

  mix->readByte(WSKey, 80);
  get_blowfish_key((const uint8_t*)&WSKey, (uint8_t*)&BFKey);
  bf.set_key((const uint8_t*)&BFKey, 56);
  mix->readByte(Block, 8);

  bf.decipher(&Block, &Block, 8);

  // Extract the header from Block
  memcpy(&header->c_files, &Block[0], sizeof(uint16_t));
  memcpy(&header->size, &Block[sizeof(uint16_t)], sizeof(uint32_t));
  header->c_files = le16toh(header->c_files);
  header->size = le32toh(header->size);

  // Decrypt all indexes
  const int m_size = sizeof(MixRecord) * header->c_files;
  const int m_f = (m_size + 5) & ~7;
  mindex = new MixRecord[header->c_files];
  e = new uint8_t[m_f];
  //fread(e, m_f, 1, mix);
  mix->readByte(e, m_f);
  memcpy(mindex, &Block[6], 2);
  bf.decipher(e, e, m_f);

  memcpy(reinterpret_cast<uint8_t*>(mindex) + 2, e, m_size - 2);
  delete[] e;

  for (int i = 0; i < header->c_files; i++) {
    mindex[i].id = le32toh(mindex[i].id);
    mindex[i].offset = le32toh(mindex[i].offset);
    mindex[i].size = le32toh(mindex[i].size);
#if 0
    if (check_ts == tscheck) {
      if (mindex[i].offset & 0xf)
        aligned = false;
      if (mindex[i].id == TS_ID)
        game = game_ts;
    }
#endif
    /* 92 = 4 byte flag + 6 byte header + 80 byte key + 2 bytes (?) */
    mindex[i].offset += 92 + m_f; /* re-center offset to be absolute offset */
  }
  /*
   if (aligned) game = game_ts;
   */
  return mindex;
}

/**
 * read the mixheader
 */
void MIXFiles::readMIXHeader(VFile *mix) {
  // Read header
  MixHeader header;
  mix->readWord(&header.c_files, 1);
  mix->readDWord(&header.size, 1);
  header.c_files = le16toh(header.c_files);
  header.size = le32toh(header.size);

  uint32_t flags = header.c_files | (header.size << 16);

  MixRecord *m_index = NULL;
  game_t game = which_game(flags);
  if (game == game_ra) {
    mix->seekCur(-2);
    if (flags & mix_encrypted) {
      m_index = decodeHeader(mix, &header, check_ts);
    } else { /* mix is not encrypted */
      bool aligned = true;
      mix->seekSet(4);
      mix->readWord(&header.c_files, 1);
      mix->readDWord(&header.size, 1);

      const int m_size = sizeof(MixRecord) * header.c_files;
      m_index = new MixRecord[header.c_files];
      mix->readByte((uint8_t*)m_index, m_size);
      for (uint16_t i = 0; i < header.c_files; i++) {
        m_index[i].id = le32toh(m_index[i].id);
        m_index[i].size = le32toh(m_index[i].size);
        m_index[i].offset = le32toh(m_index[i].offset);

        if (m_index[i].offset & 0xf)
          aligned = false;
        if (m_index[i].id == TS_ID)
          game = game_ts;
        m_index[i].offset += 4 + sizeof(MixHeader) + m_size;
      }
      if (aligned)
        game = game_ts;
    }
  } else if (game_td == game) {
#ifdef WORDS_BIGENDIAN
    mix->seekSet(0);
    mix->readWord(&header.c_files, 1);
    mix->readDWord(&header.size, 1);
#endif

    const int m_size = sizeof(MixRecord) * header.c_files;
    m_index = new MixRecord[header.c_files];
    //fread(reinterpret_cast<Uint8 *>(m_index), m_size, 1, mix);
    mix->readByte((uint8_t*)m_index, m_size);
    for (uint16_t i = 0; i < header.c_files; i++) {
      m_index[i].id = le32toh(m_index[i].id);
      m_index[i].offset = le32toh(m_index[i].offset);
      m_index[i].size = le32toh(m_index[i].size);
      /* 6 = 6 byte header - no other header/flags or keys in TD mixes */
      m_index[i].offset += 6 + m_size;
    }
  }
  for (uint16_t i = 0; i < header.c_files; ++i) {
    MIXEntry mentry;
    mentry.filenum = (uint8_t)mixfiles.size()-1;
    mentry.offset = m_index[i].offset;
    mentry.size = m_index[i].size;
    mixheaders[m_index[i].id] = mentry;
  }
  delete[] m_index;
}

size_t MIXFiles::readByte(uintptr_t file, uint8_t *databuf, size_t numBytes) {
  uint32_t id = openfiles[file].id;
  size_t pos = openfiles[file].pos;

  MIXEntry me = mixheaders[id];

  mixfiles[me.filenum]->seekSet(me.offset+pos);

  size_t numRead = std::min(numBytes, (me.size-pos));
  numRead = mixfiles[me.filenum]->readByte(databuf, numRead);
  openfiles[file].pos += numRead;
  return numRead;
}

size_t MIXFiles::readWord(uintptr_t file, uint16_t *databuf, size_t numWords) {
  uint32_t id = openfiles[file].id;
  size_t pos = openfiles[file].pos;

  MIXEntry me = mixheaders[id];

  mixfiles[me.filenum]->seekSet(me.offset+pos);

  size_t numRead = std::min(numWords, ((me.size-pos)>>1));
  numRead = mixfiles[me.filenum]->readWord(databuf, numRead);
  openfiles[file].pos += numRead<<1;
  return numRead;
}

size_t MIXFiles::readDWord(uintptr_t file, uint32_t *databuf, size_t numDWords) {
  uint32_t id = openfiles[file].id;
  size_t pos = openfiles[file].pos;

  MIXEntry me = mixheaders[id];

  mixfiles[me.filenum]->seekSet(me.offset+pos);

  size_t numRead = std::min(numDWords, ((me.size-pos)>>2));
  numRead = mixfiles[me.filenum]->readDWord(databuf, numRead);
  openfiles[file].pos += numRead<<2;
  return numRead;
}

char* MIXFiles::readLine(uintptr_t file, char *databuf, size_t buflen) {
  uint32_t id = openfiles[file].id;
  size_t pos = openfiles[file].pos;

  MIXEntry me = mixheaders[id];

  mixfiles[me.filenum]->seekSet(me.offset+pos);

  size_t numRead = std::min(buflen-1, me.size-pos);
  if (numRead == 0) {
    return NULL;
  }
  char *retval = mixfiles[me.filenum]->readLine(databuf, numRead+1);
  openfiles[file].pos += strlen(databuf);
  return retval;
}

void MIXFiles::seekSet(uintptr_t file, size_t pos) {
  openfiles[file].pos = pos;
  if( openfiles[file].pos > mixheaders[openfiles[file].id].size ) {
    openfiles[file].pos = mixheaders[openfiles[file].id].size;
  }
  mixfiles[mixheaders[openfiles[file].id].filenum]->seekSet(openfiles[file].pos+mixheaders[openfiles[file].id].offset);
}

void MIXFiles::seekCur(uintptr_t file, ptrdiff_t pos) {
  openfiles[file].pos += pos;
  if( openfiles[file].pos > mixheaders[openfiles[file].id].size ) {
    openfiles[file].pos = mixheaders[openfiles[file].id].size;
  }
  mixfiles[mixheaders[openfiles[file].id].filenum]->seekSet(openfiles[file].pos+mixheaders[openfiles[file].id].offset);
}


size_t MIXFiles::getPos(uintptr_t file) const {
  // @todo Abstract this const version of operator[]
  std::map<uintptr_t, MIXPriv::OpenFile>::const_iterator i = openfiles.find(file);
  if (openfiles.end() != i) {
    return i->second.pos;
  } else {
    // @todo Throw an exception in a later iteration of code cleanup.
    return 0;
  }
}

size_t MIXFiles::getSize(uintptr_t file) const {
  // @todo Abstract this const version of operator[]
  openfiles_t::const_iterator i = openfiles.find(file);
  if (openfiles.end() != i) {
    mixheaders_t::const_iterator i2 = mixheaders.find(i->second.id);
    if (mixheaders.end() != i2) {
      return i2->second.size;
    }
  }
  // @todo Throw an exception in a later iterator of code cleanup.
  return 0;
}

const char* MIXFiles::getPath(uintptr_t file) const {
  return NULL;
}

const char* MIXFiles::getArchiveType() const {
  return "mix archive";
}
