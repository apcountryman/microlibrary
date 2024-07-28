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

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <type_traits>

#include "microlibrary/algorithm.h"
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

/**
 * \brief Integer decimal output format specifier.
 *
 * \tparam Integer The type of integer to format.
 */
template<typename Integer>
class Dec {
  public:
    static_assert( std::is_integral_v<Integer> );

    Dec() = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] integer The integer to be formatted.
     */
    constexpr Dec( Integer integer ) noexcept : m_integer{ integer }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Dec( Dec && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Dec( Dec const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Dec() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Dec && expression ) noexcept -> Dec & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Dec const & expression ) noexcept -> Dec & = default;

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

/**
 * \brief Integer hexadecimal output format specifier.
 *
 * \tparam Integer The type of integer to format.
 */
template<typename Integer>
class Hex {
  public:
    static_assert( std::is_integral_v<Integer> );

    Hex() = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] integer The integer to be formatted.
     */
    constexpr Hex( Integer integer ) noexcept : m_integer{ integer }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Hex( Hex && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Hex( Hex const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Hex() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Hex && expression ) noexcept -> Hex & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Hex const & expression ) noexcept -> Hex & = default;

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

/**
 * \brief Hex dump output format specifier.
 *
 * \tparam Address Data address. Must be an unsigned integer type.
 * \tparam Iterator Data iterator. Data must be convertible to std::uint8_t.
 */
template<typename Address, typename Iterator>
class Hex_Dump {
  public:
    static_assert( std::is_unsigned_v<Address> );

    Hex_Dump() = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] address The address of the data to dump.
     * \param[in] begin The beginning of the data to dump.
     * \param[in] end The end of the data to dump.
     */
    constexpr Hex_Dump( Address address, Iterator begin, Iterator end ) noexcept :
        m_address{ address },
        m_begin{ begin },
        m_end{ end }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Hex_Dump( Hex_Dump && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Hex_Dump( Hex_Dump const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Hex_Dump() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Hex_Dump && expression ) noexcept -> Hex_Dump & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Hex_Dump const & expression ) noexcept -> Hex_Dump & = default;

    /**
     * \brief Get the address of the data to dump.
     *
     * \return The address of the data to dump.
     */
    constexpr auto address() const noexcept -> Address
    {
        return m_address;
    }

    /**
     * \brief Get the beginning of the data to dump.
     *
     * \return The beginning of the data to dump.
     */
    constexpr auto begin() const noexcept -> Iterator
    {
        return m_begin;
    }

    /**
     * \brief Get the end of the data to dump.
     *
     * \return The end of the data to dump.
     */
    constexpr auto end() const noexcept -> Iterator
    {
        return m_end;
    }

  private:
    /**
     * \brief The address of the data to dump.
     */
    Address m_address;

    /**
     * \brief The beginning of the data to dump.
     */
    Iterator m_begin;

    /**
     * \brief The end of the data to dump.
     */
    Iterator m_end;
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

/**
 * \brief microlibrary::Format::Dec output formatter.
 *
 * \tparam Integer The type of integer to format.
 */
template<typename Integer>
class Output_Formatter<Format::Dec<Integer>> {
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
        Formatted_Integer formatted_integer;

        auto const begin = format( integer, formatted_integer );

        stream.put( begin, formatted_integer.end() );

        return formatted_integer.end() - begin;
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
        Formatted_Integer formatted_integer;

        auto const begin = format( integer, formatted_integer );

        auto result = stream.put( begin, formatted_integer.end() );
        if ( result.is_error() ) {
            return result.error();
        } // if

        return static_cast<std::size_t>( formatted_integer.end() - begin );
    }

  private:
    /**
     * \brief Formatted integer.
     */
    using Formatted_Integer =
        Array<char, ( std::is_signed_v<Integer> ? 1 : 0 ) + std::numeric_limits<Integer>::digits10 + 1>;

    /**
     * \brief Format an integer.
     *
     * \param[in] integer The integer to format.
     * \param[in] formatted_integer The array to write the formatted integer to.
     *
     * \return An iterator to the beginning of the formatted integer.
     */
    static constexpr auto format( Integer integer, Formatted_Integer & formatted_integer ) noexcept
        -> typename Formatted_Integer::Iterator
    {
        // #lizard forgives the length

        if constexpr ( std::is_signed_v<Integer> ) {
            auto const is_negative = integer < 0;

            auto i = formatted_integer.rbegin();

            do {
                *i = '0' + std::abs( integer % 10 );

                ++i;
                integer /= 10;
            } while ( integer );

            if ( is_negative ) {
                *i = '-';

                ++i;
            } // if

            return i.base();
        } else {
            auto i = formatted_integer.rbegin();
            do {
                *i = '0' + ( integer % 10 );

                ++i;
                integer /= 10;
            } while ( integer );
            return i.base();
        } // else
    }
};

