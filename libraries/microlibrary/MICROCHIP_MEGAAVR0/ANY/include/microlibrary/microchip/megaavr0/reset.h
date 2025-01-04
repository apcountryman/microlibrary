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
 * \brief microlibrary Microchip megaAVR 0-series reset facilities interface.
 */

#ifndef MICROLIBRARY_MICROCHIP_MEGAAVR0_RESET_H
#define MICROLIBRARY_MICROCHIP_MEGAAVR0_RESET_H

#include <cstdint>

#include "microlibrary/error.h"
#include "microlibrary/microchip/megaavr0/peripheral/rstctrl.h"
#include "microlibrary/pointer.h"
#include "microlibrary/postcondition.h"

namespace microlibrary::Microchip::megaAVR0 {

/**
 * \brief Reset source.
 */
class Reset_Source {
  public:
    Reset_Source() = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] rstctrl_rstfr The RSTCTRL peripheral RSTFR value.
     */
    constexpr Reset_Source( std::uint8_t rstctrl_rstfr ) noexcept :
        m_rstctrl_rstfr{ rstctrl_rstfr }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Reset_Source( Reset_Source && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Reset_Source( Reset_Source const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Reset_Source() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Reset_Source && expression ) noexcept -> Reset_Source & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Reset_Source const & expression ) noexcept -> Reset_Source & = default;

    /**
     * \brief Get the RSTCTRL peripheral RSTFR value.
     *
     * \return The RSTCTRL peripheral RSTFR value.
     */
    constexpr auto rstctrl_rstfr() const noexcept -> std::uint8_t
    {
        return m_rstctrl_rstfr;
    }

    /**
     * \brief Check if a power-on reset has occurred.
     *
     * \return true if a power-on reset has occurred.
     * \return false if a power-on reset has not occurred.
     */
    constexpr auto is_power_on_reset() const noexcept -> bool
    {
        return m_rstctrl_rstfr & Peripheral::RSTCTRL::RSTFR::Mask::PORF;
    }

    /**
     * \brief Check if a brown-out reset has occurred.
     *
     * \return true if a brown-out reset has occurred.
     * \return false if a brown-out reset has not occurred.
     */
    constexpr auto is_brown_out_reset() const noexcept -> bool
    {
        return m_rstctrl_rstfr & Peripheral::RSTCTRL::RSTFR::Mask::BORF;
    }

    /**
     * \brief Check if an external reset has occurred.
     *
     * \return true if an external reset has occurred.
     * \return false if an external reset has not occurred.
     */
    constexpr auto is_external_reset() const noexcept -> bool
    {
        return m_rstctrl_rstfr & Peripheral::RSTCTRL::RSTFR::Mask::EXTRF;
    }

    /**
     * \brief Check if a watchdog reset has occurred.
     *
     * \return true if a watchdog reset has occurred.
     * \return false if a watchdog reset has not occurred.
     */
    constexpr auto is_watchdog_reset() const noexcept -> bool
    {
        return m_rstctrl_rstfr & Peripheral::RSTCTRL::RSTFR::Mask::WDRF;
    }

    /**
     * \brief Check if a software reset has occurred.
     *
     * \return true if a software reset has occurred.
     * \return false if a software reset has not occurred.
     */
    constexpr auto is_software_reset() const noexcept -> bool
    {
        return m_rstctrl_rstfr & Peripheral::RSTCTRL::RSTFR::Mask::SWRF;
    }

    /**
     * \brief Check if a UPDI reset has occurred.
     *
     * \return true if a UPDI reset has occurred.
     * \return false if a UPDI reset has not occurred.
     */
    constexpr auto is_updi_reset() const noexcept -> bool
    {
        return m_rstctrl_rstfr & Peripheral::RSTCTRL::RSTFR::Mask::UPDIRF;
    }

  private:
    /**
     * \brief The RSTCTRL peripheral RSTFR value.
     */
    std::uint8_t m_rstctrl_rstfr;
};

/**
 * \brief Reset controller.
 */
class Reset_Controller {
  public:
    Reset_Controller() = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] rstctrl The RSTCTRL peripheral instance.
     */
    constexpr Reset_Controller( Not_Null<Peripheral::RSTCTRL *> rstctrl ) noexcept :
        m_rstctrl{ rstctrl }
    {
    }

    Reset_Controller( Reset_Controller && ) = delete;

    Reset_Controller( Reset_Controller const & ) = delete;

    /**
     * \brief Destructor.
     */
    ~Reset_Controller() noexcept = default;

    auto operator=( Reset_Controller && ) = delete;

    auto operator=( Reset_Controller const & ) = delete;

    /**
     * \brief Get the reset source(s).
     *
     * \return The reset source(s).
     */
    auto reset_source() const noexcept -> Reset_Source
    {
        return { m_rstctrl->rstfr };
    }

    /**
     * \brief Clear the reset source(s).
     */
    void clear_reset_source() noexcept
    {
        m_rstctrl->rstfr = Peripheral::RSTCTRL::RSTFR::Mask::UPDIRF
                           | Peripheral::RSTCTRL::RSTFR::Mask::SWRF
                           | Peripheral::RSTCTRL::RSTFR::Mask::WDRF
                           | Peripheral::RSTCTRL::RSTFR::Mask::EXTRF
                           | Peripheral::RSTCTRL::RSTFR::Mask::BORF
                           | Peripheral::RSTCTRL::RSTFR::Mask::PORF;
    }

    /**
     * \brief Initiate a software reset.
     *
     * \post A software reset is initiated.
     */
    [[noreturn]] void initiate_software_reset() noexcept
    {
        m_rstctrl->swrr = Peripheral::RSTCTRL::SWRR::Mask::SWRE;

        MICROLIBRARY_GUARANTEE_NOT_MET( Generic_Error::LOGIC_ERROR );
    }

  private:
    /**
     * \brief The RSTCTRL peripheral instance.
     */
    Not_Null<Peripheral::RSTCTRL *> m_rstctrl;
};

} // namespace microlibrary::Microchip::megaAVR0

#endif // MICROLIBRARY_MICROCHIP_MEGAAVR0_RESET_H
