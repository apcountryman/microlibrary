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
 * \brief microlibrary::Result interface.
 */

#ifndef MICROLIBRARY_RESULT_H
#define MICROLIBRARY_RESULT_H

#include <new>
#include <type_traits>
#include <utility>

#include "microlibrary/error.h"

namespace microlibrary {

/**
 * \brief Operation result wrapper.
 *
 * \tparam Value_Type Operation succeeded result type.
 */
template<typename Value_Type, bool = std::is_trivially_destructible_v<Value_Type>>
class Result;

/**
 * \brief microlibrary::Result value construction tag.
 *
 * \relatedalso microlibrary::Result
 */
struct Value_Tag {
};

/**
 * \brief microlibrary::Result value construction tag.
 *
 * \relatedalso microlibrary::Result
 */
constexpr auto VALUE = Value_Tag{};

/**
 * \brief microlibrary::Result error construction tag.
 *
 * \relatedalso microlibrary::Result
 */
struct Error_Tag {
};

/**
 * \brief microlibrary::Result error construction tag.
 *
 * \relatedalso microlibrary::Result
 */
constexpr auto ERROR = Error_Tag{};

/**
 * \brief Operation result wrapper specialized for cases where no information is
 *        generated.
 */
template<>
class [[nodiscard]] Result<void, false>
{
  public:
    static_assert( not std::is_trivially_destructible_v<void> );
    static_assert( std::is_trivially_destructible_v<Error_Code> );

    /**
     * \brief Operation succeeded result type.
     */
    using Value = void;

    /**
     * \brief Constructor.
     */
    constexpr Result() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \tparam E A type implicitly convertible to microlibrary::Error.
     *
     * \param[in] error The object to construct from.
     */
    template<typename E, typename = typename std::enable_if_t<not std::is_same_v<std::decay_t<E>, Result> and std::is_convertible_v<E, Error_Code>>>
    constexpr Result( E && error, Error_Tag = {} ) noexcept :
        m_is_error{ true },
        m_error{ std::forward<E>( error ) }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam Arguments microlibrary::Error_Code construction argument types.
     *
     * \param[in] arguments microlibrary::Error_Code construction arguments.
     */
    template<typename... Arguments>
    constexpr Result( Error_Tag, Arguments && ... arguments ) noexcept :
        m_is_error{ true },
        m_error{ std::forward<Arguments>( arguments )... }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Result( Result && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Result( Result const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~Result() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Result && expression ) noexcept->Result & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Result const & expression ) noexcept->Result & = default;

    /**
     * \brief Check if the operation result is an error (operation failed).
     *
     * \return true if the operation result is an error (operation failed).
     * \return false if the operation result is not an error (operation succeeded).
     */
    [[nodiscard]] constexpr auto is_error() const noexcept->bool
    {
        return m_is_error;
    }

    /**
     * \brief Access the result of a failed operation.
     *
     * \warning Calling this function on the result of a successful operation results in
     *          undefined behavior.
     *
     * \return The error.
     */
    [[nodiscard]] constexpr auto error() const noexcept->Error_Code const &
    {
        return m_error;
    }

  private:
    /**
     * \brief Result type flag.
     */
    bool m_is_error{ false };

    /**
     * \brief Operation failed result.
     */
    Error_Code m_error{};
};

/**
 * \brief Operation result wrapper specialized for cases where trivially destructible
 *        information is generated.
 *
 * \tparam Value_Type Operation succeeded result type.
 */
template<typename Value_Type>
class [[nodiscard]] Result<Value_Type, true>
{
  public:
    static_assert( std::is_trivially_destructible_v<Value_Type> );
    static_assert( std::is_trivially_destructible_v<Error_Code> );

    /**
     * \brief Operation succeeded result type.
     */
    using Value = Value_Type;

    Result() = delete;

