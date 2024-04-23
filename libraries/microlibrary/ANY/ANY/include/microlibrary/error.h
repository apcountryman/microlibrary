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
 * \brief microlibrary error identification facilities interface.
 */

#ifndef MICROLIBRARY_ERROR_H
#define MICROLIBRARY_ERROR_H

#include <cstdint>
#include <type_traits>

namespace microlibrary {

/**
 * \brief Error ID.
 *
 * \attention This type is the expected underlying type for all error code enums.
 */
using Error_ID = std::uint_fast8_t;

/**
 * \brief Check if an enum is an error code enum.
 *
 * \tparam Enum The enum to check.
 */
template<typename Enum>
struct is_error_code_enum : std::false_type {
};

/**
 * \brief Check if an enum is an error code enum.
 *
 * \tparam Enum The enum to check.
 */
template<typename Enum>
inline constexpr auto is_error_code_enum_v = is_error_code_enum<Enum>::value;

} // namespace microlibrary

#endif // MICROLIBRARY_ERROR_H
