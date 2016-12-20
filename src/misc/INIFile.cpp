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

#include "KeyNotFound.h"
#include "Logger.hpp"
#include "vfs/vfs.h"
#include "vfs/VFile.h"

using INI::KeyNotFound;

/**
 * Constructor, opens the file
 *
 * @param filename the name of the inifile to open.
 */
INIFile::INIFile(const std::string& filename) {
  char line[1024];
  char key[1024];
  char value[1024];
  char* str;

  // Open the File
  VFile *inifile = VFSUtils::VFS_Open(filename.c_str());
  if (inifile == nullptr) {
    std::string s = "Unable to open ";
    s += filename;
    Logger::getInstance()->Error(s);
    throw std::runtime_error(s);
  }

  std::string cursectionName = "";

  // parse the inifile and write data to inidata
  while (inifile->readLine(line, 1024) != 0) {
    str = line;

    while ((*str) == ' ' || (*str) == '\t') {
      str++;
    }
    if ((*str) == ';') {
      continue;
    }
    if (sscanf(str, "[%[^]]]", key) == 1) {
      if (cursectionName != "") {
        SectionNode sectionNode;
        sectionNode.name = cursectionName;
        Inidata.push_back(sectionNode);
      }
      for (unsigned int i = 0; key[i] != '\0'; i++) {
        key[i] = toupper(key[i]);
      }
      cursectionName = key;
    } else if (cursectionName != "" && sscanf(str, "%[^=]=%[^\r\n;]", key,
                                              value) == 2) {
      for (unsigned int i = 0; key[i] != '\0'; i++) {
        key[i] = toupper(key[i]);
      }
      if (strlen(key) > 0) {
        str = key + strlen(key) - 1;
        while ((*str) == ' ' || (*str) == '\t') {
          (*str) = '\0';
          if (str == key) {
            break;
          }
          str--;
        }
      }
      if (strlen(value) > 0) {
        str = value + strlen(value) - 1;
        while ((*str) == ' ' || (*str) == '\t') {
          (*str) = '\0';
          if (str == value) {
            break;
          }
          str--;
        }
      }
      str = value;
      while ((*str) == ' ' || (*str) == '\t') {
        str++;
      }

      Inidata.back().section[key] = str;
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

/**
 * Function to extract a string from a ini file. The string is mallocated
 * in this function so it should be freed.
 *
 * @param section the section in the file to extract string from.
 * @param value the name of the string to extract.
 * @return the extracted string.
 */
std::string INIFile::readString(const std::string& section, const std::string& value) const {
  std::string s = section;
  transform(s.begin(), s.end(), s.begin(), toupper);

  // Try to find section
  const INISection *foundSection = nullptr;
  for (const SectionNode &sectionNode : Inidata) {
    if (sectionNode.name == s) {
      foundSection = &sectionNode.section;
    }
  }

  if (foundSection == nullptr) {
    return std::string();
  }

  std::string v = value;
  transform(v.begin(), v.end(), v.begin(), toupper);

  // get a const iterator
  INISection::const_iterator key = sec->second.begin();

  for (unsigned int i = 0; i < sec->second.size(); i++) {
    if (key->first == v) {
      break;
    }
    key++;
  }

  if (key == sec->second.end()) {
    return 0;
  }
  // allocate a new string
  retval = new char[key->second.length() + 1];
  // copy value
  strcpy(retval, key->second.c_str());
  // return the good one
  return retval;
}

/**
 * wrapper around readString to return a provided default instead of NULL
 */
std::string INIFile::readString(const std::string& section, const std::string& key, const std::string& deflt) const {
  // Test if the section exist
  if (isKeyInSection(section, key) == false) {
    return std::string(deflt);
  }

  std::string ret = readString(section, key);
  return ret;
}

/**
 * @param section Section in the .ini file
 * @param key Key of the section
 * @param defaultValue Default value to return if the key doesn't exist
 * @return the value of the key
 */
int INIFile::readInt(const std::string& section, const std::string& key, int defaultValue) const {
  // Test if the key exist in the section
  if (isKeyInSection(section, key) == false) {
    // Return the default value
    return defaultValue;
  }

  // Get the value in a string stream
  std::stringstream defValStr;
  defValStr << defaultValue;
  std::stringstream valueStr;
  valueStr << readString(section, key, defValStr.str());
  int ret;
  valueStr >> ret;

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
  // @todo remove that !!!!
  // We UPPER the string because strings are stored in UPPER WAY
  std::string s = section;
  transform(s.begin(), s.end(), s.begin(), toupper);
  std::string k = key;
  transform(k.begin(), k.end(), k.begin(), toupper);

  // If the section doesn't exist
  if (isKeyInSection(s, k) == false) {
    throw KeyNotFound("Can't find the section [" + s + "] in ini file.");
  }


  std::map<std::string, INISection>::const_iterator sec = Inidata.find(s);
  if (sec == Inidata.end()) {
    throw KeyNotFound("Can't find the section [" + std::string(section)
                      + "] in ini file.");
  }


  //map<string, string>::const_iterator keyIt = sec.find(k);
  INISection::const_iterator keyIt = sec->second.find(k);
  //    key = sec->second.find(v);
  //key = sec->second.begin();
  //   key.find(k);
  //for (unsigned int i = 0; i < sec->second.size(); i++) {
  //	if (key->first == v) {
  //		break;
  //	}
  //	key++;
  //}

  if (keyIt == sec->second.end()) {
    throw KeyNotFound("Can't Find the key [" + k
                      + "] in the section [" + s + "] of ini file.");
  }
  //if (sscanf(key->second.c_str(), "%d", &retval) != 1) {
  //	throw runtime_error("Unable to cast to int.");
  //}
  std::stringstream convStr;
  convStr << keyIt->second;
  int ret;
  convStr >> ret;
  return ret;
}

/**
 * Function to extract a float value from a ini file. The value
 * can be given in hex if it starts with 0x.
 *
 * @param sectionString the section in the file to extract values from.
 * @param keyString the name of the value to extract.
 * @return the value.
 */
float INIFile::readFloat(const std::string& sectionString, const std::string& keyString) {
  float retval;

  // Get the "UPPER" strings
  std::string s = sectionString;
  transform(s.begin(), s.end(), s.begin(), toupper);
  std::string v = keyString;
  transform(v.begin(), v.end(), v.begin(), toupper);

  // Check if the section is in the file
  std::map<std::string, INISection>::const_iterator sec = Inidata.find(s);
  if (sec == Inidata.end()) {
    throw new KeyNotFound("The section [" + sectionString
                          + "] was not found in the file.");
  }

  // Try to find the section (by iterations)
  INISection::const_iterator key = sec->second.begin();
  for (unsigned int i = 0; i < sec->second.size(); i++) {
    if (key->first == v) {
      break;
    }
    key++;
  }

  // If the key was not found throw an INI::KeyNotFound exception
  if (key == sec->second.end()) {
    throw new KeyNotFound("Key " + sectionString + ":" + keyString
                          + " was not found in the ini file.");
  }
  // If we can't "sscan" in float
  if (sscanf(key->second.c_str(), "%f", &retval) != 1) {
    throw new std::runtime_error("Key " + sectionString + ":" + keyString
                            + "=" + std::string(key->second.c_str())
                            + " can't be cast in float.");
  }

  // success return the value
  return retval;
}

/**
 * Read a value in a section of IniFile
 *
 * @param section section of the ini file
 * @param key key to read in the section
 * @param deflt default value to return
 * @return the value of the key or the default value if the key not exists
 */
float INIFile::readFloat(const std::string& section, const std::string& key, const float deflt) {
  //  If the key not exist default value is returned
  if (isKeyInSection(section, key) == false) {
    // return the default key
    return deflt;
  } else {
    // Read the key in a string
    std::string floatString = readString(section, key);

    // Convert and return the value of the key
    std::stringstream aStringstream;
    aStringstream << floatString;
    float ret;
    aStringstream >> ret;
    return ret;
  }
}

/**
 * Function to get number of key/value per section
 */
size_t INIFile::getNumberOfKeysInSection(const std::string& section) const {

  std::string s;

  // get the string from (char*) section
  s = std::string(section);

  // Upper the section string
  transform(s.begin(), s.end(), s.begin(), toupper);

  std::map<std::string, INISection>::const_iterator sec_new = Inidata.find(s);
  if (sec_new == Inidata.end()) {
    //throw KeyNotFound("Section [" + string(section) + "] not found in .ini file.");
    return 0;
  }

  return sec_new->second.size();
}

/**
 * Use inside a loop to read all keys of a section.  The order is as read
 * from the inifile.
 *
 * @param section The name of the section from which to read.
 * @param keynum Will skip (keynum-1) entries in section.
 * @returns an iterator to the keynum'th key in section.
 */
INISection::const_iterator INIFile::readKeyValue(const char* section, unsigned int keynum) {
  std::map<std::string, INISection>::iterator sec_new;
  std::string s;

  // get the string from (char*) section
  s = std::string(section);

  // Upper the section string
  transform(s.begin(), s.end(), s.begin(), toupper);

  sec_new = Inidata.find(s);
  if (sec_new == Inidata.end()) {
    throw KeyNotFound("Section [" + std::string(section) + "] not found in .ini file.");
  }

  if (keynum >= sec_new->second.size()) {
    throw KeyNotFound("Key number [???] in Section [" + std::string(section) + "] not found in .ini file.");
  }

  INISection::iterator Key = sec_new->second.begin();
  for (Uint32 i = 0; i < keynum; ++i) {
    Key++;
  }
  if (Key == sec_new->second.end()) {
    Logger::getInstance()->Error("throw 0 in INIFile::readKeyValue()\n");
    throw KeyNotFound("Key number [????] in Section [" + std::string(section) + "] not found in .ini file.");
  }
  return Key;
}

/**
 */
INISection::const_iterator INIFile::readIndexedKeyValue(const char* section, unsigned int index, const char* prefix) {
  std::string s = section;
  transform(s.begin(), s.end(), s.begin(), toupper);

  std::map<std::string, INISection>::iterator sec = Inidata.find(s);
  if (sec == Inidata.end()) {
    throw 0;
  }

  if (index > sec->second.size()) {
    throw 0;
  }

  std::string keyval;
  if (prefix)
    keyval = prefix;
  //keyval += lexical_cast<string>(index);

  std::stringstream TempStr;
  TempStr << (unsigned int) index;
  //	sprintf (TempString, "%u", index);
  //	keyval += TempString;
  keyval += TempStr.str();

  INISection::const_iterator key = sec->second.begin();

  for (unsigned int i = 0; i < sec->second.size(); i++) {
    if (key->first == keyval) {
      return key;
    }
    key++;
  }
  if (key == sec->second.end()) {
    throw 0;
  }
  // we should never get here
  return key;

}

std::string INIFile::readSection(unsigned int secnum) {
  if (secnum >= Inidata.size()) {
    throw 0;
  }

  std::map<std::string, INISection>::iterator sec = Inidata.begin();
  for (unsigned int i = 0; i < secnum; i++) {
    sec++;
    if (sec == Inidata.end()) {
      throw 0;
    }
  }
  return sec->first;
}

/**
 * @param section Section of the ini file
 * @return true if the section exist
 */
bool INIFile::isSection(const std::string& section) const {
  std::map<std::string, INISection>::const_iterator sec = Inidata.find(section);
  if (sec == Inidata.end()) {
    return false;
  } else {
    return true;
  }
}

/**
 * @param section Section to check
 * @param keyString Key to check
 * @return <code>true</code> if the key exist in the section else return <code>false</code>
 */
bool INIFile::isKeyInSection(const std::string& section, const std::string& keyString) const {
  // Upper version of the section
  std::string s = section;
  // Upper the section string
  transform(s.begin(), s.end(), s.begin(), toupper);

  // Try to get the section
  std::map<std::string, INISection>::const_iterator sec = Inidata.find(s);

  // If the section was not found
  if (sec == Inidata.end()) {
    // Return false
    return false;
  } else {
    // Upper version of the key string
    std::string k = keyString;
    // Upper the key string
    transform(k.begin(), k.end(), k.begin(), toupper);

    // Get an iterator
    INISection::const_iterator sec_key = sec->second.begin();
    while (sec_key!=sec->second.end()) {
      // If the Key was found
      if (sec_key->first == k) {
        // Return true
        return true;
      }
      // Continue
      sec_key++;
    }
  }
  // Nothing found, return false
  return false;
}

int INIFile::readYesNo(const std::string& section, const std::string& value, const int defaut) const {
  std::stringstream defStr;
  if (defaut != 0) {
    defStr << "yes";
  } else {
    defStr << "no";
  }
  std::string tmpAA = this->readString(section, value, defStr.str());
  int a;
  if (tmpAA == "yes") {
    a = 1;
  } else {
    a = 0;
  }
  return a;
}

/**
 * @return file name of the ini file
 */
std::string INIFile::getFileName() const {
  return this->filename;
}
