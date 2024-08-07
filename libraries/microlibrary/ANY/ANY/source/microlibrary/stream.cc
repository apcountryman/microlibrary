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

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "microlibrary/algorithm.h"
#include "microlibrary/error.h"
#include "microlibrary/precondition.h"
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

void Output_Stream::put( char character ) noexcept
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    driver()->put( character );
}

void Output_Stream::put( char const * begin, char const * end ) noexcept
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    driver()->put( begin, end );
}

void Output_Stream::put( char const * string ) noexcept
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    driver()->put( string );
}

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
void Output_Stream::put( ROM::String string ) noexcept
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    driver()->put( string );
}
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

void Output_Stream::put( std::uint8_t data ) noexcept
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    driver()->put( data );
}

void Output_Stream::put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    driver()->put( begin, end );
}

void Output_Stream::flush() noexcept
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    driver()->flush();
}

auto Fault_Reporting_Output_Stream::put( char character ) noexcept -> Result<void>
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    auto result = driver()->put( character );
    if ( result.is_error() ) {
        report_fatal_error();

        return result.error();
    } // if

    return {};
}

auto Fault_Reporting_Output_Stream::put( char const * begin, char const * end ) noexcept
    -> Result<void>
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    auto result = driver()->put( begin, end );
    if ( result.is_error() ) {
        report_fatal_error();

        return result.error();
    } // if

    return {};
}

auto Fault_Reporting_Output_Stream::put( char const * string ) noexcept -> Result<void>
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    auto result = driver()->put( string );
    if ( result.is_error() ) {
        report_fatal_error();

        return result.error();
    } // if

    return {};
}

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
auto Fault_Reporting_Output_Stream::put( ROM::String string ) noexcept -> Result<void>
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    auto result = driver()->put( string );
    if ( result.is_error() ) {
        report_fatal_error();

        return result.error();
    } // if

    return {};
}
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

auto Fault_Reporting_Output_Stream::put( std::uint8_t data ) noexcept -> Result<void>
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    auto result = driver()->put( data );
    if ( result.is_error() ) {
        report_fatal_error();

        return result.error();
    } // if

    return {};
}

auto Fault_Reporting_Output_Stream::put( std::uint8_t const * begin, std::uint8_t const * end ) noexcept
    -> Result<void>
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    auto result = driver()->put( begin, end );
    if ( result.is_error() ) {
        report_fatal_error();

        return result.error();
    } // if

    return {};
}

auto Fault_Reporting_Output_Stream::flush() noexcept -> Result<void>
{
    MICROLIBRARY_EXPECT( is_nominal(), Generic_Error::IO_STREAM_DEGRADED );

    auto result = driver()->flush();
    if ( result.is_error() ) {
        report_fatal_error();

        return result.error();
    } // if

    return {};
}

auto Output_Formatter<char>::print( Output_Stream & stream, char character ) const noexcept -> std::size_t
{
    stream.put( character );

    return 1;
}

auto Output_Formatter<char>::print( Fault_Reporting_Output_Stream & stream, char character ) const noexcept
    -> Result<std::size_t>
{
    auto result = stream.put( character );
    if ( result.is_error() ) {
        return result.error();
    } // if

    return std::size_t{ 1 };
}

auto Output_Formatter<char const *>::print( Output_Stream & stream, char const * string ) const noexcept
    -> std::size_t
{
    stream.put( string );

    return std::strlen( string );
}

auto Output_Formatter<char const *>::print( Fault_Reporting_Output_Stream & stream, char const * string ) const noexcept
    -> Result<std::size_t>
{
    auto result = stream.put( string );
    if ( result.is_error() ) {
        return result.error();
    } // if

    return std::strlen( string );
}

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
auto Output_Formatter<ROM::String>::print( Output_Stream & stream, ROM::String string ) const noexcept
    -> std::size_t
{
    stream.put( string );

    return ROM::length( string );
}
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
auto Output_Formatter<ROM::String>::print( Fault_Reporting_Output_Stream & stream, ROM::String string ) const noexcept
    -> Result<std::size_t>
{
    auto result = stream.put( string );
    if ( result.is_error() ) {
        return result.error();
    } // if

    return ROM::length( string );
}
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

auto Output_Formatter<Error_Code>::print( Output_Stream & stream, Error_Code const & error ) const noexcept
    -> std::size_t
{
    return stream.print(
        error.category().name(), MICROLIBRARY_ROM_STRING( "::" ), error.description() );
}

auto Output_Formatter<Error_Code>::print( Fault_Reporting_Output_Stream & stream, Error_Code const & error ) const noexcept
    -> Result<std::size_t>
{
    return stream.print(
        error.category().name(), MICROLIBRARY_ROM_STRING( "::" ), error.description() );
}

} // namespace microlibrary
