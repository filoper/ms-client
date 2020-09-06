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
#include "Textfield.h"

#include <sstream>
#include <utility>

#include "../UI.h"

namespace ms {
Textfield::Textfield() :
    text_(""),
    show_marker_(true),
    elapsed_(0),
    marker_pos_(0),
    bounds_(),
    limit_(),
    crypt_(0),
    state_(State::NORMAL) {}

Textfield::Textfield(Text::Font font,
                     Text::Alignment alignment,
                     Color::Name color,
                     Rectangle<int16_t> bounds,
                     size_t limit) :
    text_label_(font, alignment, color, "", 0, false),
    text_(""),
    marker_(font, alignment, color, "|"),
    show_marker_(true),
    elapsed_(0),
    marker_pos_(0),
    bounds_(bounds),
    limit_(limit),
    crypt_(0),
    state_(State::NORMAL) {}

void Textfield::draw(Point<int16_t> posiiton) const {
    if (state_ == State::DISABLED) {
        return;
    }

    Point<int16_t> absp = bounds_.get_left_top() + posiiton;

    if (!text_.empty()) {
        text_label_.draw(absp);
    }

    if (state_ == State::FOCUSED && show_marker_) {
        Point<int16_t> mpos =
            absp + Point<int16_t>(text_label_.advance(marker_pos_), -1);

        marker_.draw(mpos);
    }
}

void Textfield::update(Point<int16_t> parent) {
    if (state_ == State::DISABLED) {
        return;
    }

    parent_pos_ = parent;
    elapsed_ += Constants::TIMESTEP;

    if (elapsed_ > 256) {
        show_marker_ = !show_marker_;
        elapsed_ = 0;
    }
}

void Textfield::set_state(State st) {
    if (state_ != st) {
        state_ = st;

        if (state_ != State::DISABLED) {
            elapsed_ = 0;
            show_marker_ = true;
        } else {
            UI::get().remove_textfield();
        }

        if (state_ == State::FOCUSED) {
            UI::get().focus_textfield(this);
        }
    }
}

void Textfield::set_enter_callback(std::function<void(std::string)> onr) {
    onreturn_ = std::move(onr);
}

void Textfield::set_key_callback(KeyAction::Id key,
                                 std::function<void(void)> action) {
    callbacks_[key] = std::move(action);
}

void Textfield::send_key(KeyType::Id type, int32_t key, bool pressed) {
    if (pressed) {
        if (type == KeyType::Id::ACTION) {
            switch (key) {
                case KeyAction::Id::LEFT:
                    if (marker_pos_ > 0) {
                        marker_pos_--;
                    }

                    break;
                case KeyAction::Id::RIGHT:
                    if (marker_pos_ < text_.size()) {
                        marker_pos_++;
                    }

                    break;
                case KeyAction::Id::BACK:
                    if (!text_.empty() && marker_pos_ > 0) {
                        text_.erase(marker_pos_ - 1, 1);

                        marker_pos_--;

                        modify_text(text_);
                    }

                    break;
                case KeyAction::Id::RETURN:
                    if (onreturn_) {
                        onreturn_(text_);
                    }

                    break;
                case KeyAction::Id::SPACE: add_string(" "); break;
                case KeyAction::Id::HOME: marker_pos_ = 0; break;
                case KeyAction::Id::END: marker_pos_ = text_.size(); break;
                case KeyAction::Id::DELETE:
                    if (!text_.empty() && marker_pos_ < text_.size()) {
                        text_.erase(marker_pos_, 1);

                        modify_text(text_);
                    }

                    break;
                default:
                    if (callbacks_.count(key) != 0) {
                        callbacks_.at(key)();
                    }

                    break;
            }
        } else if (type == KeyType::Id::TEXT) {
            std::stringstream ss;
            char a = static_cast<int8_t>(key);

            ss << a;

            add_string(ss.str());
        }
    }
}

void Textfield::add_string(const std::string &str) {
    for (char c : str) {
        if (below_limit()) {
            text_.insert(marker_pos_, 1, c);

            marker_pos_++;

            modify_text(text_);
        }
    }
}

void Textfield::modify_text(const std::string &t) {
    if (crypt_ > 0) {
        std::string crypted;
        crypted.insert(0, t.size(), crypt_);

        text_label_.change_text(crypted);
    } else {
        text_label_.change_text(t);
    }

    text_ = t;
}

Cursor::State Textfield::send_cursor(Point<int16_t> cursorpos, bool clicked) {
    if (state_ == State::DISABLED) {
        return Cursor::State::IDLE;
    }

    if (get_bounds().contains(cursorpos)) {
        if (clicked) {
            if (state_ == State::NORMAL) {
                set_state(State::FOCUSED);
            }
            return Cursor::State::CLICKING;
        }
        return Cursor::State::CANCLICK;
    }

    if (clicked && state_ == State::FOCUSED) {
        set_state(State::NORMAL);
    }

    return Cursor::State::IDLE;
}

void Textfield::change_text(const std::string &t) {
    modify_text(t);

    marker_pos_ = text_.size();
}

void Textfield::set_cryptchar(int8_t character) {
    crypt_ = character;
}

bool Textfield::below_limit() const {
    if (limit_ > 0) {
        return text_.size() < limit_;
    }

    uint16_t advance = text_label_.advance(text_.size());

    return (advance + 50) < bounds_.get_horizontal().length();
}

const std::string &Textfield::get_text() const {
    return text_;
}

bool Textfield::empty() const {
    return text_.empty();
}

Textfield::State Textfield::get_state() const {
    return state_;
}

Rectangle<int16_t> Textfield::get_bounds() const {
    return Rectangle<int16_t>(bounds_.get_left_top() + parent_pos_,
                              bounds_.get_right_bottom() + parent_pos_);
}
}  // namespace ms