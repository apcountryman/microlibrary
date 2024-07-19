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

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

#include "microlibrary/error.h"
#include "microlibrary/integer.h"
#include "microlibrary/precondition.h"
#include "microlibrary/result.h"
#include "microlibrary/rom.h"

namespace microlibrary {

class Output_Stream;

class Fault_Reporting_Output_Stream;

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

    /**
     * \brief Write a formatted value to a stream.
     *
     * \param[in] stream The stream to write the formatted value to.
     * \param[in] value The value to format.
     *
     * \return The number of characters written to the stream.
     */
    auto print( Output_Stream & stream, T const & value ) const noexcept -> std::size_t;

    /**
     * \brief Write a formatted value to a stream.
     *
     * \param[in] stream The stream to write the formatted value to.
     * \param[in] value The value to format.
     *
     * \return The number of characters written to the stream if the write succeeded.
     * \return An error code if the write failed.
     */
    auto print( Fault_Reporting_Output_Stream & stream, T const & value ) const noexcept
        -> Result<std::size_t>;
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

/**
 * \brief Fault reporting stream I/O driver.
 */
class Fault_Reporting_Stream_IO_Driver {
  public:
    /**
     * \brief Write a character to the data sink.
     *
     * \param[in] character The character to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    virtual auto put( char character ) noexcept -> Result<void> = 0;

    /**
     * \brief Write a block of characters to the data sink.
     *
     * \param[in] begin The beginning of the block of characters to write to the data
     *            sink.
     * \param[in] end The end of the block of characters to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    virtual auto put( char const * begin, char const * end ) noexcept -> Result<void>;

    /**
     * \brief Write a null-terminated string to the data sink.
     *
     * \param[in] string The null-terminated string to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    virtual auto put( char const * string ) noexcept -> Result<void>;

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
    /**
     * \brief Write a null-terminated ROM string to the data sink.
     *
     * \param[in] string The null-terminated ROM string to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    virtual auto put( ROM::String string ) noexcept -> Result<void>;
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

    /**
     * \brief Write data to the data sink.
     *
     * \param[in] data The data to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    virtual auto put( std::uint8_t data ) noexcept -> Result<void> = 0;

    /**
     * \brief Write a block of data to the data sink.
     *
     * \param[in] begin The beginning of the block of data to write to the data sink.
     * \param[in] end The end of the block of data to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    virtual auto put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept
        -> Result<void>;

    /**
     * \brief Write any data that has been buffered to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    virtual auto flush() noexcept -> Result<void> = 0;

  protected:
    /**
     * \brief Constructor.
     */
    constexpr Fault_Reporting_Stream_IO_Driver() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Fault_Reporting_Stream_IO_Driver( Fault_Reporting_Stream_IO_Driver && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Fault_Reporting_Stream_IO_Driver( Fault_Reporting_Stream_IO_Driver const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Fault_Reporting_Stream_IO_Driver() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Fault_Reporting_Stream_IO_Driver && expression ) noexcept
        -> Fault_Reporting_Stream_IO_Driver & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Fault_Reporting_Stream_IO_Driver const & expression ) noexcept
        -> Fault_Reporting_Stream_IO_Driver & = default;
};

/**
 * \brief Stream core.
 *
 * This class performs the following stream functions:
 * - Stores the stream's state information (end-of-file reached, I/O error reported)
 * - Associates the stream with a stream I/O driver
 */
class Stream {
  public:
    /**
     * \brief Check if the stream is nominal (no errors reported and end-of-file has not
     *        been reached.
     *
     * \return true if the stream is nominal.
     * \return false if the stream is not nominal.
     */
    constexpr auto is_nominal() const noexcept -> bool
    {
        return not m_state;
    }

    /**
     * \brief Check if errors (I/O error) have been reported.
     *
     * \return true if errors have been reported.
     * \return false if no errors have been reported.
     */
    constexpr auto error_reported() const noexcept -> bool
    {
        return m_state & Mask::ERROR_REPORTED;
    }

