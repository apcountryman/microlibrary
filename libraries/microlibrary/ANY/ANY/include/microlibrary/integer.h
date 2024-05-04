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

#include <cstdint>
#include <cstring>
#include <limits>
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

/**
 * \brief Lookup an unsigned integer value's highest bit set.
 *
 * \tparam Integer The type of unsigned integer the lookup will be performed on.
 *
 * \param[in] value The unsigned integer value to perform the lookup on.
 *
 * \attention This function assumes value is non-zero.
 *
 * \return The unsigned integer value's highest bit set.
 */
template<typename Integer>
constexpr auto highest_bit_set( Integer value ) noexcept -> std::uint_fast8_t
{
    static_assert( std::is_unsigned_v<Integer> );

    auto bit = std::uint_fast8_t{ 0 };
    for ( ; value >>= 1; ++bit ) {} // for
    return bit;
}

/**
 * \brief Create a bit mask.
 *
 * \tparam Mask The type of unsigned integer to use for the mask.
 *
 * \param[in] size The size of the mask (the number of masked bits).
 * \param[in] bit The bit position of the least significant masked bit.
 *
 * \return The created bit mask.
 */
template<typename Mask>
constexpr auto mask( std::uint_fast8_t size, std::uint_fast8_t bit ) noexcept -> Mask
{
    static_assert( std::is_unsigned_v<Mask> );

    return ( static_cast<std::uintmax_t>( std::numeric_limits<Mask>::max() )
             >> ( std::numeric_limits<Mask>::digits - size ) )
           << bit;
}

/**
 * \brief Reflect an unsigned integer's bits.
 *
 * \tparam Integer The type of unsigned integer the reflection will be performed on.
 *
 * \param[in] value The unsigned integer value to reflect.
 *
 * \return The reflection of the unsigned integer value.
 */
template<typename Integer>
constexpr auto reflect( Integer value ) noexcept -> Integer
{
    static_assert( std::is_unsigned_v<Integer> );

    auto result = value;
    value >>= 1;
    auto remaining_shifts = std::numeric_limits<Integer>::digits - 1;
    while ( value ) {
        result <<= 1;
        result |= value & 0b1;
        value >>= 1;
        --remaining_shifts;
    } // while
    return result << remaining_shifts;
}

/**
 * \brief Check if an unsigned integer is a power of two.
 *
 * \tparam Integer The type of unsigned integer the check will be performed on.
 *
 * \param[in] value The unsigned integer value to perform the check on.
 *
 * \return true if value is a power of two.
 * \return false if value is not a power of two.
 */
template<typename Integer>
constexpr auto is_power_of_two( Integer value ) noexcept -> bool
{
    static_assert( std::is_unsigned_v<Integer> );

    return value != 0 and ( value & ( value - 1 ) ) == 0;
}

} // namespace microlibrary

#endif // MICROLIBRARY_INTEGER_H
