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
 * \brief microlibrary register facilities interface.
 */

#ifndef MICROLIBRARY_REGISTER_H
#define MICROLIBRARY_REGISTER_H

#include <type_traits>

#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
#include "microlibrary/testing/automated/register.h"
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

namespace microlibrary {

#if MICROLIBRARY_TARGET_IS_HARDWARE
#define MICROLIBRARY_PACKED_REGISTER __attribute__( ( __packed__ ) )
#else // MICROLIBRARY_TARGET_IS_HARDWARE
#define MICROLIBRARY_PACKED_REGISTER
#endif // MICROLIBRARY_TARGET_IS_HARDWARE

/**
 * \brief Register.
 *
 * \tparam T The register's underlying integer type.
 */
template<typename T>
#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
using Register = Testing::Automated::Mock_Register<T>;
#else  // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
class MICROLIBRARY_PACKED_REGISTER Register {
  public:
    static_assert( std::is_integral_v<T> );

    /**
     * \brief The register's underlying integer type.
     */
    using Type = T;

    Register() = delete;

    Register( Register && ) = delete;

    Register( Register const & ) = delete;

    ~Register() = delete;

    auto operator=( Register && ) = delete;

    auto operator=( Register const & ) = delete;

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
    auto operator=( Type expression ) noexcept -> Register &
    {
        m_register = expression;

        return *this;
    }

    /**
     * \brief Bitwise AND assignment operator.
     *
     * \param[in] expression The expression to bitwise AND into the register.
     *
     * \return The assigned to object.
     */
    auto operator&=( Type expression ) noexcept -> Register &
    {
        m_register &= expression;

        return *this;
    }

    /**
     * \brief Bitwise OR assignment operator.
     *
     * \param[in] expression The expression to bitwise OR into the register.
     *
     * \return The assigned to object.
     */
    auto operator|=( Type expression ) noexcept -> Register &
    {
        m_register |= expression;

        return *this;
    }

    /**
     * \brief Bitwise XOR assignment operator.
     *
     * \param[in] expression The expression to bitwise XOR into the register.
     *
     * \return The assigned to object.
     */
    auto operator^=( Type expression ) noexcept -> Register &
    {
        m_register ^= expression;

        return *this;
    }

  private:
    /**
     * \brief The register.
     */
    Type volatile m_register;
};
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

/**
 * \brief Reserved register.
 *
 * \tparam T The register's underlying integer type.
 */
template<typename T>
class MICROLIBRARY_PACKED_REGISTER Reserved_Register {
  public:
    static_assert( std::is_integral_v<T> );

    /**
     * \brief The register's underlying integer type.
     */
    using Type = T;

    Reserved_Register() = delete;

    Reserved_Register( Reserved_Register && ) = delete;

    Reserved_Register( Reserved_Register const & ) = delete;

    ~Reserved_Register() = delete;

    auto operator=( Reserved_Register && ) = delete;

    auto operator=( Reserved_Register const & ) = delete;

  private:
    /**
     * \brief The register.
     */
    Type volatile m_register;
};

/**
 * \brief Read-only register.
 *
 * \tparam T The register's underlying integer type.
 */
template<typename T>
#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
using Read_Only_Register = Testing::Automated::Mock_Read_Only_Register<T>;
#else  // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
class MICROLIBRARY_PACKED_REGISTER Read_Only_Register {
  public:
    static_assert( std::is_integral_v<T> );

    /**
     * \brief The register's underlying integer type.
     */
    using Type = T;

    Read_Only_Register() = delete;

    Read_Only_Register( Read_Only_Register && ) = delete;

    Read_Only_Register( Read_Only_Register const & ) = delete;

    ~Read_Only_Register() = delete;

    auto operator=( Read_Only_Register && ) = delete;

    auto operator=( Read_Only_Register const & ) = delete;

    /**
     * \brief Read the register.
     *
     * \return The register contents.
     */
    operator Type() const noexcept
    {
        return m_register;
    }

  private:
    /**
     * \brief The register.
     */
    Type const volatile m_register;
};
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

} // namespace microlibrary

#endif // MICROLIBRARY_REGISTER_H
