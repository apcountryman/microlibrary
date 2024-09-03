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
 * \brief microlibrary::Microchip::megaAVR0::Clock_Controller interface.
 */

#ifndef MICROLIBRARY_MICROCHIP_MEGAAVR0_CLOCK_CONTROLLER_H
#define MICROLIBRARY_MICROCHIP_MEGAAVR0_CLOCK_CONTROLLER_H

#include <cstdint>

#include "microlibrary/error.h"
#include "microlibrary/integer.h"
#include "microlibrary/microchip/megaavr0/peripheral/clkctrl.h"
#include "microlibrary/pointer.h"
#include "microlibrary/precondition.h"

namespace microlibrary::Microchip::megaAVR0 {

/**
 * \brief Clock source.
 */
enum class Clock_Source : std::uint8_t {
    INTERNAL_16_20_MHz_OSCILLATOR                  = Peripheral::CLKCTRL::MCLKCTRLA::CLKSEL_OSC20M, ///< Internal 16/20 MHz oscillator.
    INTERNAL_32_768_kHz_ULTRA_LOW_POWER_OSCILLATOR = Peripheral::CLKCTRL::MCLKCTRLA::CLKSEL_OSCULP32K, ///< 32.768 kHz ultra low-power oscillator.
    EXTERNAL_32_768_kHz_CRYSTAL_OSCILLATOR         = Peripheral::CLKCTRL::MCLKCTRLA::CLKSEL_XOSC32K, ///< External 32.768 kHz crystal oscillator.
    EXTERNAL_CLOCK = Peripheral::CLKCTRL::MCLKCTRLA::CLKSEL_EXTCLK, ///< External clock.
};

/**
 * \brief Clock prescaler configuration.
 */
enum class Clock_Prescaler : std::uint8_t {
    DISABLED = 0b0 << Peripheral::CLKCTRL::MCLKCTRLB::Bit::PEN, ///< Disabled.
    ENABLED  = 0b1 << Peripheral::CLKCTRL::MCLKCTRLB::Bit::PEN, ///< Enabled.
};

/**
 * \brief Clock prescaler value.
 */
enum class Clock_Prescaler_Value : std::uint8_t {
    _2  = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV2,  ///< 2.
    _4  = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV4,  ///< 4.
    _6  = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV6,  ///< 6.
    _8  = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV8,  ///< 8.
    _10 = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV10, ///< 10.
    _12 = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV12, ///< 12.
    _16 = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV16, ///< 16.
    _24 = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV24, ///< 24.
    _32 = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV32, ///< 32.
    _48 = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV48, ///< 48.
    _64 = Peripheral::CLKCTRL::MCLKCTRLB::PDIV_DIV64, ///< 64.
};

/**
 * \brief Internal 16/20 MHz oscillator mode.
 */
enum class Internal_16_20_MHz_Oscillator_Mode : std::uint8_t {
    NORMAL    = 0b0 << Peripheral::CLKCTRL::OSC20MCTRLA::Bit::RUNSTDBY, ///< Normal.
    FORCED_ON = 0b1 << Peripheral::CLKCTRL::OSC20MCTRLA::Bit::RUNSTDBY, ///< Forced on.
};

/**
 * \brief Internal 32.768 kHz ultra low-power oscillator mode.
 */
enum class Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode : std::uint8_t {
    NORMAL    = 0b0 << Peripheral::CLKCTRL::OSC32KCTRLA::Bit::RUNSTDBY, ///< Normal.
    FORCED_ON = 0b1 << Peripheral::CLKCTRL::OSC32KCTRLA::Bit::RUNSTDBY, ///< Forced on.
};

/**
 * \brief External 32.768 kHz crystal oscillator source.
 */
enum class External_32_768_kHz_Crystal_Oscillator_Source : std::uint8_t {
    CRYSTAL = 0b0 << Peripheral::CLKCTRL::XOSC32KCTRLA::Bit::SEL, ///< Crystal.
    CLOCK   = 0b1 << Peripheral::CLKCTRL::XOSC32KCTRLA::Bit::SEL, ///< Clock.
};

/**
 * \brief External 32.768 kHz crystal oscillator start-up time.
 */
enum class External_32_768_kHz_Crystal_Oscillator_Start_Up_Time : std::uint8_t {
    _1k_CYCLES  = Peripheral::CLKCTRL::XOSC32KCTRLA::CSUT_1K,  ///< 1k cycles.
    _16k_CYCLES = Peripheral::CLKCTRL::XOSC32KCTRLA::CSUT_16K, ///< 16k cycles.
    _32k_CYCLES = Peripheral::CLKCTRL::XOSC32KCTRLA::CSUT_32K, ///< 32k cycles.
    _64k_CYCLES = Peripheral::CLKCTRL::XOSC32KCTRLA::CSUT_64K, ///< 64k cycles.
};

/**
 * \brief External 32.768 kHz crystal oscillator mode.
 */
enum class External_32_768_kHz_Crystal_Oscillator_Mode : std::uint8_t {
    NORMAL    = 0b0 << Peripheral::CLKCTRL::XOSC32KCTRLA::Bit::RUNSTDBY, ///< Normal.
    FORCED_ON = 0b1 << Peripheral::CLKCTRL::XOSC32KCTRLA::Bit::RUNSTDBY, ///< Forced on.
};

/**
 * \brief Clock controller.
 */
class Clock_Controller {
  public:
    Clock_Controller() = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] clkctrl The CLKCTRL peripheral instance.
     */
    constexpr Clock_Controller( Not_Null<Peripheral::CLKCTRL *> clkctrl ) noexcept :
        m_clkctrl{ clkctrl }
    {
    }

