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
 * \brief microlibrary::ROM interface.
 */

#ifndef MICROLIBRARY_HIL_ROM_H
#define MICROLIBRARY_HIL_ROM_H

#include <avr-libcpp/pgmspace>
#include <cstddef>

namespace microlibrary::ROM {

/**
 * \brief microlibrary::ROM::String is HIL defined.
 */
#define MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED 1

/**
 * \brief A pointer to a null-terminated string stored in ROM.
 */
class String {
  public:
    /**
     * \brief Constructor.
     */
    constexpr String() noexcept = default;

    /**
     * \brief Constructor.
     *
     * \attention To create a string literal stored in ROM, use MICROLIBRARY_ROM_STRING().
     *
     * \param[in] string The underlying ROM character pointer.
     */
    constexpr explicit String( char const * string ) noexcept : m_string{ string }
    {
    }

    /**
     * \brief Constructor.
     *
     * \param[in] source The source of the move.
     */
    constexpr String( String && source ) noexcept = default;

    /**
     * \brief Constructor.
     *
     * \param[in] original The original to copy.
     */
    constexpr String( String const & original ) noexcept = default;

    /**
     * \brief Destructor.
     */
    ~String() noexcept = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( String && expression ) noexcept -> String & = default;

    /**
     * \brief Assignment operator.
     *
     * \param[in] expression The expression to be assigned.
     *
     * \return The assigned to object.
     */
    constexpr auto operator=( String const & expression ) noexcept -> String & = default;

    /**
     * \brief Access the pointed to character.
     *
     * \return The pointed to character.
     */
    auto operator*() const noexcept -> char
    {
        return pgm_read_byte( m_string );
    }

    /**
     * \brief Access the character at the specified offset from the pointed to character.
     *
     * \param[in] offset The offset of the character to access.
     *
     * \return The character at the specified offset from the pointed to character.
     */
    auto operator[]( std::ptrdiff_t offset ) const noexcept -> char
    {
        return pgm_read_byte( m_string + offset );
    }

    /**
     * \brief Advance the pointer to the next character.
     *
     * \return The advanced pointer.
     */
    constexpr auto operator++() noexcept -> String &
    {
        ++m_string;

        return *this;
    }

    /**
     * \brief Retreat the pointer to the previous character.
     *
     * \return The retreated pointer.
     */
    constexpr auto operator--() noexcept -> String &
    {
        --m_string;

        return *this;
    }

    /**
     * \brief Advance the pointer to the next character.
     *
     * \return A copy of the pointer that was made before it was advanced.
     */
    constexpr auto operator++( int ) noexcept -> String
    {
        auto string = m_string;

        ++m_string;

        return String{ string };
    }

    /**
     * \brief Retreat the pointer to the previous character.
     *
     * \return A copy of the pointer that was made before it was retreated.
     */
    constexpr auto operator--( int ) noexcept -> String
    {
        auto string = m_string;

        --m_string;

        return String{ string };
    }

    /**
     * \brief Advance a copy of the pointer n characters.
     *
     * \param[in] n The number of characters to advance the copy of the pointer.
     *
     * \return A copy of the pointer that has been advanced n characters.
     */
    constexpr auto operator+( std::ptrdiff_t n ) const noexcept -> String
    {
        return String{ m_string + n };
    }

    /**
     * \brief Retreat a copy of the pointer n characters.
     *
     * \param[in] n The number of characters to retreat the copy of the pointer.
     *
     * \return A copy of the pointer that has been retreated n characters.
     */
    constexpr auto operator-( std::ptrdiff_t n ) const noexcept -> String
    {
        return String{ m_string - n };
    }

    /**
     * \brief Advance the pointer n characters.
     *
     * \param[in] n The number of characters to advance the pointer.
     *
     * \return The advanced pointer.
     */
    constexpr auto operator+=( std::ptrdiff_t n ) noexcept -> String &
    {
        m_string += n;

        return *this;
    }

