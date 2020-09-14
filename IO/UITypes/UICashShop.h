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

#include "../../Data/ItemData.h"
#include "../../Graphics/Text.h"
#include "../Components/Charset.h"
#include "../Components/Gauge.h"
#include "../Components/Slider.h"
#include "../UIElement.h"

namespace ms {
class UICashShop : public UIElement {
public:
    static constexpr Type TYPE = UIElement::Type::CASHSHOP;
    static constexpr bool FOCUSED = true;
    static constexpr bool TOGGLED = false;

    UICashShop();

    void draw(float inter) const override;
    void update() override;

    Button::State button_pressed(uint16_t buttonid) override;

    Cursor::State send_cursor(bool clicked, Point<int16_t> cursorpos) override;

    UIElement::Type get_type() const override;

    void exit_cashshop();

private:
    void update_items();

    static constexpr uint8_t MAX_ITEMS = 7u * 2u + 1u;

    class Item {
    public:
        enum Label : uint8_t {
            ACTION,
            BOMB_SALE,
            BONUS,
            EVENT = 4,
            HOT,
            LIMITED,
            LIMITED_BRONZE,
            LIMITED_GOLD,
            LIMITED_SILVER,
            LUNA_CRYSTAL,
            MASTER = 12,
            MUST,
            NEW,
            SALE = 17,
            SPEICAL,
            SPECIAL_PRICE,
            TIME,
            TODAY,
            WEEKLY,
            WONDER_BERRY,
            WORLD_SALE,
            NONE
        };

        Item(int32_t itemid, Label label, int32_t discount, uint16_t count) :
            label(label),
            discount_price(discount),
            count(count),
            data_(ItemData::get(itemid)) {}

        Label label;
        int32_t discount_price;
        uint16_t count;

        void draw(const DrawArgument &args) const {
            data_.get_icon(false).draw(args);
        }

        const std::string get_name() const { return data_.get_name(); }

        const int32_t get_price() const { return data_.get_price(); }

    private:
        const ItemData &data_;
    };

    enum Buttons : uint16_t {
        BtPreview1,
        BtPreview2,
        BtPreview3,
        BtExit,
        BtChargeNX,
        BtChargeRefresh,
        BtWish,
        BtMileage,
        BtHelp,
        BtCoupon,
        BtNext,
        BtPrev,
        BtDetailPackage,
        BtNonGrade,
        BtBuyAvatar,
        BtDefaultAvatar,
        BtInventory,
        BtSaveAvatar,
        BtTakeoffAvatar,
        BtBuy
    };

    Point<int16_t> best_new_dim_;

    Sprite preview_sprites_[3];
    uint8_t preview_index_;

    Sprite menu_tabs_[9];
    uint8_t menu_index_;

    Text job_label_;
    Text name_label_;

    std::vector<Sprite> promotion_sprites_;
    Point<int16_t> promotion_pos_;
    int8_t promotion_index_;

    Sprite mvp_sprites_[7];
    Point<int16_t> mvp_pos_;
    uint8_t mvp_grade_;
    Gauge mvp_gauge_;
    float_t mvp_exp_;

    Charset charge_charset_;

    Sprite item_base_;
    Sprite item_line_;
    Sprite item_none_;
    std::vector<Sprite> item_labels_;
    std::vector<Item> items_;
    Text item_name_[MAX_ITEMS];
    Text item_price_[MAX_ITEMS];
    Text item_discount_[MAX_ITEMS];
    Text item_percent_[MAX_ITEMS];

    Slider list_slider_;
    int16_t list_offset_;
};
}  // namespace ms