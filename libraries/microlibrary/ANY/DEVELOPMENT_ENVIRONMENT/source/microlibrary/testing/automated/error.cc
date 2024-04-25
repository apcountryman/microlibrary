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
 * \brief microlibrary error identification automated testing facilities implementation.
 */

#include "microlibrary/testing/automated/error.h"

#include <cstdint>
#include <ios>
#include <ostream>
#include <stdexcept>
#include <typeinfo>

namespace microlibrary {

auto operator<<( std::ostream & stream, Error_Code const & error ) -> std::ostream &
{
    if ( &error.category() == &Testing::Automated::Mock_Error_Category::instance() ) {
        return stream << "::microlibrary::Testing::Automated::Mock_Error::" << std::dec
                      << static_cast<std::uint_fast16_t>( error.id() );
    } // if

    if ( typeid( error.category() ) == typeid( Testing::Automated::Mock_Error_Category ) ) {
        return stream << "::microlibrary::Testing::Automated::Mock_Error( " << &error.category()
                      << " )::" << std::dec << static_cast<std::uint_fast16_t>( error.id() );
    } // if

    return stream << error.category().name() << "::" << error.description();
}

auto operator<<( std::ostream & stream, Generic_Error generic_error ) -> std::ostream &
{
    switch ( generic_error ) {
            // clang-format off

        case Generic_Error::INVALID_ARGUMENT: return stream << "::microlibrary::Generic_Error::INVALID_ARGUMENT";
        case Generic_Error::LOGIC_ERROR:      return stream << "::microlibrary::Generic_Error::LOGIC_ERROR";
        case Generic_Error::OUT_OF_RANGE:     return stream << "::microlibrary::Generic_Error::OUT_OF_RANGE";
        case Generic_Error::RUNTIME_ERROR:    return stream << "::microlibrary::Generic_Error::RUNTIME_ERROR";

            // clang-format on
    } // switch

    throw std::invalid_argument{
        "generic_error is not a valid ::microlibrary::Generic_Error"
    };
}

} // namespace microlibrary

namespace microlibrary::Testing::Automated {

auto operator<<( std::ostream & stream, Mock_Error error ) -> std::ostream &
{
    return stream << "::microlibrary::Testing::Automated::Mock_Error::" << std::dec
                  << static_cast<std::uint_fast16_t>( error );
}

} // namespace microlibrary::Testing::Automated
