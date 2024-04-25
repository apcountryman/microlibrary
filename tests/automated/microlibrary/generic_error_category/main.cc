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
 * \brief microlibrary:::Generic_Error_Category automated tests.
 */

#include <cstdint>
#include <ios>
#include <ostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/enum.h"
#include "microlibrary/error.h"

namespace {

using ::microlibrary::Error_ID;
using ::microlibrary::Generic_Error;
using ::microlibrary::Generic_Error_Category;
using ::microlibrary::to_underlying;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

} // namespace

/**
 * \brief Verify microlibrary::Generic_Error_Category::name() works properly.
 */
TEST( name, worksProperly )
{
    EXPECT_STREQ(
        Generic_Error_Category::instance().name(), "::microlibrary::Generic_Error" );
}

/**
 * \brief microlibrary::Generic_Error_Category::error_description() test case.
 */
struct errorDescription_Test_Case {
    /**
     * \brief The error ID whose description is to be got.
     */
    Error_ID id;

    /**
     * \brief The error ID's description.
     */
    char const * error_description;
};

auto operator<<( std::ostream & stream, errorDescription_Test_Case const & test_case ) -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".id = " << std::dec << static_cast<std::uint_fast16_t>( test_case.id )
                  << ", "
                  << ".error_description = " << test_case.error_description
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Generic_Error_Category::error_description() test fixture.
 */
class errorDescription : public TestWithParam<errorDescription_Test_Case> {
};

/**
 * \brief Verify microlibrary::Generic_Error_Category::error_description() works properly.
 */
TEST_P( errorDescription, worksProperly )
{
    auto const test_case = GetParam();

    EXPECT_STREQ(
        Generic_Error_Category::instance().error_description( test_case.id ), test_case.error_description );
}

/**
 * \brief microlibrary::Generic_Error_Category::error_description() test cases.
 */
errorDescription_Test_Case const errorDescription_TEST_CASES[]{
    // clang-format off

    { to_underlying( Generic_Error::INVALID_ARGUMENT ), "INVALID_ARGUMENT" },
    { to_underlying( Generic_Error::LOGIC_ERROR ), "LOGIC_ERROR" },
    { to_underlying( Generic_Error::OUT_OF_RANGE ), "OUT_OF_RANGE" },
    { to_underlying( Generic_Error::RUNTIME_ERROR ), "RUNTIME_ERROR" },

    { to_underlying( Generic_Error::RUNTIME_ERROR ) + 1, "UNKNOWN" },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P( testCases, errorDescription, ValuesIn( errorDescription_TEST_CASES ) );
