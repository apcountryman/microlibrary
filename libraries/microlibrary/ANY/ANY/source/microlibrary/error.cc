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
 * \brief microlibrary error identification facilities implementation.
 */

#include "microlibrary/error.h"

#include "microlibrary/rom.h"

namespace microlibrary {

#if MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION
auto Error_Category::name() const noexcept -> ROM::String
{
    return MICROLIBRARY_ROM_STRING( "" );
}
#endif // MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION

#if MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION
auto Error_Category::error_description( Error_ID id ) const noexcept -> ROM::String
{
    static_cast<void>( id );

    return MICROLIBRARY_ROM_STRING( "" );
}
#endif // MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION

Error_Code::Default_Error_Category const Error_Code::Default_Error_Category::INSTANCE{};

#if !MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION
auto Error_Code::Default_Error_Category::name() const noexcept -> ROM::String
{
    return MICROLIBRARY_ROM_STRING( "::microlibrary::Default_Error" );
}
#endif // !MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION

#if !MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION
auto Error_Code::Default_Error_Category::error_description( Error_ID id ) const noexcept -> ROM::String
{
    static_cast<void>( id );

    return MICROLIBRARY_ROM_STRING( "UNKNOWN" );
}
#endif // !MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION

Generic_Error_Category const Generic_Error_Category::INSTANCE{};

#if !MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION
auto Generic_Error_Category::name() const noexcept -> ROM::String
{
    return MICROLIBRARY_ROM_STRING( "::microlibrary::Generic_Error" );
}
#endif // !MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION

#if !MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION
auto Generic_Error_Category::error_description( Error_ID id ) const noexcept -> ROM::String
{
    switch ( static_cast<Generic_Error>( id ) ) {
            // clang-format off

        case Generic_Error::INVALID_ARGUMENT: return MICROLIBRARY_ROM_STRING( "INVALID_ARGUMENT" );
        case Generic_Error::LOGIC_ERROR: return MICROLIBRARY_ROM_STRING( "LOGIC_ERROR" );
        case Generic_Error::OUT_OF_RANGE: return MICROLIBRARY_ROM_STRING( "OUT_OF_RANGE" );
        case Generic_Error::RUNTIME_ERROR: return MICROLIBRARY_ROM_STRING( "RUNTIME_ERROR" );

            // clang-format on
    } // switch

    return MICROLIBRARY_ROM_STRING( "UNKNOWN" );
}
#endif // !MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION

} // namespace microlibrary