/**
 * \brief microlibrary::Format::Hex output formatter.
 *
 * \tparam Integer The type of integer to format.
 */
template<typename Integer>
class Output_Formatter<Format::Hex<Integer>> {
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
     * \brief The number of bits in a nibble.
     */
    static constexpr auto NIBBLE_DIGITS = 4;

    /**
     * \brief The number of nibbles in an unsigned integer.
     */
    static constexpr auto NIBBLES = std::numeric_limits<std::make_unsigned_t<Integer>>::digits / NIBBLE_DIGITS;

    /**
     * \brief Nibble bit mask.
     */
    static constexpr auto NIBBLE_MASK = mask<std::uint_fast8_t>( NIBBLE_DIGITS, 0 );

    /**
     * \brief Formatted integer.
     */
    using Formatted_Integer = Array<char, 2 + NIBBLES>;

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
        for ( auto nibble = 0; nibble < NIBBLES; ++nibble, ++i, unsigned_integer >>= NIBBLE_DIGITS ) {
            auto const n = static_cast<std::uint_fast8_t>( unsigned_integer & NIBBLE_MASK );

            *i = n < 0xA ? '0' + n : 'A' + ( n - 0xA );
        } // for
        *i = 'x';
        ++i;
        *i = '0';

        return formatted_integer;
    }
};

/**
 * \brief microlibrary::Format::Hex_Dump output formatter.
 *
 * \tparam Address Data address. Must be an unsigned integer type.
 * \tparam Iterator Data iterator. Data must be convertible to std::uint8_t.
 */
template<typename Address, typename Iterator>
class Output_Formatter<Format::Hex_Dump<Address, Iterator>> {
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
     * \brief Write a formatted microlibrary::Format::Hex_Dump to a stream.
     *
     * \param[in] stream The stream to write the formatted microlibrary::Format::Hex_Dump
     *            to.
     * \param[in] hex_dump The microlibrary::Format::Hex_Dump to format.
     *
     * \return The number of characters written to the stream.
     */
    auto print( Output_Stream & stream, Format::Hex_Dump<Address, Iterator> const & hex_dump ) const noexcept
        -> std::size_t
    {
        Row row;

        auto address = hex_dump.address();
        auto begin   = hex_dump.begin();
        auto end     = hex_dump.end();
        auto n       = std::size_t{ 0 };

        for ( ; begin != end; address += ROW_BYTES, n += row.size() ) {
            begin = generate_row( address, begin, end, row );

            stream.put( row.begin(), row.end() );
        } // for

        return n;
    }

    /**
     * \brief Write a formatted microlibrary::Format::Hex_Dump to a stream.
     *
     * \param[in] stream The stream to write the formatted microlibrary::Format::Hex_Dump
     *            to.
     * \param[in] hex_dump The microlibrary::Format::Hex_Dump to format.
     *
     * \return The number of characters written to the stream if the write succeeded.
     * \return An error code if the write failed.
     */
    auto print( Fault_Reporting_Output_Stream & stream, Format::Hex_Dump<Address, Iterator> const & hex_dump ) const noexcept
        -> Result<std::size_t>
    {
        Row row;

        auto address = hex_dump.address();
        auto begin   = hex_dump.begin();
        auto end     = hex_dump.end();
        auto n       = std::size_t{ 0 };

        for ( ; begin != end; address += ROW_BYTES, n += row.size() ) {
            begin = generate_row( address, begin, end, row );

            auto result = stream.put( row.begin(), row.end() );
            if ( result.is_error() ) {
                return result.error();
            } // if
        }     // for

        return n;
    }

  private:
    /**
     * \brief The number of bits in a nibble.
     */
    static constexpr auto NIBBLE_DIGITS = 4;

    /**
     * \brief Nibble bit mask.
     */
    static constexpr auto NIBBLE_MASK = mask<std::uint_fast8_t>( NIBBLE_DIGITS, 0 );

