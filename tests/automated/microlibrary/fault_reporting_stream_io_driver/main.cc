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
 * \brief microlibrary::Fault_Reporting_Stream_IO_Driver automated tests.
 */

#include <cstdint>
#include <string_view>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/result.h"
#include "microlibrary/stream.h"
#include "microlibrary/testing/automated/error.h"
#include "microlibrary/testing/automated/stream.h"

namespace {

using ::microlibrary::Result;
using ::microlibrary::Testing::Automated::Mock_Error;
using ::microlibrary::Testing::Automated::Mock_Fault_Reporting_Stream_IO_Driver;
using ::testing::A;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::SafeMatcherCast;

} // namespace

/**
 * \brief Verify microlibrary::Fault_Reporting_Stream_IO_Driver::put( char const *, char
 *        const * ) properly handles a put error.
 */
TEST( putCharBlockErrorHandling, putError )
{
    auto driver = Mock_Fault_Reporting_Stream_IO_Driver{};

    auto const error = Mock_Error{ 254 };

    EXPECT_CALL( driver, put( A<char>() ) ).WillOnce( Return( error ) );

    auto const string = std::string_view{ "ocWsrYVYyIuSvW8" };

    auto const result = driver.Fault_Reporting_Stream_IO_Driver::put(
        string.begin(), string.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Stream_IO_Driver::put( char const *, char
 *        const * ) works properly.
 */
TEST( putCharBlock, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto driver = Mock_Fault_Reporting_Stream_IO_Driver{};

    auto const string = std::string_view{ "XnQmlICQXCrJ" };

    for ( auto const character : string ) {
        EXPECT_CALL( driver, put( SafeMatcherCast<char>( Eq( character ) ) ) )
            .WillOnce( Return( Result<void>{} ) );
    } // for

    EXPECT_FALSE(
        driver.Fault_Reporting_Stream_IO_Driver::put( string.begin(), string.end() ).is_error() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Stream_IO_Driver::put( char const * )
 *        properly handles a put error.
 */
TEST( putNullTerminatedStringErrorHandling, putError )
{
    auto driver = Mock_Fault_Reporting_Stream_IO_Driver{};

    auto const error = Mock_Error{ 96 };

    EXPECT_CALL( driver, put( A<char>() ) ).WillOnce( Return( error ) );

    auto const result = driver.Fault_Reporting_Stream_IO_Driver::put( "ifYRD2I" );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Stream_IO_Driver::put( char const * ) works
 *        properly.
 */
TEST( putNullTerminatedString, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto driver = Mock_Fault_Reporting_Stream_IO_Driver{};

    auto const string = std::string_view{ "0cCzet1DQC" };

    for ( auto const character : string ) {
        EXPECT_CALL( driver, put( SafeMatcherCast<char>( Eq( character ) ) ) )
            .WillOnce( Return( Result<void>{} ) );
    } // for

    EXPECT_FALSE( driver.Fault_Reporting_Stream_IO_Driver::put( string.data() ).is_error() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Stream_IO_Driver::put( std::uint8_t const
 *        *, std::uint8_t const * ) properly handles a put error.
 */
TEST( putDataBlockErrorHandling, putError )
{
    auto driver = Mock_Fault_Reporting_Stream_IO_Driver{};

    auto const error = Mock_Error{ 224 };

    EXPECT_CALL( driver, put( A<std::uint8_t>() ) ).WillOnce( Return( error ) );

    auto const values = std::vector<std::uint8_t>{ 0x8D, 0xBA, 0xF1, 0x37, 0x1F };

    auto const result = driver.Fault_Reporting_Stream_IO_Driver::put(
        &*values.begin(), &*values.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Stream_IO_Driver::put( std::uint8_t const
 *        *, std::uint8_t const * ) works properly.
 */
TEST( putDataBlock, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto driver = Mock_Fault_Reporting_Stream_IO_Driver{};

    auto const values = std::vector<std::uint8_t>{ 0x0E, 0x2D, 0xE6, 0xB0, 0x4D, 0x35 };

    for ( auto const value : values ) {
        EXPECT_CALL( driver, put( SafeMatcherCast<std::uint8_t>( Eq( value ) ) ) )
            .WillOnce( Return( Result<void>{} ) );
    } // for

    EXPECT_FALSE(
        driver.Fault_Reporting_Stream_IO_Driver::put( &*values.begin(), &*values.end() ).is_error() );
}