    /**
     * \brief Check if end-of-file has been reached.
     *
     * \return true if end-of-file has been reached.
     * \return false if end-of-file has not been reached.
     */
    constexpr auto end_of_file_reached() const noexcept -> bool
    {
        return m_state & Mask::END_OF_FILE_REACHED;
    }

    /**
     * \brief Check if an I/O error has been reported.
     *
     * \return true if an I/O error has been reported.
     * \return false if an I/O error has not been reported.
     */
    constexpr auto io_error_reported() const noexcept -> bool
    {
        return m_state & Mask::IO_ERROR_REPORTED;
    }

    /**
     * \brief Report an I/O error.
     */
    constexpr void report_io_error() noexcept
    {
        m_state |= Mask::IO_ERROR_REPORTED;
    }

    /**
     * \brief Clear I/O error report.
     */
    constexpr void clear_io_error_report() noexcept
    {
        m_state &= ~Mask::IO_ERROR_REPORTED;
    }

    /**
     * \brief Check if the stream is associated with a stream I/O driver.
     *
     * \return true if the stream is associated with a stream I/O driver.
     * \return false if the stream is not associated with a stream I/O driver.
     */
    constexpr auto driver_is_set() const noexcept -> bool
    {
        return m_driver;
    }

  protected:
    /**
     * \brief Constructor.
     */
    constexpr Stream() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Stream( Stream && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Stream( Stream const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Stream() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Stream && expression ) noexcept -> Stream & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Stream const & expression ) noexcept -> Stream & = default;

    /**
     * \brief Report that end-of-file has been reached.
     */
    constexpr void report_end_of_file_reached() noexcept
    {
        m_state |= Mask::END_OF_FILE_REACHED;
    }

    /**
     * \brief Clear end-of-file reached report.
     */
    constexpr void clear_end_of_file_reached_report() noexcept
    {
        m_state &= ~Mask::END_OF_FILE_REACHED;
    }

    /**
     * \brief Get the stream I/O driver associated with the stream.
     *
     * \return The stream I/O driver associated with the stream.
     */
    constexpr auto driver() noexcept -> Stream_IO_Driver *
    {
        return m_driver;
    }

    /**
     * \brief Associate the stream with a stream I/O driver.
     *
     * \param[in] driver The stream I/O driver to associate the stream with.
     */
    constexpr void set_driver( Stream_IO_Driver * driver ) noexcept
    {
        m_driver = driver;
    }

  private:
    /**
     * \brief State flags.
     */
    using State = std::uint_fast8_t;

    /**
     * \brief State flag bit positions.
     */
    enum Bit : std::uint_fast8_t {
        END_OF_FILE_REACHED, ///< End-of-file reached.
        IO_ERROR_REPORTED,   ///< I/O error reported.
    };

    /**
     * \brief State flag bit masks.
     */
    struct Mask {
        static constexpr auto END_OF_FILE_REACHED = mask<State>( 1, Bit::END_OF_FILE_REACHED ); ///< End-of-file reached.
        static constexpr auto IO_ERROR_REPORTED = mask<State>( 1, Bit::IO_ERROR_REPORTED ); ///< I/O error reported.

        static constexpr auto ERROR_REPORTED = IO_ERROR_REPORTED; ///< Error reported.
    };

    /**
     * \brief The stream's state flags.
     */
    State m_state{ 0 };

    /**
     * \brief The stream I/O driver associated with the stream.
     */
    Stream_IO_Driver * m_driver{ nullptr };
};

/**
 * \brief Fault reporting stream core.
 *
 * This class performs the following stream functions:
 * - Stores the stream's state information (end-of-file reached, I/O error reported, fatal
 *   error (fault) reported)
 * - Associates the stream with a stream I/O driver
 */
class Fault_Reporting_Stream {
  public:
    /**
     * \brief Check if the stream is nominal (no errors reported and end-of-file has not
     *        been reached.
     *
     * \return true if the stream is nominal.
     * \return false if the stream is not nominal.
     */
    constexpr auto is_nominal() const noexcept -> bool
    {
        return not m_state;
    }

