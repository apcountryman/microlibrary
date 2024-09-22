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
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller automated tests.
 */

#include <bitset>
#include <cstdint>
#include <ios>
#include <limits>
#include <ostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/microchip/megaavr0/clock_controller.h"
#include "microlibrary/microchip/megaavr0/peripheral/clkctrl.h"
#include "microlibrary/pointer.h"
#include "microlibrary/testing/automated/microchip/megaavr0/clock_controller.h"

namespace {

using ::microlibrary::Not_Null;
using ::microlibrary::Microchip::megaAVR0::Clock_Controller;
using ::microlibrary::Microchip::megaAVR0::Clock_Prescaler;
using ::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value;
using ::microlibrary::Microchip::megaAVR0::Clock_Source;
using ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode;
using ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source;
using ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time;
using ::microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode;
using ::microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode;
using ::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

} // namespace

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source_is_changing()
 *        test case.
 */
struct clockSourceIsChanging_Test_Case {
    /**
     * \brief The MCLKSTATUS register value.
     */
    std::uint8_t mclkstatus;

    /**
     * \brief Clock source is changing.
     */
    bool clock_source_is_changing;
};

auto operator<<( std::ostream & stream, clockSourceIsChanging_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkstatus = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkstatus }
                  << ", "
                  << ".clock_source_is_changing = " << std::boolalpha << test_case.clock_source_is_changing
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source_is_changing()
 *        test fixture.
 */
class clockSourceIsChanging : public TestWithParam<clockSourceIsChanging_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source_is_changing()
 *        works properly.
 */
TEST_P( clockSourceIsChanging, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkstatus, read() ).WillOnce( Return( test_case.mclkstatus ) );

    EXPECT_EQ( clock_controller.clock_source_is_changing(), test_case.clock_source_is_changing );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source_is_changing()
 *        test cases.
 */
