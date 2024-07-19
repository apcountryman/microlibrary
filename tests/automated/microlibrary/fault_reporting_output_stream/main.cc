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
 * \brief microlibrary::Fault_Reporting_Output_Stream automated tests.
 */

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/result.h"
#include "microlibrary/stream.h"
#include "microlibrary/testing/automated/error.h"
#include "microlibrary/testing/automated/stream.h"

namespace {

using ::microlibrary::Fault_Reporting_Output_Stream;
using ::microlibrary::Output_Formatter;
using ::microlibrary::Result;
using ::microlibrary::Testing::Automated::Fault_Reporting_Output_String_Stream;
using ::microlibrary::Testing::Automated::Mock_Error;
using ::microlibrary::Testing::Automated::Mock_Fault_Reporting_Output_Stream;
using ::testing::_;
using ::testing::A;
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

    MOCK_METHOD( (Result<std::size_t>), print, (Fault_Reporting_Output_Stream &, Foo const &), ( const ) );
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

    auto print( Fault_Reporting_Output_Stream & stream, ::Foo const & foo ) const noexcept
        -> Result<std::size_t>
    {
        return m_mock_output_formatter->print( stream, foo );
    }

  private:
    ::Mock_Output_Formatter const * m_mock_output_formatter{};
};

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( char ) properly handles
 *        a put error.
 */
TEST( putCharErrorHandling, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 63 };

    EXPECT_CALL( stream.driver(), put( A<char>() ) ).WillOnce( Return( error ) );

    auto const result = stream.put( 'W' );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( char ) works properly.
 */
TEST( putChar, worksProperly )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const character = 'g';

    EXPECT_CALL( stream.driver(), put( SafeMatcherCast<char>( Eq( character ) ) ) )
        .WillOnce( Return( Result<void>{} ) );

    EXPECT_FALSE( stream.put( character ).is_error() );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( char const *, char
 *        const * ) properly handles a put error.
 */
