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
 * \brief microlibrary pointer utilities interface.
 */

#ifndef MICROLIBRARY_POINTER_H
#define MICROLIBRARY_POINTER_H

#include <cstddef>
#include <utility>

#include "microlibrary/error.h"
#include "microlibrary/precondition.h"

namespace microlibrary {

/**
 * \brief Not-null pointer wrapper.
 *
 * \tparam Pointer The type of the wrapped pointer.
 *
 * \warning If the wrapped pointer is a move-only smart pointer, a moved from
 *          microlibrary::Not_Null will wrap a null pointer that can only be assigned
 *          to or destroyed.
 */
template<typename Pointer>
class Not_Null {
  public:
    Not_Null() = delete;

    Not_Null( std::nullptr_t ) = delete;

    /**
     * \brief Constructor.
     *
     * \param[in] pointer The pointer to wrap.
     *
     * \pre pointer != nullptr
     */
    constexpr explicit Not_Null( Pointer && pointer ) noexcept :
        m_pointer{ std::move( pointer ) }
    {
        MICROLIBRARY_EXPECT( m_pointer != nullptr, Generic_Error::INVALID_ARGUMENT );
    }

    /**
     * \brief Constructor.
     *
     * \param[in] pointer The pointer to wrap.
     *
     * \warning pointer must not be null.
     */
    constexpr Not_Null( Bypass_Precondition_Expectation_Checks, Pointer && pointer ) noexcept :
        m_pointer{ std::move( pointer ) }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] pointer The pointer to wrap.
     *
     * \pre pointer != nullptr
     */
    constexpr explicit Not_Null( Pointer const & pointer ) noexcept : m_pointer{ pointer }
    {
        MICROLIBRARY_EXPECT( m_pointer != nullptr, Generic_Error::INVALID_ARGUMENT );
    }

    /**
     * \brief Constructor.
     *
     * \param[in] pointer The pointer to wrap.
     *
     * \warning pointer must not be null.
     */
    constexpr Not_Null( Bypass_Precondition_Expectation_Checks, Pointer const & pointer ) noexcept :
        m_pointer{ pointer }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam P The type of pointer to construct from.
     *
     * \param[in] pointer The pointer to wrap.
     *
     * \pre pointer != nullptr
     */
    template<typename P, typename = std::enable_if_t<not std::is_same_v<std::decay_t<P>, Pointer> and std::is_convertible_v<P, Pointer>>>
    constexpr explicit Not_Null( P && pointer ) noexcept :
        m_pointer{ std::forward<P>( pointer ) }
    {
        MICROLIBRARY_EXPECT( m_pointer != nullptr, Generic_Error::INVALID_ARGUMENT );
    }

    /**
     * \brief Constructor.
     *
     * \tparam P The type of pointer to construct from.
     *
     * \param[in] pointer The pointer to wrap.
     *
     * \warning pointer must not be null.
     */
    template<typename P, typename = std::enable_if_t<not std::is_same_v<std::decay_t<P>, Pointer> and std::is_convertible_v<P, Pointer>>>
    constexpr Not_Null( Bypass_Precondition_Expectation_Checks, P && pointer ) noexcept :
        m_pointer{ std::forward<P>( pointer ) }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam P The type of pointer to construct from.
     *
     * \param[in] pointer The pointer to wrap.
     */
    template<typename P, typename = std::enable_if_t<not std::is_same_v<std::decay_t<P>, Pointer> and std::is_convertible_v<P, Pointer>>>
    constexpr explicit Not_Null( Not_Null<P> && pointer ) noexcept :
        m_pointer{ std::forward<Not_Null<P>>( pointer ).get() }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Not_Null( Not_Null && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Not_Null( Not_Null const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Not_Null() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Not_Null && expression ) noexcept -> Not_Null & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Not_Null const & expression ) noexcept -> Not_Null & = default;

    /**
     * \brief Dereference operator.
     *
     * \return The pointed to object.
     */
    constexpr auto & operator*() const noexcept
    {
        return *m_pointer;
    }

    /**
     * \brief Member access operator
     *
     * \return The wrapped pointer.
     */
    constexpr auto operator->() const noexcept -> Pointer const &
    {
        return m_pointer;
    }

    /**
     * \brief Get the wrapped pointer.
     *
     * \return The wrapped pointer.
     */
    [[nodiscard]] constexpr auto get() && noexcept -> Pointer &&
    {
        return static_cast<Pointer &&>( m_pointer );
    }

    /**
     * \brief Get the wrapped pointer.
     *
     * \return The wrapped pointer.
     */
    [[nodiscard]] constexpr auto get() const && noexcept -> Pointer const &&
    {
        return static_cast<Pointer const &&>( m_pointer );
    }

    /**
     * \brief Get the wrapped pointer.
     *
     * \return The wrapped pointer.
     */
    [[nodiscard]] constexpr auto get() & noexcept -> Pointer &
    {
        return static_cast<Pointer &>( m_pointer );
    }

    /**
     * \brief Get the wrapped pointer.
     *
     * \return The wrapped pointer.
     */
    [[nodiscard]] constexpr auto get() const & noexcept -> Pointer const &
    {
        return static_cast<Pointer const &>( m_pointer );
    }

  private:
    /**
     * \brief The wrapped pointer.
     */
    Pointer m_pointer;
};

} // namespace microlibrary

#endif // MICROLIBRARY_POINTER_H
