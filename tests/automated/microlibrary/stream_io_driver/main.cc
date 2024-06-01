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
 * \brief microlibrary::Stream_IO_Driver automated tests.
 */

#include <cstdint>
#include <string_view>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/stream.h"
#include "microlibrary/testing/automated/stream.h"

namespace {

using ::microlibrary::Testing::Automated::Mock_Stream_IO_Driver;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::SafeMatcherCast;

} // namespace

/**
 * \brief Verify microlibrary::Stream_IO_Driver::put( char const *, char const * ) works
 *        properly.
 */
TEST( putCharBlock, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto driver = Mock_Stream_IO_Driver{};

    auto const string = std::string_view{ "XnQmlICQXCrJ" };

    for ( auto const character : string ) {
        EXPECT_CALL( driver, put( SafeMatcherCast<char>( Eq( character ) ) ) );
    } // for

    driver.Stream_IO_Driver::put( string.begin(), string.end() );
}

/**
 * \brief Verify microlibrary::Stream_IO_Driver::put( char const * ) works properly.
 */
TEST( putNullTerminatedString, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto driver = Mock_Stream_IO_Driver{};

    auto const string = std::string_view{ "0cCzet1DQC" };

    for ( auto const character : string ) {
        EXPECT_CALL( driver, put( SafeMatcherCast<char>( Eq( character ) ) ) );
    } // for

    driver.Stream_IO_Driver::put( string.data() );
}

/**
 * \brief Verify microlibrary::Stream_IO_Driver::put( std::uint8_t const *, std::uint8_t
 *        const * ) works properly.
 */
TEST( putDataBlock, worksProperly )
{
    auto const in_sequence = InSequence{};

    auto driver = Mock_Stream_IO_Driver{};

    auto const values = std::vector<std::uint8_t>{ 0x0E, 0x2D, 0xE6, 0xB0, 0x4D, 0x35 };

    for ( auto const value : values ) {
        EXPECT_CALL( driver, put( SafeMatcherCast<std::uint8_t>( Eq( value ) ) ) );
    } // for

    driver.Stream_IO_Driver::put( &*values.begin(), &*values.end() );
}