    /**
     * \brief Check if errors (I/O error and/or fatal error (fault)) have been reported.
     *
     * \return true if errors have been reported.
     * \return false if no errors have been reported.
     */
    constexpr auto error_reported() const noexcept -> bool
    {
        return m_state & Mask::ERROR_REPORTED;
    }

    /**
     * \brief Check if end-of-file has been reached.
     *
     * \return true if end-of-file has been reached.
     * \return false if end-of-file has not been reached.
     */
    constexpr auto end_of_file_reached() const noexcept -> bool
    {
        return m_state & Mask::END_OF_FILE_REACHED;
    }

    /**
     * \brief Check if an I/O error has been reported.
     *
     * \return true if an I/O error has been reported.
     * \return false if an I/O error has not been reported.
     */
    constexpr auto io_error_reported() const noexcept -> bool
    {
        return m_state & Mask::IO_ERROR_REPORTED;
    }

    /**
     * \brief Report an I/O error.
     */
    constexpr void report_io_error() noexcept
    {
        m_state |= Mask::IO_ERROR_REPORTED;
    }

    /**
     * \brief Clear I/O error report.
     */
    constexpr void clear_io_error_report() noexcept
    {
        m_state &= ~Mask::IO_ERROR_REPORTED;
    }

    /**
     * \brief Check if a fatal error (fault) has been reported.
     *
     * \return true if a fatal error (fault) has been reported.
     * \return false if a fatal error (fault) has not been reported.
     */
    constexpr auto fatal_error_reported() const noexcept -> bool
    {
        return m_state & Mask::FATAL_ERROR_REPORTED;
    }

    /**
     * \brief Check if the stream is associated with a stream I/O driver.
     *
     * \return true if the stream is associated with a stream I/O driver.
     * \return false if the stream is not associated with a stream I/O driver.
     */
    constexpr auto driver_is_set() const noexcept -> bool
    {
        return m_driver;
    }

  protected:
    /**
     * \brief Constructor.
     */
    constexpr Fault_Reporting_Stream() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Fault_Reporting_Stream( Fault_Reporting_Stream && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Fault_Reporting_Stream( Fault_Reporting_Stream const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Fault_Reporting_Stream() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator         =( Fault_Reporting_Stream && expression ) noexcept
        -> Fault_Reporting_Stream & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Fault_Reporting_Stream const & expression ) noexcept
        -> Fault_Reporting_Stream & = default;

    /**
     * \brief Report that end-of-file has been reached.
     */
    constexpr void report_end_of_file_reached() noexcept
    {
        m_state |= Mask::END_OF_FILE_REACHED;
    }

    /**
     * \brief Clear end-of-file reached report.
     */
    constexpr void clear_end_of_file_reached_report() noexcept
    {
        m_state &= ~Mask::END_OF_FILE_REACHED;
    }

    /**
     * \brief Report a fatal error (fault).
     */
    constexpr void report_fatal_error() noexcept
    {
        m_state |= Mask::FATAL_ERROR_REPORTED;
    }

    /**
     * \brief Clear fatal error (fault) report.
     */
    constexpr void clear_fatal_error_report() noexcept
    {
        m_state &= ~Mask::FATAL_ERROR_REPORTED;
    }

    /**
     * \brief Get the stream I/O driver associated with the stream.
     *
     * \return The stream I/O driver associated with the stream.
     */
    constexpr auto driver() noexcept -> Fault_Reporting_Stream_IO_Driver *
    {
        return m_driver;
    }

    /**
     * \brief Associate the stream with a stream I/O driver.
     *
     * \param[in] driver The stream I/O driver to associate the stream with.
     */
    constexpr void set_driver( Fault_Reporting_Stream_IO_Driver * driver ) noexcept
    {
        m_driver = driver;
    }

  private:
    /**
     * \brief State flags.
     */
    using State = std::uint_fast8_t;

    /**
     * \brief State flag bit positions.
     */
    enum Bit : std::uint_fast8_t {
        END_OF_FILE_REACHED,  ///< End-of-file reached.
        IO_ERROR_REPORTED,    ///< I/O error reported.
        FATAL_ERROR_REPORTED, ///< Fatal error (fault) reported.
    };

    /**
     * \brief State flag bit masks.
     */
    struct Mask {
        static constexpr auto END_OF_FILE_REACHED = mask<State>( 1, Bit::END_OF_FILE_REACHED ); ///< End-of-file reached.
        static constexpr auto IO_ERROR_REPORTED = mask<State>( 1, Bit::IO_ERROR_REPORTED ); ///< I/O error reported.
        static constexpr auto FATAL_ERROR_REPORTED = mask<State>( 1, Bit::FATAL_ERROR_REPORTED ); ///< fatal error (fault) reported.

        static constexpr auto ERROR_REPORTED = IO_ERROR_REPORTED | FATAL_ERROR_REPORTED; ///< Error reported.
    };

    /**
     * \brief The stream's state flags.
     */
    State m_state{ 0 };

    /**
     * \brief The stream I/O driver associated with the stream.
     */
    Fault_Reporting_Stream_IO_Driver * m_driver{ nullptr };
};

/**
 * \brief Output stream.
 */
class Output_Stream : public Stream {
  public:
    /**
     * \brief Write a character to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] character The character to write to the data sink.
     */
    void put( char character ) noexcept;

