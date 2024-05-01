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
 * \brief microlibrary integer utilities interface.
 */

#ifndef MICROLIBRARY_INTEGER_H
#define MICROLIBRARY_INTEGER_H

#include <cstring>
#include <type_traits>

namespace microlibrary {

/**
 * \brief Convert a potentially signed integer to its bitwise unsigned integer equivalent.
 *
 * \tparam Integer The type of potentially signed integer to convert.
 *
 * \param[in] integer The potentially signed integer to convert.
 *
 * \return The potentially signed integer converted to its bitwise unsigned integer
 *         equivalent.
 */
template<typename Integer>
constexpr auto to_unsigned( Integer integer ) noexcept
{
    std::make_unsigned_t<Integer> unsigned_integer;
    static_assert( sizeof( unsigned_integer ) == sizeof( integer ) );
    std::memcpy( &unsigned_integer, &integer, sizeof( unsigned_integer ) );
    return unsigned_integer;
}

} // namespace microlibrary

#endif // MICROLIBRARY_INTEGER_H
