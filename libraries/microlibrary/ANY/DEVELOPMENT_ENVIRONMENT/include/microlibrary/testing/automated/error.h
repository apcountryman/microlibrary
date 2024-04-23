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
 * \brief microlibrary error identification automated testing facilities interface.
 */

#ifndef MICROLIBRARY_TESTING_AUTOMATED_AUTOMATED_ERROR_H
#define MICROLIBRARY_TESTING_AUTOMATED_AUTOMATED_ERROR_H

#include "gmock/gmock.h"
#include "microlibrary/error.h"

namespace microlibrary::Testing::Automated {

/**
 * \brief Mock error category.
 */
class Mock_Error_Category : public Error_Category {
  public:
    static auto instance() -> Mock_Error_Category const &
    {
        static auto const category = Mock_Error_Category{};

        return category;
    }

    Mock_Error_Category() = default;

    Mock_Error_Category( Mock_Error_Category && ) = delete;

    Mock_Error_Category( Mock_Error_Category const & ) = delete;

    ~Mock_Error_Category() noexcept = default;

    auto operator=( Mock_Error_Category && ) = delete;

    auto operator=( Mock_Error_Category const & ) = delete;

    MOCK_METHOD( char const *, name, (), ( const, noexcept, override ) );

    MOCK_METHOD( char const *, error_description, ( Error_ID ), ( const, noexcept, override ) );
};

} // namespace microlibrary::Testing::Automated

#endif // MICROLIBRARY_TESTING_AUTOMATED_AUTOMATED_ERROR_H