    /**
     * \brief Write a block of characters to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] begin The beginning of the block of characters to write to the data
     *            sink.
     * \param[in] end The end of the block of characters to write to the data sink.
     */
    void put( char const * begin, char const * end ) noexcept;

    /**
     * \brief Write a null-terminated string to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] string The null-terminated string to write to the data sink.
     */
    void put( char const * string ) noexcept;

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
    /**
     * \brief Write a null-terminated ROM string to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] string The null-terminated ROM string to write to the data sink.
     */
    void put( ROM::String string ) noexcept;
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

    /**
     * \brief Write data to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] data The data to write to the data sink.
     */
    void put( std::uint8_t data ) noexcept;

    /**
     * \brief Write a block of data to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] begin The beginning of the block of data to write to the data sink.
     * \param[in] end The end of the block of data to write to the data sink.
     */
    void put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept;

    /**
     * \brief Write formatted values to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \tparam Types The types to print.
     *
     * \param[in] values The values to format. If a value is followed by an output
     *            formatter, the output formatter will be used to format the value and
     *            write the formatted value to the data sink. If a value is not followed
     *            by an output formatter, a default constructed output formatter will be
     *            used to format the value and write the formatted value to the data sink.
     *
     * \return The number of characters written to the data sink.
     */
    template<typename... Types>
    auto print( Types &&... values ) noexcept -> std::size_t
    {
        MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

        return print_implementation( std::size_t{ 0 }, std::forward<Types>( values )... );
    }

    /**
     * \brief Write any data that has been buffered to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     */
    void flush() noexcept;

  protected:
    /**
     * \brief Constructor.
     */
    constexpr Output_Stream() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Output_Stream( Output_Stream && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Output_Stream( Output_Stream const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Output_Stream() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Output_Stream && expression ) noexcept -> Output_Stream & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Output_Stream const & expression ) noexcept -> Output_Stream & = default;

  private:
    /**
     * \brief Write formatted values to the data sink.
     *
     * \param[in] n The number of characters that have been written to the data sink.
     *
     * \return The number of characters written to the data sink.
     */
    auto print_implementation( std::size_t n ) noexcept -> std::size_t
    {
        return n;
    }

    /**
     * \brief Write formatted values to the data sink.
     *
     * \tparam Type The type to print.
     * \tparam Types The types to print.
     *
     * \param[in] n The number of characters that have been written to the data sink.
     * \param[in] value The value to format.
     * \param[in] formatter The output formatter to use to format the value and write the
     *            formatted value to the data sink.
     * \param[in] values The values to format.
     *
     * \return The number of characters written to the data sink.
     */
    template<typename Type, typename... Types>
    auto print_implementation( std::size_t n, Type && value, Output_Formatter<std::decay_t<Type>> formatter, Types &&... values ) noexcept
        -> std::size_t
    {
        return print_implementation(
            n + formatter.print( *this, value ), std::forward<Types>( values )... );
    }

