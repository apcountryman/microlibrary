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
 * \brief microlibrary::Format interface.
 */

#ifndef MICROLIBRARY_FORMAT_H
#define MICROLIBRARY_FORMAT_H

#include <cstddef>
#include <type_traits>

#include "microlibrary/array.h"
#include "microlibrary/integer.h"
#include "microlibrary/result.h"
#include "microlibrary/stream.h"

/**
 * \brief Formatting facilities.
 */
namespace microlibrary::Format {

/**
 * \brief Integer binary output format specifier.
 *
 * \tparam Integer The type of integer to format.
 */
template<typename Integer>
class Bin {
  public:
    static_assert( std::is_integral_v<Integer> );

    Bin() = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] integer The integer to be formatted.
     */
    constexpr Bin( Integer integer ) noexcept : m_integer{ integer }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Bin( Bin && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Bin( Bin const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Bin() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Bin && expression ) noexcept -> Bin & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Bin const & expression ) noexcept -> Bin & = default;

    /**
     * \brief Get the integer to be formatted.
     *
     * \return The integer to be formatted.
     */
    constexpr operator Integer() const noexcept
    {
        return m_integer;
    }

  private:
    /**
     * \brief The integer to be formatted.
     */
    Integer m_integer;
};

} // namespace microlibrary::Format

namespace microlibrary {

/**
 * \brief microlibrary::Format::Bin output formatter.
 *
 * \tparam Integer The type of integer to format.
 */
template<typename Integer>
class Output_Formatter<Format::Bin<Integer>> {
  public:
    /**
     * \brief Constructor.
     */
    constexpr Output_Formatter() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Output_Formatter( Output_Formatter && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Output_Formatter( Output_Formatter const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Output_Formatter() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Output_Formatter && expression ) noexcept -> Output_Formatter & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator   =( Output_Formatter const & expression ) noexcept
        -> Output_Formatter & = default;

    /**
     * \brief Write a formatted integer to a stream.
     *
     * \param[in] stream The stream to write the formatted integer to.
     * \param[in] integer The integer to format.
     *
     * \return The number of characters written to the stream.
     */
    auto print( Output_Stream & stream, Integer integer ) const noexcept -> std::size_t
    {
        auto const formatted_integer = format( integer );

        stream.put( formatted_integer.begin(), formatted_integer.end() );

        return formatted_integer.size();
    }

    /**
     * \brief Write a formatted integer to a stream.
     *
     * \param[in] stream The stream to write the formatted integer to.
     * \param[in] integer The integer to format.
     *
     * \return The number of characters written to the stream if the write succeeded.
     * \return An error code if the write failed.
     */
    auto print( Fault_Reporting_Output_Stream & stream, Integer integer ) const noexcept
        -> Result<std::size_t>
    {
        auto const formatted_integer = format( integer );

        auto result = stream.put( formatted_integer.begin(), formatted_integer.end() );
        if ( result.is_error() ) {
            return result.error();
        } // if

        return formatted_integer.size();
    }

  private:
    /**
     * \brief The number of bits in an unsigned integer.
     */
    static constexpr auto DIGITS = std::numeric_limits<std::make_unsigned_t<Integer>>::digits;

    /**
     * \brief Formatted integer.
     */
    using Formatted_Integer = Array<char, 2 + DIGITS>;

    /**
     * \brief Format an integer.
     *
     * \param[in] integer The integer to format.
     *
     * \return The formatted integer.
     */
    static constexpr auto format( Integer integer ) noexcept -> Formatted_Integer
    {
        auto unsigned_integer = to_unsigned( integer );

        Formatted_Integer formatted_integer;

        auto i = formatted_integer.rbegin();
        for ( auto bit = 0; bit < DIGITS; ++bit, ++i, unsigned_integer >>= 1 ) {
            *i = '0' + ( unsigned_integer & 0b1 );
        } // for
        *i = 'b';
        ++i;
        *i = '0';

        return formatted_integer;
    }
};

} // namespace microlibrary

#endif // MICROLIBRARY_FORMAT_H
