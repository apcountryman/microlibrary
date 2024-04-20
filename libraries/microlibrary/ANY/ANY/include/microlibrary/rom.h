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

#ifndef MICROLIBRARY_ROM_H
#define MICROLIBRARY_ROM_H

#if __has_include( "microlibrary/hil/rom.h" )
#include "microlibrary/hil/rom.h"
#endif // __has_include( "microlibrary/hil/rom.h" )

/**
 * \brief ROM facilities.
 */
namespace microlibrary::ROM {

#if !MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
/**
 * \brief A handle to a null-terminated string that may be stored in ROM.
 *
 * To create a string literal that can be stored in ROM, use MICROLIBRARY_ROM_STRING().
 *
 * A custom HIL can replace this type with a HIL specific version by doing the following:
 * - Provide a microlibrary-custom library that provides microlibrary/hil/rom.h
 * - Define MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED to be a value that will be evaluated as
 *   true by the preprocessor (e.g. 1) in microlibrary/hil/rom.h
 * - Define the HIL specific version of microlibrary::ROM::String in
 *   microlibrary/hil/rom.h
 */
using String = char const *;
#endif // !MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

#if !MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
/**
 * \brief Create a string literal that can be stored in ROM.
 *
 * \relatedalso microlibrary::ROM::String
 *
 * \param[in] string The string literal that can be stored in ROM.
 *
 * \return A handle to the string literal that may be stored in ROM.
 *
 * A custom HIL can replace this macro with a HIL specific version by doing the following:
 * - Provide a microlibrary-custom library that provides microlibrary/hil/rom.h
 * - Define MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED to be a value that will be evaluated as
 *   true by the preprocessor (e.g. 1) in microlibrary/hil/rom.h
 * - Define the HIL specific version of MICROLIBRARY_ROM_STRING() in
 *   microlibrary/hil/rom.h
 */
#define MICROLIBRARY_ROM_STRING( string ) ( string )
#endif // !MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED

} // namespace microlibrary::ROM

#endif // MICROLIBRARY_ROM_H