    /**
     * \brief Constructor.
     *
     * \tparam V A type implicitly convertible to Value and not implicitly convertible to
     *         microlibrary::Error_Code.
     *
     * \param[in] value The object to construct from.
     */
    template<typename V, typename = typename std::enable_if_t<not std::is_same_v<std::decay_t<V>, Result> and std::is_convertible_v<V, Value> and not std::is_convertible_v<V, Error_Code>>>
    constexpr Result( V && value, Value_Tag = {} ) noexcept :
        m_is_error{ false },
        m_value{ std::forward<V>( value ) }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam Arguments Value construction argument types.
     *
     * \param[in] arguments Value construction arguments.
     */
    template<typename... Arguments>
    constexpr Result( Value_Tag, Arguments && ... arguments ) noexcept :
        m_is_error{ false },
        m_value{ std::forward<Arguments>( arguments )... }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam E A type implicitly convertible to microlibrary::Error and not implicitly
     *         convertible to Value.
     *
     * \param[in] error The object to construct from.
     */
    template<typename E, typename = typename std::enable_if_t<not std::is_same_v<std::decay_t<E>, Result> and std::is_convertible_v<E, Error_Code> and not std::is_convertible_v<E, Value>>>
    constexpr Result( E && error, Error_Tag = {} ) noexcept :
        m_is_error{ true },
        m_error{ std::forward<E>( error ) }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam Arguments microlibrary::Error_Code construction argument types.
     *
     * \param[in] arguments microlibrary::Error_Code construction arguments.
     */
    template<typename... Arguments>
    constexpr Result( Error_Tag, Arguments && ... arguments ) noexcept :
        m_is_error{ true },
        m_error{ std::forward<Arguments>( arguments )... }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Result( Result && source ) noexcept : m_is_error{ source.m_is_error }
    {
        if ( m_is_error ) {
            new ( &m_error ) Error_Code{ std::move( source.m_error ) };
        } else {
            new ( &m_value ) Value{ std::move( source.m_value ) };
        } // else
    }

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Result( Result const & original ) noexcept :
        m_is_error{ original.m_is_error }
    {
        if ( m_is_error ) {
            new ( &m_error ) Error_Code{ original.m_error };
        } else {
            new ( &m_value ) Value{ original.m_value };
        } // else
    }

    /**
     * \brief Destructor.
     */
    ~Result() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Result && expression ) noexcept->Result &
    {
        if ( &expression != this ) {
            if ( m_is_error == expression.m_is_error ) {
                if ( m_is_error ) {
                    m_error = std::move( expression.m_error );
                } else {
                    m_value = std::move( expression.m_value );
                } // else
            } else {
                if ( m_is_error ) {
                    new ( &m_value ) Value{ std::move( expression.m_value ) };
                } else {
                    new ( &m_error ) Error_Code{ std::move( expression.m_error ) };
                } // else

                m_is_error = expression.m_is_error;
            } // else
        }     // if

        return *this;
    }

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Result const & expression ) noexcept->Result &
    {
        if ( &expression != this ) {
            if ( m_is_error == expression.m_is_error ) {
                if ( m_is_error ) {
                    m_error = expression.m_error;
                } else {
                    m_value = expression.m_value;
                } // else
            } else {
                if ( m_is_error ) {
                    new ( &m_value ) Value{ expression.m_value };
                } else {
                    new ( &m_error ) Error_Code{ expression.m_error };
                } // else

                m_is_error = expression.m_is_error;
            } // else
        }     // if

        return *this;
    }

    /**
     * \brief Check if the operation result is an error (operation failed).
     *
     * \return true if the operation result is an error (operation failed).
     * \return false if the operation result is not an error (operation succeeded).
     */
    [[nodiscard]] constexpr auto is_error() const noexcept->bool
    {
        return m_is_error;
    }

    /**
     * \brief Access the result of a successful operation.
     *
     * \warning Calling this function on the result of a failed operation results in
     *          undefined behavior.
     *
     * \return The generated information.
     */
    [[nodiscard]] constexpr auto value() && noexcept->Value &&
    {
        return static_cast<Value &&>( m_value );
    }

    /**
     * \brief Access the result of a successful operation.
     *
     * \warning Calling this function on the result of a failed operation results in
     *          undefined behavior.
     *
     * \return The generated information.
     */
    [[nodiscard]] constexpr auto value() const && noexcept->Value const &&
    {
        return static_cast<Value const &&>( m_value );
    }

    /**
     * \brief Access the result of a successful operation.
     *
     * \warning Calling this function on the result of a failed operation results in
     *          undefined behavior.
     *
     * \return The generated information.
     */
    [[nodiscard]] constexpr auto value() & noexcept->Value &
    {
        return static_cast<Value &>( m_value );
    }

    /**
     * \brief Access the result of a successful operation.
     *
     * \warning Calling this function on the result of a failed operation results in
     *          undefined behavior.
     *
     * \return The generated information.
     */
    [[nodiscard]] constexpr auto value() const & noexcept->Value const &
    {
        return static_cast<Value const &>( m_value );
    }

    /**
     * \brief Access the result of a failed operation.
     *
     * \warning Calling this function on the result of a successful operation results in
     *          undefined behavior.
     *
     * \return The error.
     */
    [[nodiscard]] constexpr auto error() const noexcept->Error_Code const &
    {
        return m_error;
    }

  private:
    /**
     * \brief Result type flag.
     */
    bool m_is_error;

    union {
        /**
         * \brief Operation succeeded result.
         */
        Value m_value;

        /**
         * \brief Operation failed result.
         */
        Error_Code m_error;
    };
};