    /**
     * \brief Write formatted values to the data sink.
     *
     * \tparam Type The type to print.
     * \tparam Types The types to print.
     *
     * \param[in] n The number of characters that have been written to the data sink.
     * \param[in] value The value to format.
     * \param[in] values The values to format.
     *
     * \return The number of characters written to the data sink.
     */
    template<typename Type, typename... Types>
    auto print_implementation( std::size_t n, Type && value, Types &&... values ) noexcept
        -> std::size_t
    {
        return print_implementation(
            n,
            std::forward<Type>( value ),
            Output_Formatter<std::decay_t<Type>>{},
            std::forward<Types>( values )... );
    }
};

/**
 * \brief Fault reporting output stream.
 */
class Fault_Reporting_Output_Stream : public Fault_Reporting_Stream {
  public:
    /**
     * \brief Write a character to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] character The character to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    auto put( char character ) noexcept -> Result<void>;

    /**
     * \brief Write a block of characters to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] begin The beginning of the block of characters to write to the data
     *            sink.
     * \param[in] end The end of the block of characters to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    auto put( char const * begin, char const * end ) noexcept -> Result<void>;

    /**
     * \brief Write a null-terminated string to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] string The null-terminated string to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    auto put( char const * string ) noexcept -> Result<void>;

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
    /**
     * \brief Write a null-terminated ROM string to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] string The null-terminated ROM string to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    auto put( ROM::String string ) noexcept -> Result<void>;
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

    /**
     * \brief Write data to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] data The data to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    auto put( std::uint8_t data ) noexcept -> Result<void>;

    /**
     * \brief Write a block of data to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \param[in] begin The beginning of the block of data to write to the data sink.
     * \param[in] end The end of the block of data to write to the data sink.
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    auto put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept -> Result<void>;

    /**
     * \brief Write formatted values to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \tparam Types The types to print.
     *
     * \param[in] values The values to format. If a value is followed by an output
     *            formatter, the output formatter will be used to format the value and
     *            write the formatted value to the data sink. If a value is not followed
     *            by an output formatter, a default constructed output formatter will be
     *            used to format the value and write the formatted value to the data sink.
     *
     * \return The number of characters written to the data sink if the write succeeded.
     * \return An error code if the write failed.
     */
    template<typename... Types>
    auto print( Types &&... values ) noexcept -> Result<std::size_t>
    {
        MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

        return print_implementation( std::size_t{ 0 }, std::forward<Types>( values )... );
    }

    /**
     * \brief Write any data that has been buffered to the data sink.
     *
     * \pre microlibrary::Stream::is_nominal()
     *
     * \return Nothing if the write succeeded.
     * \return An error code if the write failed.
     */
    auto flush() noexcept -> Result<void>;

  protected:
    /**
     * \brief Constructor.
     */
    constexpr Fault_Reporting_Output_Stream() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Fault_Reporting_Output_Stream( Fault_Reporting_Output_Stream && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Fault_Reporting_Output_Stream( Fault_Reporting_Output_Stream const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Fault_Reporting_Output_Stream() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Fault_Reporting_Output_Stream && expression ) noexcept
        -> Fault_Reporting_Output_Stream & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Fault_Reporting_Output_Stream const & expression ) noexcept
        -> Fault_Reporting_Output_Stream & = default;

  private:
    /**
     * \brief Write formatted values to the data sink.
     *
     * \param[in] n The number of characters that have been written to the data sink.
     *
     * \return The number of characters written to the data sink.
     */
    auto print_implementation( std::size_t n ) noexcept -> Result<std::size_t>
    {
        return n;
    }