    Clock_Controller( Clock_Controller && ) = delete;

    Clock_Controller( Clock_Controller const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~Clock_Controller() noexcept = default;

    auto operator=( Clock_Controller && ) = delete;

    auto operator=( Clock_Controller const & ) = delete;

    /**
     * \brief Check if the clock source is changing.
     *
     * \return true if the clock source is changing.
     * \return false if the clock source is not changing.
     */
    auto clock_source_is_changing() const noexcept -> bool
    {
        return m_clkctrl->mclkstatus & Peripheral::CLKCTRL::MCLKSTATUS::Mask::SOSC;
    }

    /**
     * \brief Get the clock source.
     *
     * \return The clock source.
     */
    auto clock_source() const noexcept -> Clock_Source
    {
        return static_cast<Clock_Source>(
            m_clkctrl->mclkctrla & Peripheral::CLKCTRL::MCLKCTRLA::Mask::CLKSEL );
    }

    /**
     * \brief Set the clock source.
     *
     * \param[in] source The desired clock source.
     */
    void set_clock_source( Clock_Source source ) noexcept
    {
        m_clkctrl->mclkctrla = ( m_clkctrl->mclkctrla & ~Peripheral::CLKCTRL::MCLKCTRLA::Mask::CLKSEL )
                               | to_underlying( source );
    }

    /**
     * \brief Check if clock output is enabled.
     *
     * \return true if clock output is enabled.
     * \return false if clock output is not enabled.
     */
    auto clock_output_is_enabled() const noexcept -> bool
    {
        return m_clkctrl->mclkctrla & Peripheral::CLKCTRL::MCLKCTRLA::Mask::CLKOUT;
    }

    /**
     * \brief Enable clock output.
     */
    void enable_clock_output() noexcept
    {
        m_clkctrl->mclkctrla |= Peripheral::CLKCTRL::MCLKCTRLA::Mask::CLKOUT;
    }

    /**
     * \brief Disable clock output.
     */
    void disable_clock_output() noexcept
    {
        m_clkctrl->mclkctrla &= static_cast<std::uint8_t>( ~Peripheral::CLKCTRL::MCLKCTRLA::Mask::CLKOUT );
    }

    /**
     * \brief Check if the clock prescaler enabled.
     *
     * \return true if the clock prescaler enabled.
     * \return false if the clock prescaler is not enabled.
     */
    auto clock_prescaler_is_enabled() const noexcept -> bool
    {
        return m_clkctrl->mclkctrlb & Peripheral::CLKCTRL::MCLKCTRLB::Mask::PEN;
    }

    /**
     * \brief Get the clock prescaler configuration.
     *
     * \return The clock prescaler configuration.
     */
    auto clock_prescaler_configuration() const noexcept -> Clock_Prescaler
    {
        return static_cast<Clock_Prescaler>(
            m_clkctrl->mclkctrlb & Peripheral::CLKCTRL::MCLKCTRLB::Mask::PEN );
    }

    /**
     * \brief Get the clock prescaler value.
     *
     * \return The clock prescaler value.
     */
    auto clock_prescaler_value() const noexcept -> Clock_Prescaler_Value
    {
        return static_cast<Clock_Prescaler_Value>(
            m_clkctrl->mclkctrlb & Peripheral::CLKCTRL::MCLKCTRLB::Mask::PDIV );
    }

    /**
     * \brief Configure the clock prescaler.
     *
     * \param[in] value The desired clock prescaler value.
     * \param[in] configuration The desired clock prescaler configuration.
     */
    void configure_clock_prescaler( Clock_Prescaler_Value value, Clock_Prescaler configuration ) noexcept
    {
        m_clkctrl->mclkctrlb = to_underlying( value ) | to_underlying( configuration );
    }

    /**
     * \brief Enable the clock prescaler.
     */
    void enable_clock_prescaler() noexcept
    {
        m_clkctrl->mclkctrlb |= Peripheral::CLKCTRL::MCLKCTRLB::Mask::PEN;
    }

    /**
     * \brief Disable the clock prescaler.
     */
    void disable_clock_prescaler() noexcept
    {
        m_clkctrl->mclkctrlb &= ~Peripheral::CLKCTRL::MCLKCTRLB::Mask::PEN;
    }

    /**
     * \brief Check if the clock configuration is locked.
     *
     * \return true if the clock configuration is locked.
     * \return false if the clock configuration is not locked.
     */
    auto clock_configuration_is_locked() const noexcept -> bool
    {
        return m_clkctrl->mclklock & Peripheral::CLKCTRL::MCLKLOCK::Mask::LOCKEN;
    }

    /**
     * \brief Lock the clock configuration.
     */
    void lock_clock_configuration() noexcept
    {
        m_clkctrl->mclklock = Peripheral::CLKCTRL::MCLKLOCK::Mask::LOCKEN;
    }

    /**
     * \brief Check if the internal 16/20 MHz oscillator is stable.
     *
     * \return true if the internal 16/20 MHz oscillator is stable.
     * \return false if the internal 16/20 MHz oscillator is not stable.
     */
    auto internal_16_20_MHz_oscillator_is_stable() const noexcept -> bool
    {
        return m_clkctrl->mclkstatus & Peripheral::CLKCTRL::MCLKSTATUS::Mask::OSC20MS;
    }

    /**
     * \brief Get the internal 16/20 MHz oscillator mode.
     *
     * \return The internal 16/20 MHz oscillator mode.
     */
    auto internal_16_20_MHz_oscillator_mode() const noexcept -> Internal_16_20_MHz_Oscillator_Mode
    {
        return static_cast<Internal_16_20_MHz_Oscillator_Mode>(
            m_clkctrl->osc20mctrla & Peripheral::CLKCTRL::OSC20MCTRLA::Mask::RUNSTDBY );
    }

    /**
     * \brief Set the internal 16/20 MHz oscillator mode.
     *
     * \param[in] mode The desired internal 16/20 MHz oscillator mode.
     */
    void set_internal_16_20_MHz_oscillator_mode( Internal_16_20_MHz_Oscillator_Mode mode ) noexcept
    {
        m_clkctrl->osc20mctrla = to_underlying( mode );
    }

    /**
     * \brief Check if the internal 16/20 MHz oscillator calibration settings are locked.
     *
     * \return true if the internal 16/20 MHz oscillator calibration settings are locked.
     * \return false if the internal 16/20 MHz oscillator calibration settings are not
     *         locked.
     */
    auto internal_16_20_MHz_oscillator_calibration_settings_are_locked() const noexcept -> bool
    {
        return m_clkctrl->osc20mcalibb & Peripheral::CLKCTRL::OSC20MCALIBB::Mask::LOCK;
    }

    /**
     * \brief Configure the internal 16/20 MHz oscillator calibration settings.
     *
     * \param[in] value The desired internal 16/20 MHz oscillator calibration value (value
     *            to be written to the CLKCTRL.OSC20MCALIBA register's CAL20M field).
     * \param[in] temperature_coefficient The desired internal 16/20 MHz oscillator
     *            temperature coefficient (value to be written to the CLKCTRL.OSC20MCALIBB
     *            register's TEMPCAL20M field).
     *
     * \pre value is a valid internal 16/20 MHz oscillator calibration value.
     * \pre temperature_coefficient is a valid internal 16/20 MHz oscillator temperature
     *      coefficient.
     */
    void configure_internal_16_20_MHz_oscillator_calibration_settings( std::uint_fast8_t value, std::uint_fast8_t temperature_coefficient ) noexcept
    {
        MICROLIBRARY_EXPECT(
            ( value & ~Peripheral::CLKCTRL::OSC20MCALIBA::Mask::CAL20M ) == 0,
            Generic_Error::INVALID_ARGUMENT );
        MICROLIBRARY_EXPECT(
            ( temperature_coefficient & ~Peripheral::CLKCTRL::OSC20MCALIBB::Mask::TEMPCAL20M ) == 0,
            Generic_Error::INVALID_ARGUMENT );

        m_clkctrl->osc20mcaliba = value;
        m_clkctrl->osc20mcalibb = temperature_coefficient;
    }

    /**
     * \brief Check if the internal 32.768 kHz ultra low-power oscillator is stable.
     *
     * \return true if the internal 32.768 kHz ultra low-power oscillator is stable.
     * \return false if the internal 32.768 kHz ultra low-power oscillator is not stable.
     */
    auto internal_32_768_kHz_ultra_low_power_oscillator_is_stable() const noexcept -> bool
    {
        return m_clkctrl->mclkstatus & Peripheral::CLKCTRL::MCLKSTATUS::Mask::OSC32KS;
    }

    /**
     * \brief Get the internal 32.768 kHz ultra low-power oscillator mode.
     *
     * \return The internal 32.768 kHz ultra low-power oscillator mode.
     */
    auto internal_32_768_kHz_ultra_low_power_oscillator_mode() const noexcept
        -> Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode
    {
        return static_cast<Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode>(
            m_clkctrl->osc32kctrla & Peripheral::CLKCTRL::OSC32KCTRLA::Mask::RUNSTDBY );
    }

    /**
     * \brief Set the internal 32.768 kHz ultra low-power oscillator mode.
     *
     * \param[in] mode The desired internal 32.768 kHz ultra low-power oscillator mode.
     */
    void set_internal_32_768_kHz_ultra_low_power_oscillator_mode( Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode mode ) noexcept
    {
        m_clkctrl->osc32kctrla = to_underlying( mode );
    }

    /**
     * \brief Check if the external 32.786 kHz crystal oscillator is stable.
     *
     * \return true if the external 32.786 kHz crystal oscillator is stable.
     * \return false if the external 32.786 kHz crystal oscillator is not stable.
     */
    auto external_32_768_kHz_cystal_oscillator_is_stable() const noexcept -> bool
    {
        return m_clkctrl->mclkstatus & Peripheral::CLKCTRL::MCLKSTATUS::Mask::XOSC32KS;
    }

    /**
     * \brief Get the external 32.768 kHz crystal oscillator source.
     *
     * \return The external 32.768 kHz crystal oscillator source.
     */
    auto external_32_768_kHz_crystal_oscillator_source() const noexcept -> External_32_768_kHz_Crystal_Oscillator_Source
    {
        return static_cast<External_32_768_kHz_Crystal_Oscillator_Source>(
            m_clkctrl->xosc32kctrla & Peripheral::CLKCTRL::XOSC32KCTRLA::Mask::SEL );
    }

    /**
     * \brief Get the external 32.768 kHz crystal oscillator start-up time.
     *
     * \return The external 32.768 kHz crystal oscillator start-up time.
     */
    auto external_32_768_kHz_crystal_oscillator_start_up_time() const noexcept
        -> External_32_768_kHz_Crystal_Oscillator_Start_Up_Time
    {
        return static_cast<External_32_768_kHz_Crystal_Oscillator_Start_Up_Time>(
            m_clkctrl->xosc32kctrla & Peripheral::CLKCTRL::XOSC32KCTRLA::Mask::CSUT );
    }

    /**
     * \brief Get the external 32.768 kHz crystal oscillator mode.
     *
     * \return The external 32.768 kHz crystal oscillator mode.
     */
    auto external_32_768_kHz_crystal_oscillator_mode() const noexcept -> External_32_768_kHz_Crystal_Oscillator_Mode
    {
        return static_cast<External_32_768_kHz_Crystal_Oscillator_Mode>(
            m_clkctrl->xosc32kctrla & Peripheral::CLKCTRL::XOSC32KCTRLA::Mask::RUNSTDBY );
    }

    /**
     * \brief Configure the external 32.768 kHz crystal oscillator.
     *
     * \param[in] source The external 32.768 kHz crystal oscillator source.
     * \param[in] start_up_time The external 32.768 kHz crystal oscillator start-up time.
     * \param[in] mode The desired external 32.768 kHz crystal oscillator mode.
     */
    void configure_external_32_768_kHz_crystal_oscillator(
        External_32_768_kHz_Crystal_Oscillator_Source        source,
        External_32_768_kHz_Crystal_Oscillator_Start_Up_Time start_up_time,
        External_32_768_kHz_Crystal_Oscillator_Mode          mode ) noexcept
    {
        m_clkctrl->xosc32kctrla = to_underlying( source ) | to_underlying( start_up_time )
                                  | to_underlying( mode );
    }

    /**
     * \brief Set the external 32.768 kHz crystal oscillator mode.
     *
     * \param[in] mode The desired external 32.768 kHz crystal oscillator mode.
     */
    void set_external_32_768_kHz_crystal_oscillator_mode( External_32_768_kHz_Crystal_Oscillator_Mode mode ) noexcept
    {
        m_clkctrl->xosc32kctrla = ( m_clkctrl->xosc32kctrla
                                    & ~Peripheral::CLKCTRL::XOSC32KCTRLA::Mask::RUNSTDBY )
                                  | to_underlying( mode );
    }

    /**
     * \brief Check if the clock external 32.768 kHz crystal oscillator is enabled.
     *
     * \return true if the clock external 32.768 kHz crystal oscillator is enabled.
     * \return false if the clock external 32.768 kHz crystal oscillator is not enabled.
     */
    auto external_32_768_kHz_crystal_oscillator_is_enabled() const noexcept -> bool
    {
        return m_clkctrl->xosc32kctrla & Peripheral::CLKCTRL::XOSC32KCTRLA::Mask::ENABLE;
    }

    /**
     * \brief Enable the external 32.768 kHz crystal oscillator.
     */
    void enable_external_32_768_kHz_crystal_oscillator() noexcept
    {
        m_clkctrl->xosc32kctrla |= Peripheral::CLKCTRL::XOSC32KCTRLA::Mask::ENABLE;
    }

    /**
     * \brief Disable the external 32.768 kHz crystal oscillator.
     */
    void disable_external_32_768_kHz_crystal_oscillator() noexcept
    {
        m_clkctrl->xosc32kctrla &= ~Peripheral::CLKCTRL::XOSC32KCTRLA::Mask::ENABLE;
    }

    /**
     * \brief Check if the external clock is stable.
     *
     * \return true if the external clock is stable.
     * \return false if the external clock is not stable.
     */
    auto external_clock_is_stable() const noexcept -> bool
    {
        return m_clkctrl->mclkstatus & Peripheral::CLKCTRL::MCLKSTATUS::Mask::EXTS;
    }

  private:
    /**
     * \brief The CLKCTRL peripheral instance.
     */
    Not_Null<Peripheral::CLKCTRL *> m_clkctrl;
};

} // namespace microlibrary::Microchip::megaAVR0

#endif // MICROLIBRARY_MICROCHIP_MEGAAVR0_CLOCK_CONTROLLER_H
