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
 * \brief microlibrary::Format::Dec automated tests.
 */

#include <cstdint>
#include <limits>
#include <ostream>
#include <string>
#include <string_view>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/format.h"
#include "microlibrary/testing/automated/error.h"
#include "microlibrary/testing/automated/stream.h"

namespace {

using ::microlibrary::Format::Dec;
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
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) properly handles a put
 *        error.
 */
TEST( outputFormatterFormatDecPrintFaultReportingOutputStreamErrorHandling, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 216 };

    EXPECT_CALL( stream.driver(), put( A<std::string>() ) ).WillOnce( Return( error ) );

    auto const result = stream.print( Dec{ 712629789 } );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print() test
 *        case.
 *
 * \tparam Integer The type of integer to format.
 */
template<typename Integer>
struct outputFormatterFormatDecPrint_Test_Case {
    /**
     * \brief The integer to be formatted.
     */
    Integer integer;

    /**
     * \brief The formatted integer.
     */
    std::string_view dec;
};

template<typename Integer>
auto operator<<( std::ostream & stream, outputFormatterFormatDecPrint_Test_Case<Integer> const & test_case )
    -> std::ostream &
{
    return stream << test_case.dec;
}

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print()
 *        std::int8_t test cases.
 */
outputFormatterFormatDecPrint_Test_Case<std::int8_t> const outputFormatterFormatDecPrintI8_TEST_CASES[]{
    // clang-format off

    { std::numeric_limits<std::int8_t>::min(), "-128" },
    {                                      -1,   "-1" },
    {                                       0,    "0" },
    {                                       1,    "1" },
    { std::numeric_limits<std::int8_t>::max(),  "127" },

    {   69,   "69" },
    {   77,   "77" },
    {  -93,  "-93" },
    {  121,  "121" },
    { -119, "-119" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::int8_t test fixture.
 */
class outputFormatterFormatDecPrintOutputStreamI8 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::int8_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintOutputStreamI8, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Dec{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintOutputStreamI8, ValuesIn( outputFormatterFormatDecPrintI8_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::int8_t test
 *        fixture.
 */
class outputFormatterFormatDecPrintFaultReportingOutputStreamI8 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::int8_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintFaultReportingOutputStreamI8, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Dec{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintFaultReportingOutputStreamI8, ValuesIn( outputFormatterFormatDecPrintI8_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print()
 *        std::uint8_t test cases.
 */
outputFormatterFormatDecPrint_Test_Case<std::uint8_t> const outputFormatterFormatDecPrintU8_TEST_CASES[]{
    // clang-format off

    { std::numeric_limits<std::uint8_t>::min(),   "0" },
    { std::numeric_limits<std::uint8_t>::max(), "255" },

    { 251, "251" },
    { 109, "109" },
    { 107, "107" },
    { 217, "217" },
    { 116, "116" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::uint8_t test fixture.
 */
class outputFormatterFormatDecPrintOutputStreamU8 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::uint8_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintOutputStreamU8, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Dec{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintOutputStreamU8, ValuesIn( outputFormatterFormatDecPrintU8_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::uint8_t test
 *        fixture.
 */
class outputFormatterFormatDecPrintFaultReportingOutputStreamU8 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::uint8_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintFaultReportingOutputStreamU8, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Dec{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintFaultReportingOutputStreamU8, ValuesIn( outputFormatterFormatDecPrintU8_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print()
 *        std::int16_t test cases.
 */
outputFormatterFormatDecPrint_Test_Case<std::int16_t> const outputFormatterFormatDecPrintI16_TEST_CASES[]{
    // clang-format off

    { std::numeric_limits<std::int16_t>::min(), "-32768" },
    {                                       -1,     "-1" },
    {                                        0,      "0" },
    {                                        1,      "1" },
    { std::numeric_limits<std::int16_t>::max(),  "32767" },

    {   8680,   "8680" },
    { -11493, "-11493" },
    { -25384, "-25384" },
    {   6601,   "6601" },
    {   8398,   "8398" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::int16_t test fixture.
 */
class outputFormatterFormatDecPrintOutputStreamI16 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::int16_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintOutputStreamI16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Dec{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintOutputStreamI16, ValuesIn( outputFormatterFormatDecPrintI16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::int16_t test
 *        fixture.
 */
class outputFormatterFormatDecPrintFaultReportingOutputStreamI16 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::int16_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintFaultReportingOutputStreamI16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Dec{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintFaultReportingOutputStreamI16, ValuesIn( outputFormatterFormatDecPrintI16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print()
 *        std::uint16_t test cases.
 */
outputFormatterFormatDecPrint_Test_Case<std::uint16_t> const outputFormatterFormatDecPrintU16_TEST_CASES[]{
    // clang-format off

    { std::numeric_limits<std::uint16_t>::min(),     "0" },
    { std::numeric_limits<std::uint16_t>::max(), "65535" },

    { 27690, "27690" },
    { 38952, "38952" },
    { 23570, "23570" },
    { 50329, "50329" },
    {  8091,  "8091" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::uint16_t test fixture.
 */
class outputFormatterFormatDecPrintOutputStreamU16 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::uint16_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintOutputStreamU16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Dec{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintOutputStreamU16, ValuesIn( outputFormatterFormatDecPrintU16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::uint16_t test
 *        fixture.
 */
class outputFormatterFormatDecPrintFaultReportingOutputStreamU16 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::uint16_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintFaultReportingOutputStreamU16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Dec{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintFaultReportingOutputStreamU16, ValuesIn( outputFormatterFormatDecPrintU16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print()
 *        std::int32_t test cases.
 */
outputFormatterFormatDecPrint_Test_Case<std::int32_t> const outputFormatterFormatDecPrintI32_TEST_CASES[]{
    // clang-format off

    { std::numeric_limits<std::int32_t>::min(), "-2147483648" },
    {                                       -1,          "-1" },
    {                                        0,           "0" },
    {                                        1,           "1" },
    { std::numeric_limits<std::int32_t>::max(),  "2147483647" },

    {  -162212520,  "-162212520" },
    { -1860052064, "-1860052064" },
    { -2031119590, "-2031119590" },
    {  1086379968,  "1086379968" },
    {   128785365,   "128785365" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::int32_t test fixture.
 */
class outputFormatterFormatDecPrintOutputStreamI32 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::int32_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintOutputStreamI32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Dec{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintOutputStreamI32, ValuesIn( outputFormatterFormatDecPrintI32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::int32_t test
 *        fixture.
 */
class outputFormatterFormatDecPrintFaultReportingOutputStreamI32 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::int32_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintFaultReportingOutputStreamI32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Dec{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintFaultReportingOutputStreamI32, ValuesIn( outputFormatterFormatDecPrintI32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print()
 *        std::uint32_t test cases.
 */
outputFormatterFormatDecPrint_Test_Case<std::uint32_t> const outputFormatterFormatDecPrintU32_TEST_CASES[]{
    // clang-format off

    { std::numeric_limits<std::uint32_t>::min(),          "0" },
    { std::numeric_limits<std::uint32_t>::max(), "4294967295" },

    { 4132754776, "4132754776" },
    { 2434915232, "2434915232" },
    { 2263847706, "2263847706" },
    { 1086379968, "1086379968" },
    {  128785365,  "128785365" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::uint32_t test fixture.
 */
class outputFormatterFormatDecPrintOutputStreamU32 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::uint32_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintOutputStreamU32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Dec{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintOutputStreamU32, ValuesIn( outputFormatterFormatDecPrintU32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::uint32_t test
 *        fixture.
 */
class outputFormatterFormatDecPrintFaultReportingOutputStreamU32 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::uint32_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintFaultReportingOutputStreamU32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Dec{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintFaultReportingOutputStreamU32, ValuesIn( outputFormatterFormatDecPrintU32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print()
 *        std::int64_t test cases.
 */
outputFormatterFormatDecPrint_Test_Case<std::int64_t> const outputFormatterFormatDecPrintI64_TEST_CASES[]{
    // clang-format off

    { std::numeric_limits<std::int64_t>::min(), "-9223372036854775808" },
    {                                       -1,                   "-1" },
    {                                        0,                    "0" },
    {                                        1,                    "1" },
    { std::numeric_limits<std::int64_t>::max(),  "9223372036854775807" },

    {  -162212520,  "-162212520" },
    { -1860052064, "-1860052064" },
    { -2031119590, "-2031119590" },
    {  1086379968,  "1086379968" },
    {   128785365,   "128785365" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::int64_t test fixture.
 */
class outputFormatterFormatDecPrintOutputStreamI64 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::int64_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintOutputStreamI64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Dec{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintOutputStreamI64, ValuesIn( outputFormatterFormatDecPrintI64_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::int64_t test
 *        fixture.
 */
class outputFormatterFormatDecPrintFaultReportingOutputStreamI64 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::int64_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintFaultReportingOutputStreamI64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Dec{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintFaultReportingOutputStreamI64, ValuesIn( outputFormatterFormatDecPrintI64_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print()
 *        std::uint64_t test cases.
 */
outputFormatterFormatDecPrint_Test_Case<std::uint64_t> const outputFormatterFormatDecPrintU64_TEST_CASES[]{
    // clang-format off

    { std::numeric_limits<std::uint64_t>::min(),                    "0" },
    { std::numeric_limits<std::uint64_t>::max(), "18446744073709551615" },

    { 4132754776, "4132754776" },
    { 2434915232, "2434915232" },
    { 2263847706, "2263847706" },
    { 1086379968, "1086379968" },
    {  128785365,  "128785365" },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) std::uint64_t test fixture.
 */
class outputFormatterFormatDecPrintOutputStreamU64 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::uint64_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintOutputStreamU64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print( Dec{ test_case.integer } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintOutputStreamU64, ValuesIn( outputFormatterFormatDecPrintU64_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) std::uint64_t test
 *        fixture.
 */
class outputFormatterFormatDecPrintFaultReportingOutputStreamU64 :
    public TestWithParam<outputFormatterFormatDecPrint_Test_Case<std::uint64_t>> {
};

/**
 * \brief Verify
 *        microlibrary::Output_Formatter<microlibrary::Format::Dec<Integer>>::print(
 *        microlibrary::Fault_Reporting_Output_Stream &, Integer ) works properly.
 */
TEST_P( outputFormatterFormatDecPrintFaultReportingOutputStreamU64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print( Dec{ test_case.integer } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.dec );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatDecPrintFaultReportingOutputStreamU64, ValuesIn( outputFormatterFormatDecPrintU64_TEST_CASES ) );
