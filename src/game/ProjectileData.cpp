// ProjectileData.cpp
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

#include "ProjectileData.h"

#include <iostream>

#include "misc/common.h"
#include "misc/INIFile.h"

ProjectileData::ProjectileData(){
	// by defaut "none" indicates no image
	setImage(std::string("none"));
}

uint32_t ProjectileData::getAA() {
	return AA;
}

void ProjectileData::setAA(uint32_t AA) {
	this->AA = AA;
}

uint32_t ProjectileData::getAG() {
	return AG;
}

void ProjectileData::setAG(uint32_t AG) {
	this->AG = AG;
}

int ProjectileData::getASW() {
	return ASW;
}

void ProjectileData::setASW(int ASW) {
	this->ASW = ASW;
}

int ProjectileData::getAnimates() {
	return animates;
}

void ProjectileData::setAnimates(int animates) {
	this->animates = animates;
}

int ProjectileData::getArcing() {
	return arcing;
}

void ProjectileData::setArcing(int arcing) {
	this->arcing = arcing;
}

int ProjectileData::getArm() {
	return arm;
}

void ProjectileData::setArm(int arm) {
	this->arm = arm;
}

int ProjectileData::getDegenerates() {
	return degenerates;
}

void ProjectileData::setDegenerates(int degenerates) {
	this->degenerates = degenerates;
}
int ProjectileData::getDropping()
{
	return dropping;
}
void ProjectileData::setDropping(int dropping)
{
	this->dropping = dropping;
}
int ProjectileData::getFrames()
{
	return frames;
}
void ProjectileData::setFrames(int frames)
{
	this->frames = frames;
}
int ProjectileData::getGigundo()
{
	return gigundo;
}
void ProjectileData::setGigundo(int gigundo)
{
	this->gigundo = gigundo;
}
int ProjectileData::getHigh()
{
	return high;
}
void ProjectileData::setHigh(int high)
{
	this->high = high;
}

std::string ProjectileData::getImage() {
	return image;
}

void ProjectileData::setImage(std::string image) {
	this->image = image;
}

int ProjectileData::getInaccurate() {
	return inaccurate;
}

void ProjectileData::setInaccurate(int inaccurate) {
	this->inaccurate = inaccurate;
}

int ProjectileData::getInviso() {
	return inviso;
}

void ProjectileData::setInviso(int inviso) {
	this->inviso = inviso;
}

int ProjectileData::getProximity()
{
	return proximity;
}
void ProjectileData::setProximity(int proximity)
{
	this->proximity = proximity;
}
int ProjectileData::getROT()
{
	return ROT;
}
void ProjectileData::setROT(int ROT)
{
	this->ROT = ROT;
}
int ProjectileData::getRanged()
{
	return ranged;
}
void ProjectileData::setRanged(int ranged)
{
	this->ranged = ranged;
}
int ProjectileData::getRotates()
{
	return rotates;
}
void ProjectileData::setRotates(int rotates)
{
	this->rotates = rotates;
}
int ProjectileData::getShadow()
{
	return shadow;
}
void ProjectileData::setShadow(int shadow)
{
	this->shadow = shadow;
}
int ProjectileData::getTranslucent()
{
	return translucent;
}
void ProjectileData::setTranslucent(int translucent)
{
	this->translucent = translucent;
}
int ProjectileData::getParachuted()
{
	return parachuted;
}
void ProjectileData::setParachuted(int parachuted)
{
	this->parachuted = parachuted;
}
int ProjectileData::getUnderWater()
{
	return underWater;
}
void ProjectileData::setUnderWater(int underWater)
{
	this->underWater = underWater;
}

