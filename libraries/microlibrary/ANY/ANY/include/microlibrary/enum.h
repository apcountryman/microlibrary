/**
 * microlibrary
 *
 * Copyright 2024, Andrew Countryman <apcountryman@gmail.com> and the microlibrary
 * contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under
 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * \file
 * \brief microlibrary enum utilities interface.
 */

#ifndef MICROLIBRARY_ENUM_H
#define MICROLIBRARY_ENUM_H

#include <type_traits>

namespace microlibrary {

/**
 * \brief Convert an enum value to its underlying type.
 *
 * \tparam Enum The type of enum to convert.
 *
 * \param[in] value The enum value to convert.
 *
 * \return The enum value converted to its underlying type.
 */
template<typename Enum>
constexpr auto to_underlying( Enum value ) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>( value );
}

} // namespace microlibrary

#endif // MICROLIBRARY_ENUM_H