    /**
     * \brief Retreat the pointer n characters.
     *
     * \param[in] n The number of characters to retreat the pointer.
     *
     * \return The retreated pointer.
     */
    constexpr auto operator-=( std::ptrdiff_t n ) noexcept -> String &
    {
        m_string -= n;

        return *this;
    }

  private:
    /**
     * \brief The underlying ROM character pointer.
     */
    char const * m_string{ nullptr };

    friend constexpr auto operator==( String lhs, String rhs ) noexcept -> bool;

    friend constexpr auto operator<( String lhs, String rhs ) noexcept -> bool;

    friend constexpr auto operator+( std::ptrdiff_t n, String string ) noexcept -> String;

    friend constexpr auto operator-( std::ptrdiff_t n, String string ) noexcept -> String;

    friend constexpr auto operator-( String lhs, String rhs ) noexcept -> std::ptrdiff_t;
};

/**
 * \brief Equality operator.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is equal to rhs.
 * \return false if lhs is not equal to rhs.
 */
constexpr auto operator==( String lhs, String rhs ) noexcept -> bool
{
    return lhs.m_string == rhs.m_string;
}

/**
 * \brief Inequality operator.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is not equal to rhs.
 * \return false if lhs is equal to rhs.
 */
constexpr auto operator!=( String lhs, String rhs ) noexcept -> bool
{
    return not( lhs == rhs );
}

/**
 * \brief Less than operator.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is less than rhs.
 * \return false if lhs is not less than rhs.
 */
constexpr auto operator<( String lhs, String rhs ) noexcept -> bool
{
    return lhs.m_string < rhs.m_string;
}

/**
 * \brief Greater than operator.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is greater than rhs.
 * \return false if lhs is not greater than rhs.
 */
constexpr auto operator>( String lhs, String rhs ) noexcept -> bool
{
    return rhs < lhs;
}

/**
 * \brief Less than or equal to operator.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is less than or equal to rhs.
 * \return false if lhs is not less than or equal to rhs.
 */
constexpr auto operator<=( String lhs, String rhs ) noexcept -> bool
{
    return not( lhs > rhs );
}

/**
 * \brief Greater than or equal to operator.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] lhs The left hand side of the comparison.
 * \param[in] rhs The right hand side of the comparison.
 *
 * \return true if lhs is greater than or equal to rhs.
 * \return false if lhs is not greater than or equal to rhs.
 */
constexpr auto operator>=( String lhs, String rhs ) noexcept -> bool
{
    return not( lhs < rhs );
}

/**
 * \brief Advance a copy of the pointer n characters.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] n The number of characters to advance the copy of the pointer.
 *
 * \return A copy of the pointer that has been advanced n characters.
 */
constexpr auto operator+( std::ptrdiff_t n, String string ) noexcept -> String
{
    return String{ string.m_string + n };
}

/**
 * \brief Retreat a copy of the pointer n characters.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] n The number of characters to retreat the copy of the pointer.
 *
 * \return A copy of the pointer that has been retreated n characters.
 */
constexpr auto operator-( std::ptrdiff_t n, String string ) noexcept -> String
{
    return String{ string.m_string - n };
}

/**
 * \brief Get the distance between two pointers.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] lhs The left hand side of the operation.
 * \param[in] rhs The right hand side of the operation.
 *
 * \return The distance between the two pointers.
 */
constexpr auto operator-( String lhs, String rhs ) noexcept -> std::ptrdiff_t
{
    return lhs.m_string - rhs.m_string;
}

/**
 * \brief Create a string literal stored in ROM.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] string The string literal to store in ROM.
 *
 * \return A pointer to the string literal stored in ROM.
 */
#define MICROLIBRARY_ROM_STRING( string ) \
    ( ::microlibrary::ROM::String{ PSTR( string ) } )

} // namespace microlibrary::ROM

#endif // MICROLIBRARY_HIL_ROM_H
