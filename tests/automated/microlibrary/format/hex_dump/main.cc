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
 * \brief microlibrary::Format::Hex_Dump automated tests.
 */

#include <cstdint>
#include <iomanip>
#include <ios>
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

using ::microlibrary::Format::Hex_Dump;
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
 * \brief Verify microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Fault_Reporting_Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) properly handles a
 *        put error.
 */
TEST( outputFormatterFormatHexDumpPrintFaultReportingOutputStreamErrorHandling, putError )
{
    auto stream = Mock_Fault_Reporting_Output_Stream{};

    auto const error = Mock_Error{ 153 };

    EXPECT_CALL( stream.driver(), put( A<std::string>() ) ).WillOnce( Return( error ) );

    auto const data = std::string_view{ "odMJz0Qd28QFM2" };

    auto const result = stream.print( Hex_Dump{ std::uint16_t{ 0x36B2 }, data.begin(), data.end() } );

    EXPECT_TRUE( result.is_error() );
    EXPECT_EQ( result.error(), error );

    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
    EXPECT_TRUE( stream.fatal_error_reported() );
}

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print() test case.
 */
template<typename Address>
struct outputFormatterFormatHexDumpPrint_Test_Case {
    /**
     * \brief The address of the data to dump.
     */
    Address address;

    /**
     * \brief The data to dump.
     */
    std::string_view data;

    /**
     * \brief The hex dump.
     */
    std::string_view hex_dump;
};