TEST( putCharBlockErrorHandling, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 83 };

    EXPECT_CALL( stream.driver(), put( A<std::string>() ) ).WillOnce( Return( error ) );

    auto const string = std::string_view{ "QoHCz0" };

    auto const result = stream.put( string.begin(), string.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( char const *, char
 *        const * ) works properly.
 */
TEST( putCharBlock, worksProperly )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const string = std::string_view{ "FDBVjQgD" };

    EXPECT_CALL( stream.driver(), put( std::string{ string } ) ).WillOnce( Return( Result<void>{} ) );

    EXPECT_FALSE( stream.put( string.begin(), string.end() ).is_error() );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( char const * ) properly
 *        handles a put error.
 */
TEST( putNullTerminatedString, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 169 };

    EXPECT_CALL( stream.driver(), put( A<std::string>() ) ).WillOnce( Return( error ) );

    auto const result = stream.put( "du1JWCGcsfXR3" );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( char const * ) works
 *        properly.
 */
TEST( putNullTerminatedstring, worksProperly )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const string = "UStwlrJdq";

    EXPECT_CALL( stream.driver(), put( string ) ).WillOnce( Return( Result<void>{} ) );

    EXPECT_FALSE( stream.put( string ).is_error() );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( std::uint8_t ) properly
 *        handles a put error.
 */
TEST( putDataErrorHandling, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 9 };

    EXPECT_CALL( stream.driver(), put( A<std::uint8_t>() ) ).WillOnce( Return( error ) );

    auto const result = stream.put( std::uint8_t{ 0xB6 } );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( std::uint8_t ) works
 *        properly.
 */
TEST( putData, worksProperly )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const data = std::uint8_t{ 0xFB };

    EXPECT_CALL( stream.driver(), put( SafeMatcherCast<std::uint8_t>( Eq( data ) ) ) )
        .WillOnce( Return( Result<void>{} ) );

    EXPECT_FALSE( stream.put( data ).is_error() );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( std::uint8_t const *,
 *        std::uint8_t const * ) properly handles a put error.
 */
TEST( putDataBlockErrorHandling, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 101 };

    EXPECT_CALL( stream.driver(), put( A<std::vector<std::uint8_t>>() ) ).WillOnce( Return( error ) );

    auto const data = std::vector<std::uint8_t>{ 0x04, 0x35, 0x13, 0x53 };

    auto const result = stream.put( &*data.begin(), &*data.end() );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::put( std::uint8_t const *,
 *        std::uint8_t const * ) works properly.
 */
TEST( putDataBlock, worksProperly )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const data = std::vector<std::uint8_t>{ 0x49, 0x70, 0xB9, 0x97, 0x02 };

    EXPECT_CALL( stream.driver(), put( data ) ).WillOnce( Return( Result<void>{} ) );

    EXPECT_FALSE( stream.put( &*data.begin(), &*data.end() ).is_error() );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::print() properly handles a
 *        microlibrary::Output_Formatter::print() error.
 */
TEST( printErrorHandling, outputFormatterPrintError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const formatter_a = Mock_Output_Formatter{};
    auto const formatter_b = Mock_Output_Formatter{};

    auto const error = Mock_Error{ 242 };

    EXPECT_CALL( formatter_a, print( _, _ ) ).WillOnce( Return( error ) );
    EXPECT_CALL( formatter_b, print( _, _ ) ).Times( 0 );

    auto const result = stream.print(
        Foo{ 89 }, Output_Formatter<Foo>{ formatter_a }, Foo{ 219 }, Output_Formatter<Foo>{ formatter_b } );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::print() works properly when
 *        there is a single value to format.
 */
TEST( print, worksProperlySingleValue )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const foo           = Foo{ 243 };
    auto const foo_formatter = Mock_Output_Formatter{};
    auto const foo_size      = std::size_t{ 156 };

    EXPECT_CALL( foo_formatter, print( Ref( stream ), Ref( foo ) ) ).WillOnce( Return( foo_size ) );

    auto const result = stream.print( foo, Output_Formatter<Foo>{ foo_formatter } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), foo_size );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::print() works properly when
 *        there are multiple values to format.
 */
TEST( print, worksProperlyMultipleValues )
{
    auto const in_sequence = InSequence{};

    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const foo_a           = Foo{ 201 };
    auto const foo_a_formatter = Mock_Output_Formatter{};
    auto const foo_a_size      = std::size_t{ 47 };
    auto const foo_b           = Foo{ 141 };
    auto const foo_b_formatter = Mock_Output_Formatter{};
    auto const foo_b_size      = std::size_t{ 253 };

    EXPECT_CALL( foo_a_formatter, print( Ref( stream ), Ref( foo_a ) ) ).WillOnce( Return( foo_a_size ) );
    EXPECT_CALL( foo_b_formatter, print( Ref( stream ), Ref( foo_b ) ) ).WillOnce( Return( foo_b_size ) );

    auto const result = stream.print(
        foo_a, Output_Formatter<Foo>{ foo_a_formatter }, foo_b, Output_Formatter<Foo>{ foo_b_formatter } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), foo_a_size + foo_b_size );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::flush() properly handles a
 *        flush error.
 */
TEST( flushErrorHandling, flushError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 33 };

    EXPECT_CALL( stream.driver(), flush() ).WillOnce( Return( error ) );

    auto const result = stream.flush();

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief Verify microlibrary::Fault_Reporting_Output_Stream::flush() works properly.
 */
TEST( flush, worksProperly )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    EXPECT_CALL( stream.driver(), flush() ).WillOnce( Return( Result<void>{} ) );

    EXPECT_FALSE( stream.flush().is_error() );

    EXPECT_TRUE( stream.is_nominal() );
}

/**
 * \brief Verify microlibrary::Output_Formatter<char>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, char ) properly handles a put
 *        error.
 */
TEST( outputFormatterCharPrintFaultReportingOutputStreamErrorHandling, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 181 };

    EXPECT_CALL( stream.driver(), put( A<char>() ) ).WillOnce( Return( error ) );

    auto const result = stream.print( 'g' );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief Verify microlibrary::Output_Formatter<char>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, char ) works properly.
 */
TEST( outputFormatterCharPrintFaultReportingOutputStream, worksProperly )
{
    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const character = 'u';

    auto const result = stream.print( character );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), std::string{ character } );
}
