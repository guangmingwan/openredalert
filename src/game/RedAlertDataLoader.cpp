// RedAlertDataLoader.cpp
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

#include "RedAlertDataLoader.h"

#include <string>
#include <iostream>

#include "Logger.h"

#include "WarheadDataList.h"
#include "ProjectileDataList.h"
#include "WeaponDataList.h"
#include "WeaponData.h"
#include "WarheadData.h"
#include "UnitType.h"

#include "misc/INIFile.h"
#include "vfs/vfs.h"
#include "vfs/VFile.h"

void RedAlertDataLoader::load()
{
    INIFile *rules_ini;
    //WarheadDataList * theWarList;
    //ProjectileDataList * theProjList;
    //WeaponDataList * theWeapList;

    //WeaponData* tempWeaponData;

    //theWarList = new WarheadDataList();
    //theProjList = new ProjectileDataList();
    //theWeapList = new WeaponDataList();
    /*
     // Load Tesla weapon
     string tempStrTezla = "TeslaZap";
     theWeapList->loadWeapon(rules_ini, tempStrTezla, theWarList, theProjList);

     // Print for debug
     cout << "[" << tempStrTezla << "]" << endl;
     (*theWeapList)[tempStrTezla]->print();

     
     
     // Load Colt for Tanya weapon
     string tempStr45 = "Colt45";
     theWeapList->loadWeapon(rules_ini, tempStr45, theWarList, theProjList);

     // Print for debug
     cout << "[" << tempStr45 << "]" << endl;
     (*theWeapList)[tempStr45]->print();

     
     
     // Print for debug
     string tempSuper = "Super";
     cout << "[" << tempSuper << "]" << endl;
     (*theWarList)[tempSuper]->print();
     // Print for debug
     string tempHollowPoint = "HollowPoint";
     cout << "[" << tempHollowPoint << "]" << endl;
     (*theWarList)[tempHollowPoint]->print();
     */

    //
    // Loads all warhead in the REDALERT.mix/LOCAL.mix/rules.ini
    //
    // Load the rules ini file
    rules_ini = new INIFile("rules.ini");
    if (rules_ini == NULL)
    {
        Logger::getInstance()->Error("CAN'T FIND rules.ini\n");
        return;
    }

    // SA
    std::string tempStrSA = "SA";
    lnkWarheadDataList->loadWarheadData(rules_ini, tempStrSA);
    // HE
    std::string tempStrHE = "HE";
    lnkWarheadDataList->loadWarheadData(rules_ini, tempStrHE);
    // AP
    std::string tempStrAP = "AP";
    lnkWarheadDataList->loadWarheadData(rules_ini, tempStrAP);
    // Fire
    std::string tempStrFire = "Fire";
    lnkWarheadDataList->loadWarheadData(rules_ini, tempStrFire);
    // HollowPoint
    std::string tempStrHollowPoint = "HollowPoint";
    lnkWarheadDataList->loadWarheadData(rules_ini, tempStrHollowPoint);
    // Super
    std::string tempStrSuper = "Super";
    lnkWarheadDataList->loadWarheadData(rules_ini, tempStrSuper);
    // Organic
    std::string tempStrOrganic = "Organic";
    lnkWarheadDataList->loadWarheadData(rules_ini, tempStrOrganic);
    // Nuke
    std::string tempStrNuke = "Nuke";
    lnkWarheadDataList->loadWarheadData(rules_ini, tempStrNuke);

    // Print for debug
    //lnkWarheadDataList->print();

    // Invisible
    std::string tempStrInvisible = "Invisible";
    lnkProjectileDataList->loadProjectileData(rules_ini, tempStrInvisible);
    // LeapDog
    std::string tempStrLeapDog = "LeapDog";
    lnkProjectileDataList->loadProjectileData(rules_ini, tempStrLeapDog);
    // Cannon
    std::string tempStrCannon = "Cannon";
    lnkProjectileDataList->loadProjectileData(rules_ini, tempStrCannon);
    // Ack
    std::string tempStrAck = "Ack";
    lnkProjectileDataList->loadProjectileData(rules_ini, tempStrAck);
    // Torpedo
    std::string tempStrTorpedo = "Torpedo";
    lnkProjectileDataList->loadProjectileData(rules_ini, tempStrTorpedo);
    // FROG
    std::string tempStrFROG = "FROG";
    lnkProjectileDataList->loadProjectileData(rules_ini, tempStrFROG);

    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("HeatSeeker"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("LaserGuided"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("AAMissile"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("Lobbed"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("Catapult"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("Bomblet"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("Ballistic"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("Parachute"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("GPSSatellite"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("NukeUp"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("NukeDown"));
    lnkProjectileDataList->loadProjectileData(rules_ini, std::string("Fireball"));

    // Print for debug
    //lnkProjectileDataList->print();
        
    //
    // Try to load strings from MIX archive file
    // @todo DEBUG MAKE READING OF KEYS
    // Loads all strings in the REDALERT.mix/LOCAL.mix/conquer.eng
    //VFile* raStrings = VFSUtils::VFS_Open("conquer.eng");
    //logger->debug("File SIZE = %d", raStrings->fileSize());
    //raStrings->tell();
    /*
    Uint8* buf0 = new Uint8[100]; 
    for (int i=0; i<60; i++){
        logger->debug("line %d = \"%s\"", i, raStrings->readByte(buf0, 100));
    }
    */
    //char* tmpC = "E4";
    //new UnitType(tmpC, new INIFile("./data/settings/ra/unit.ini"));
}
