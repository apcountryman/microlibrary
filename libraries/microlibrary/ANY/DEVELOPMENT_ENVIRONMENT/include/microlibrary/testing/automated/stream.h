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
 * \brief microlibrary automated testing I/O streams interface.
 */

#ifndef MICROLIBRARY_TESTING_AUTOMATED_STREAM_H
#define MICROLIBRARY_TESTING_AUTOMATED_STREAM_H

#include <cstdint>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "microlibrary/result.h"
#include "microlibrary/stream.h"

namespace microlibrary::Testing::Automated {

/**
 * \brief Mock stream I/O driver.
 */
class Mock_Stream_IO_Driver : public Stream_IO_Driver {
  public:
    Mock_Stream_IO_Driver() = default;

    Mock_Stream_IO_Driver( Mock_Stream_IO_Driver && ) = delete;

    Mock_Stream_IO_Driver( Mock_Stream_IO_Driver const & ) = delete;

    ~Mock_Stream_IO_Driver() noexcept = default;

    auto operator=( Mock_Stream_IO_Driver && ) = delete;

    auto operator=( Mock_Stream_IO_Driver const & ) = delete;

    MOCK_METHOD( void, put, (char), ( noexcept, override ) );
    MOCK_METHOD( void, put, ( std::string ) );

    void put( char const * begin, char const * end ) noexcept override
    {
        put( std::string{ begin, end } );
    }

    void put( char const * string ) noexcept override
    {
        put( std::string{ string } );
    }

    MOCK_METHOD( void, put, ( std::uint8_t ), ( noexcept, override ) );
    MOCK_METHOD( void, put, (std::vector<std::uint8_t>));

    void put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept override
    {
        put( std::vector<std::uint8_t>{ begin, end } );
    }

    MOCK_METHOD( void, flush, (), ( noexcept, override ) );
};

/**
 * \brief Mock stream I/O driver.
 */
class Mock_Fault_Reporting_Stream_IO_Driver : public Fault_Reporting_Stream_IO_Driver {
  public:
    Mock_Fault_Reporting_Stream_IO_Driver() = default;

    Mock_Fault_Reporting_Stream_IO_Driver( Mock_Fault_Reporting_Stream_IO_Driver && ) = delete;

    Mock_Fault_Reporting_Stream_IO_Driver( Mock_Fault_Reporting_Stream_IO_Driver const & ) = delete;

    ~Mock_Fault_Reporting_Stream_IO_Driver() noexcept = default;

    auto operator=( Mock_Fault_Reporting_Stream_IO_Driver && ) = delete;

    auto operator=( Mock_Fault_Reporting_Stream_IO_Driver const & ) = delete;

    MOCK_METHOD( Result<void>, put, (char), ( noexcept, override ) );
    MOCK_METHOD( Result<void>, put, ( std::string ) );

    auto put( char const * begin, char const * end ) noexcept -> Result<void> override
    {
        return put( std::string{ begin, end } );
    }

    auto put( char const * string ) noexcept -> Result<void> override
    {
        return put( std::string{ string } );
    }

    MOCK_METHOD( Result<void>, put, ( std::uint8_t ), ( noexcept, override ) );
    MOCK_METHOD( Result<void>, put, (std::vector<std::uint8_t>));

    auto put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept -> Result<void> override
    {
        return put( std::vector<std::uint8_t>{ begin, end } );
    }

    MOCK_METHOD( Result<void>, flush, (), ( noexcept, override ) );
};

/**
 * \brief String stream I/O driver.
 */
class String_Stream_IO_Driver final : public Stream_IO_Driver {
  public:
    /**
     * \brief Constructor.
     */
    String_Stream_IO_Driver() = default;

    String_Stream_IO_Driver( String_Stream_IO_Driver && ) = delete;

    String_Stream_IO_Driver( String_Stream_IO_Driver const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~String_Stream_IO_Driver() noexcept = default;

    auto operator=( String_Stream_IO_Driver && ) = delete;

    auto operator=( String_Stream_IO_Driver const & ) = delete;

    /**
     * \brief Get the string that is wrapped by the stream I/O driver.
     *
     * \return The string that is wrapped by the stream I/O driver.
     */
    auto string() const noexcept -> std::string const &
    {
        return m_string;
    }

    /**
     * \brief Write a character to the string.
     *
     * \param[in] character The character to write to the string.
     */
    void put( char character ) noexcept override final;

    /**
     * \brief Write data to the string.
     *
     * \param[in] data The data to write to the string.
     */
    void put( std::uint8_t data ) noexcept override final;

    /**
     * \brief Do nothing.
     */
    void flush() noexcept override final;

  private:
    /**
     * \brief The string wrapped by the stream I/O driver.
     */
    std::string m_string{};
};

} // namespace microlibrary::Testing::Automated

#endif // MICROLIBRARY_TESTING_AUTOMATED_STREAM_H
