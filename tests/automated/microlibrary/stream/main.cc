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
 * \brief microlibrary::Stream automated tests.
 */

#include <ios>
#include <ostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/stream.h"
#include "microlibrary/testing/automated/stream.h"

namespace {

using ::microlibrary::Testing::Automated::Mock_Stream_IO_Driver;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

class Stream : public ::microlibrary::Stream {
  public:
    using ::microlibrary::Stream::Stream;

    ~Stream() noexcept = default;

    constexpr auto operator=( Stream && expression ) noexcept -> Stream & = default;

    constexpr auto operator=( Stream const & expression ) noexcept -> Stream & = default;

    using ::microlibrary::Stream::clear_end_of_file_reached_report;
    using ::microlibrary::Stream::report_end_of_file_reached;

    using ::microlibrary::Stream::driver;
    using ::microlibrary::Stream::set_driver;
};

} // namespace

/**
 * \brief microlibrary::Stream::is_nominal(), microlibrary::Stream::error_reported(),
 *        microlibrary::Stream::end_of_file_reached(),
 *        microlibrary::Stream::report_end_of_file_reached(),
 *        microlibrary::Stream::clear_end_of_file_reached_report(),
 *        microlibrary::Stream::io_error_reported(),
 *        microlibrary::Stream::report_io_error(), and
 *        microlibrary::Stream::clear_io_error_report() test case.
 */
struct flagSetClear_Test_Case {
    /**
     * \brief Flag manipulation function pointer.
     */
    using Flag_Manipulation_Function_Pointer = void ( Stream::* )();

    /**
     * \brief The function to call to set the flag.
     */
    Flag_Manipulation_Function_Pointer set_flag;

    /**
     * \brief The function to call to clear the flag.
     */
    Flag_Manipulation_Function_Pointer clear_flag;

    /**
     * \brief Errors have been reported.
     */
    bool error_reported;

    /**
     * \brief End-of-file has been reached.
     */
    bool end_of_file_reached;

    /**
     * \brief I/O error has been reported.
     */
    bool io_error_reported;
};

auto operator<<( std::ostream & stream, flagSetClear_Test_Case const & test_case ) -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".error_reported = " << std::boolalpha << test_case.error_reported
                  << ", "
                  << ".end_of_file_reached = " << std::boolalpha << test_case.end_of_file_reached
                  << ", "
                  << ".io_error_reported = " << std::boolalpha << test_case.io_error_reported
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Stream::is_nominal(), microlibrary::Stream::error_reported(),
 *        microlibrary::Stream::end_of_file_reached(),
 *        microlibrary::Stream::report_end_of_file_reached(),
 *        microlibrary::Stream::clear_end_of_file_reached_report(),
 *        microlibrary::Stream::io_error_reported(),
 *        microlibrary::Stream::report_io_error(), and
 *        microlibrary::Stream::clear_io_error_report() test fixture.
 */
class flagSetClear : public TestWithParam<flagSetClear_Test_Case> {
};

/**
 * \brief Verify microlibrary::Stream::is_nominal(),
 *        microlibrary::Stream::error_reported(),
 *        microlibrary::Stream::end_of_file_reached(),
 *        microlibrary::Stream::report_end_of_file_reached(),
 *        microlibrary::Stream::clear_end_of_file_reached_report(),
 *        microlibrary::Stream::io_error_reported(),
 *        microlibrary::Stream::report_io_error(), and
 *        microlibrary::Stream::clear_io_error_report() work properly.
 */
TEST_P( flagSetClear, worksProperly )
{
    auto const test_case = GetParam();

    auto stream = Stream{};

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_FALSE( stream.error_reported() );
    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );

    ( stream.*( test_case.clear_flag ) )();

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_FALSE( stream.error_reported() );
    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );

    ( stream.*( test_case.set_flag ) )();

    EXPECT_FALSE( stream.is_nominal() );
    EXPECT_EQ( stream.error_reported(), test_case.error_reported );
    EXPECT_EQ( stream.end_of_file_reached(), test_case.end_of_file_reached );
    EXPECT_EQ( stream.io_error_reported(), test_case.io_error_reported );

    ( stream.*( test_case.set_flag ) )();

    EXPECT_FALSE( stream.is_nominal() );
    EXPECT_EQ( stream.error_reported(), test_case.error_reported );
    EXPECT_EQ( stream.end_of_file_reached(), test_case.end_of_file_reached );
    EXPECT_EQ( stream.io_error_reported(), test_case.io_error_reported );

    ( stream.*( test_case.clear_flag ) )();

    EXPECT_TRUE( stream.is_nominal() );
    EXPECT_FALSE( stream.error_reported() );
    EXPECT_FALSE( stream.end_of_file_reached() );
    EXPECT_FALSE( stream.io_error_reported() );
}

/**
 * \brief microlibrary::Stream::is_nominal(), microlibrary::Stream::error_reported(),
 *        microlibrary::Stream::end_of_file_reached(),
 *        microlibrary::Stream::report_end_of_file_reached(),
 *        microlibrary::Stream::clear_end_of_file_reached_report(),
 *        microlibrary::Stream::io_error_reported(),
 *        microlibrary::Stream::report_io_error(), and
 *        microlibrary::Stream::clear_io_error_report() test cases.
 */
flagSetClear_Test_Case const flagSetClear_TEST_CASES[]{
    // clang-format off

    { &Stream::report_end_of_file_reached, &Stream::clear_end_of_file_reached_report, false,  true, false },
    { &Stream::report_io_error,            &Stream::clear_io_error_report,             true, false,  true },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, flagSetClear, ValuesIn( flagSetClear_TEST_CASES ) );

/**
 * \brief Verify microlibrary::Stream::driver_is_set(), microlibrary::Stream::driver(),
 *        and microlibrary::Stream::set_driver() work properly.
 */
TEST( driver, worksProperly )
{
    auto stream = Stream{};

    EXPECT_FALSE( stream.driver_is_set() );
    EXPECT_EQ( stream.driver(), nullptr );

    auto driver = Mock_Stream_IO_Driver{};

    stream.set_driver( &driver );

    EXPECT_TRUE( stream.driver_is_set() );
    EXPECT_EQ( stream.driver(), &driver );

    stream.set_driver( nullptr );

    EXPECT_FALSE( stream.driver_is_set() );
    EXPECT_EQ( stream.driver(), nullptr );
}
