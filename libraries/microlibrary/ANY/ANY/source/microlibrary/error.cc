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

} // namespace microlibrary
