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
 * \brief microlibrary::Format::Bin automated tests.
 */

#include <cstdint>
#include <ostream>
#include <string>
#include <string_view>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/format.h"
#include "microlibrary/testing/automated/error.h"
#include "microlibrary/testing/automated/stream.h"

namespace {

using ::microlibrary::Format::Bin;
using ::microlibrary::Testing::Automated::Fault_Reporting_Output_String_Stream;
using ::microlibrary::Testing::Automated::Mock_Error;
using ::microlibrary::Testing::Automated::Mock_Fault_Reporting_Output_Stream;
using ::microlibrary::Testing::Automated::Output_String_Stream;
using ::testing::A;
using ::testing::Return;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

} // namespace

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) properly handles a put
 *        error.
 */
TEST( outputFormatterFormatBinPrintFaultReportingOutputStreamErrorHandling, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 216 };

    EXPECT_CALL( stream.driver(), put( A<std::string>() ) ).WillOnce( Return( error ) );

    auto const result = stream.print( Bin{ 0b11000010010001110100010101101011 } );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print() test
 *        case.
 *
 * \tparam Integer The type of integer to format.
 */
template<typename Integer>
struct outputFormatterFormatBinPrint_Test_Case {
    /**
     * \brief The integer to be formatted.
     */
    Integer integer;

    /**
     * \brief The formatted integer.
     */
    std::string_view bin;
};

template<typename Integer>
auto operator<<( std::ostream & stream, outputFormatterFormatBinPrint_Test_Case<Integer> const & test_case )
    -> std::ostream &
{
    return stream << test_case.bin;
}

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print()
 *        std::int8_t test cases.
 */