    /**
     * \brief The number of nibbles in an address.
     */
    static constexpr auto ADDRESS_NIBBLES = std::uint_fast8_t{ std::numeric_limits<Address>::digits
                                                               / NIBBLE_DIGITS };

    /**
     * \brief The number of nibbles in a byte.
     */
    static constexpr auto BYTE_NIBBLES = std::uint_fast8_t{ std::numeric_limits<std::uint8_t>::digits
                                                            / NIBBLE_DIGITS };

    /**
     * \brief Group separation spaces.
     */
    static constexpr auto GROUP_SEPARATION = std::uint_fast8_t{ 2 };

    /**
     * \brief The number of bytes in a row.
     */
    static constexpr auto ROW_BYTES = std::uint_fast8_t{ 16 };

    /**
     * \brief Row buffer address (hex) offset.
     */
    static constexpr auto ADDRESS_HEX_OFFSET = std::uint_fast8_t{ 0 };

    /**
     * \brief Row buffer data (hex) offset.
     */
    static constexpr auto DATA_HEX_OFFSET = std::uint_fast8_t{ ADDRESS_HEX_OFFSET + ADDRESS_NIBBLES
                                                               + GROUP_SEPARATION };

    /**
     * \brief Row buffer data (ASCII) offset.
     */
    static constexpr auto DATA_ASCII_OFFSET = std::uint_fast8_t{
        DATA_HEX_OFFSET + ( ( ( BYTE_NIBBLES + 1 ) * ROW_BYTES ) - 1 ) + GROUP_SEPARATION + 1
    };

    /**
     * \brief Row buffer.
     */
    using Row =
        Array<char, ADDRESS_NIBBLES + GROUP_SEPARATION + ( ( ( BYTE_NIBBLES + 1 ) * ROW_BYTES ) - 1 ) + GROUP_SEPARATION + 1 + ROW_BYTES + 1 + 1>;

    /**
     * \brief Format an integer (hex).
     *
     * \param[in] integer The integer to format.
     * \param[out] location The location to write the formatted integer to.
     */
    template<typename Integer>
    static void format_hex( Integer integer, typename Row::Iterator location ) noexcept
    {
        constexpr auto nibbles = std::uint_fast8_t{ std::numeric_limits<Integer>::digits / 4 };
        auto           i       = typename Row::Reverse_Iterator{ location + nibbles };
        for ( auto nibble = std::uint_fast8_t{ 0 }; nibble < nibbles;
              ++nibble, ++i, integer >>= NIBBLE_DIGITS ) {
            auto const n = static_cast<std::uint_fast8_t>( integer & NIBBLE_MASK );

            *i = n < 0xA ? '0' + n : 'A' + ( n - 0xA );
        } // for
    }

    /**
     * \brief Format a byte (ASCII).
     *
     * \param[in] byte The byte to format.
     * \param[out] location The location to write the formatted byte to.
     */
    static void format_ascii( std::uint8_t byte, typename Row::Iterator location ) noexcept
    {
        *location = std::isprint( byte ) ? static_cast<char>( byte ) : '.';
    }

    /**
     * \brief Generate a row.
     *
     * \param[in] address The row's address.
     * \param[in] begin The beginning of the data to dump.
     * \param[in] end The end of the data to dump.
     * \param[out] row The row buffer to write the generated row to.
     *
     * \return The beginning of the remaining data to dump.
     */
    static auto generate_row( Address address, Iterator begin, Iterator end, Row & row ) noexcept -> Iterator
    {
        fill( row.begin() + ADDRESS_NIBBLES, row.end() - 1, ' ' );

        row.back() = '\n';

        *( row.begin() + DATA_ASCII_OFFSET - 1 ) = '|';

        format_hex( address, row.begin() + ADDRESS_HEX_OFFSET );

        auto byte = std::uint_fast8_t{ 0 };
        for ( ; begin != end and byte < ROW_BYTES; ++begin, ++byte ) {
            format_hex(
                static_cast<std::uint8_t>( *begin ),
                row.begin() + DATA_HEX_OFFSET + ( ( BYTE_NIBBLES + 1 ) * byte ) );
            format_ascii( static_cast<std::uint8_t>( *begin ), row.begin() + DATA_ASCII_OFFSET + byte );
        } // for
        *( row.begin() + DATA_ASCII_OFFSET + byte ) = '|';

        return begin;
    }
};

} // namespace microlibrary

#endif // MICROLIBRARY_FORMAT_H