    /**
     * \brief Write formatted values to the data sink.
     *
     * \tparam Type The type to print.
     * \tparam Types The types to print.
     *
     * \param[in] n The number of characters that have been written to the data sink.
     * \param[in] value The value to format.
     * \param[in] formatter The output formatter to use to format the value and write the
     *            formatted value to the data sink.
     * \param[in] values The values to format.
     *
     * \return The number of characters written to the data sink if the write succeeded.
     * \return An error code if the write failed.
     */
    template<typename Type, typename... Types>
    auto print_implementation( std::size_t n, Type && value, Output_Formatter<std::decay_t<Type>> formatter, Types &&... values ) noexcept
        -> Result<std::size_t>
    {
        auto result = formatter.print( *this, value );
        if ( result.is_error() ) {
            return result.error();
        } // if

        return print_implementation( n + result.value(), std::forward<Types>( values )... );
    }

    /**
     * \brief Write formatted values to the data sink.
     *
     * \tparam Type The type to print.
     * \tparam Types The types to print.
     *
     * \param[in] n The number of characters that have been written to the data sink.
     * \param[in] value The value to format.
     * \param[in] values The values to format.
     *
     * \return The number of characters written to the data sink if the write succeeded.
     * \return An error code if the write failed.
     */
    template<typename Type, typename... Types>
    auto print_implementation( std::size_t n, Type && value, Types &&... values ) noexcept
        -> Result<std::size_t>
    {
        return print_implementation(
            n,
            std::forward<Type>( value ),
            Output_Formatter<std::decay_t<Type>>{},
            std::forward<Types>( values )... );
    }
};

/**
 * \brief Character output formatter.
 */
template<>
class Output_Formatter<char> {
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
     * \brief Write a formatted character to a stream.
     *
     * \param[in] stream The stream to write the formatted character to.
     * \param[in] character The character to format.
     *
     * \return The number of characters written to the stream.
     */
    auto print( Output_Stream & stream, char character ) const noexcept -> std::size_t;

    /**
     * \brief Write a formatted character to a stream.
     *
     * \param[in] stream The stream to write the formatted character to.
     * \param[in] character The character to format.
     *
     * \return The number of characters written to the stream if the write succeeded.
     * \return An error code if the write failed.
     */
    auto print( Fault_Reporting_Output_Stream & stream, char character ) const noexcept
        -> Result<std::size_t>;
};

/**
 * \brief Null-terminated string output formatter.
 */
template<>
class Output_Formatter<char const *> {
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
     * \brief Write a formatted null-terminated string to a stream.
     *
     * \param[in] stream The stream to write the formatted null-terminated string to.
     * \param[in] string The null-terminated string to format.
     *
     * \return The number of characters written to the stream.
     */
    auto print( Output_Stream & stream, char const * string ) const noexcept -> std::size_t;

    /**
     * \brief Write a formatted null-terminated string to a stream.
     *
     * \param[in] stream The stream to write the formatted null-terminated string to.
     * \param[in] string The null-terminated string to format.
     *
     * \return The number of characters written to the stream if the write succeeded.
     * \return An error code if the write failed.
     */
    auto print( Fault_Reporting_Output_Stream & stream, char const * string ) const noexcept
        -> Result<std::size_t>;
};

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
/**
 * \brief Null-terminated ROM string output formatter.
 */
template<>
class Output_Formatter<ROM::String> {
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
     * \brief Write a formatted null-terminated ROM string to a stream.
     *
     * \param[in] stream The stream to write the formatted null-terminated ROM string to.
     * \param[in] string The null-terminated ROM string to format.
     *
     * \return The number of characters written to the stream.
     */
    auto print( Output_Stream & stream, ROM::String string ) const noexcept -> std::size_t;

    /**
     * \brief Write a formatted null-terminated ROM string to a stream.
     *
     * \param[in] stream The stream to write the formatted null-terminated ROM string to.
     * \param[in] string The null-terminated ROM string to format.
     *
     * \return The number of characters written to the stream if the write succeeded.
     * \return An error code if the write failed.
     */
    auto print( Fault_Reporting_Output_Stream & stream, ROM::String string ) const noexcept
        -> Result<std::size_t>;
};
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

} // namespace microlibrary

#endif // MICROLIBRARY_STREAM_H