template<typename Address>
auto operator<<( std::ostream & stream, outputFormatterFormatHexDumpPrint_Test_Case<Address> const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".address = 0x" << std::hex << std::uppercase << std::setw( std::numeric_limits<Address>::digits / 4 ) << std::setfill( '0' ) << test_case.address
                  << ", "
                  << ".data = " << test_case.data
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print() std::uint16_t address test cases.
 */
outputFormatterFormatHexDumpPrint_Test_Case<std::uint16_t> const outputFormatterFormatHexDumpPrint16_TEST_CASES[]{
    // clang-format off

    {
        0x3E4D,
        "",
        "",
    },
    {
        0x0000,
        "(Y !d5vz\t^2",
        "0000  28 59 20 21 64 35 76 7A 09 5E 32                 |(Y !d5vz.^2|     \n"
    },
    {
        0xFFFF,
        ":X;27N8u]hde[e&+",
        "FFFF  3A 58 3B 32 37 4E 38 75 5D 68 64 65 5B 65 26 2B  |:X;27N8u]hde[e&+|\n"
    },
    {
        0x0000,
        "{yZZk7V!/{>fm[lxV!$e|:",
        "0000  7B 79 5A 5A 6B 37 56 21 2F 7B 3E 66 6D 5B 6C 78  |{yZZk7V!/{>fm[lx|\n"
        "0010  56 21 24 65 7C 3A                                |V!$e|:|          \n"
    },
    {
        0xFFFF,
        "/B>wiGoUZ|6cjO(_`T.8jV:RxSUssq!L",
        "FFFF  2F 42 3E 77 69 47 6F 55 5A 7C 36 63 6A 4F 28 5F  |/B>wiGoUZ|6cjO(_|\n"
        "000F  60 54 2E 38 6A 56 3A 52 78 53 55 73 73 71 21 4C  |`T.8jV:RxSUssq!L|\n"
    },
    {
        0x2627,
        "(Y !d5vz\t^2",
        "2627  28 59 20 21 64 35 76 7A 09 5E 32                 |(Y !d5vz.^2|     \n"
    },
    {
        0x577B,
        ":X;27N8u]hde[e&+",
        "577B  3A 58 3B 32 37 4E 38 75 5D 68 64 65 5B 65 26 2B  |:X;27N8u]hde[e&+|\n"
    },
    {
        0x95A1,
        "{yZZk7V!/{>fm[lxV!$e|:",
        "95A1  7B 79 5A 5A 6B 37 56 21 2F 7B 3E 66 6D 5B 6C 78  |{yZZk7V!/{>fm[lx|\n"
        "95B1  56 21 24 65 7C 3A                                |V!$e|:|          \n"
    },
    {
        0xD512,
        "/B>wiGoUZ|6cjO(_`T.8jV:RxSUssq!L",
        "D512  2F 42 3E 77 69 47 6F 55 5A 7C 36 63 6A 4F 28 5F  |/B>wiGoUZ|6cjO(_|\n"
        "D522  60 54 2E 38 6A 56 3A 52 78 53 55 73 73 71 21 4C  |`T.8jV:RxSUssq!L|\n"
    },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) std::uint16_t
 *        address test fixture.
 */
class outputFormatterFormatHexDumpPrintOutputStream16 :
    public TestWithParam<outputFormatterFormatHexDumpPrint_Test_Case<std::uint16_t>> {
};

/**
 * \brief Verify microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) works properly.
 */
TEST_P( outputFormatterFormatHexDumpPrintOutputStream16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print(
        Hex_Dump{ test_case.address, test_case.data.begin(), test_case.data.end() } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.hex_dump );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatHexDumpPrintOutputStream16, ValuesIn( outputFormatterFormatHexDumpPrint16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Fault_Reporting_Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) std::uint16_t
 *        address test fixture.
 */
class outputFormatterFormatHexDumpPrintFaultReportingOutputStream16 :
    public TestWithParam<outputFormatterFormatHexDumpPrint_Test_Case<std::uint16_t>> {
};

/**
 * \brief Verify microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Fault_Reporting_Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) works properly.
 */
TEST_P( outputFormatterFormatHexDumpPrintFaultReportingOutputStream16, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print(
        Hex_Dump{ test_case.address, test_case.data.begin(), test_case.data.end() } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.hex_dump );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatHexDumpPrintFaultReportingOutputStream16, ValuesIn( outputFormatterFormatHexDumpPrint16_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print() std::uint32_t address test cases.
 */
outputFormatterFormatHexDumpPrint_Test_Case<std::uint32_t> const outputFormatterFormatHexDumpPrint32_TEST_CASES[]{
    // clang-format off

    {
        0x5DED7EB6,
        "",
        "",
    },
    {
        0x00000000,
        "(Y !d5vz\t^2",
        "00000000  28 59 20 21 64 35 76 7A 09 5E 32                 |(Y !d5vz.^2|     \n"
    },
    {
        0xFFFFFFFF,
        ":X;27N8u]hde[e&+",
        "FFFFFFFF  3A 58 3B 32 37 4E 38 75 5D 68 64 65 5B 65 26 2B  |:X;27N8u]hde[e&+|\n"
    },
    {
        0x00000000,
        "{yZZk7V!/{>fm[lxV!$e|:",
        "00000000  7B 79 5A 5A 6B 37 56 21 2F 7B 3E 66 6D 5B 6C 78  |{yZZk7V!/{>fm[lx|\n"
        "00000010  56 21 24 65 7C 3A                                |V!$e|:|          \n"
    },
    {
        0xFFFFFFFF,
        "/B>wiGoUZ|6cjO(_`T.8jV:RxSUssq!L",
        "FFFFFFFF  2F 42 3E 77 69 47 6F 55 5A 7C 36 63 6A 4F 28 5F  |/B>wiGoUZ|6cjO(_|\n"
        "0000000F  60 54 2E 38 6A 56 3A 52 78 53 55 73 73 71 21 4C  |`T.8jV:RxSUssq!L|\n"
    },
    {
        0x984DBBA7,
        "(Y !d5vz\t^2",
        "984DBBA7  28 59 20 21 64 35 76 7A 09 5E 32                 |(Y !d5vz.^2|     \n"
    },
    {
        0xDA2C2551,
        ":X;27N8u]hde[e&+",
        "DA2C2551  3A 58 3B 32 37 4E 38 75 5D 68 64 65 5B 65 26 2B  |:X;27N8u]hde[e&+|\n"
    },
    {
        0x3F4B1FCF,
        "{yZZk7V!/{>fm[lxV!$e|:",
        "3F4B1FCF  7B 79 5A 5A 6B 37 56 21 2F 7B 3E 66 6D 5B 6C 78  |{yZZk7V!/{>fm[lx|\n"
        "3F4B1FDF  56 21 24 65 7C 3A                                |V!$e|:|          \n"
    },
    {
        0x3F331547,
        "/B>wiGoUZ|6cjO(_`T.8jV:RxSUssq!L",
        "3F331547  2F 42 3E 77 69 47 6F 55 5A 7C 36 63 6A 4F 28 5F  |/B>wiGoUZ|6cjO(_|\n"
        "3F331557  60 54 2E 38 6A 56 3A 52 78 53 55 73 73 71 21 4C  |`T.8jV:RxSUssq!L|\n"
    },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) std::uint32_t
 *        address test fixture.
 */
class outputFormatterFormatHexDumpPrintOutputStream32 :
    public TestWithParam<outputFormatterFormatHexDumpPrint_Test_Case<std::uint32_t>> {
};

/**
 * \brief Verify microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) works properly.
 */
TEST_P( outputFormatterFormatHexDumpPrintOutputStream32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print(
        Hex_Dump{ test_case.address, test_case.data.begin(), test_case.data.end() } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.hex_dump );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatHexDumpPrintOutputStream32, ValuesIn( outputFormatterFormatHexDumpPrint32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Fault_Reporting_Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) std::uint32_t
 *        address test fixture.
 */
class outputFormatterFormatHexDumpPrintFaultReportingOutputStream32 :
    public TestWithParam<outputFormatterFormatHexDumpPrint_Test_Case<std::uint32_t>> {
};

/**
 * \brief Verify microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Fault_Reporting_Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) works properly.
 */
TEST_P( outputFormatterFormatHexDumpPrintFaultReportingOutputStream32, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print(
        Hex_Dump{ test_case.address, test_case.data.begin(), test_case.data.end() } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.hex_dump );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatHexDumpPrintFaultReportingOutputStream32, ValuesIn( outputFormatterFormatHexDumpPrint32_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print() std::uint64_t address test cases.
 */
outputFormatterFormatHexDumpPrint_Test_Case<std::uint64_t> const outputFormatterFormatHexDumpPrint64_TEST_CASES[]{
    // clang-format off

    {
        0x4A2283195D3ADAB6,
        "",
        "",
    },
    {
        0x0000000000000000,
        "(Y !d5vz\t^2",
        "0000000000000000  28 59 20 21 64 35 76 7A 09 5E 32                 |(Y !d5vz.^2|     \n"
    },
    {
        0xFFFFFFFFFFFFFFFF,
        ":X;27N8u]hde[e&+",
        "FFFFFFFFFFFFFFFF  3A 58 3B 32 37 4E 38 75 5D 68 64 65 5B 65 26 2B  |:X;27N8u]hde[e&+|\n"
    },
    {
        0x0000000000000000,
        "{yZZk7V!/{>fm[lxV!$e|:",
        "0000000000000000  7B 79 5A 5A 6B 37 56 21 2F 7B 3E 66 6D 5B 6C 78  |{yZZk7V!/{>fm[lx|\n"
        "0000000000000010  56 21 24 65 7C 3A                                |V!$e|:|          \n"
    },
    {
        0xFFFFFFFFFFFFFFFF,
        "/B>wiGoUZ|6cjO(_`T.8jV:RxSUssq!L",
        "FFFFFFFFFFFFFFFF  2F 42 3E 77 69 47 6F 55 5A 7C 36 63 6A 4F 28 5F  |/B>wiGoUZ|6cjO(_|\n"
        "000000000000000F  60 54 2E 38 6A 56 3A 52 78 53 55 73 73 71 21 4C  |`T.8jV:RxSUssq!L|\n"
    },
    {
        0xCB91B0F9ADD06CED,
        "(Y !d5vz\t^2",
        "CB91B0F9ADD06CED  28 59 20 21 64 35 76 7A 09 5E 32                 |(Y !d5vz.^2|     \n"
    },
    {
        0x499907CB64B7CDF9,
        ":X;27N8u]hde[e&+",
        "499907CB64B7CDF9  3A 58 3B 32 37 4E 38 75 5D 68 64 65 5B 65 26 2B  |:X;27N8u]hde[e&+|\n"
    },
    {
        0x235570C8A88DC896,
        "{yZZk7V!/{>fm[lxV!$e|:",
        "235570C8A88DC896  7B 79 5A 5A 6B 37 56 21 2F 7B 3E 66 6D 5B 6C 78  |{yZZk7V!/{>fm[lx|\n"
        "235570C8A88DC8A6  56 21 24 65 7C 3A                                |V!$e|:|          \n"
    },
    {
        0x37F53DF0D3FC15DF,
        "/B>wiGoUZ|6cjO(_`T.8jV:RxSUssq!L",
        "37F53DF0D3FC15DF  2F 42 3E 77 69 47 6F 55 5A 7C 36 63 6A 4F 28 5F  |/B>wiGoUZ|6cjO(_|\n"
        "37F53DF0D3FC15EF  60 54 2E 38 6A 56 3A 52 78 53 55 73 73 71 21 4C  |`T.8jV:RxSUssq!L|\n"
    },

    // clang-format on
};

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) std::uint64_t
 *        address test fixture.
 */
class outputFormatterFormatHexDumpPrintOutputStream64 :
    public TestWithParam<outputFormatterFormatHexDumpPrint_Test_Case<std::uint64_t>> {
};

/**
 * \brief Verify microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) works properly.
 */
TEST_P( outputFormatterFormatHexDumpPrintOutputStream64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Output_String_Stream{};

    auto const n = stream.print(
        Hex_Dump{ test_case.address, test_case.data.begin(), test_case.data.end() } );

    EXPECT_EQ( n, stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.hex_dump );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatHexDumpPrintOutputStream64, ValuesIn( outputFormatterFormatHexDumpPrint64_TEST_CASES ) );

/**
 * \brief microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Fault_Reporting_Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) std::uint64_t
 *        address test fixture.
 */
class outputFormatterFormatHexDumpPrintFaultReportingOutputStream64 :
    public TestWithParam<outputFormatterFormatHexDumpPrint_Test_Case<std::uint64_t>> {
};

/**
 * \brief Verify microlibrary::Output_Formatter<microlibrary::Format::Hex_Dump<Address,
 *        Iterator>>::print( microlibrary::Fault_Reporting_Output_Stream &,
 *        microlibrary::Format::Hex_Dump<Address, Iterator> const & ) works properly.
 */
TEST_P( outputFormatterFormatHexDumpPrintFaultReportingOutputStream64, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Fault_Reporting_Output_String_Stream{};

    auto const result = stream.print(
        Hex_Dump{ test_case.address, test_case.data.begin(), test_case.data.end() } );

    EXPECT_FALSE( result.is_error() );
    EXPECT_EQ( result.value(), stream.string().size() );

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_EQ( stream.string(), test_case.hex_dump );
}

INSTANTIATE_TEST_SUITE_P(, outputFormatterFormatHexDumpPrintFaultReportingOutputStream64, ValuesIn( outputFormatterFormatHexDumpPrint64_TEST_CASES ) );
