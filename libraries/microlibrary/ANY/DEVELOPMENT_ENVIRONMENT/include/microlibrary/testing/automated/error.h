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

#include <ostream>
#include <type_traits>

#include "gmock/gmock.h"
#include "microlibrary/enum.h"
#include "microlibrary/error.h"

namespace microlibrary {

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the microlibrary::Error_Code to.
 * \param[in] error The microlibrary::Error_Code to write to the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, Error_Code const & error ) -> std::ostream &;

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the microlibrary::Generic_Error to.
 * \param[in] generic_error The microlibrary::Generic_Error to write to the stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, Generic_Error generic_error ) -> std::ostream &;

} // namespace microlibrary

namespace microlibrary::Testing::Automated {

/**
 * \brief Mock errors.
 *
 * \relatedalso microlibrary::Testing::Automated::Mock_Error_Category
 */
enum class Mock_Error : Error_ID {};

/**
 * \brief Insertion operator.
 *
 * \param[in] stream The stream to write the microlibrary::Testing::Automated::Mock_Error
 *            to.
 * \param[in] error The microlibrary::Testing::Automated::Mock_Error to write to the
 *            stream.
 *
 * \return stream
 */
auto operator<<( std::ostream & stream, Mock_Error error ) -> std::ostream &;

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

/**
 * \brief Construct an error code from a mock error.
 *
 * \relatedalso microlibrary::Testing::Automated::Mock_Error_Category
 *
 * \param[in] error The mock error to construct the error code from.
 *
 * \return The constructed error code.
 */
inline auto make_error_code( Mock_Error error ) noexcept -> Error_Code
{
    return { Mock_Error_Category::instance(), to_underlying( error ) };
}

} // namespace microlibrary::Testing::Automated

namespace microlibrary {

/**
 * \brief microlibrary::Testing::Automated::Mock_Error error code enum registration.
 *
 * \relatedalso microlibrary::Testing::Automated::Mock_Error_Category
 */
template<>
struct is_error_code_enum<Testing::Automated::Mock_Error> : std::true_type {
};

} // namespace microlibrary

#endif // MICROLIBRARY_TESTING_AUTOMATED_AUTOMATED_ERROR_H
