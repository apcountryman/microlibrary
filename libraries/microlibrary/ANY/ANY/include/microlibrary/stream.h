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
 * \brief microlibrary I/O streams interface.
 */

#ifndef MICROLIBRARY_STREAM_H
#define MICROLIBRARY_STREAM_H

#include <cstdint>

#include "microlibrary/rom.h"

namespace microlibrary {

/**
 * \brief Output formatter.
 *
 * \tparam T The type to print.
 *
 * \attention This class must be fully or partially specialized for each type that will
 *            support formatted output.
 */
template<typename T, typename = void>
class Output_Formatter {
  public:
    /**
     * \brief Constructor.
     */
    Output_Formatter() noexcept;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    Output_Formatter( Output_Formatter && source ) noexcept;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    Output_Formatter( Output_Formatter const & original ) noexcept;

    /**
     * \brief Destructor.
     */
    ~Output_Formatter() noexcept;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    auto operator=( Output_Formatter && expression ) noexcept -> Output_Formatter &;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    auto operator=( Output_Formatter const & expression ) noexcept -> Output_Formatter &;
};

/**
 * \brief Stream I/O driver.
 */
class Stream_IO_Driver {
  public:
    /**
     * \brief Write a character to the data sink.
     *
     * \param[in] character The character to write to the data sink.
     */
    virtual void put( char character ) noexcept = 0;

    /**
     * \brief Write a block of characters to the data sink.
     *
     * \param[in] begin The beginning of the block of characters to write to the data
     *            sink.
     * \param[in] end The end of the block of characters to write to the data sink.
     */
    virtual void put( char const * begin, char const * end ) noexcept;

    /**
     * \brief Write a null-terminated string to the data sink.
     *
     * \param[in] string The null-terminated string to write to the data sink.
     */
    virtual void put( char const * string ) noexcept;

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
    /**
     * \brief Write a null-terminated ROM string to the data sink.
     *
     * \param[in] string The null-terminated ROM string to write to the data sink.
     */
    virtual void put( ROM::String string ) noexcept;
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

    /**
     * \brief Write data to the data sink.
     *
     * \param[in] data The data to write to the data sink.
     */
    virtual void put( std::uint8_t data ) noexcept = 0;

    /**
     * \brief Write a block of data to the data sink.
     *
     * \param[in] begin The beginning of the block of data to write to the data sink.
     * \param[in] end The end of the block of data to write to the data sink.
     */
    virtual void put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept;

    /**
     * \brief Write any data that has been buffered to the data sink.
     */
    virtual void flush() noexcept = 0;

  protected:
    /**
     * \brief Constructor.
     */
    constexpr Stream_IO_Driver() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Stream_IO_Driver( Stream_IO_Driver && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Stream_IO_Driver( Stream_IO_Driver const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Stream_IO_Driver() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Stream_IO_Driver && expression ) noexcept -> Stream_IO_Driver & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator   =( Stream_IO_Driver const & expression ) noexcept
        -> Stream_IO_Driver & = default;
};

} // namespace microlibrary

#endif // MICROLIBRARY_STREAM_H
