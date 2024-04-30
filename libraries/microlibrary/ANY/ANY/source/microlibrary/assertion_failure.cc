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
 * \brief microlibrary assertion failure handling facilities implementation.
 */

#include "microlibrary/assertion_failure.h"

#include <cstdlib>

#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
#include <iostream>
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

#include "microlibrary/error.h"
#include "microlibrary/rom.h"

#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
#include "microlibrary/testing/automated/error.h"
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Handle an assertion failure (default implementation).
 *
 * \param[in] file The file in which the assertion failure occurred.
 * \param[in] line The line on which the assertion failure occurred.
 * \param[in] error The error that the assertion detected.
 */
extern "C" [[noreturn]] void microlibrary_handle_assertion_failure(
    ::microlibrary::ROM::String        file,
    int                                line,
    ::microlibrary::Error_Code const & error ) noexcept
{
#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
    std::cerr << file << ':' << line << ": " << error << '\n';
#else  // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
    static_cast<void>( file );
    static_cast<void>( line );
    static_cast<void>( error );
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

    std::abort();
}
#else // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Handle an assertion failure (default implementation).
 *
 * \param[in] error The error that the assertion detected.
 */
extern "C" [[noreturn]] void microlibrary_handle_assertion_failure( ::microlibrary::Error_Code const & error ) noexcept
{
#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
    std::cerr << error << '\n';
#else  // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
    static_cast<void>( error );
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

    std::abort();
}
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

namespace microlibrary {

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
[[noreturn]] void handle_assertion_failure( ROM::String file, int line, Error_Code const & error ) noexcept
    __attribute__( ( weak, alias( "microlibrary_handle_assertion_failure" ) ) );
#else  // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
[[noreturn]] void handle_assertion_failure( Error_Code const & error ) noexcept
    __attribute__( ( weak, alias( "microlibrary_handle_assertion_failure" ) ) );
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

} // namespace microlibrary
