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
#pragma once

#include <unordered_map>
#include <vector>

#include "../../Template/Point.h"
#include "Stance.h"

namespace ms {
// A frame of animation for a skill or similar 'meta-stance'
// This simply redirects to a different stance and frame to use
class BodyAction {
public:
    BodyAction(nl::node src) {
        stance_ = Stance::by_string(src["action"]);
        frame_ = src["frame"];
        move_ = src["move"];

        int16_t sgndelay = src["delay"];

        if (sgndelay == 0)
            sgndelay = 100;

        if (sgndelay > 0) {
            delay_ = sgndelay;
            attack_frame_ = true;
        } else if (sgndelay < 0) {
            delay_ = -sgndelay;
            attack_frame_ = false;
        }
    }

    BodyAction() {}

    bool isattackframe() const { return attack_frame_; }

    uint8_t get_frame() const { return frame_; }

    uint16_t get_delay() const { return delay_; }

    Point<int16_t> get_move() const { return move_; }

    Stance::Id get_stance() const { return stance_; }

private:
    Stance::Id stance_;
    uint8_t frame_;
    uint16_t delay_;
    Point<int16_t> move_;
    bool attack_frame_;
};

class BodyDrawInfo {
public:
    void init();

    Point<int16_t> get_body_position(Stance::Id stance, uint8_t frame) const;

    Point<int16_t> get_arm_position(Stance::Id stance, uint8_t frame) const;

    Point<int16_t> get_hand_position(Stance::Id stance, uint8_t frame) const;

    Point<int16_t> get_head_position(Stance::Id stance, uint8_t frame) const;

    Point<int16_t> gethairpos(Stance::Id stance, uint8_t frame) const;

    Point<int16_t> getfacepos(Stance::Id stance, uint8_t frame) const;

    uint8_t nextframe(Stance::Id stance, uint8_t frame) const;

    uint16_t get_delay(Stance::Id stance, uint8_t frame) const;

    uint16_t get_attackdelay(std::string action, size_t no) const;

    uint8_t next_actionframe(std::string action, uint8_t frame) const;

    const BodyAction *get_action(std::string action, uint8_t frame) const;

private:
    std::unordered_map<uint8_t, Point<int16_t>>
        body_positions[Stance::Id::LENGTH];
    std::unordered_map<uint8_t, Point<int16_t>>
        arm_positions[Stance::Id::LENGTH];
    std::unordered_map<uint8_t, Point<int16_t>>
        hand_positions[Stance::Id::LENGTH];
    std::unordered_map<uint8_t, Point<int16_t>>
        head_positions[Stance::Id::LENGTH];
    std::unordered_map<uint8_t, Point<int16_t>>
        hair_positions[Stance::Id::LENGTH];
    std::unordered_map<uint8_t, Point<int16_t>>
        face_positions[Stance::Id::LENGTH];
    std::unordered_map<uint8_t, uint16_t> stance_delays[Stance::Id::LENGTH];

    std::unordered_map<std::string, std::unordered_map<uint8_t, BodyAction>>
        body_actions;
    std::unordered_map<std::string, std::vector<uint16_t>> attack_delays;
};
}  // namespace ms
