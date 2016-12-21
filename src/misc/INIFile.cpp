// INIFile.cpp
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

#include "INIFile.h"

#include <sstream>

#include "Logger.hpp"
#include "vfs/vfs.h"
#include "vfs/VFile.h"

// trim from start
static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
          s.end());
  return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}

/**
 * Constructor, opens the file
 *
 * @param filename the name of the inifile to open.
 */
INIFile::INIFile(const std::string& filename) {
  char line[1024];
  char key[1024];
  char value[1024];

  // Open the File
  VFile *inifile = VFSUtils::VFS_Open(filename.c_str());
  if (inifile == nullptr) {
    std::string s = "Unable to open ";
    s += filename;
    Logger::getInstance()->Error(s);
    throw std::runtime_error(s);
  }

  // parse the inifile and write data to inidata
  while (inifile->readLine(line, 1024) != 0) {
    std::string str(line);
    str = trim(str);
    if (str.empty() || str[0] == ';') {
      continue;
    }
    if (sscanf(str.c_str(), "[%[^]]]", key) == 1) {
      std::string sectionName = key;
      sectionName = trim(sectionName);
      transform(sectionName.begin(), sectionName.end(), sectionName.begin(),
                toupper);
      SectionNode sectionNode;
      sectionNode.name = sectionName;
      Inidata.push_back(sectionNode);
    } else if (!Inidata.empty() &&
               sscanf(str.c_str(), "%[^=]=%[^\r\n;]", key, value) == 2) {
      std::string keyName = key;
      keyName = trim(keyName);
      transform(keyName.begin(), keyName.end(), keyName.begin(), toupper);
      std::string valueString(value);
      valueString = trim(valueString);
      KeyNode node;
      node.name = keyName;
      node.value = valueString;
      Inidata.back().section.push_back(node);
    }
  }

  // Close the file
  VFSUtils::VFS_Close(inifile);
}

/**
 * Destructor, closes the file
 */
INIFile::~INIFile() {
  // delete all entries in inidata
  Inidata.clear();
}

const INIFile::INISection *INIFile::findSection(const std::string& section) const {
  std::string s = section;
  transform(s.begin(), s.end(), s.begin(), toupper);

  // Try to find section
  for (const SectionNode &sectionNode : Inidata) {
    if (sectionNode.name == s) {
      return &sectionNode.section;
    }
  }

  return nullptr;
}

/**
 * Function to extract a string from a ini file. The string is mallocated
 * in this function so it should be freed.
 *
 * @param section the section in the file to extract string from.
 * @param key the name of the string to extract.
 * @return the extracted string.
 */
std::string INIFile::readString(const std::string& section,
                                const std::string& key) const {
  const INISection *foundSection = findSection(section);
  if (foundSection == nullptr) {
    throw KeyNotFound("Can't find the section [" + section + "] in ini file.");
  }

  std::string v = key;
  transform(v.begin(), v.end(), v.begin(), toupper);

  for (const KeyNode &keyNode : *foundSection) {
    if (keyNode.name == v) {
      return keyNode.value;
    }
  }

  return std::string();
}

/**
 * wrapper around readString to return a provided default instead of NULL
 */
std::string INIFile::readString(const std::string& section,
                                const std::string& key,
                                const std::string& deflt) const {
  // Test if the section exist
  if (isKeyInSection(section, key) == false) {
    return deflt;
  }

  return readString(section, key);
}

/**
 * @param section Section in the .ini file
 * @param key Key of the section
 * @param defaultValue Default value to return if the key doesn't exist
 * @return the value of the key
 */
int INIFile::readInt(const std::string& section, const std::string& key,
                     int defaultValue) const {
  // Test if the key exist in the section
  if (isKeyInSection(section, key) == false) {
    // Return the default value
    return defaultValue;
  }

  // Get the value in a string stream
  std::stringstream valStream(readString(section, key));
  int ret;
  valStream >> ret;

  // Return the value
  return ret;
}

/**
 * Function to extract a integer value from a ini file. The value
 * can be given in hex if it starts with 0x.
 *
 * @param section the section in the file to extract values from.
 * @param key the name of the value to extract.
 * @return the value.
 */
