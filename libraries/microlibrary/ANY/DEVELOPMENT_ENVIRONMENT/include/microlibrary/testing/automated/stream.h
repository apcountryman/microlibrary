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

} // namespace microlibrary::Testing::Automated

#endif // MICROLIBRARY_TESTING_AUTOMATED_STREAM_H
