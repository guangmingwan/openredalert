// INIFile.h
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

#ifndef INIFILE_H
#define INIFILE_H

#include <vector>
#include <string>
#include <map>

class INISection : public std::map<std::string, std::string> {};

/**
 * Parses inifiles.
 *
 */
class INIFile {
 public:
  class KeyNotFound : public std::runtime_error {
   public:
    KeyNotFound(const std::string& msg) : std::runtime_error(msg) {}
  };

 protected:
  class SectionNode {
   public:
    std::string name;
    INISection section;
  };

 public:
  explicit INIFile(const std::string& filename);
  ~INIFile();

  /** Read a String */
  std::string readString(const std::string& section, const std::string& key) const;
  /** Read a string and return the default value if the key not exist */
  std::string readString(const std::string& section, const std::string& key, const std::string& defaultValue) const;

  /** Read an integer */
  int readInt(const std::string& section, const std::string& key) const;
  /** Read an integer and return the default value if the key not exist */
  int readInt(const std::string& section, const std::string& key, const int defaultValue) const;

  float readFloat(const std::string& section, const std::string& key);
  float readFloat(const std::string& section, const std::string& key, const float defaultValue);

  INISection::const_iterator readKeyValue(const std::string& section, unsigned int keynum);
  INISection::const_iterator readIndexedKeyValue(const std::string& section, unsigned int keynum, const char* prefix=0);
  std::string readSection(unsigned int secnum);

  /** Read a Key with value equal 'yes' or 'no' */
  int readYesNo(const std::string& section, const std::string& value, const int defaultValue) const;

  /** Function to test if a section is in the inifile */
  bool isSection(const std::string& section) const;
  /** Function to test if a key is in a section in the inifile */
  bool isKeyInSection(const std::string& section, const std::string& keyString) const;

  /** Function to get number of key/value per section */
  size_t getNumberOfKeysInSection(const std::string& section) const;

  /** Get the file name of the ini file */
  std::string getFileName() const;

 private:
  /** File name of the inifile loaded */
  std::string filename;

  /** Internal data */
  std::vector<SectionNode> Inidata;

  const INISection *findSection(const std::string& section) const;
};

#endif //INIFILE_H
