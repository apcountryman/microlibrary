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
 * \brief microlibrary::Output_Stream automated tests.
 */

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/stream.h"
#include "microlibrary/testing/automated/stream.h"

namespace {

using ::microlibrary::Output_Formatter;
using ::microlibrary::Output_Stream;
using ::microlibrary::Testing::Automated::Mock_Output_Stream;
using ::microlibrary::Testing::Automated::Output_String_Stream;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::Ref;
using ::testing::Return;
using ::testing::SafeMatcherCast;

enum class Foo {};

class Mock_Output_Formatter {
  public:
    Mock_Output_Formatter() = default;

    Mock_Output_Formatter( Mock_Output_Formatter && ) = delete;

    Mock_Output_Formatter( Mock_Output_Formatter const & ) = delete;

    ~Mock_Output_Formatter() noexcept = default;

    auto operator=( Mock_Output_Formatter && ) = delete;

    auto operator=( Mock_Output_Formatter const & ) = delete;

    MOCK_METHOD( std::size_t, print, (Output_Stream &, Foo const &), ( const ) );
};

} // namespace

template<>
class microlibrary::Output_Formatter<::Foo> {
  public:
    Output_Formatter() = delete;

    Output_Formatter( ::Mock_Output_Formatter const & mock_output_formatter ) noexcept :
        m_mock_output_formatter{ &mock_output_formatter }
    {
    }

    Output_Formatter( Output_Formatter && source ) noexcept = default;

    Output_Formatter( Output_Formatter const & original ) noexcept = default;

    ~Output_Formatter() noexcept = default;

    auto operator=( Output_Formatter && expression ) noexcept -> Output_Formatter & = default;

    auto operator=( Output_Formatter const & expression ) noexcept -> Output_Formatter & = default;

    auto print( Output_Stream & stream, ::Foo const & foo ) const noexcept -> std::size_t
    {
        return m_mock_output_formatter->print( stream, foo );
    }

  private:
    ::Mock_Output_Formatter const * m_mock_output_formatter{};
};

/**
 * \brief Verify microlibrary::Output_Stream::put( char ) works properly.
 */
TEST( putChar, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const character = 'g';

    EXPECT_CALL( stream.driver(), put( SafeMatcherCast<char>( Eq( character ) ) ) );

    stream.put( character );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Stream::put( char const *, char const * ) works
 *        properly.
 */
TEST( putCharBlock, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const string = std::string_view{ "FDBVjQgD" };

    EXPECT_CALL( stream.driver(), put( std::string{ string } ) );

    stream.put( string.begin(), string.end() );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Stream::put( char const * ) works properly.
 */
TEST( putNullTerminatedString, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const string = "UStwlrJdq";

    EXPECT_CALL( stream.driver(), put( string ) );

    stream.put( string );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Stream::put( std::uint8_t ) works properly.
 */
TEST( putData, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const data = std::uint8_t{ 0xFB };

    EXPECT_CALL( stream.driver(), put( SafeMatcherCast<std::uint8_t>( Eq( data ) ) ) );

    stream.put( data );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Stream::put( std::uint8_t const *, std::uint8_t
 *        const * ) works properly.
 */
TEST( putDataBlock, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    auto const data = std::vector<std::uint8_t>{ 0x49, 0x70, 0xB9, 0x97, 0x02 };

    EXPECT_CALL( stream.driver(), put( data ) );

    stream.put( &*data.begin(), &*data.end() );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Stream::print() works properly when there is a
 *        single value to format.
 */
TEST( print, worksProperlySingleValue )
{
    auto stream = Mock_Output_Stream{};

    auto const foo           = Foo{ 243 };
    auto const foo_formatter = Mock_Output_Formatter{};
    auto const foo_size      = std::size_t{ 156 };

    EXPECT_CALL( foo_formatter, print( Ref( stream ), Ref( foo ) ) ).WillOnce( Return( foo_size ) );

    EXPECT_EQ( stream.print( foo, Output_Formatter<Foo>{ foo_formatter } ), foo_size );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Stream::print() works properly when there are
 *        multiple values to format.
 */
TEST( print, worksProperlyMultipleValues )
{
    auto const in_sequence = InSequence{};

    auto stream = Mock_Output_Stream{};

    auto const foo_a           = Foo{ 201 };
    auto const foo_a_formatter = Mock_Output_Formatter{};
    auto const foo_a_size      = std::size_t{ 47 };
    auto const foo_b           = Foo{ 141 };
    auto const foo_b_formatter = Mock_Output_Formatter{};
    auto const foo_b_size      = std::size_t{ 253 };

    EXPECT_CALL( foo_a_formatter, print( Ref( stream ), Ref( foo_a ) ) ).WillOnce( Return( foo_a_size ) );
    EXPECT_CALL( foo_b_formatter, print( Ref( stream ), Ref( foo_b ) ) ).WillOnce( Return( foo_b_size ) );

    EXPECT_EQ(
        stream.print(
            foo_a, Output_Formatter<Foo>{ foo_a_formatter }, foo_b, Output_Formatter<Foo>{ foo_b_formatter } ),
        foo_a_size + foo_b_size );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Stream::flush() works properly.
 */
TEST( flush, worksProperly )
{
    auto stream = Mock_Output_Stream{};

    EXPECT_CALL( stream.driver(), flush() );

    stream.flush();

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Formatter<char>::print( microlibrary::Output_Stream
 *        &, char ) works properly.
 */
TEST( outputFormatterCharPrintOutputStream, worksProperly )
{
    auto stream = Output_String_Stream{};

    auto const character = 'u';

    auto const n = stream.print( character );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), std::string{ character } );
}

/**
 * \brief Verify microlibrary::Output_Formatter<char const *>::print(
 *        microlibrary::Output_Stream &, char const * ) works properly.
 */
TEST( outputFormatterNullTerminatedStringPrintOutputStream, worksProperly )
{
    auto stream = Output_String_Stream{};

    auto const string = "Ku67TKN3M5ITORA";

    auto const n = stream.print( string );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), string );
}
