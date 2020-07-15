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

#include <functional>
#include <type_traits>

namespace ms {
template<typename T>
class Optional {
public:
    template<typename R,
             typename = std::enable_if_t<std::is_base_of<R, T>::value
                                         || std::is_base_of<T, R>::value>>
    constexpr Optional(R *r_val) : val_(static_cast<T *>(r_val)) {}

    template<typename R,
             typename = std::enable_if_t<std::is_base_of<R, T>::value
                                         || std::is_base_of<T, R>::value>>
    constexpr Optional(Optional<R> r_opt) : Optional(r_opt.get()) {}
    constexpr Optional(T *p) : val_(p) {}
    constexpr Optional(T &p) : val_(&p) {}
    constexpr Optional() : val_(nullptr) {}

    explicit operator bool() const { return val_ != nullptr; }

    T *get() const { return val_; }

    T *operator->() const { return val_; }

    T &operator*() const { return *val_; }

private:
    T *val_;
};
}  // namespace ms