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

} // namespace microlibrary

namespace microlibrary::Testing::Automated {

auto operator<<( std::ostream & stream, Mock_Error error ) -> std::ostream &
{
    return stream << "::microlibrary::Testing::Automated::Mock_Error::" << std::dec
                  << static_cast<std::uint_fast16_t>( error );
}

} // namespace microlibrary::Testing::Automated