/**
 * \brief Operation result wrapper specialized for cases where non-trivially destructible
 *        information is generated.
 *
 * \tparam Value_Type Operation succeeded result type.
 */
template<typename Value_Type>
class [[nodiscard]] Result<Value_Type, false>
{
  public:
    static_assert( not std::is_trivially_destructible_v<Value_Type> );
    static_assert( std::is_trivially_destructible_v<Error_Code> );

    /**
     * \brief Operation succeeded result type.
     */
    using Value = Value_Type;

    Result() = delete;

    /**
     * \brief Constructor.
     *
     * \tparam V A type implicitly convertible to Value and not implicitly convertible to
     *         microlibrary::Error_Code.
     *
     * \param[in] value The object to construct from.
     */
    template<typename V, typename = typename std::enable_if_t<not std::is_same_v<std::decay_t<V>, Result> and std::is_convertible_v<V, Value> and not std::is_convertible_v<V, Error_Code>>>
    constexpr Result( V && value, Value_Tag = {} ) noexcept :
        m_is_error{ false },
        m_value{ std::forward<V>( value ) }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam Arguments Value construction argument types.
     *
     * \param[in] arguments Value construction arguments.
     */
    template<typename... Arguments>
    constexpr Result( Value_Tag, Arguments && ... arguments ) noexcept :
        m_is_error{ false },
        m_value{ std::forward<Arguments>( arguments )... }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam E A type implicitly convertible to microlibrary::Error and not implicitly
     *         convertible to Value.
     *
     * \param[in] error The object to construct from.
     */
    template<typename E, typename = typename std::enable_if_t<not std::is_same_v<std::decay_t<E>, Result> and std::is_convertible_v<E, Error_Code> and not std::is_convertible_v<E, Value>>>
    constexpr Result( E && error, Error_Tag = {} ) noexcept :
        m_is_error{ true },
        m_error{ std::forward<E>( error ) }
    {
    }

    /**
     * \brief Constructor.
     *
     * \tparam Arguments microlibrary::Error_Code construction argument types.
     *
     * \param[in] arguments microlibrary::Error_Code construction arguments.
     */
    template<typename... Arguments>
    constexpr Result( Error_Tag, Arguments && ... arguments ) noexcept :
        m_is_error{ true },
        m_error{ std::forward<Arguments>( arguments )... }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr Result( Result && source ) noexcept : m_is_error{ source.m_is_error }
    {
        if ( m_is_error ) {
            new ( &m_error ) Error_Code{ std::move( source.m_error ) };
        } else {
            new ( &m_value ) Value{ std::move( source.m_value ) };
        } // else
    }

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr Result( Result const & original ) noexcept :
        m_is_error{ original.m_is_error }
    {
        if ( m_is_error ) {
            new ( &m_error ) Error_Code{ original.m_error };
        } else {
            new ( &m_value ) Value{ original.m_value };
        } // else
    }