ProjectileData* ProjectileData::loadProjectileData(INIFile * file, std::string name) {
    ProjectileData* lProjectileData;

    // Create the ProjectileData object
    lProjectileData = new ProjectileData();
        
    // AA = Can this weapon fire upon flying aircraft (def=no)?
    lProjectileData->setAA(file->readYesNo(name.c_str(), "AA", 0));
            
    // AG = Can this weapon fire upon ground objects (def=yes)?
    lProjectileData->setAG(file->readYesNo(name.c_str(), "AG", 1));
    
    // ASW = Is this an Anti-Submarine-Warfare projectile (def=no)?
    lProjectileData->setASW(file->readYesNo(name.c_str(), "ASW", 0));
    
    // Animates = Does it animate [this means smoke puffs] (def=no)?
    lProjectileData->setAnimates(file->readYesNo(name.c_str(), "Animates", 0));
        
    // Arcing = Does it have a ballistic trajectory (def=no)?
    lProjectileData->setArcing(file->readYesNo(name.c_str(), "Arcing", 0));
        
    // Arm = arming delay (def=0)
    lProjectileData->setArm(file->readInt(name.c_str(), "Arm", 0));
    
    // Degenerates = Does the bullet strength weaken as it travels (def=no)?
    lProjectileData->setDegenerates(file->readYesNo(name.c_str(), "Degenerates", 0));
    
    // Dropping = Does it fall from a starting height (def=no)?
    lProjectileData->setDropping(file->readYesNo(name.c_str(), "Dropping", 0));
        
    // Frames = number of image frames for animation purposes (def=1)
    lProjectileData->setFrames(file->readInt(name.c_str(), "Frames", 1));
        
    // Gigundo = Is the projectile larger than normal (def=no)?
    lProjectileData->setGigundo(file->readYesNo(name.c_str(), "Gigundo", 0));
        
    // High = Can it fly over walls (def=no)?
    lProjectileData->setHigh(file->readYesNo(name.c_str(), "High", 0));
    
    // Image = image to use during flight
    lProjectileData->setImage(file->readString(name.c_str(), "Image", "none"));
    
    // Inaccurate = Is it inherently inaccurate (def=no)?
    lProjectileData->setInaccurate(file->readYesNo(name.c_str(), "Inaccurate", 0));

    // Inviso = Is the projectile invisible as it travels (def=no)?
    lProjectileData->setInviso(file->readYesNo(name.c_str(), "Inviso", 0));

    // Parachuted = Equipped with a parachute for dropping from plane (def=no)?
    lProjectileData->setParachuted(file->readYesNo(name.c_str(), "Parachuted", 0));

    // Proximity = Does it blow up when near its target (def=no)?
    lProjectileData->setProximity(file->readYesNo(name.c_str(), "Proximity", 0));

    // ROT = Rate Of Turn [non zero implies homing] (def=0)
    lProjectileData->setROT(file->readInt(name.c_str(), "ROT", 0));

    // Ranged = Can it run out of fuel (def=no)?
    lProjectileData->setRanged(file->readYesNo(name.c_str(), "Ranged", 0));

    // Rotates = Does the projectile have rotation specific imagery (def=no)?
    lProjectileData->setRotates(file->readYesNo(name.c_str(), "Rotates", 0));

    // Shadow = If High, does this bullet need to have a shadow drawn? (def = yes)
    lProjectileData->setShadow(file->readYesNo(name.c_str(), "Shadow", 1));

    // Translucent = Are translucent colors used in artwork (def=no)?
    lProjectileData->setTranslucent(file->readYesNo(name.c_str(), "Translucent", 0));

    // UnderWater = Does the projectile travel under water?
    lProjectileData->setUnderWater(file->readYesNo(name.c_str(), "UnderWater", 0));

    // Returns the constructed object
    return lProjectileData;
}

/**
 * Print the Data
 */
void ProjectileData::print() {
  std::cout << "AA=" << getAA() << std::endl;
	std::cout << "AG=" << getAG() << std::endl;
	std::cout << "ASW=" << getASW() << std::endl;
	std::cout << "Animates=" << getAnimates() << std::endl;
	std::cout << "Arcing=" << getArcing() << std::endl;
	std::cout << "Arm=" << getArm() << std::endl;
	std::cout << "Degenerates=" << getDegenerates() << std::endl;
	std::cout << "Dropping=" << getDropping() << std::endl;
	std::cout << "Frames=" << getFrames() << std::endl;
	std::cout << "Gigundo=" << getGigundo() << std::endl;
	std::cout << "High=" << getHigh() << std::endl;
	std::cout << "Image=" << getImage() << std::endl;
	std::cout << "Inaccurate=" << getInaccurate() << std::endl;
	std::cout << "Inviso=" << getInviso() << std::endl;
	std::cout << "Parachuted=" << getParachuted() << std::endl;
	std::cout << "Proximity=" << getProximity() << std::endl;
	std::cout << "ROT=" << getROT() << std::endl;
	std::cout << "Ranged=" << getRanged() << std::endl;
	std::cout << "Rotates=" << getRotates() << std::endl;
	std::cout << "Shadow=" << getShadow() << std::endl;
	std::cout << "Translucent=" << getTranslucent() << std::endl;
	std::cout << "UnderWater=" << getUnderWater() << std::endl;
}
