//////////////////////////////////////////////////////////////////////////////////
//	This file is part of the continued Journey MMORPG client // 	Copyright
//(C) 2015-2019  Daniel Allendorf, Ryan Payton, lain3d						//
//																				//
//	This program is free software: you can redistribute it and/or modify
//// 	it under the terms of the GNU Affero General Public License as published
/// by / 	the Free Software Foundation, either version 3 of the License, or //
///(at
// your option) any later version.											//
//																				//
//	This program is distributed in the hope that it will be useful, // 	but
// WITHOUT ANY WARRANTY; without even the implied warranty of				//
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the // 	GNU
// Affero General Public License for more details.							//
//																				//
//	You should have received a copy of the GNU Affero General Public License
//// 	along with this program.  If not, see <https://www.gnu.org/licenses/>.
////
//////////////////////////////////////////////////////////////////////////////////
#include "Audio.h"

#include "../Configuration.h"

// #ifdef _WIN32
// #define WIN32_LEAN_AND_MEAN
// #include <bass.h>
// #else
// #include <AL/alc.h>
// #endif
#include <AL/alc.h>

#include <nlnx/audio.hpp>
#include <nlnx/nx.hpp>

namespace ms {

alure::DeviceManager Music::dev_mngr_;
alure::Device Music::dev_;
alure::Context Music::ctx_;
alure::Source Music::music_src_;
alure::Buffer Music::music_buff_;
std::unordered_map<std::string, membuf *> Music::audiodb_;
size_t Sound::source_inc_;
alure::Source Sound::sound_srcs_[100];

void Sound::create_alure_source() {
    /* TODO: create interface to batch sounds. If a large amount of sounds are
     * queued up by say all the monsters in a map being set to die in the next
     * "update" cycle then more than the max number of sounds will be required
     * for the next few game ticks. AKA OpenAL will throw an uncatchable error.
     * Below will prevent this error but may not be ideal...
     */
    // while (source_inc_ > 200); /* openal limits to 256 concurrent sources */

    bool create = true;

    while (sound_srcs_[source_inc_ - 1] != nullptr
           && !sound_srcs_[source_inc_ - 1].isPlaying()) {
        sound_srcs_[source_inc_ - 1].destroy();
        sound_srcs_[source_inc_ - 1] = NULL;
        source_inc_--;
    }

    if (sound_srcs_[source_inc_]) {
        if (source_inc_ > 99) {
            create = false;
        }
    }

    if (create) {
        sound_src_ = Music::ctx_.createSource();
        sound_srcs_[source_inc_] = sound_src_;
        source_inc_++;
    }
}

// Sound::~Sound()
//{
//    source_inc_--;
//}

Sound::Sound(Name name) {
    id_ = soundids_[name];
    create_alure_source();
}

Sound::Sound(int32_t itemid) {
    auto fitemid = format_id(itemid);

    if (itemids_.find(fitemid) != itemids_.end()) {
        id_ = itemids_.at(fitemid);
    } else {
        auto pid = (10000 * (itemid / 10000));
        auto fpid = format_id(pid);

        if (itemids_.find(fpid) != itemids_.end())
            id_ = itemids_.at(fpid);
        else
            id_ = itemids_.at("02000000");
    }
    create_alure_source();
}

Sound::Sound(nl::node src) {
    id_ = add_sound(src);
    create_alure_source();
}

Sound::Sound() {
    id_ = 0;
    create_alure_source();
}

void Sound::play() {
    if (id_ > 0) {
        std::string id_s = std::to_string((uint32_t)id_);
        alure::Buffer buff = Music::ctx_.getBuffer(id_s);
        if (sound_src_)
            sound_src_.play(buff);
    }
}

Error Sound::init() {
    // if (!BASS_Init(1, 44100, 0, nullptr, 0))
    //	return Error::Code::AUDIO;

    nl::node uisrc = nl::nx::sound["UI.img"];

    add_sound(Sound::Name::BUTTONCLICK, uisrc["BtMouseClick"]);
    add_sound(Sound::Name::BUTTONOVER, uisrc["BtMouseOver"]);
    add_sound(Sound::Name::CHARSELECT, uisrc["CharSelect"]);
    add_sound(Sound::Name::DLGNOTICE, uisrc["DlgNotice"]);
    add_sound(Sound::Name::MENUDOWN, uisrc["MenuDown"]);
    add_sound(Sound::Name::MENUUP, uisrc["MenuUp"]);
    add_sound(Sound::Name::RACESELECT, uisrc["RaceSelect"]);
    add_sound(Sound::Name::SCROLLUP, uisrc["ScrollUp"]);
    add_sound(Sound::Name::SELECTMAP, uisrc["SelectMap"]);
    add_sound(Sound::Name::TAB, uisrc["Tab"]);
    add_sound(Sound::Name::WORLDSELECT, uisrc["WorldSelect"]);
    add_sound(Sound::Name::DRAGSTART, uisrc["DragStart"]);
    add_sound(Sound::Name::DRAGEND, uisrc["DragEnd"]);
    add_sound(Sound::Name::WORLDMAPOPEN, uisrc["WorldmapOpen"]);
    add_sound(Sound::Name::WORLDMAPCLOSE, uisrc["WorldmapClose"]);

    nl::node gamesrc = nl::nx::sound["Game.img"];

    add_sound(Sound::Name::GAMESTART, gamesrc["GameIn"]);
    add_sound(Sound::Name::JUMP, gamesrc["Jump"]);
    add_sound(Sound::Name::DROP, gamesrc["DropItem"]);
    add_sound(Sound::Name::PICKUP, gamesrc["PickUpItem"]);
    add_sound(Sound::Name::PORTAL, gamesrc["Portal"]);
    add_sound(Sound::Name::LEVELUP, gamesrc["LevelUp"]);
    add_sound(Sound::Name::TOMBSTONE, gamesrc["Tombstone"]);

    nl::node itemsrc = nl::nx::sound["Item.img"];

    for (auto node : itemsrc)
        add_sound(node.name(), node["Use"]);

    uint8_t volume = Setting<SFXVolume>::get().load();

    source_inc_ = 1;
    // if (!set_sfxvolume(volume))
    //	return Error::Code::AUDIO;

    return Error::Code::NONE;
}

void Sound::close() {
    sound_srcs_[source_inc_ - 1].destroy();
    sound_srcs_[source_inc_ - 1] = NULL;
    // BASS_Free();
}

bool Sound::set_sfxvolume(uint8_t vol) {
    // TODO: implement in-game volume
    return false;
}

size_t Sound::add_sound(nl::node src) {
    nl::audio ad = src;

    auto data = reinterpret_cast<const char *>(ad.data());

    if (data) {
        size_t id_ = ad.id();

        std::string id_s = std::to_string((uint32_t)id_);
        Music::audiodb_[id_s] = new membuf(data + 82, ad.length() - 82);

        return id_;
    } else {
        return 0;
    }
}

void Sound::add_sound(Name name, nl::node src) {
    size_t id_ = add_sound(src);

    if (id_)
        soundids_[name] = id_;
}

void Sound::add_sound(std::string itemid, nl::node src) {
    size_t id_ = add_sound(src);

    if (id_)
        itemids_[itemid] = id_;
}

std::string Sound::format_id(int32_t itemid) {
    std::string strid = std::to_string(itemid);
    strid.insert(0, 8 - strid.size(), '0');

    return strid;
}

EnumMap<Sound::Name, size_t> Sound::soundids_;
std::unordered_map<std::string, size_t> Sound::itemids_;

Music::Music(std::string p) {
    path_ = p;
}

void Music::play() const {
    static std::string bgmpath = "";

    if (path_ == bgmpath)
        return;

    /* will throw std::out:of:range if not used before. */
    try {
        audiodb_.at(path_);
    } catch (std::out_of_range e) {
        nl::audio ad = nl::nx::sound.resolve(path_);
        auto data = reinterpret_cast<const char *>(ad.data());
        audiodb_[path_] = new membuf(data + 82, ad.length() - 82);
    }

    music_buff_ = Music::ctx_.getBuffer(path_);
    music_src_.setLooping(true);
    music_src_.play(music_buff_);

    bgmpath = path_;
}

void Music::play_once() const {
    static std::string bgmpath = "";

    if (path_ == bgmpath)
        return;

    /* will throw std::out:of:range if not used before. */
    try {
        audiodb_.at(path_);
    } catch (std::out_of_range e) {
        nl::audio ad = nl::nx::sound.resolve(path_);
        auto data = reinterpret_cast<const char *>(ad.data());
        audiodb_[path_] = new membuf(data + 82, ad.length() - 82);
    }

    // alure::Context::MakeCurrent(ctx_);
    music_buff_ = Music::ctx_.getBuffer(path_);
    music_src_.setLooping(false);
    music_src_.play(music_buff_);

    bgmpath = path_;
}

Error Music::init() {
    uint8_t volume = Setting<BGMVolume>::get().load();

    dev_mngr_ = alure::DeviceManager::getInstance();
    dev_ = dev_mngr_.openPlayback();
    ctx_ = dev_.createContext();
    alure::Context::MakeCurrent(ctx_);
    music_src_ = ctx_.createSource();

    alure::FileIOFactory::set(alure::MakeUnique<FileFactory>(&audiodb_));
    /*TODO: add checks*/

    // if (!set_bgmvolume(volume))
    //	return Error::Code::AUDIO;

    return Error::Code::NONE;
}

bool Music::set_bgmvolume(uint8_t vol) {
    return true;  // BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, vol * 100) == TRUE;
}

void Music::update_context() {
    if (ctx_)
        ctx_.update();
}
}  // namespace ms