int INIFile::readInt(const std::string& section, const std::string& key) const {
  // If the section doesn't exist
  if (isKeyInSection(section, key) == false) {
    throw KeyNotFound("Can't find the section [" + section + "] in ini file.");
  }

  return readInt(section, key, 0);
}

/**
 * Function to extract a float value from a ini file. The value
 * can be given in hex if it starts with 0x.
 *
 * @param section the section in the file to extract values from.
 * @param key the name of the value to extract.
 * @return the value.
 */
float INIFile::readFloat(const std::string &section, const std::string &key) {
  // If the section doesn't exist
  if (isKeyInSection(section, key) == false) {
    throw KeyNotFound("Can't find the section [" + section + "] in ini file.");
  }

  // Get the value in a string stream
  std::stringstream valStream(readString(section, key));
  float ret;
  valStream >> ret;

  // Return the value
  return ret;
}

/**
 * Read a value in a section of IniFile
 *
 * @param section section of the ini file
 * @param key key to read in the section
 * @param deflt default value to return
 * @return the value of the key or the default value if the key not exists
 */
float INIFile::readFloat(const std::string& section, const std::string& key,
                         const float deflt) {
  // If the section doesn't exist
  if (isKeyInSection(section, key) == false) {
    return deflt;
  }

  // Get the value in a string stream
  std::stringstream valStream(readString(section, key));
  float ret;
  valStream >> ret;

  // Return the value
  return ret;
}

/**
 * Function to get number of key/value per section
 */
size_t INIFile::getNumberOfKeysInSection(const std::string& section) const {
  const INISection *foundSection = findSection(section);
  if (foundSection == nullptr) {
    throw KeyNotFound("Can't find the section [" + section + "] in ini file.");
  }

  return foundSection->size();
}

/**
 * Use inside a loop to read all keys of a section.  The order is as read
 * from the inifile.
 *
 * @param section The name of the section from which to read.
 * @param keynum Will skip (keynum-1) entries in section.
 * @returns an iterator to the keynum'th key in section.
 */
INIFile::KeyNode INIFile::readKeyValue(const std::string& section,
                                       unsigned int keynum) {
  const INISection *foundSection = findSection(section);
  if (foundSection == nullptr) {
    throw KeyNotFound("Can't find the section [" + section + "] in ini file.");
  }

  if (keynum >= foundSection->size()) {
    throw KeyNotFound("Can't find the key with # in ini file.");
  }

  INISection::const_iterator it = foundSection->begin();
  unsigned int i = 0;
  while (i != keynum) {
    it++;
    i++;
  }

  return *it;
}

/**
 */
std::string
INIFile::readIndexedKeyValue(const std::string& section, unsigned int index,
                             const std::string& prefix) {
  std::stringstream TempStr;
  TempStr << prefix << index;
  std::string key = TempStr.str();

  if (!isKeyInSection(section, key)) {
    throw KeyNotFound("Can't find the key '" + key + "' in ini file.");
  }

  return readString(section, key);
}

std::string INIFile::readSection(unsigned int secnum) {
  if (secnum >= Inidata.size()) {
    throw 0;
  }

  return Inidata[secnum].name;
}

/**
 * @param section Section of the ini file
 * @return true if the section exist
 */
bool INIFile::isSection(const std::string& section) const {
  const INISection *foundSection = findSection(section);
  return (foundSection != nullptr);
}

/**
 * @param section Section to check
 * @param key Key to check
 * @return <code>true</code> if the key exist in the section else return <code>false</code>
 */
bool INIFile::isKeyInSection(const std::string &section,
                             const std::string &key) const {
  const INISection *foundSection = findSection(section);
  if (foundSection == nullptr) {
    return false;
  }

  std::string v = key;
  transform(v.begin(), v.end(), v.begin(), toupper);

  for (const KeyNode &keyNode : *foundSection) {
    if (keyNode.name == v) {
      return true;
    }
  }

  return false;
}

int INIFile::readYesNo(const std::string& section, const std::string& value,
                       const int defaut) const {
  std::string res = this->readString(section, value,
                                     (defaut == 0) ? "no" : "yes");
  return (res == "yes");
}

/**
 * @return file name of the ini file
 */
std::string INIFile::getFileName() const {
  return this->filename;
}