    /**
     * \brief Destructor.
     */
    ~Result() noexcept
    {
        if ( not m_is_error ) {
            m_value.~Value();
        } // if
    }

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Result && expression ) noexcept->Result &
    {
        if ( &expression != this ) {
            if ( m_is_error == expression.m_is_error ) {
                if ( m_is_error ) {
                    m_error = std::move( expression.m_error );
                } else {
                    m_value = std::move( expression.m_value );
                } // else
            } else {
                if ( m_is_error ) {
                    new ( &m_value ) Value{ std::move( expression.m_value ) };
                } else {
                    m_value.~Value();
                    new ( &m_error ) Error_Code{ std::move( expression.m_error ) };
                } // else

                m_is_error = expression.m_is_error;
            } // else
        }     // if

        return *this;
    }

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( Result const & expression ) noexcept->Result &
    {
        if ( &expression != this ) {
            if ( m_is_error == expression.m_is_error ) {
                if ( m_is_error ) {
                    m_error = expression.m_error;
                } else {
                    m_value = expression.m_value;
                } // else
            } else {
                if ( m_is_error ) {
                    new ( &m_value ) Value{ expression.m_value };
                } else {
                    m_value.~Value();
                    new ( &m_error ) Error_Code{ expression.m_error };
                } // else

                m_is_error = expression.m_is_error;
            } // else
        }     // if

        return *this;
    }

    /**
     * \brief Check if the operation result is an error (operation failed).
     *
     * \return true if the operation result is an error (operation failed).
     * \return false if the operation result is not an error (operation succeeded).
     */
    [[nodiscard]] constexpr auto is_error() const noexcept->bool
    {
        return m_is_error;
    }

    /**
     * \brief Access the result of a successful operation.
     *
     * \warning Calling this function on the result of a failed operation results in
     *          undefined behavior.
     *
     * \return The generated information.
     */
    [[nodiscard]] constexpr auto value() && noexcept->Value &&
    {
        return static_cast<Value &&>( m_value );
    }

    /**
     * \brief Access the result of a successful operation.
     *
     * \warning Calling this function on the result of a failed operation results in
     *          undefined behavior.
     *
     * \return The generated information.
     */
    [[nodiscard]] constexpr auto value() const && noexcept->Value const &&
    {
        return static_cast<Value const &&>( m_value );
    }

    /**
     * \brief Access the result of a successful operation.
     *
     * \warning Calling this function on the result of a failed operation results in
     *          undefined behavior.
     *
     * \return The generated information.
     */
    [[nodiscard]] constexpr auto value() & noexcept->Value &
    {
        return static_cast<Value &>( m_value );
    }

    /**
     * \brief Access the result of a successful operation.
     *
     * \warning Calling this function on the result of a failed operation results in
     *          undefined behavior.
     *
     * \return The generated information.
     */
    [[nodiscard]] constexpr auto value() const & noexcept->Value const &
    {
        return static_cast<Value const &>( m_value );
    }

    /**
     * \brief Access the result of a failed operation.
     *
     * \warning Calling this function on the result of a successful operation results in
     *          undefined behavior.
     *
     * \return The error.
     */
    [[nodiscard]] constexpr auto error() const noexcept->Error_Code const &
    {
        return m_error;
    }

  private:
    /**
     * \brief Result type flag.
     */
    bool m_is_error;

    union {
        /**
         * \brief Operation succeeded result.
         */
        Value m_value;

        /**
         * \brief Operation failed result.
         */
        Error_Code m_error;
    };
};

} // namespace microlibrary

#endif // MICROLIBRARY_RESULT_H
