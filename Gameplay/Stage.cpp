//	This file is part of the continued Journey MMORPG client
//	Copyright (C) 2015-2019  Daniel Allendorf, Ryan Payton
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU Affero General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU Affero General Public License for more details.
//
//	You should have received a copy of the GNU Affero General Public License
//	along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "Stage.h"

#include <nlnx/nx.hpp>

#include "../Configuration.h"
#include "../IO/UI.h"
#include "../IO/UITypes/UIStatusBar.h"
#include "../Net/Packets/AttackAndSkillPackets.h"
#include "../Net/Packets/GameplayPackets.h"
#include "../Util/Misc.h"
#include "Timer.h"

namespace ms {
Stage::Stage() :
    combat_(player_, chars_, mobs_, reactors_),
    mob_combat_(player_, chars_, mobs_) {
    state_ = State::INACTIVE;
}

void Stage::init() {
    drops_.init();
}

void Stage::load(int32_t mapid, int8_t portalid) {
    switch (state_) {
        case State::INACTIVE:
            load_map(mapid);
            respawn(portalid);
            break;
        case State::TRANSITION: respawn(portalid); break;
    }

    state_ = State::ACTIVE;
}

void Stage::loadplayer(const CharEntry &entry,
                       uint8_t wid,
                       uint8_t channel_id) {
    player_ = Player(entry, wid, channel_id);
    playable_ = player_;

    start_ = ContinuousTimer::get().start();

    CharStats stats = player_.get_stats();
    level_before_ = stats.get_stat(MapleStat::Id::LEVEL);
    exp_before_ = stats.get_exp();
}

void Stage::clear() {
    state_ = State::INACTIVE;

    chars_.clear();
    npcs_.clear();
    mobs_.clear();
    drops_.clear();
    reactors_.clear();
}

void Stage::load_map(int32_t mapid) {
    Stage::map_id_ = mapid;

    std::string strid = string_format::extend_id(mapid, 9);
    std::string prefix = std::to_string(mapid / 100000000);

    nl::node src = mapid == -1
                       ? nl::nx::ui["CashShopPreview.img"]
                       : nl::nx::map["Map"]["Map" + prefix][strid + ".img"];

    tiles_objs_ = MapTilesObjs(src);
    backgrounds_ = MapBackgrounds(src["back"]);
    physics_ = Physics(src["foothold"]);
    map_info_ = MapInfo(src,
                        physics_.get_fht().get_walls(),
                        physics_.get_fht().get_borders());
    portals_ = MapPortals(src["portal"], mapid);
}

void Stage::respawn(int8_t portalid) {
    Music(map_info_.get_bgm()).play();

    Point<int16_t> spawnpoint = portals_.get_portal_by_id(portalid);
    Point<int16_t> startpos = physics_.get_y_below(spawnpoint);
    player_.respawn(startpos, map_info_.is_underwater());
    camera_.set_position(startpos);
    camera_.set_view(map_info_.get_walls(), map_info_.get_borders());
}

void Stage::draw(float alpha) const {
    if (state_ != State::ACTIVE)
        return;

    Point<int16_t> viewpos = camera_.position(alpha);
    Point<double> viewrpos = camera_.real_position(alpha);
    double viewx = viewrpos.x();
    double viewy = viewrpos.y();

    backgrounds_.drawbackgrounds(viewx, viewy, alpha);

    for (auto id : Layer::IDs) {
        tiles_objs_.draw(id, viewpos, alpha);
        reactors_.draw(id, viewx, viewy, alpha);
        npcs_.draw(id, viewx, viewy, alpha);
        mobs_.draw(id, viewx, viewy, alpha);
        chars_.draw(id, viewx, viewy, alpha);
        player_.draw(id, viewx, viewy, alpha);
        drops_.draw(id, viewx, viewy, alpha);
    }

    combat_.draw(viewx, viewy, alpha);
    mob_combat_.draw(viewx, viewy, alpha);
    portals_.draw(viewpos, alpha);
    backgrounds_.drawforegrounds(viewx, viewy, alpha);
    effect_.draw();
}

void Stage::update() {
    if (state_ != State::ACTIVE)
        return;

    combat_.update();
    mob_combat_.update();
    backgrounds_.update();
    effect_.update();
    tiles_objs_.update();

    reactors_.update(physics_);
    npcs_.update(physics_);
    mobs_.update(physics_);
    chars_.update(physics_);
    drops_.update(physics_);
    player_.update(physics_);

    portals_.update(player_.get_position());
    camera_.update(player_.get_position());

    if (player_.is_invincible())
        return;

    if (int32_t oid_id = mobs_.find_colliding(player_.get_phobj())) {
        if (MobAttack attack = mobs_.create_attack(oid_id)) {
            MobAttackResult result = player_.damage(attack);
            TakeDamagePacket(result, TakeDamagePacket::From::TOUCH).dispatch();
        }
    }
}

void Stage::show_character_effect(int32_t cid, CharEffect::Id effect) {
    if (auto character = get_character(cid))
        character->show_effect_id(effect);
}

void Stage::check_portals() {
    if (player_.is_attacking())
        return;

    Point<int16_t> playerpos = player_.get_position();
    Portal::WarpInfo warpinfo = portals_.find_warp_at(playerpos);

    if (warpinfo.intramap) {
        Point<int16_t> spawnpoint =
            portals_.get_portal_by_name(warpinfo.toname);
        Point<int16_t> startpos = physics_.get_y_below(spawnpoint);

        player_.respawn(startpos, map_info_.is_underwater());
    } else if (warpinfo.valid) {
        ChangeMapPacket(false, -1, warpinfo.name, false).dispatch();

        CharStats &stats = Stage::get().get_player().get_stats();

        stats.set_mapid(warpinfo.mapid);

        Sound(Sound::Name::PORTAL).play();
    }
}

void Stage::check_seats() {
    if (player_.is_sitting() || player_.is_attacking())
        return;

    Optional<const Seat> seat = map_info_.findseat(player_.get_position());
    player_.set_seat(seat);
}

void Stage::check_ladders(bool up) {
    if (player_.is_climbing() || player_.is_attacking())
        return;

    Optional<const Ladder> ladder =
        map_info_.findladder(player_.get_position(), up);
    player_.set_ladder(ladder);
}

void Stage::check_drops() {
    Point<int16_t> playerpos = player_.get_position();
    MapDrops::Loot loot = drops_.find_loot_at(playerpos);

    if (loot.first)
        PickupItemPacket(loot.first, loot.second).dispatch();
}

void Stage::send_key(KeyType::Id type, int32_t action, bool down) {
    if (state_ != State::ACTIVE || !playable_)
        return;

    switch (type) {
        case KeyType::Id::ACTION:
            if (down) {
                switch (action) {
                    case KeyAction::Id::UP:
                        check_ladders(true);
                        check_portals();
                        break;
                    case KeyAction::Id::DOWN: check_ladders(false); break;
                    case KeyAction::Id::SIT: check_seats(); break;
                    case KeyAction::Id::ATTACK: combat_.use_move(0); break;
                    case KeyAction::Id::PICKUP: check_drops(); break;
                }
            }

            playable_->send_action(KeyAction::actionbyid(action), down);
            break;
        case KeyType::Id::SKILL: combat_.use_move(action); break;
        case KeyType::Id::ITEM: player_.use_item(action); break;
        case KeyType::Id::FACE: player_.set_expression(action); break;
    }
}

Cursor::State Stage::send_cursor(bool pressed, Point<int16_t> position) {
    auto statusbar = UI::get().get_element<UIStatusBar>();

    if (statusbar && statusbar->is_menu_active()) {
        if (pressed)
            statusbar->remove_menus();

        if (statusbar->is_in_range(position))
            return statusbar->send_cursor(pressed, position);
    }

    return npcs_.send_cursor(pressed, position, camera_.position());
}

bool Stage::is_player(int32_t cid) const {
    return cid == player_.get_oid();
}

MapNpcs &Stage::get_npcs() {
    return npcs_;
}

MapChars &Stage::get_chars() {
    return chars_;
}

MapMobs &Stage::get_mobs() {
    return mobs_;
}

MapReactors &Stage::get_reactors() {
    return reactors_;
}

MapDrops &Stage::get_drops() {
    return drops_;
}

Player &Stage::get_player() {
    return player_;
}

Combat &Stage::get_combat() {
    return combat_;
}

MobCombat &Stage::get_mob_combat() {
    return mob_combat_;
}

Optional<Char> Stage::get_character(int32_t cid) {
    if (is_player(cid))
        return player_;
    else
        return chars_.get_char(cid);
}

int Stage::get_mapid() {
    return map_id_;
}

void Stage::add_effect(std::string path) {
    effect_ = MapEffect(path);
}

int64_t Stage::get_uptime() {
    return ContinuousTimer::get().stop(start_);
}

uint16_t Stage::get_uplevel() {
    return level_before_;
}

int64_t Stage::get_upexp() {
    return exp_before_;
}

void Stage::transfer_player() {
    PlayerMapTransferPacket().dispatch();

    if (Configuration::get().get_admin())
        AdminEnterMapPacket(AdminEnterMapPacket::Operation::ALERT_ADMINS)
            .dispatch();
}

void Stage::clear_channel_objects() {
    chars_.clear();
    mobs_.clear();
    drops_.clear();
    reactors_.clear();
}

void Stage::change_channel(uint8_t ch) {
    UI::get().disable();
    GraphicsGL::get().lock();
    ChangeChannelPacket(ch).dispatch();
    player_.set_channel_id(ch);
    state_ = State::TRANSITION;
}
}  // namespace ms