outputFormatterFormatBinPrint_Test_Case<std::int8_t> const outputFormatterFormatBinPrintI8_TEST_CASES[]{
    // clang-format off

    { static_cast<std::int8_t>( 0b00000000 ), "0b00000000" },
    { static_cast<std::int8_t>( 0b11111111 ), "0b11111111" },

    { static_cast<std::int8_t>( 0b10101110 ), "0b10101110" },
    { static_cast<std::int8_t>( 0b01001100 ), "0b01001100" },
    { static_cast<std::int8_t>( 0b00100010 ), "0b00100010" },
    { static_cast<std::int8_t>( 0b01100001 ), "0b01100001" },
    { static_cast<std::int8_t>( 0b00110011 ), "0b00110011" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::int8_t test fixture.
 */
class outputFormatterFormatBinPrintOutputStreamI8 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::int8_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintOutputStreamI8, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Bin{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintOutputStreamI8, ValuesIn( outputFormatterFormatBinPrintI8_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::int8_t test
 *        fixture.
 */
class outputFormatterFormatBinPrintFaultReportingOutputStreamI8 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::int8_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintFaultReportingOutputStreamI8, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Bin{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintFaultReportingOutputStreamI8, ValuesIn( outputFormatterFormatBinPrintI8_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print()
 *        std::uint8_t test cases.
 */
outputFormatterFormatBinPrint_Test_Case<std::uint8_t> const outputFormatterFormatBinPrintU8_TEST_CASES[]{
    // clang-format off

    { 0b00000000, "0b00000000" },
    { 0b11111111, "0b11111111" },

    { 0b10101110, "0b10101110" },
    { 0b01001100, "0b01001100" },
    { 0b00100010, "0b00100010" },
    { 0b01100001, "0b01100001" },
    { 0b00110011, "0b00110011" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::uint8_t test fixture.
 */
class outputFormatterFormatBinPrintOutputStreamU8 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::uint8_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintOutputStreamU8, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Bin{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintOutputStreamU8, ValuesIn( outputFormatterFormatBinPrintU8_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::uint8_t test
 *        fixture.
 */
class outputFormatterFormatBinPrintFaultReportingOutputStreamU8 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::uint8_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintFaultReportingOutputStreamU8, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Bin{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintFaultReportingOutputStreamU8, ValuesIn( outputFormatterFormatBinPrintU8_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print()
 *        std::int16_t test cases.
 */
outputFormatterFormatBinPrint_Test_Case<std::int16_t> const outputFormatterFormatBinPrintI16_TEST_CASES[]{
    // clang-format off

    { static_cast<std::int16_t>( 0b0000000000000000 ), "0b0000000000000000" },
    { static_cast<std::int16_t>( 0b1111111111111111 ), "0b1111111111111111" },

    { static_cast<std::int16_t>( 0b1100101000000110 ), "0b1100101000000110" },
    { static_cast<std::int16_t>( 0b0110000000011111 ), "0b0110000000011111" },
    { static_cast<std::int16_t>( 0b0011100110110100 ), "0b0011100110110100" },
    { static_cast<std::int16_t>( 0b0010000110100010 ), "0b0010000110100010" },
    { static_cast<std::int16_t>( 0b1100111110100011 ), "0b1100111110100011" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::int16_t test fixture.
 */
class outputFormatterFormatBinPrintOutputStreamI16 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::int16_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintOutputStreamI16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Bin{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintOutputStreamI16, ValuesIn( outputFormatterFormatBinPrintI16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::int16_t test
 *        fixture.
 */
class outputFormatterFormatBinPrintFaultReportingOutputStreamI16 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::int16_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintFaultReportingOutputStreamI16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Bin{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintFaultReportingOutputStreamI16, ValuesIn( outputFormatterFormatBinPrintI16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print()
 *        std::uint16_t test cases.
 */
outputFormatterFormatBinPrint_Test_Case<std::uint16_t> const outputFormatterFormatBinPrintU16_TEST_CASES[]{
    // clang-format off

    { 0b0000000000000000, "0b0000000000000000" },
    { 0b1111111111111111, "0b1111111111111111" },

    { 0b1100101000000110, "0b1100101000000110" },
    { 0b0110000000011111, "0b0110000000011111" },
    { 0b0011100110110100, "0b0011100110110100" },
    { 0b0010000110100010, "0b0010000110100010" },
    { 0b1100111110100011, "0b1100111110100011" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::uint16_t test fixture.
 */
class outputFormatterFormatBinPrintOutputStreamU16 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::uint16_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintOutputStreamU16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Bin{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintOutputStreamU16, ValuesIn( outputFormatterFormatBinPrintU16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::uint16_t test
 *        fixture.
 */
class outputFormatterFormatBinPrintFaultReportingOutputStreamU16 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::uint16_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintFaultReportingOutputStreamU16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Bin{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintFaultReportingOutputStreamU16, ValuesIn( outputFormatterFormatBinPrintU16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print()
 *        std::int32_t test cases.
 */
outputFormatterFormatBinPrint_Test_Case<std::int32_t> const outputFormatterFormatBinPrintI32_TEST_CASES[]{
    // clang-format off

    { static_cast<std::int32_t>( 0b00000000000000000000000000000000 ), "0b00000000000000000000000000000000" },
    { static_cast<std::int32_t>( 0b11111111111111111111111111111111 ), "0b11111111111111111111111111111111" },

    { static_cast<std::int32_t>( 0b01111000000011100010000000011110 ), "0b01111000000011100010000000011110" },
    { static_cast<std::int32_t>( 0b00101110111011110111101100000000 ), "0b00101110111011110111101100000000" },
    { static_cast<std::int32_t>( 0b10101011001010001111000101010010 ), "0b10101011001010001111000101010010" },
    { static_cast<std::int32_t>( 0b11100010000110100110101010011001 ), "0b11100010000110100110101010011001" },
    { static_cast<std::int32_t>( 0b11011001110010011000010111111100 ), "0b11011001110010011000010111111100" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::int32_t test fixture.
 */
class outputFormatterFormatBinPrintOutputStreamI32 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::int32_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintOutputStreamI32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Bin{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintOutputStreamI32, ValuesIn( outputFormatterFormatBinPrintI32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::int32_t test
 *        fixture.
 */
class outputFormatterFormatBinPrintFaultReportingOutputStreamI32 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::int32_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintFaultReportingOutputStreamI32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Bin{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintFaultReportingOutputStreamI32, ValuesIn( outputFormatterFormatBinPrintI32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print()
 *        std::uint32_t test cases.
 */
outputFormatterFormatBinPrint_Test_Case<std::uint32_t> const outputFormatterFormatBinPrintU32_TEST_CASES[]{
    // clang-format off

    { 0b00000000000000000000000000000000, "0b00000000000000000000000000000000" },
    { 0b11111111111111111111111111111111, "0b11111111111111111111111111111111" },

    { 0b01111000000011100010000000011110, "0b01111000000011100010000000011110" },
    { 0b00101110111011110111101100000000, "0b00101110111011110111101100000000" },
    { 0b10101011001010001111000101010010, "0b10101011001010001111000101010010" },
    { 0b11100010000110100110101010011001, "0b11100010000110100110101010011001" },
    { 0b11011001110010011000010111111100, "0b11011001110010011000010111111100" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::uint32_t test fixture.
 */
class outputFormatterFormatBinPrintOutputStreamU32 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::uint32_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintOutputStreamU32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Bin{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintOutputStreamU32, ValuesIn( outputFormatterFormatBinPrintU32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::uint32_t test
 *        fixture.
 */
class outputFormatterFormatBinPrintFaultReportingOutputStreamU32 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::uint32_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintFaultReportingOutputStreamU32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Bin{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintFaultReportingOutputStreamU32, ValuesIn( outputFormatterFormatBinPrintU32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print()
 *        std::int64_t test cases.
 */
outputFormatterFormatBinPrint_Test_Case<std::int64_t> const outputFormatterFormatBinPrintI64_TEST_CASES[]{
    // clang-format off

    { static_cast<std::int64_t>( 0b0000000000000000000000000000000000000000000000000000000000000000 ), "0b0000000000000000000000000000000000000000000000000000000000000000" },
    { static_cast<std::int64_t>( 0b1111111111111111111111111111111111111111111111111111111111111111 ), "0b1111111111111111111111111111111111111111111111111111111111111111" },

    { static_cast<std::int64_t>( 0b0100100100001001011001110111111001010010001110011010111001011001 ), "0b0100100100001001011001110111111001010010001110011010111001011001" },
    { static_cast<std::int64_t>( 0b0000101101010101011010110101001101100010011011111010101011101000 ), "0b0000101101010101011010110101001101100010011011111010101011101000" },
    { static_cast<std::int64_t>( 0b0001011000011000100000111001100110000101010001100101000010001110 ), "0b0001011000011000100000111001100110000101010001100101000010001110" },
    { static_cast<std::int64_t>( 0b1111100001110010111110011111101010101111101010000001001110001100 ), "0b1111100001110010111110011111101010101111101010000001001110001100" },
    { static_cast<std::int64_t>( 0b1110001100011011000111000010110011110011101101010011010100100011 ), "0b1110001100011011000111000010110011110011101101010011010100100011" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::int64_t test fixture.
 */
class outputFormatterFormatBinPrintOutputStreamI64 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::int64_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintOutputStreamI64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Bin{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintOutputStreamI64, ValuesIn( outputFormatterFormatBinPrintI64_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::int64_t test
 *        fixture.
 */
class outputFormatterFormatBinPrintFaultReportingOutputStreamI64 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::int64_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintFaultReportingOutputStreamI64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Bin{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintFaultReportingOutputStreamI64, ValuesIn( outputFormatterFormatBinPrintI64_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print()
 *        std::uint64_t test cases.
 */
outputFormatterFormatBinPrint_Test_Case<std::uint64_t> const outputFormatterFormatBinPrintU64_TEST_CASES[]{
    // clang-format off

    { 0b0000000000000000000000000000000000000000000000000000000000000000, "0b0000000000000000000000000000000000000000000000000000000000000000" },
    { 0b1111111111111111111111111111111111111111111111111111111111111111, "0b1111111111111111111111111111111111111111111111111111111111111111" },

    { 0b0100100100001001011001110111111001010010001110011010111001011001, "0b0100100100001001011001110111111001010010001110011010111001011001" },
    { 0b0000101101010101011010110101001101100010011011111010101011101000, "0b0000101101010101011010110101001101100010011011111010101011101000" },
    { 0b0001011000011000100000111001100110000101010001100101000010001110, "0b0001011000011000100000111001100110000101010001100101000010001110" },
    { 0b1111100001110010111110011111101010101111101010000001001110001100, "0b1111100001110010111110011111101010101111101010000001001110001100" },
    { 0b1110001100011011000111000010110011110011101101010011010100100011, "0b1110001100011011000111000010110011110011101101010011010100100011" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::uint64_t test fixture.
 */
class outputFormatterFormatBinPrintOutputStreamU64 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::uint64_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintOutputStreamU64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Bin{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintOutputStreamU64, ValuesIn( outputFormatterFormatBinPrintU64_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::uint64_t test
 *        fixture.
 */
class outputFormatterFormatBinPrintFaultReportingOutputStreamU64 :
    public TestWithParam<outputFormatterFormatBinPrint_Test_Case<std::uint64_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Bin<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatBinPrintFaultReportingOutputStreamU64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Bin{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.bin );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatBinPrintFaultReportingOutputStreamU64, ValuesIn( outputFormatterFormatBinPrintU64_TEST_CASES ) );
