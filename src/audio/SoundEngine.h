// SoundEngine.h
// 1.3
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

#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <vector>
#include <string>

#include "SoundCache.h"

#include "SDL_mixer.h"

namespace Sound {

  /**
   * Manager of all sounds in OpenRedAlert
   *
   * This object provide function to load/start/stop all music/sounds in the game
   */
  class SoundEngine {
   public:
    SoundEngine(bool disableSound = false);
    ~SoundEngine();

    void LoadSound(const std::string& sound);

    /** Set the volume in the range of 0-128 of all sounds */
    void SetSoundVolume(int volume);
    void PlaySound(const std::string& sound);
    int  PlayLoopedSound(const std::string& sound, unsigned int loops);
    void StopLoopedSound(int id);
    void PauseLoopedSound(int id);
    void ResumeLoopedSound(int id);

    /** Set the volume in the range of 0-128 of all musics */
    void SetMusicVolume(int volume);
    /** Create the playlist with RA musics */
    bool CreatePlaylist();
    void PlayMusic(); // Starts|Resumes playing
    void PauseMusic();
    void StopMusic();
    /** Plays a specific track */
    void PlayTrack(const std::string& sound);
    /** Selects the next track in the playlist */
    void NextTrack();
    /** Selects the previous track in the playlist */
    void PrevTrack();

    static void MusicHook(void* userdata, uint8_t* stream, int len);

    typedef void (*MixFunc)(void*, uint8_t*, int);

    void SetMusicHook(MixFunc mixfunc, void *arg);

    bool NoSound() const;

   private:
    typedef std::vector<std::string> Playlist;

    SoundBuffer* LoadSoundImpl(const std::string& sound);

    bool nosound;
    bool mutesound;
    bool musicFinished;
    unsigned int soundVolume;

    SoundCache soundCache;

    Playlist playlist;
    Playlist::iterator currentTrack;
  };
  
}

#endif //SOUNDENGINE_H