clockSourceIsChanging_Test_Case const clockSourceIsChanging_TEST_CASES[]{
    // clang-format off

    { 0b1'1'0'1'000'0, false },
    { 0b1'1'0'1'000'1, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, clockSourceIsChanging, ValuesIn( clockSourceIsChanging_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source() test case.
 */
struct clockSource_Test_Case {
    /**
     * \brief The MCLKCTRLA register value.
     */
    std::uint8_t mclkctrla;

    /**
     * \brief The clock source.
     */
    Clock_Source clock_source;
};

auto operator<<( std::ostream & stream, clockSource_Test_Case const & test_case ) -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkctrla }
                  << ", "
                  << ".clock_source = " << test_case.clock_source
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source() test
 *        fixture.
 */
class clockSource : public TestWithParam<clockSource_Test_Case> {
};

/**
 * \brief Verify microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source() works
 *        properly.
 */
TEST_P( clockSource, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrla, read() ).WillOnce( Return( test_case.mclkctrla ) );

    EXPECT_EQ( clock_controller.clock_source(), test_case.clock_source );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source() test cases.
 */
clockSource_Test_Case const clockSource_TEST_CASES[]{
    // clang-format off

    { 0b1'01000'00, Clock_Source::INTERNAL_16_20_MHz_OSCILLATOR                  },
    { 0b1'01000'01, Clock_Source::INTERNAL_32_768_kHz_ULTRA_LOW_POWER_OSCILLATOR },
    { 0b1'01000'10, Clock_Source::EXTERNAL_32_768_kHz_CRYSTAL_OSCILLATOR         },
    { 0b1'01000'11, Clock_Source::EXTERNAL_CLOCK                                 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, clockSource, ValuesIn( clockSource_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_clock_source() test
 *        case.
 */
struct setClockSource_Test_Case {
    /**
     * \brief The initial MCLKCTRLA register value.
     */
    std::uint8_t mclkctrla_initial;

    /**
     * \brief The desired clock source.
     */
    Clock_Source source;

    /**
     * \brief The final MCLKCTRLA register value.
     */
    std::uint8_t mclkctrla_final;
};

auto operator<<( std::ostream & stream, setClockSource_Test_Case const & test_case ) -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkctrla_initial = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkctrla_initial }
                  << ", "
                  << ".source = " << test_case.source
                  << ", "
                  << ".mclkctrla_final = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkctrla_final }
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_clock_source() test
 *        fixture.
 */
class setClockSource : public TestWithParam<setClockSource_Test_Case> {
};

/**
 * \brief Verify microlibrary::Microchip::megaAVR0::Clock_Controller::set_clock_source()
 *        works properly.
 */
TEST_P( setClockSource, worksProperly )
{
    auto const test_case = GetParam();

    auto const in_sequence = InSequence{};

    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrla, read() ).WillOnce( Return( test_case.mclkctrla_initial ) );
    EXPECT_CALL( clkctrl.mclkctrla, write( test_case.mclkctrla_final ) );

    clock_controller.set_clock_source( test_case.source );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_clock_source() test
 *        cases.
 */
setClockSource_Test_Case const setClockSource_TEST_CASES[]{
    // clang-format off

    { 0b0'00000'00, Clock_Source::INTERNAL_16_20_MHz_OSCILLATOR,                  0b0'00000'00 },
    { 0b0'00000'00, Clock_Source::INTERNAL_32_768_kHz_ULTRA_LOW_POWER_OSCILLATOR, 0b0'00000'01 },
    { 0b0'00000'00, Clock_Source::EXTERNAL_32_768_kHz_CRYSTAL_OSCILLATOR,         0b0'00000'10 },
    { 0b0'00000'00, Clock_Source::EXTERNAL_CLOCK,                                 0b0'00000'11 },

    { 0b1'11111'11, Clock_Source::INTERNAL_16_20_MHz_OSCILLATOR,                  0b1'11111'00 },
    { 0b1'11111'11, Clock_Source::INTERNAL_32_768_kHz_ULTRA_LOW_POWER_OSCILLATOR, 0b1'11111'01 },
    { 0b1'11111'11, Clock_Source::EXTERNAL_32_768_kHz_CRYSTAL_OSCILLATOR,         0b1'11111'10 },
    { 0b1'11111'11, Clock_Source::EXTERNAL_CLOCK,                                 0b1'11111'11 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, setClockSource, ValuesIn( setClockSource_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_output_is_enabled()
 *        test case.
 */
struct clockOutputIsEnabled_Test_Case {
    /**
     * \brief The MCLKCTRLA register value.
     */
    std::uint8_t mclkctrla;

    /**
     * \brief Clock output is enabled.
     */
    bool clock_output_is_enabled;
};

auto operator<<( std::ostream & stream, clockOutputIsEnabled_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkctrla }
                  << ", "
                  << ".clock_output_is_enabled = " << std::boolalpha << test_case.clock_output_is_enabled
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_output_is_enabled()
 *        test fixture.
 */
class clockOutputIsEnabled : public TestWithParam<clockOutputIsEnabled_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::clock_output_is_enabled()
 *        works properly.
 */
TEST_P( clockOutputIsEnabled, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrla, read() ).WillOnce( Return( test_case.mclkctrla ) );

    EXPECT_EQ( clock_controller.clock_output_is_enabled(), test_case.clock_output_is_enabled );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_output_is_enabled()
 *        test cases.
 */
clockOutputIsEnabled_Test_Case const clockOutputIsEnabled_TEST_CASES[]{
    // clang-format off

    { 0b0'10011'01, false },
    { 0b1'10011'01, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, clockOutputIsEnabled, ValuesIn( clockOutputIsEnabled_TEST_CASES ) );

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::enable_clock_output() works
 *        properly.
 */
TEST( enableClockOutput, worksProperly )
{
    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrla, write_or( 0b1'00000'00 ) );

    clock_controller.enable_clock_output();
}

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::disable_clock_output()
 *        works properly.
 */
TEST( disableClockOutput, worksProperly )
{
    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrla, write_and( 0b0'11111'11 ) );

    clock_controller.disable_clock_output();
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_is_enabled()
 *        test case.
 */
struct clockPrescalerIsEnabled_Test_Case {
    /**
     * \brief The MCLKCTRLB register value.
     */
    std::uint8_t mclkctrlb;

    /**
     * \brief Clock prescaler is enabled.
     */
    bool clock_prescaler_is_enabled;
};

auto operator<<( std::ostream & stream, clockPrescalerIsEnabled_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkctrlb = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkctrlb }
                  << ", "
                  << ".clock_prescaler_is_enabled = " << std::boolalpha << test_case.clock_prescaler_is_enabled
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_is_enabled()
 *        test fixture.
 */
class clockPrescalerIsEnabled : public TestWithParam<clockPrescalerIsEnabled_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_is_enabled()
 *        works properly.
 */
TEST_P( clockPrescalerIsEnabled, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrlb, read() ).WillOnce( Return( test_case.mclkctrlb ) );

    EXPECT_EQ( clock_controller.clock_prescaler_is_enabled(), test_case.clock_prescaler_is_enabled );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_is_enabled()
 *        test cases.
 */
clockPrescalerIsEnabled_Test_Case const clockPrescalerIsEnabled_TEST_CASES[]{
    // clang-format off

    { 0b010'0111'0, false },
    { 0b010'0111'1, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, clockPrescalerIsEnabled, ValuesIn( clockPrescalerIsEnabled_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_configuration()
 *        test case.
 */
struct clockPrescalerConfiguration_Test_Case {
    /**
     * \brief The MCLKCTRLB register value.
     */
    std::uint8_t mclkctrlb;

    /**
     * \brief The clock prescaler configuration.
     */
    Clock_Prescaler clock_prescaler_configuration;
};

auto operator<<( std::ostream & stream, clockPrescalerConfiguration_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkctrlb = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkctrlb }
                  << ", "
                  << ".clock_prescaler_configuration = " << test_case.clock_prescaler_configuration
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_configuration()
 *        test fixture.
 */
class clockPrescalerConfiguration : public TestWithParam<clockPrescalerConfiguration_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_configuration()
 *        works properly.
 */
TEST_P( clockPrescalerConfiguration, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrlb, read() ).WillOnce( Return( test_case.mclkctrlb ) );

    EXPECT_EQ( clock_controller.clock_prescaler_configuration(), test_case.clock_prescaler_configuration );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_configuration()
 *        test cases.
 */
clockPrescalerConfiguration_Test_Case const clockPrescalerConfiguration_TEST_CASES[]{
    // clang-format off

    { 0b010'0111'0, Clock_Prescaler::DISABLED },
    { 0b010'0111'1, Clock_Prescaler::ENABLED  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, clockPrescalerConfiguration, ValuesIn( clockPrescalerConfiguration_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_value()
 *        test case.
 */
struct clockPrescalerValue_Test_Case {
    /**
     * \brief The MCLKCTRLB register value.
     */
    std::uint8_t mclkctrlb;

    /**
     * \brief The clock prescaler value.
     */
    Clock_Prescaler_Value clock_prescaler_value;
};

auto operator<<( std::ostream & stream, clockPrescalerValue_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkctrlb = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkctrlb }
                  << ", "
                  << ".clock_prescaler_value = " << test_case.clock_prescaler_value
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_value()
 *        test fixture.
 */
class clockPrescalerValue : public TestWithParam<clockPrescalerValue_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_value()
 *        works properly.
 */
TEST_P( clockPrescalerValue, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrlb, read() ).WillOnce( Return( test_case.mclkctrlb ) );

    EXPECT_EQ( clock_controller.clock_prescaler_value(), test_case.clock_prescaler_value );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_value()
 *        test cases.
 */
clockPrescalerValue_Test_Case const clockPrescalerValue_TEST_CASES[]{
    // clang-format off

    { 0b110'0000'1, Clock_Prescaler_Value::_2  },
    { 0b110'0001'1, Clock_Prescaler_Value::_4  },
    { 0b110'0010'1, Clock_Prescaler_Value::_8  },
    { 0b110'0011'1, Clock_Prescaler_Value::_16 },
    { 0b110'0100'1, Clock_Prescaler_Value::_32 },
    { 0b110'0101'1, Clock_Prescaler_Value::_64 },
    { 0b110'1000'1, Clock_Prescaler_Value::_6  },
    { 0b110'1001'1, Clock_Prescaler_Value::_10 },
    { 0b110'1010'1, Clock_Prescaler_Value::_12 },
    { 0b110'1011'1, Clock_Prescaler_Value::_24 },
    { 0b110'1100'1, Clock_Prescaler_Value::_48 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, clockPrescalerValue, ValuesIn( clockPrescalerValue_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_clock_prescaler()
 *        test case.
 */
struct configureClockPrescaler_Test_Case {
    /**
     * \brief The desired clock prescaler value.
     */
    Clock_Prescaler_Value value;

    /**
     * \brief The desired clock prescaler configuration.
     */
    Clock_Prescaler configuration;

    /**
     * \brief The MCLKCTRLA register value.
     */
    std::uint8_t mclkctrlb;
};

auto operator<<( std::ostream & stream, configureClockPrescaler_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".value = " << test_case.value
                  << ", "
                  << ".configuration = " << test_case.configuration
                  << ", "
                  << ".mclkctrlb = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkctrlb }
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_clock_prescaler()
 *        test fixture.
 */
class configureClockPrescaler : public TestWithParam<configureClockPrescaler_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::configure_clock_prescaler()
 *        works properly.
 */
TEST_P( configureClockPrescaler, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrlb, write( test_case.mclkctrlb ) );

    clock_controller.configure_clock_prescaler( test_case.value, test_case.configuration );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_clock_prescaler()
 *        test cases.
 */
configureClockPrescaler_Test_Case const configureClockPrescaler_TEST_CASES[]{
    // clang-format off

    { Clock_Prescaler_Value::_2,  Clock_Prescaler::DISABLED, 0b000'0000'0 },
    { Clock_Prescaler_Value::_4,  Clock_Prescaler::DISABLED, 0b000'0001'0 },
    { Clock_Prescaler_Value::_8,  Clock_Prescaler::DISABLED, 0b000'0010'0 },
    { Clock_Prescaler_Value::_16, Clock_Prescaler::DISABLED, 0b000'0011'0 },
    { Clock_Prescaler_Value::_32, Clock_Prescaler::DISABLED, 0b000'0100'0 },
    { Clock_Prescaler_Value::_64, Clock_Prescaler::DISABLED, 0b000'0101'0 },
    { Clock_Prescaler_Value::_6,  Clock_Prescaler::DISABLED, 0b000'1000'0 },
    { Clock_Prescaler_Value::_10, Clock_Prescaler::DISABLED, 0b000'1001'0 },
    { Clock_Prescaler_Value::_12, Clock_Prescaler::DISABLED, 0b000'1010'0 },
    { Clock_Prescaler_Value::_24, Clock_Prescaler::DISABLED, 0b000'1011'0 },
    { Clock_Prescaler_Value::_48, Clock_Prescaler::DISABLED, 0b000'1100'0 },

    { Clock_Prescaler_Value::_2,  Clock_Prescaler::ENABLED, 0b000'0000'1 },
    { Clock_Prescaler_Value::_4,  Clock_Prescaler::ENABLED, 0b000'0001'1 },
    { Clock_Prescaler_Value::_8,  Clock_Prescaler::ENABLED, 0b000'0010'1 },
    { Clock_Prescaler_Value::_16, Clock_Prescaler::ENABLED, 0b000'0011'1 },
    { Clock_Prescaler_Value::_32, Clock_Prescaler::ENABLED, 0b000'0100'1 },
    { Clock_Prescaler_Value::_64, Clock_Prescaler::ENABLED, 0b000'0101'1 },
    { Clock_Prescaler_Value::_6,  Clock_Prescaler::ENABLED, 0b000'1000'1 },
    { Clock_Prescaler_Value::_10, Clock_Prescaler::ENABLED, 0b000'1001'1 },
    { Clock_Prescaler_Value::_12, Clock_Prescaler::ENABLED, 0b000'1010'1 },
    { Clock_Prescaler_Value::_24, Clock_Prescaler::ENABLED, 0b000'1011'1 },
    { Clock_Prescaler_Value::_48, Clock_Prescaler::ENABLED, 0b000'1100'1 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, configureClockPrescaler, ValuesIn( configureClockPrescaler_TEST_CASES ) );

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::enable_clock_prescaler()
 *        works properly.
 */
TEST( enableClockPrescaler, worksProperly )
{
    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrlb, write_or( 0b000'0000'1 ) );

    clock_controller.enable_clock_prescaler();
}

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::disable_clock_prescaler()
 *        works properly.
 */
TEST( disableClockPrescaler, worksProperly )
{
    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkctrlb, write_and( 0b111'1111'0 ) );

    clock_controller.disable_clock_prescaler();
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_configuration_is_locked()
 *        test case.
 */
struct clockConfigurationIsLocked_Test_Case {
    /**
     * \brief The MCLKLOCK register value.
     */
    std::uint8_t mclklock;

    /**
     * \brief Clock configuration is locked.
     */
    bool clock_configuration_is_locked;
};

auto operator<<( std::ostream & stream, clockConfigurationIsLocked_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclklock = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclklock }
                  << ", "
                  << ".clock_configuration_is_locked = " << std::boolalpha << test_case.clock_configuration_is_locked
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_configuration_is_locked()
 *        test fixture.
 */
class clockConfigurationIsLocked : public TestWithParam<clockConfigurationIsLocked_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::clock_configuration_is_locked()
 *        works properly.
 */
TEST_P( clockConfigurationIsLocked, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclklock, read() ).WillOnce( Return( test_case.mclklock ) );

    EXPECT_EQ( clock_controller.clock_configuration_is_locked(), test_case.clock_configuration_is_locked );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::clock_configuration_is_locked()
 *        test cases.
 */
clockConfigurationIsLocked_Test_Case const clockConfigurationIsLocked_TEST_CASES[]{
    // clang-format off

    { 0b0111100'0, false },
    { 0b0111100'1, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, clockConfigurationIsLocked, ValuesIn( clockConfigurationIsLocked_TEST_CASES ) );

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::lock_clock_configuration()
 *        works properly.
 */
TEST( lockClockConfiguration, worksProperly )
{
    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclklock, write( 0b0000000'1 ) );

    clock_controller.lock_clock_configuration();
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_is_stable()
 *        test case.
 */
struct internal1620MHzOscillatorIsStable_Test_Case {
    /**
     * \brief The MCLKSTATUS register value.
     */
    std::uint8_t mclkstatus;

    /**
     * \brief Internal 16/20 MHz oscillator is stable.
     */
    bool internal_16_20_MHz_oscillator_is_stable;
};

auto operator<<( std::ostream & stream, internal1620MHzOscillatorIsStable_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkstatus = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkstatus }
                  << ", "
                  << ".internal_16_20_MHz_oscillator_is_stable = " << std::boolalpha << test_case.internal_16_20_MHz_oscillator_is_stable
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_is_stable()
 *        test fixture.
 */
class internal1620MHzOscillatorIsStable :
    public TestWithParam<internal1620MHzOscillatorIsStable_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_is_stable()
 *        works properly.
 */
TEST_P( internal1620MHzOscillatorIsStable, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkstatus, read() ).WillOnce( Return( test_case.mclkstatus ) );

    EXPECT_EQ( clock_controller.internal_16_20_MHz_oscillator_is_stable(), test_case.internal_16_20_MHz_oscillator_is_stable );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_is_stable()
 *        test cases.
 */
internal1620MHzOscillatorIsStable_Test_Case const internal1620MHzOscillatorIsStable_TEST_CASES[]{
    // clang-format off

    { 0b0'1'0'0'001'1, false },
    { 0b0'1'0'1'001'1, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, internal1620MHzOscillatorIsStable, ValuesIn( internal1620MHzOscillatorIsStable_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_mode()
 *        test case.
 */
struct internal1620MHzOscillatorMode_Test_Case {
    /**
     * \brief The OSC20MCTRLA register value.
     */
    std::uint8_t osc20mctrla;

    /**
     * \brief The 16/20 MHz oscillator mode.
     */
    Internal_16_20_MHz_Oscillator_Mode internal_16_20_MHz_oscillator_mode;
};

auto operator<<( std::ostream & stream, internal1620MHzOscillatorMode_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".osc20mctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.osc20mctrla }
                  << ", "
                  << ".internal_16_20_MHz_oscillator_mode = " << test_case.internal_16_20_MHz_oscillator_mode
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_mode()
 *        test fixture.
 */
class internal1620MHzOscillatorMode : public TestWithParam<internal1620MHzOscillatorMode_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_mode()
 *        works properly.
 */
TEST_P( internal1620MHzOscillatorMode, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.osc20mctrla, read() ).WillOnce( Return( test_case.osc20mctrla ) );

    EXPECT_EQ( clock_controller.internal_16_20_MHz_oscillator_mode(), test_case.internal_16_20_MHz_oscillator_mode );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_mode()
 *        test cases.
 */
internal1620MHzOscillatorMode_Test_Case const internal1620MHzOscillatorMode_TEST_CASES[]{
    // clang-format off

    { 0b100010'0'1, Internal_16_20_MHz_Oscillator_Mode::NORMAL    },
    { 0b100010'1'1, Internal_16_20_MHz_Oscillator_Mode::FORCED_ON },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, internal1620MHzOscillatorMode, ValuesIn( internal1620MHzOscillatorMode_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_16_20_MHz_oscillator_mode()
 *        test case.
 */
struct setInternal1620MHzOscillatorMode_Test_Case {
    /**
     * \brief The desired internal 16/20 MHz oscillator mode.
     */
    Internal_16_20_MHz_Oscillator_Mode mode;

    /**
     * \brief The OSC20MCTRLA register value.
     */
    std::uint8_t osc20mctrla;
};

auto operator<<( std::ostream & stream, setInternal1620MHzOscillatorMode_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mode = " << test_case.mode
                  << ", "
                  << ".osc20mctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.osc20mctrla }
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_16_20_MHz_oscillator_mode()
 *        test fixture.
 */
class setInternal1620MHzOscillatorMode :
    public TestWithParam<setInternal1620MHzOscillatorMode_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_16_20_MHz_oscillator_mode()
 *        works properly.
 */
TEST_P( setInternal1620MHzOscillatorMode, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.osc20mctrla, write( test_case.osc20mctrla ) );

    clock_controller.set_internal_16_20_MHz_oscillator_mode( test_case.mode );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_16_20_MHz_oscillator_mode()
 *        test cases.
 */
setInternal1620MHzOscillatorMode_Test_Case const setInternal1620MHzOscillatorMode_TEST_CASES[]{
    // clang-format off

    { Internal_16_20_MHz_Oscillator_Mode::NORMAL,    0b000000'0'0 },
    { Internal_16_20_MHz_Oscillator_Mode::FORCED_ON, 0b000000'1'0 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, setInternal1620MHzOscillatorMode, ValuesIn( setInternal1620MHzOscillatorMode_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_calibration_settings_are_locked()
 *        test case.
 */
struct internal1620MHzOscillatorCalibrationSettingsAreLocked_Test_Case {
    /**
     * \brief The OSC20MCALIBB register value.
     */
    std::uint8_t osc20mcalibb;

    /**
     * \brief Internal 16/20 MHz oscillator calibration settings are locked.
     */
    bool internal_16_20_MHz_oscillator_calibration_settings_are_locked;
};

auto operator<<( std::ostream & stream, internal1620MHzOscillatorCalibrationSettingsAreLocked_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".osc20mcalibb = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.osc20mcalibb }
                  << ", "
                  << ".internal_16_20_MHz_oscillator_calibration_settings_are_locked = " << std::boolalpha << test_case.internal_16_20_MHz_oscillator_calibration_settings_are_locked
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_calibration_settings_are_locked()
 *        test fixture.
 */
class internal1620MHzOscillatorCalibrationSettingsAreLocked :
    public TestWithParam<internal1620MHzOscillatorCalibrationSettingsAreLocked_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_calibration_settings_are_locked()
 *        works properly.
 */
TEST_P( internal1620MHzOscillatorCalibrationSettingsAreLocked, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.osc20mcalibb, read() ).WillOnce( Return( test_case.osc20mcalibb ) );

    EXPECT_EQ(
        clock_controller.internal_16_20_MHz_oscillator_calibration_settings_are_locked(),
        test_case.internal_16_20_MHz_oscillator_calibration_settings_are_locked );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_calibration_settings_are_locked()
 *        test cases.
 */
internal1620MHzOscillatorCalibrationSettingsAreLocked_Test_Case const internal1620MHzOscillatorCalibrationSettingsAreLocked_TEST_CASES[]{
    // clang-format off

    { 0b0'110'1001, false },
    { 0b1'110'1001, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(
    ,
    internal1620MHzOscillatorCalibrationSettingsAreLocked,
    ValuesIn( internal1620MHzOscillatorCalibrationSettingsAreLocked_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_internal_16_20_MHz_oscillator_calibration_settings()
 *        test case.
 */
struct configureInternal1620MHzOscillatorCalibrationSettings_Test_Case {
    /**
     * \brief The desired internal 16/20 MHz oscillator calibration value.
     */
    std::uint_fast8_t value;

    /**
     * \brief The desired internal 16/20 MHz oscillator temperature coefficient.
     */
    std::uint_fast8_t temperature_coefficient;
};

auto operator<<( std::ostream & stream, configureInternal1620MHzOscillatorCalibrationSettings_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".value = " << std::bitset<7>{ test_case.value }
                  << ", "
                  << ".temperature_coefficient = " << std::bitset<4>{ test_case.temperature_coefficient }
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_internal_16_20_MHz_oscillator_calibration_settings()
 *        test fixture.
 */
class configureInternal1620MHzOscillatorCalibrationSettings :
    public TestWithParam<configureInternal1620MHzOscillatorCalibrationSettings_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::configure_internal_16_20_MHz_oscillator_calibration_settings()
 *        works properly.
 */
TEST_P( configureInternal1620MHzOscillatorCalibrationSettings, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.osc20mcaliba, write( test_case.value ) );
    EXPECT_CALL( clkctrl.osc20mcalibb, write( test_case.temperature_coefficient ) );

    clock_controller.configure_internal_16_20_MHz_oscillator_calibration_settings(
        test_case.value, test_case.temperature_coefficient );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_internal_16_20_MHz_oscillator_calibration_settings()
 *        test cases.
 */
configureInternal1620MHzOscillatorCalibrationSettings_Test_Case const configureInternal1620MHzOscillatorCalibrationSettings_TEST_CASES[]{
    // clang-format off

    { 0b0000000, 0b1101 },
    { 0b1111111, 0b1101 },

    { 0b1011000, 0b0000 },
    { 0b1011000, 0b1111 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(
    ,
    configureInternal1620MHzOscillatorCalibrationSettings,
    ValuesIn( configureInternal1620MHzOscillatorCalibrationSettings_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_is_stable()
 *        test case.
 */
struct internal32768kHzUltraLowPowerOscillatorIsStable_Test_Case {
    /**
     * \brief The MCLKSTATUS register value.
     */
    std::uint8_t mclkstatus;

    /**
     * \brief Internal 32.768 kHz ultra low-power oscillator is stable.
     */
    bool internal_32_768_kHz_ultra_low_power_oscillator_is_stable;
};

auto operator<<( std::ostream & stream, internal32768kHzUltraLowPowerOscillatorIsStable_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkstatus = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkstatus }
                  << ", "
                  << ".internal_32_768_kHz_ultra_low_power_oscillator_is_stable = " << std::boolalpha << test_case.internal_32_768_kHz_ultra_low_power_oscillator_is_stable
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_is_stable()
 *        test fixture.
 */
class internal32768kHzUltraLowPowerOscillatorIsStable :
    public TestWithParam<internal32768kHzUltraLowPowerOscillatorIsStable_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_is_stable()
 *        works properly.
 */
TEST_P( internal32768kHzUltraLowPowerOscillatorIsStable, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkstatus, read() ).WillOnce( Return( test_case.mclkstatus ) );

    EXPECT_EQ(
        clock_controller.internal_32_768_kHz_ultra_low_power_oscillator_is_stable(),
        test_case.internal_32_768_kHz_ultra_low_power_oscillator_is_stable );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_is_stable()
 *        test cases.
 */
internal32768kHzUltraLowPowerOscillatorIsStable_Test_Case const internal32768kHzUltraLowPowerOscillatorIsStable_TEST_CASES[]{
    // clang-format off

    { 0b0'0'0'1'101'1, false },
    { 0b0'0'1'1'101'1, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, internal32768kHzUltraLowPowerOscillatorIsStable, ValuesIn( internal32768kHzUltraLowPowerOscillatorIsStable_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_mode()
 *        test case.
 */
struct internal32768kHzUltraLowPowerOscillatorMode_Test_Case {
    /**
     * \brief The OSC32KCTRLA register value.
     */
    std::uint8_t osc32kctrla;

    /**
     * \brief The 16/20 MHz oscillator mode.
     */
    Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode internal_32_768_kHz_ultra_low_power_oscillator_mode;
};

auto operator<<( std::ostream & stream, internal32768kHzUltraLowPowerOscillatorMode_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".osc32kctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.osc32kctrla }
                  << ", "
                  << ".internal_32_768_kHz_ultra_low_power_oscillator_mode = " << test_case.internal_32_768_kHz_ultra_low_power_oscillator_mode
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_mode()
 *        test fixture.
 */
class internal32768kHzUltraLowPowerOscillatorMode :
    public TestWithParam<internal32768kHzUltraLowPowerOscillatorMode_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_mode()
 *        works properly.
 */
TEST_P( internal32768kHzUltraLowPowerOscillatorMode, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.osc32kctrla, read() ).WillOnce( Return( test_case.osc32kctrla ) );

    EXPECT_EQ(
        clock_controller.internal_32_768_kHz_ultra_low_power_oscillator_mode(),
        test_case.internal_32_768_kHz_ultra_low_power_oscillator_mode );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_mode()
 *        test cases.
 */
internal32768kHzUltraLowPowerOscillatorMode_Test_Case const internal32768kHzUltraLowPowerOscillatorMode_TEST_CASES[]{
    // clang-format off

    { 0b010111'0'1, Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode::NORMAL    },
    { 0b010111'1'1, Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode::FORCED_ON },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, internal32768kHzUltraLowPowerOscillatorMode, ValuesIn( internal32768kHzUltraLowPowerOscillatorMode_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_32_768_kHz_ultra_low_power_oscillator_mode()
 *        test case.
 */
struct setInternal32768kHzUltraLowPowerOscillatorMode_Test_Case {
    /**
     * \brief The desired internal 32.768 kHz ultra low-power oscillator mode.
     */
    Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode mode;

    /**
     * \brief The OSC32KCTRLA register value.
     */
    std::uint8_t osc32kctrla;
};

auto operator<<( std::ostream & stream, setInternal32768kHzUltraLowPowerOscillatorMode_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mode = " << test_case.mode
                  << ", "
                  << ".osc32kctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.osc32kctrla }
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_32_768_kHz_ultra_low_power_oscillator_mode()
 *        test fixture.
 */
class setInternal32768kHzUltraLowPowerOscillatorMode :
    public TestWithParam<setInternal32768kHzUltraLowPowerOscillatorMode_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_32_768_kHz_ultra_low_power_oscillator_mode()
 *        works properly.
 */
TEST_P( setInternal32768kHzUltraLowPowerOscillatorMode, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.osc32kctrla, write( test_case.osc32kctrla ) );

    clock_controller.set_internal_32_768_kHz_ultra_low_power_oscillator_mode( test_case.mode );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_32_768_kHz_ultra_low_power_oscillator_mode()
 *        test cases.
 */
setInternal32768kHzUltraLowPowerOscillatorMode_Test_Case const setInternal32768kHzUltraLowPowerOscillatorMode_TEST_CASES[]{
    // clang-format off

    { Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode::NORMAL,    0b000000'0'0 },
    { Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode::FORCED_ON, 0b000000'1'0 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, setInternal32768kHzUltraLowPowerOscillatorMode, ValuesIn( setInternal32768kHzUltraLowPowerOscillatorMode_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_cystal_oscillator_is_stable()
 *        test case.
 */
struct external32768kHzCrystalOscillatorIsStable_Test_Case {
    /**
     * \brief The MCLKSTATUS register value.
     */
    std::uint8_t mclkstatus;

    /**
     * \brief External 32.768 kHz crystal oscillator is stable.
     */
    bool external_32_768_kHz_cystal_oscillator_is_stable;
};

auto operator<<( std::ostream & stream, external32768kHzCrystalOscillatorIsStable_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkstatus = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkstatus }
                  << ", "
                  << ".external_32_768_kHz_cystal_oscillator_is_stable = " << std::boolalpha << test_case.external_32_768_kHz_cystal_oscillator_is_stable
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_cystal_oscillator_is_stable()
 *        test fixture.
 */
class external32768kHzCrystalOscillatorIsStable :
    public TestWithParam<external32768kHzCrystalOscillatorIsStable_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_cystal_oscillator_is_stable()
 *        works properly.
 */
TEST_P( external32768kHzCrystalOscillatorIsStable, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkstatus, read() ).WillOnce( Return( test_case.mclkstatus ) );

    EXPECT_EQ(
        clock_controller.external_32_768_kHz_cystal_oscillator_is_stable(),
        test_case.external_32_768_kHz_cystal_oscillator_is_stable );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_cystal_oscillator_is_stable()
 *        test cases.
 */
external32768kHzCrystalOscillatorIsStable_Test_Case const external32768kHzCrystalOscillatorIsStable_TEST_CASES[]{
    // clang-format off

    { 0b0'0'0'1'101'1, false },
    { 0b0'1'0'1'101'1, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, external32768kHzCrystalOscillatorIsStable, ValuesIn( external32768kHzCrystalOscillatorIsStable_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_source()
 *        test case.
 */
struct external32768kHzCrystalOscillatorSource_Test_Case {
    /**
     * \brief The XOSC32KCTRLA register value.
     */
    std::uint8_t xosc32kctrla;

    /**
     * \brief The external 32.768 kHz crystal oscillator source.
     */
    External_32_768_kHz_Crystal_Oscillator_Source external_32_768_kHz_crystal_oscillator_source;
};

auto operator<<( std::ostream & stream, external32768kHzCrystalOscillatorSource_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".xosc32kctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.xosc32kctrla }
                  << ", "
                  << ".external_32_768_kHz_crystal_oscillator_source = " << test_case.external_32_768_kHz_crystal_oscillator_source
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_source()
 *        test fixture.
 */
class external32768kHzCrystalOscillatorSource :
    public TestWithParam<external32768kHzCrystalOscillatorSource_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_source()
 *        works properly.
 */
TEST_P( external32768kHzCrystalOscillatorSource, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.xosc32kctrla, read() ).WillOnce( Return( test_case.xosc32kctrla ) );

    EXPECT_EQ(
        clock_controller.external_32_768_kHz_crystal_oscillator_source(),
        test_case.external_32_768_kHz_crystal_oscillator_source );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_source()
 *        test cases.
 */
external32768kHzCrystalOscillatorSource_Test_Case const external32768kHzCrystalOscillatorSource_TEST_CASES[]{
    // clang-format off

    { 0b11'01'0'0'1'0, External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL },
    { 0b11'01'0'1'1'0, External_32_768_kHz_Crystal_Oscillator_Source::CLOCK   },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, external32768kHzCrystalOscillatorSource, ValuesIn( external32768kHzCrystalOscillatorSource_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_start_up_time()
 *        test case.
 */
struct external32768kHzCrystalOscillatorStartUpTime_Test_Case {
    /**
     * \brief The XOSC32KCTRLA register value.
     */
    std::uint8_t xosc32kctrla;

    /**
     * \brief The external 32.768 kHz crystal oscillator start-up time.
     */
    External_32_768_kHz_Crystal_Oscillator_Start_Up_Time external_32_768_kHz_crystal_oscillator_start_up_time;
};

auto operator<<( std::ostream & stream, external32768kHzCrystalOscillatorStartUpTime_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".xosc32kctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.xosc32kctrla }
                  << ", "
                  << ".external_32_768_kHz_crystal_oscillator_start_up_time = " << test_case.external_32_768_kHz_crystal_oscillator_start_up_time
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_start_up_time()
 *        test fixture.
 */
class external32768kHzCrystalOscillatorStartUpTime :
    public TestWithParam<external32768kHzCrystalOscillatorStartUpTime_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_start_up_time()
 *        works properly.
 */
TEST_P( external32768kHzCrystalOscillatorStartUpTime, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.xosc32kctrla, read() ).WillOnce( Return( test_case.xosc32kctrla ) );

    EXPECT_EQ(
        clock_controller.external_32_768_kHz_crystal_oscillator_start_up_time(),
        test_case.external_32_768_kHz_crystal_oscillator_start_up_time );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_start_up_time()
 *        test cases.
 */
external32768kHzCrystalOscillatorStartUpTime_Test_Case const external32768kHzCrystalOscillatorStartUpTime_TEST_CASES[]{
    // clang-format off

    { 0b01'00'0'1'1'0, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_1k_CYCLES  },
    { 0b01'01'0'1'1'0, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_16k_CYCLES },
    { 0b01'10'0'1'1'0, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_32k_CYCLES },
    { 0b01'11'0'1'1'0, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_64k_CYCLES },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, external32768kHzCrystalOscillatorStartUpTime, ValuesIn( external32768kHzCrystalOscillatorStartUpTime_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_mode()
 *        test case.
 */
struct external32768kHzCrystalOscillatorMode_Test_Case {
    /**
     * \brief The XOSC32KCTRLA register value.
     */
    std::uint8_t xosc32kctrla;

    /**
     * \brief The external 32.768 kHz crystal oscillator mode.
     */
    External_32_768_kHz_Crystal_Oscillator_Mode external_32_768_kHz_crystal_oscillator_mode;
};

auto operator<<( std::ostream & stream, external32768kHzCrystalOscillatorMode_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".xosc32kctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.xosc32kctrla }
                  << ", "
                  << ".external_32_768_kHz_crystal_oscillator_mode = " << test_case.external_32_768_kHz_crystal_oscillator_mode
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_mode()
 *        test fixture.
 */
class external32768kHzCrystalOscillatorMode :
    public TestWithParam<external32768kHzCrystalOscillatorMode_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_mode()
 *        works properly.
 */
TEST_P( external32768kHzCrystalOscillatorMode, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.xosc32kctrla, read() ).WillOnce( Return( test_case.xosc32kctrla ) );

    EXPECT_EQ(
        clock_controller.external_32_768_kHz_crystal_oscillator_mode(),
        test_case.external_32_768_kHz_crystal_oscillator_mode );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_mode()
 *        test cases.
 */
external32768kHzCrystalOscillatorMode_Test_Case const external32768kHzCrystalOscillatorMode_TEST_CASES[]{
    // clang-format off

    { 0b01'01'0'1'0'0, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL    },
    { 0b01'01'0'1'1'0, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, external32768kHzCrystalOscillatorMode, ValuesIn( external32768kHzCrystalOscillatorMode_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_external_32_768_kHz_crystal_oscillator()
 *        test case.
 */
struct configureExternal32768kHzCrystalOscillator_Test_Case {
    /**
     * \brief The external 32.768 kHz crystal oscillator source.
     */
    External_32_768_kHz_Crystal_Oscillator_Source source;

    /**
     * \brief The external 32.768 kHz crystal oscillator start-up time.
     */
    External_32_768_kHz_Crystal_Oscillator_Start_Up_Time start_up_time;

    /**
     * \brief The desired external 32.768 kHz crystal oscillator mode.
     */
    External_32_768_kHz_Crystal_Oscillator_Mode mode;

    /**
     * \brief The XOSC32KCTRLA register value.
     */
    std::uint8_t xosc32kctrla;
};

auto operator<<( std::ostream & stream, configureExternal32768kHzCrystalOscillator_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".source = " << test_case.source
                  << ", "
                  << ".start_up_time = " << test_case.start_up_time
                  << ", "
                  << ".mode = " << test_case.mode
                  << ", "
                  << ".xosc32kctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.xosc32kctrla }
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_external_32_768_kHz_crystal_oscillator()
 *        test fixture.
 */
class configureExternal32768kHzCrystalOscillator :
    public TestWithParam<configureExternal32768kHzCrystalOscillator_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::configure_external_32_768_kHz_crystal_oscillator()
 *        works properly.
 */
TEST_P( configureExternal32768kHzCrystalOscillator, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.xosc32kctrla, write( test_case.xosc32kctrla ) );

    clock_controller.configure_external_32_768_kHz_crystal_oscillator(
        test_case.source, test_case.start_up_time, test_case.mode );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::configure_external_32_768_kHz_crystal_oscillator()
 *        test cases.
 */
configureExternal32768kHzCrystalOscillator_Test_Case const configureExternal32768kHzCrystalOscillator_TEST_CASES[]{
    // clang-format off

    { External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_1k_CYCLES,  External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL, 0b00'00'0'0'0'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_16k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL, 0b00'01'0'0'0'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_32k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL, 0b00'10'0'0'0'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_64k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL, 0b00'11'0'0'0'0 },

    { External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_1k_CYCLES,  External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'00'0'0'1'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_16k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'01'0'0'1'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_32k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'10'0'0'1'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_64k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'11'0'0'1'0 },

    { External_32_768_kHz_Crystal_Oscillator_Source::CLOCK, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_1k_CYCLES,  External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL, 0b00'00'0'1'0'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CLOCK, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_16k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL, 0b00'01'0'1'0'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CLOCK, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_32k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL, 0b00'10'0'1'0'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CLOCK, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_64k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL, 0b00'11'0'1'0'0 },

    { External_32_768_kHz_Crystal_Oscillator_Source::CLOCK, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_1k_CYCLES,  External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'00'0'1'1'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CLOCK, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_16k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'01'0'1'1'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CLOCK, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_32k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'10'0'1'1'0 },
    { External_32_768_kHz_Crystal_Oscillator_Source::CLOCK, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_64k_CYCLES, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'11'0'1'1'0 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, configureExternal32768kHzCrystalOscillator, ValuesIn( configureExternal32768kHzCrystalOscillator_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_external_32_768_kHz_crystal_oscillator_mode()
 *        test case.
 */
struct setExternal32768kHzCrystalOscillatorMode_Test_Case {
    /**
     * \brief The initial XOSC32KCTRLA register value.
     */
    std::uint8_t xosc32kctrla_initial;

    /**
     * \brief The desired external 32.768 kHz crystal oscillator mode.
     */
    External_32_768_kHz_Crystal_Oscillator_Mode mode;

    /**
     * \brief The final XOSC32KCTRLA register value.
     */
    std::uint8_t xosc32kctrla_final;
};

auto operator<<( std::ostream & stream, setExternal32768kHzCrystalOscillatorMode_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".xosc32kctrla_initial = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.xosc32kctrla_initial }
                  << ", "
                  << ".mode = " << test_case.mode
                  << ", "
                  << ".xosc32kctrla_final = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.xosc32kctrla_final }
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_external_32_768_kHz_crystal_oscillator_mode()
 *        test fixture.
 */
class setExternal32768kHzCrystalOscillatorMode :
    public TestWithParam<setExternal32768kHzCrystalOscillatorMode_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::set_external_32_768_kHz_crystal_oscillator_mode()
 *        works properly.
 */
TEST_P( setExternal32768kHzCrystalOscillatorMode, worksProperly )
{
    auto const test_case = GetParam();

    auto const in_sequence = InSequence{};

    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.xosc32kctrla, read() ).WillOnce( Return( test_case.xosc32kctrla_initial ) );
    EXPECT_CALL( clkctrl.xosc32kctrla, write( test_case.xosc32kctrla_final ) );

    clock_controller.set_external_32_768_kHz_crystal_oscillator_mode( test_case.mode );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::set_external_32_768_kHz_crystal_oscillator_mode()
 *        test cases.
 */
setExternal32768kHzCrystalOscillatorMode_Test_Case const setExternal32768kHzCrystalOscillatorMode_TEST_CASES[]{
    // clang-format off

    { 0b00'00'0'0'0'0, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL,    0b00'00'0'0'0'0 },
    { 0b00'00'0'0'0'0, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b00'00'0'0'1'0 },

    { 0b11'11'1'1'1'1, External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL,    0b11'11'1'1'0'1 },
    { 0b11'11'1'1'1'1, External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON, 0b11'11'1'1'1'1 },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, setExternal32768kHzCrystalOscillatorMode, ValuesIn( setExternal32768kHzCrystalOscillatorMode_TEST_CASES ) );

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_is_enabled()
 *        test case.
 */
struct external32768kHzCrystalOscillatorIsEnabled_Test_Case {
    /**
     * \brief The XOSC32KCTRLA register value.
     */
    std::uint8_t xosc32kctrla;

    /**
     * \brief External 32.768 kHz crystal oscillator is enabled.
     */
    bool external_32_768_kHz_crystal_oscillator_is_enabled;
};

auto operator<<( std::ostream & stream, external32768kHzCrystalOscillatorIsEnabled_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".xosc32kctrla = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.xosc32kctrla }
                  << ", "
                  << ".external_32_768_kHz_crystal_oscillator_is_enabled = " << std::boolalpha << test_case.external_32_768_kHz_crystal_oscillator_is_enabled
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_is_enabled()
 *        test fixture.
 */
class external32768kHzCrystalOscillatorIsEnabled :
    public TestWithParam<external32768kHzCrystalOscillatorIsEnabled_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_is_enabled()
 *        works properly.
 */
TEST_P( external32768kHzCrystalOscillatorIsEnabled, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.xosc32kctrla, read() ).WillOnce( Return( test_case.xosc32kctrla ) );

    EXPECT_EQ(
        clock_controller.external_32_768_kHz_crystal_oscillator_is_enabled(),
        test_case.external_32_768_kHz_crystal_oscillator_is_enabled );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_is_enabled()
 *        test cases.
 */
external32768kHzCrystalOscillatorIsEnabled_Test_Case const external32768kHzCrystalOscillatorIsEnabled_TEST_CASES[]{
    // clang-format off

    { 0b00'10'1'1'0'0, false },
    { 0b00'10'1'1'0'1, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, external32768kHzCrystalOscillatorIsEnabled, ValuesIn( external32768kHzCrystalOscillatorIsEnabled_TEST_CASES ) );

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::enable_external_32_768_kHz_crystal_oscillator()
 *        works properly.
 */
TEST( enableExternal32768kHzCrystalOscillator, worksProperly )
{
    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.xosc32kctrla, write_or( 0b00'00'0'0'0'1 ) );

    clock_controller.enable_external_32_768_kHz_crystal_oscillator();
}

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::disable_external_32_768_kHz_crystal_oscillator()
 *        works properly.
 */
TEST( disableExternal32768kHzCrystalOscillator, worksProperly )
{
    auto clkctrl = CLKCTRL{};

    auto clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.xosc32kctrla, write_and( 0b11'11'1'1'1'0 ) );

    clock_controller.disable_external_32_768_kHz_crystal_oscillator();
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_clock_is_stable()
 *        test case.
 */
struct externalClockIsStable_Test_Case {
    /**
     * \brief The MCLKSTATUS register value.
     */
    std::uint8_t mclkstatus;

    /**
     * \brief External clock is stable.
     */
    bool external_clock_is_stable;
};

auto operator<<( std::ostream & stream, externalClockIsStable_Test_Case const & test_case )
    -> std::ostream &
{
    // clang-format off

    return stream << "{ "
                  << ".mclkstatus = 0b" << std::bitset<std::numeric_limits<std::uint8_t>::digits>{ test_case.mclkstatus }
                  << ", "
                  << ".external_clock_is_stable = " << std::boolalpha << test_case.external_clock_is_stable
                  << " }";

    // clang-format on
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_clock_is_stable()
 *        test fixture.
 */
class externalClockIsStable : public TestWithParam<externalClockIsStable_Test_Case> {
};

/**
 * \brief Verify
 *        microlibrary::Microchip::megaAVR0::Clock_Controller::external_clock_is_stable()
 *        works properly.
 */
TEST_P( externalClockIsStable, worksProperly )
{
    auto const test_case = GetParam();

    auto clkctrl = CLKCTRL{};

    auto const clock_controller = Clock_Controller{ Not_Null{ &clkctrl } };

    EXPECT_CALL( clkctrl.mclkstatus, read() ).WillOnce( Return( test_case.mclkstatus ) );

    EXPECT_EQ( clock_controller.external_clock_is_stable(), test_case.external_clock_is_stable );
}

/**
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller::external_clock_is_stable()
 *        test cases.
 */
externalClockIsStable_Test_Case const externalClockIsStable_TEST_CASES[]{
    // clang-format off

    { 0b0'0'0'1'110'1, false },
    { 0b1'0'0'1'110'1, true  },

    // clang-format on
};

INSTANTIATE_TEST_SUITE_P(, externalClockIsStable, ValuesIn( externalClockIsStable_TEST_CASES ) );
