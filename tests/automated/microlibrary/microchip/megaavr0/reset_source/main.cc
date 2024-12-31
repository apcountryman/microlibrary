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
 * \brief microlibrary::Microchip::megaAVR0::Reset_Source automated tests.
 */

#include <bitset>
#include <cstdint>
#include <ios>
#include <limits>
#include <ostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/microchip/megaavr0/reset.h"

namespace {

using ::microlibrary::Microchip::megaAVR0::Reset_Source;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

} // namespace

/**
 * \brief microlibrary::Microchip::megaAVR0::Reset_Source::Reset_Source( std::uint8_t )
 *        test case.
 */
struct constructor_Test_Case {
    /**
     * \brief The RSTCTRL peripheral RSTFR value.
     */
    std::uint8_t rstctrl_rstfr;

    /**
     * \brief A UPDI reset has occurred.
     */
    bool is_updi_reset;

    /**
     * \brief A software reset has occurred.
     */
    bool is_software_reset;

    /**
     * \brief A watchdog reset has occurred.
     */
    bool is_watchdog_reset;

    /**
     * \brief An external reset has occurred.
     */
    bool is_external_reset;

    /**
     * \brief A brown-out reset has occurred.
     */
    bool is_brown_out_reset;

    /**
     * \brief A power-on reset has occurred.
     */
    bool is_power_on_reset;
};

auto operator<<( std::ostream & stream, constructor_Test_Case const & test_case ) -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".rstctrl_rstfr = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.rstctrl_rstfr }
                  << ", "
                  << ".is_updi_reset = " << std::boolalpha << test_case.is_updi_reset
                  << ", "
                  << ".is_software_reset = " << std::boolalpha << test_case.is_software_reset
                  << ", "
                  << ".is_watchdog_reset = " << std::boolalpha << test_case.is_watchdog_reset
                  << ", "
                  << ".is_external_reset = " << std::boolalpha << test_case.is_external_reset
                  << ", "
                  << ".is_brown_out_reset = " << std::boolalpha << test_case.is_brown_out_reset
                  << ", "
                  << ".is_power_on_reset = " << std::boolalpha << test_case.is_power_on_reset
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Reset_Source::Reset_Source( std::uint8_t )
 *        test fixture.
 */
class constructor : public TestWithParam<constructor_Test_Case> {
};

/**
 * \brief Verify microlibrary::Microchip::megaAVR0::Reset_Source::Reset_Source(
 *        std::uint8_t ) works properly.
 */
TEST_P( constructor, worksProperly )
{
    auto const test_case = GetParam();

    auto const reset_source = Reset_Source{ test_case.rstctrl_rstfr };

    EXPECT_EQ( reset_source.rstctrl_rstfr(), test_case.rstctrl_rstfr );
    EXPECT_EQ( reset_source.is_power_on_reset(), test_case.is_power_on_reset );
    EXPECT_EQ( reset_source.is_brown_out_reset(), test_case.is_brown_out_reset );
    EXPECT_EQ( reset_source.is_external_reset(), test_case.is_external_reset );
    EXPECT_EQ( reset_source.is_watchdog_reset(), test_case.is_watchdog_reset );
    EXPECT_EQ( reset_source.is_software_reset(), test_case.is_software_reset );
    EXPECT_EQ( reset_source.is_updi_reset(), test_case.is_updi_reset );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Reset_Source::Reset_Source( std::uint8_t )
 *        test cases.
 */
constructor_Test_Case const constructor_TEST_CASES[]{
    // clang-format off

    { 0b00'0'0'0'0'0'0, false, false, false, false, false, false },
    { 0b00'0'0'0'0'0'1, false, false, false, false, false,  true },
    { 0b00'0'0'0'0'1'0, false, false, false, false,  true, false },
    { 0b00'0'0'0'1'0'0, false, false, false,  true, false, false },
    { 0b00'0'0'1'0'0'0, false, false,  true, false, false, false },
    { 0b00'0'1'0'0'0'0, false,  true, false, false, false, false },
    { 0b00'1'0'0'0'0'0,  true, false, false, false, false, false },
    { 0b00'1'1'1'1'1'1,  true,  true,  true,  true,  true,  true },

    { 0b01'0'0'0'0'0'0, false, false, false, false, false, false },
    { 0b01'0'0'0'0'0'1, false, false, false, false, false,  true },
    { 0b01'0'0'0'0'1'0, false, false, false, false,  true, false },
    { 0b01'0'0'0'1'0'0, false, false, false,  true, false, false },
    { 0b01'0'0'1'0'0'0, false, false,  true, false, false, false },
    { 0b01'0'1'0'0'0'0, false,  true, false, false, false, false },
    { 0b01'1'0'0'0'0'0,  true, false, false, false, false, false },
    { 0b01'1'1'1'1'1'1,  true,  true,  true,  true,  true,  true },

    { 0b10'0'0'0'0'0'0, false, false, false, false, false, false },
    { 0b10'0'0'0'0'0'1, false, false, false, false, false,  true },
    { 0b10'0'0'0'0'1'0, false, false, false, false,  true, false },
    { 0b10'0'0'0'1'0'0, false, false, false,  true, false, false },
    { 0b10'0'0'1'0'0'0, false, false,  true, false, false, false },
    { 0b10'0'1'0'0'0'0, false,  true, false, false, false, false },
    { 0b10'1'0'0'0'0'0,  true, false, false, false, false, false },
    { 0b10'1'1'1'1'1'1,  true,  true,  true,  true,  true,  true },

    { 0b11'0'0'0'0'0'0, false, false, false, false, false, false },
    { 0b11'0'0'0'0'0'1, false, false, false, false, false,  true },
    { 0b11'0'0'0'0'1'0, false, false, false, false,  true, false },
    { 0b11'0'0'0'1'0'0, false, false, false,  true, false, false },
    { 0b11'0'0'1'0'0'0, false, false,  true, false, false, false },
    { 0b11'0'1'0'0'0'0, false,  true, false, false, false, false },
    { 0b11'1'0'0'0'0'0,  true, false, false, false, false, false },
    { 0b11'1'1'1'1'1'1,  true,  true,  true,  true,  true,  true },

    { 0b01'1'0'0'0'1'0,  true, false, false, false,  true, false },
    { 0b11'1'0'0'1'1'0,  true, false, false,  true,  true, false },
    { 0b00'1'1'1'0'0'1,  true,  true,  true, false, false,  true },
    { 0b00'0'1'0'0'1'1, false,  true, false, false,  true,  true },
    { 0b01'1'0'0'0'1'0,  true, false, false, false,  true, false },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, constructor, ValuesIn( constructor_TEST_CASES ) );
