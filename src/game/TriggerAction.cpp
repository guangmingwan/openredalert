// TriggerAction.cpp
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

#include "TriggerAction.h"

/**
 * Build
 *
 * @param action Number of the action
 */
TriggerAction::TriggerAction(int action) {
	this->action = action;
}

TriggerAction::~TriggerAction() {
}

int TriggerAction::getAction() {
	return action;
}

std::string TriggerAction::getName() {
  switch (action) {
    case NO_ACTION: return "NO_ACTION";
		case WINNER_IS: return "WINNER_IS";
		case LOSER_IS: return "LOSER_IS";
		case PRODUCTION_BEGINS: return "PRODUCTION_BEGINS";
		case CREATE_TEAM: return "CREATE_TEAM";
		case DESTROY_TEAM: return "DESTROY_TEAM";
		case ALL_TO_HUNT: return "ALL_TO_HUNT";
		case REINFORCEMENTS: return "REINFORCEMENTS";
		case DROP_ZONE_FLARE: return "DROP_ZONE_FLARE";
		case FIRE_SALE: return "FIRE_SALE";
		case PLAY_MOVIE: return "PLAY_MOVIE";
		case TEXT: return "TEXT";
		case DESTROY_TRIGGER: return "DESTROY_TRIGGER";
		case AUTOCREATE_BEGINS: return "AUTOCREATE_BEGINS";
		case XXXX: return "XXXX";
		case ALLOW_WIN: return "ALLOW_WIN";
		case REVEAL_MAP: return "REVEAL_MAP";
		case REVEAL_AROUND_WAYPOINT: return "REVEAL_AROUND_WAYPOINT";
		case REVEAL_ZONE_OF_WAYPOINT: return "REVEAL_ZONE_OF_WAYPOINT";
		case PLAY_SOUND: return "PLAY_SOUND";
		case PLAY_MUSIC: return "PLAY_MUSIC";
		case PLAY_SPEECH: return "PLAY_SPEECH";
		case FORCE_TRIGGER: return "FORCE_TRIGGER";
		case TIMER_START: return "TIMER_START";
		case TIMER_STOP: return "TIMER_STOP";
		case TIMER_EXTEND: return "TIMER_EXTEND";
		case TIMER_SHORTEN: return "TIMER_SHORTEN";
		case TIMER_SET: return "TIMER_SET";
		case GLOBAL_SET: return "GLOBAL_SET";
		case GLOBAL_CLEAR: return "GLOBAL_CLEAR";
		case AUTO_BASE_BUILDING: return "AUTO_BASE_BUILDING";
		case GROW_SHROUD_ONE_STEP: return "GROW_SHROUD_ONE_STEP";
		case DESTROY_BUILDING: return "DESTROY_BUILDING";
		case ADD_1TIME_SPEC_WEAPON: return "ADD_1TIME_SPEC_WEAPON";
		case ADD_SPEC_WEAPON: return "ADD_SPEC_WEAPON";
		case PREFERRED_TARGET: return "PREFERRED_TARGET";
		case LAUNCH_NUKES: return "LAUNCH_NUKES";
  }
  return "";
}
