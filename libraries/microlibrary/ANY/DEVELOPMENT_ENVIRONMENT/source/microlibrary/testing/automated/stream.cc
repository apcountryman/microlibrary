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
 * \brief microlibrary automated testing I/O streams implementation.
 */

#include "microlibrary/testing/automated/stream.h"

#include <cstdint>

namespace microlibrary::Testing::Automated {

void String_Stream_IO_Driver::put( char character ) noexcept
{
    m_string.push_back( character );
}

void String_Stream_IO_Driver::put( std::uint8_t data ) noexcept
{
    m_string.push_back( data );
}

void String_Stream_IO_Driver::flush() noexcept
{
}

} // namespace microlibrary::Testing::Automated
