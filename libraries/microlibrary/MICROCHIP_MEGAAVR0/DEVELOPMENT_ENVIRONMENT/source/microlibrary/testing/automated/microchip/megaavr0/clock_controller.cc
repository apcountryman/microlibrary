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
 * \brief microlibrary::Testing::Automated::Microchip::megaAVR0::Mock_Clock_Controller
 *        implementation.
 */

#include "microlibrary/testing/automated/microchip/megaavr0/clock_controller.h"

#include <ostream>
#include <stdexcept>

#include "microlibrary/microchip/megaavr0/clock_controller.h"

namespace microlibrary::Microchip::megaAVR0 {

auto operator<<( std::ostream & stream, Clock_Source clock_source ) -> std::ostream &
{
    switch ( clock_source ) {
            // clang-format off

        case Clock_Source::INTERNAL_16_20_MHz_OSCILLATOR: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Source::INTERNAL_16_20_MHz_OSCILLATOR";
        case Clock_Source::INTERNAL_32_768_kHz_ULTRA_LOW_POWER_OSCILLATOR: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Source::INTERNAL_32_768_kHz_ULTRA_LOW_POWER_OSCILLATOR";
        case Clock_Source::EXTERNAL_32_768_kHz_CRYSTAL_OSCILLATOR: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Source::EXTERNAL_32_768_kHz_CRYSTAL_OSCILLATOR";
        case Clock_Source::EXTERNAL_CLOCK: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Source::EXTERNAL_CLOCK";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "clock_source is not a valid ::microlibrary::Microchip::megaAVR0::Clock_Source"
    };
}

auto operator<<( std::ostream & stream, Clock_Prescaler clock_prescaler_configuration ) -> std::ostream &
{
    switch ( clock_prescaler_configuration ) {
            // clang-format off

        case Clock_Prescaler::DISABLED: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler::DISABLED";
        case Clock_Prescaler::ENABLED: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler::ENABLED";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "clock_prescaler_configuration is not a valid "
        "::microlibrary::Microchip::megaAVR0::Clock_Prescaler"
    };
}

auto operator<<( std::ostream & stream, Clock_Prescaler_Value clock_prescaler_value ) -> std::ostream &
{
    switch ( clock_prescaler_value ) {
            // clang-format off

        case Clock_Prescaler_Value::_2: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_2";
        case Clock_Prescaler_Value::_4: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_4";
        case Clock_Prescaler_Value::_6: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_6";
        case Clock_Prescaler_Value::_8: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_8";
        case Clock_Prescaler_Value::_10: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_10";
        case Clock_Prescaler_Value::_12: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_12";
        case Clock_Prescaler_Value::_16: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_16";
        case Clock_Prescaler_Value::_24: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_24";
        case Clock_Prescaler_Value::_32: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_32";
        case Clock_Prescaler_Value::_48: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_48";
        case Clock_Prescaler_Value::_64: return stream << "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value::_64";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "clock_prescaler_value is not a valid "
        "::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value"
    };
}

auto operator<<( std::ostream & stream, Internal_16_20_MHz_Oscillator_Mode internal_16_20_MHz_oscillator_mode )
    -> std::ostream &
{
    switch ( internal_16_20_MHz_oscillator_mode ) {
            // clang-format off

        case Internal_16_20_MHz_Oscillator_Mode::NORMAL: return stream << "::microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode::NORMAL";
        case Internal_16_20_MHz_Oscillator_Mode::FORCED_ON: return stream << "::microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode::FORCED_ON";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "internal_16_20_MHz_oscillator_mode is not a valid "
        "::microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode"
    };
}

auto operator<<( std::ostream & stream, Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode internal_32_768_kHz_ultra_low_power_oscillator_mode )
    -> std::ostream &
{
    switch ( internal_32_768_kHz_ultra_low_power_oscillator_mode ) {
            // clang-format off

        case Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode::NORMAL: return stream << "::microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode::NORMAL";
        case Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode::FORCED_ON: return stream << "::microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode::FORCED_ON";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "internal_32_768_kHz_ultra_low_power_oscillator_mode is not a valid "
        "::microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_"
        "Oscillator_Mode"
    };
}

auto operator<<( std::ostream & stream, External_32_768_kHz_Crystal_Oscillator_Source external_32_768_kHz_crystal_oscillator_source )
    -> std::ostream &
{
    switch ( external_32_768_kHz_crystal_oscillator_source ) {
            // clang-format off

        case External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL: return stream << "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source::CRYSTAL";
        case External_32_768_kHz_Crystal_Oscillator_Source::CLOCK: return stream << "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source::CLOCK";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "external_32_768_kHz_crystal_oscillator_source is not a valid "
        "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_"
        "Source"
    };
}

auto operator<<( std::ostream & stream, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time external_32_768_kHz_crystal_oscillator_start_up_time )
    -> std::ostream &
{
    switch ( external_32_768_kHz_crystal_oscillator_start_up_time ) {
            // clang-format off

        case External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_1k_CYCLES: return stream << "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_1k_CYCLES";
        case External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_16k_CYCLES: return stream << "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_16k_CYCLES";
        case External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_32k_CYCLES: return stream << "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_32k_CYCLES";
        case External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_64k_CYCLES: return stream << "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time::_64k_CYCLES";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "external_32_768_kHz_crystal_oscillator_start_up_time is not a valid "
        "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_"
        "Start_Up_Time"
    };
}

auto operator<<( std::ostream & stream, External_32_768_kHz_Crystal_Oscillator_Mode external_32_768_kHz_crystal_oscillator_mode )
    -> std::ostream &
{
    switch ( external_32_768_kHz_crystal_oscillator_mode ) {
            // clang-format off

        case External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL: return stream << "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode::NORMAL";
        case External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON: return stream << "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode::FORCED_ON";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "external_32_768_kHz_crystal_oscillator_mode is not a valid "
        "::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_"
        "Oscillator_Mode"
    };
}

} // namespace microlibrary::Microchip::megaAVR0
