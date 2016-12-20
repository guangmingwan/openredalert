// StringTableFile.cpp
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

#include "StringTableFile.h"

#include <stdexcept>
#include <string>
#include <vector>

#include "vfs/vfs.h"
#include "vfs/VFile.h"

/**
 * @param filename File name to load
 */
StringTableFile::StringTableFile(const std::string& filename) {
  // Load strings in the file "filename"
  this->loadStringFile(filename.c_str());
}

/**
 * Load all strings in the file specified and stroe it in a std::vector
 *
 * @param filename File name to load
 */
void StringTableFile::loadStringFile(const char* filename) {
  VFile* stringFile; // Ref to the file in the mix (YEAH!)
  uint16_t headerLenght; // size of the header
  uint16_t numString; // Number of string in the file

  // Open the File
  stringFile = VFSUtils::VFS_Open(filename);
  if (stringFile == 0) {
    std::string s = "Unable to open ";
    s += filename;
    throw std::runtime_error(s);
  }

  // Read the first byte (Uint16) to discover the size of the header
  stringFile->readWord(&headerLenght, 1);

  // Calculate the number of strings
  numString = headerLenght / 2;


  // Read offsets
  for (int i = 0; i < numString - 1; i++) {
    uint16_t bufStart;
    uint16_t bufEnd;

    // Seek to header
    stringFile->seekSet(i * 2);

    // Read the offset of Start in the header
    stringFile->readWord(&bufStart, 1);

    // Read the offset of End in the header
    stringFile->readWord(&bufEnd, 1);

    uint16_t lenght = bufEnd - bufStart;
    uint8_t* tabChar = new uint8_t[lenght];

    // Seek to the str
    stringFile->seekSet(bufStart);

    // read the str
    stringFile->readByte(tabChar, lenght);

    std::string toto = std::string(((char*) tabChar));

    // Add the decoded string in the vector
    data.push_back(toto);

    delete[] tabChar;
  }

  // Close the file
  VFSUtils::VFS_Close(stringFile);
}

/**
 * Free only data by calling vector::clear() function.
 */
StringTableFile::~StringTableFile() {
  // delete all entries in inidata
  this->data.clear();
}

/**
 * Return string by id
 *
 * @param id Number (id) of the string
 * @return The string with the id specified
 */
std::string StringTableFile::getString(unsigned int id) const {
  // Copy the string from the internal data
  std::string ret = this->data[id];

  // Return the string
  return ret;
}
