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
 * \brief microlibrary Microchip megaAVR 0-series clock automated testing facilities
 *        interface.
 */

#ifndef MICROLIBRARY_TESTING_AUTOMATED_MICROCHIP_MEGAAVR0_CLOCK_H
#define MICROLIBRARY_TESTING_AUTOMATED_MICROCHIP_MEGAAVR0_CLOCK_H

#include <cstdint>
#include <ostream>

#include "gmock/gmock.h"
#include "microlibrary/microchip/megaavr0/clock.h"

namespace microlibrary::Microchip::megaAVR0 {

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the
 *            microlibrary::Microchip::megaAVR0::Clock_Source to.
 * \param[in] clock_source The microlibrary::Microchip::megaAVR0::Clock_Source to write to
 *            the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, Clock_Source clock_source ) -> std::ostream &;

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the
 *            microlibrary::Microchip::megaAVR0::Clock_Prescaler to.
 * \param[in] clock_prescaler_configuration The
 *            microlibrary::Microchip::megaAVR0::Clock_Prescaler to write to the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, Clock_Prescaler clock_prescaler_configuration )
    -> std::ostream &;

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the
 *            microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value to.
 * \param[in] clock_prescaler_value The
 *            microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value to write to the
 *            stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, Clock_Prescaler_Value clock_prescaler_value )
    -> std::ostream &;

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the
 *            microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode to.
 * \param[in] internal_16_20_MHz_oscillator_mode The
 *            microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode to
 *            write to the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, Internal_16_20_MHz_Oscillator_Mode internal_16_20_MHz_oscillator_mode )
    -> std::ostream &;

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the
 *            microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode
 *            to.
 * \param[in] internal_32_768_kHz_ultra_low_power_oscillator_mode The
 *            microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode
 *            to write to the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode internal_32_768_kHz_ultra_low_power_oscillator_mode )
    -> std::ostream &;

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the
 *            microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source
 *            to.
 * \param[in] external_32_768_kHz_crystal_oscillator_source The
 *            microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source
 *            to write to the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, External_32_768_kHz_Crystal_Oscillator_Source external_32_768_kHz_crystal_oscillator_source )
    -> std::ostream &;

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the
 *            microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time
 *            to.
 * \param[in] external_32_768_kHz_crystal_oscillator_start_up_time The
 *            microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time
 *            to write to the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, External_32_768_kHz_Crystal_Oscillator_Start_Up_Time external_32_768_kHz_crystal_oscillator_start_up_time )
    -> std::ostream &;

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the
 *            microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode
 *            to.
 * \param[in] external_32_768_kHz_crystal_oscillator_mode The
 *            microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode
 *            to write to the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, External_32_768_kHz_Crystal_Oscillator_Mode external_32_768_kHz_crystal_oscillator_mode )
    -> std::ostream &;

} // namespace microlibrary::Microchip::megaAVR0

namespace microlibrary::Testing::Automated::Microchip::megaAVR0 {

/**
 * \brief Mock clock controller.
 */
class Mock_Clock_Controller {
  public:
    Mock_Clock_Controller() = default;

    Mock_Clock_Controller( Mock_Clock_Controller && ) = delete;

    Mock_Clock_Controller( Mock_Clock_Controller const & ) = delete;

    ~Mock_Clock_Controller() noexcept = default;

    auto operator=( Mock_Clock_Controller && ) = delete;

    auto operator=( Mock_Clock_Controller const & ) = delete;

    MOCK_METHOD( bool, clock_source_is_changing, (), ( const ) );

    MOCK_METHOD( ::microlibrary::Microchip::megaAVR0::Clock_Source, clock_source, (), ( const ) );
    MOCK_METHOD( void, set_clock_source, ( ::microlibrary::Microchip::megaAVR0::Clock_Source ) );

    MOCK_METHOD( bool, clock_output_is_enabled, (), ( const ) );
    MOCK_METHOD( void, enable_clock_output, () );
    MOCK_METHOD( void, disable_clock_output, () );

    MOCK_METHOD( bool, clock_prescaler_is_enabled, (), ( const ) );
    MOCK_METHOD( ::microlibrary::Microchip::megaAVR0::Clock_Prescaler, clock_prescaler_configuration, (), ( const ) );
    MOCK_METHOD( ::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value, clock_prescaler_value, (), ( const ) );
    MOCK_METHOD(
        void,
        configure_clock_prescaler,
        ( ::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value,
          ::microlibrary::Microchip::megaAVR0::Clock_Prescaler ) );
    MOCK_METHOD( void, enable_clock_prescaler, () );
    MOCK_METHOD( void, disable_clock_prescaler, () );

    MOCK_METHOD( bool, clock_configuration_is_locked, (), ( const ) );
    MOCK_METHOD( void, lock_clock_configuration, () );

    MOCK_METHOD( bool, internal_16_20_MHz_oscillator_is_stable, (), ( const ) );

    MOCK_METHOD(
        ::microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode,
        internal_16_20_MHz_oscillator_mode,
        (),
        ( const ) );
    MOCK_METHOD( void, set_internal_16_20_MHz_oscillator_mode, ( ::microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode ) );

    MOCK_METHOD( bool, internal_16_20_MHz_oscillator_calibration_settings_are_locked, (), ( const ) );
    MOCK_METHOD( void, configure_internal_16_20_MHz_oscillator_calibration_settings, ( std::uint_fast8_t, std::uint_fast8_t ) );

    MOCK_METHOD( bool, internal_32_768_kHz_ultra_low_power_oscillator_is_stable, (), ( const ) );

    MOCK_METHOD(
        ::microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode,
        internal_32_768_kHz_ultra_low_power_oscillator_mode,
        (),
        ( const ) );
    MOCK_METHOD(
        void,
        set_internal_32_768_kHz_ultra_low_power_oscillator_mode,
        ( ::microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode ) );

    MOCK_METHOD( bool, external_32_768_kHz_cystal_oscillator_is_stable, (), ( const ) );

    MOCK_METHOD(
        ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source,
        external_32_768_kHz_crystal_oscillator_source,
        (),
        ( const ) );
    MOCK_METHOD(
        ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time,
        external_32_768_kHz_crystal_oscillator_start_up_time,
        (),
        ( const ) );
    MOCK_METHOD(
        ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode,
        external_32_768_kHz_crystal_oscillator_mode,
        (),
        ( const ) );
    MOCK_METHOD(
        void,
        configure_external_32_768_kHz_oscillator,
        ( ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source,
          ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time,
          ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode ) );
    MOCK_METHOD(
        void,
        set_external_32_768_kHz_crystal_oscillator_mode,
        ( ::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode ) );

    MOCK_METHOD( bool, external_32_768_kHz_crystal_oscillator_is_enabled, (), ( const ) );
    MOCK_METHOD( void, enable_external_32_768_kHz_crystal_oscillator, () );
    MOCK_METHOD( void, disable_external_32_768_kHz_crystal_oscillator, () );

    MOCK_METHOD( bool, external_clock_is_stable, (), ( const ) );
};

} // namespace microlibrary::Testing::Automated::Microchip::megaAVR0

#endif // MICROLIBRARY_TESTING_AUTOMATED_MICROCHIP_MEGAAVR0_CLOCK_H
