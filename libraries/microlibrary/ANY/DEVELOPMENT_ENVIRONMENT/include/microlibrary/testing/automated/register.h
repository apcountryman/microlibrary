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
 * \brief microlibrary register automated testing facilities interface.
 */

#ifndef MICROLIBRARY_TESTING_AUTOMATED_REGISTER_H
#define MICROLIBRARY_TESTING_AUTOMATED_REGISTER_H

#include <type_traits>

#include "gmock/gmock.h"

namespace microlibrary::Testing::Automated {

/**
 * \brief Mock register.
 *
 * \tparam T The register's underlying integer type.
 */
template<typename T>
class Mock_Register {
  public:
    static_assert( std::is_integral_v<T> );

    using Type = T;

    Mock_Register() = default;

    Mock_Register( Mock_Register && ) = delete;

    Mock_Register( Mock_Register const & ) = delete;

    ~Mock_Register() noexcept = default;

    auto operator=( Mock_Register && ) = delete;

    auto operator=( Mock_Register const & ) = delete;

    MOCK_METHOD( Type, read, () );

    MOCK_METHOD( void, write, ( Type ) );
    MOCK_METHOD( void, write_and, ( Type ) );
    MOCK_METHOD( void, write_or, ( Type ) );
    MOCK_METHOD( void, write_xor, ( Type ) );

    operator Type() const noexcept
    {
        return read();
    }

    auto operator=( Type expression ) noexcept -> Mock_Register &
    {
        write( expression );

        return *this;
    }

    auto operator&=( Type expression ) noexcept -> Mock_Register &
    {
        write_and( expression );

        return *this;
    }

    auto operator|=( Type expression ) noexcept -> Mock_Register &
    {
        write_or( expression );

        return *this;
    }

    auto operator^=( Type expression ) noexcept -> Mock_Register &
    {
        write_xor( expression );

        return *this;
    }
};

} // namespace microlibrary::Testing::Automated

#endif // MICROLIBRARY_TESTING_AUTOMATED_REGISTER_H
