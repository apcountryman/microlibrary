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
 * \brief microlibrary I/O streams implementation.
 */

#include "microlibrary/stream.h"

#include <cstdint>

#include "microlibrary/algorithm.h"
#include "microlibrary/result.h"
#include "microlibrary/rom.h"

namespace microlibrary {

void Stream_IO_Driver::put( char const * begin, char const * end ) noexcept
{
    ::microlibrary::for_each(
        begin, end, [ this ]( auto character ) noexcept { put( character ); } );
}

void Stream_IO_Driver::put( char const * string ) noexcept
{
    while ( auto const character = *string++ ) { put( character ); } // while
}

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
void Stream_IO_Driver::put( ROM::String string ) noexcept
{
    while ( auto const character = *string++ ) { put( character ); } // while
}
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

void Stream_IO_Driver::put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept
{
    ::microlibrary::for_each( begin, end, [ this ]( auto data ) noexcept { put( data ); } );
}

auto Fault_Reporting_Stream_IO_Driver::put( char const * begin, char const * end ) noexcept
    -> Result<void>
{
    return ::microlibrary::for_each<Functor_Reports_Errors_Discard_Functor>(
        begin, end, [ this ]( auto character ) noexcept { return put( character ); } );
}

auto Fault_Reporting_Stream_IO_Driver::put( char const * string ) noexcept -> Result<void>
{
    while ( auto const character = *string++ ) {
        auto result = put( character );
        if ( result.is_error() ) {
            return result.error();
        } // if
    }     // while

    return {};
}

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
auto Fault_Reporting_Stream_IO_Driver::put( ROM::String string ) noexcept -> Result<void>
{
    while ( auto const character = *string++ ) {
        auto result = put( character );
        if ( result.is_error() ) {
            return result.error();
        } // if
    }     // while

    return {};
}
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

auto Fault_Reporting_Stream_IO_Driver::put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept
    -> Result<void>
{
    return ::microlibrary::for_each<Functor_Reports_Errors_Discard_Functor>(
        begin, end, [ this ]( auto data ) noexcept { return put( data ); } );
}

} // namespace microlibrary
