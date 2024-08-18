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
 * \brief microlibrary Microchip megaAVR 0-series register facilities interface.
 */

#ifndef MICROLIBRARY_MICROCHIP_MEGAAVR0_REGISTER_H
#define MICROLIBRARY_MICROCHIP_MEGAAVR0_REGISTER_H

#include <cstdint>
#include <type_traits>

#include "microlibrary/enum.h"
#include "microlibrary/register.h"

#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
#include "microlibrary/testing/automated/register.h"
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

namespace microlibrary::Microchip::megaAVR0 {

/**
 * \brief CPU peripheral CCP register key.
 */
enum class CPU_CCP_Key : std::uint8_t {
    SPM   = 0x9D, ///< Allow self-programming.
    IOREG = 0xD8, ///< Unlock protected I/O registers.
};

/**
 * \brief Protected register
 *
 * \tparam T The register's underlying integral type (must be std::uint8_t).
 * \tparam CPU_CCP_KEY The register's CPU peripheral CCP register key.
 */
template<typename T, CPU_CCP_Key CPU_CCP_KEY>
#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
using Protected_Register = Testing::Automated::Mock_Register<T>;
#else // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
class MICROLIBRARY_PACKED_REGISTER Protected_Register {
  public:
    static_assert( std::is_same_v<T, std::uint8_t> );

    /**
     * \brief The register's underlying integer type.
     */
    using Type = T;

    Protected_Register() = delete;

    Protected_Register( Protected_Register && ) = delete;

    Protected_Register( Protected_Register const & ) = delete;

    ~Protected_Register() = delete;

    auto operator=( Protected_Register && ) = delete;

    auto operator=( Protected_Register const & ) = delete;

    /**
     * \brief Read the register.
     *
     * \return The register contents.
     */
    operator Type() const noexcept
    {
        return m_register;
    }

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to assign to the register.
     *
     * \return The assigned to object.
     */
    auto operator=( Type expression ) noexcept -> Protected_Register &
    {
        write( expression );

        return *this;
    }

    /**
     * \brief Bitwise AND assignment operator.
     *
     * \param[in] expression The expression to bitwise AND into the register.
     *
     * \return The assigned to object.
     */
    auto operator&=( Type expression ) noexcept -> Protected_Register &
    {
        write( m_register & expression );

        return *this;
    }

    /**
     * \brief Bitwise OR assignment operator.
     *
     * \param[in] expression The expression to bitwise OR into the register.
     *
     * \return The assigned to object.
     */
    auto operator|=( Type expression ) noexcept -> Protected_Register &
    {
        write( m_register | expression );

        return *this;
    }

    /**
     * \brief Bitwise XOR assignment operator.
     *
     * \param[in] expression The expression to bitwise XOR into the register.
     *
     * \return The assigned to object.
     */
    auto operator^=( Type expression ) noexcept -> Protected_Register &
    {
        write( m_register ^ expression );

        return *this;
    }

  private:
    /**
     * \brief CPU peripheral address.
     */
    static constexpr auto CPU_ADDRESS = std::uintptr_t{ 0x0030 };

    /**
     * \brief CPU peripheral CCP register offset.
     */
    static constexpr auto CPU_CCP_OFFSET = std::uint8_t{ 0x04 };

    /**
     * \brief CPU peripheral CCP register address.
     */
    static constexpr auto CPU_CCP_ADDRESS = std::uintptr_t{ CPU_ADDRESS + CPU_CCP_OFFSET };

    /**
     * \brief The register.
     */
    Type volatile m_register;

    /**
     * \brief Write to the register.
     *
     * \param[in] data The data to write to the register.
     */
    void write( Type data ) noexcept
    {
#if MICROLIBRARY_TARGET_IS_HARDWARE
        asm volatile(
            "out %[cpu_ccp_address], %[cpu_ccp_unlock_protected_registers] \n\t"
            "sts %[protected_register_address], %[protected_register_data]"
            :
            : [ cpu_ccp_address ] "I"( CPU_CCP_ADDRESS ),
              [ cpu_ccp_unlock_protected_registers ] "d"( to_underlying( CPU_CCP_KEY ) ),
              [ protected_register_address ] "n"( &m_register ),
              [ protected_register_data ] "r"( data ) );
#else  // MICROLIBRARY_TARGET_IS_HARDWARE
        m_register = data;
#endif // MICROLIBRARY_TARGET_IS_HARDWARE
    }
};
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

} // namespace microlibrary::Microchip::megaAVR0

#endif // MICROLIBRARY_MICROCHIP_MEGAAVR0_REGISTER_H
