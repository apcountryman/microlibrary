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
 * \brief microlibrary assertion failure handling facilities interface.
 */

#ifndef MICROLIBRARY_ASSERTION_FAILURE_H
#define MICROLIBRARY_ASSERTION_FAILURE_H

#include "microlibrary/error.h"
#include "microlibrary/rom.h"

namespace microlibrary {

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Handle an assertion failure.
 *
 * \attention This function is defined as a weak alias for its default implementation so
 *            that its behavior can be overridden. The behavior of the default
 *            implementation depends on MICROLIBRARY_TARGET. If MICROLIBRARY_TARGET is
 *            DEVELOPMENT_ENVIRONMENT, the default implementation writes all available
 *            information about an assertion failure to std::cerr and calls std::abort().
 *            If MICROLIBRARY_TARGET is not DEVELOPMENT_ENVIRONMENT, the default
 *            implementation simply calls std::abort().
 *
 * \param[in] file The file in which the assertion failure occurred.
 * \param[in] line The line on which the assertion failure occurred.
 * \param[in] error The error that the assertion detected.
 */
[[noreturn]] void handle_assertion_failure( ROM::String file, int line, Error_Code const & error ) noexcept;
#else  // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Handle an assertion failure.
 *
 * \attention This function is defined as a weak alias for its default implementation so
 *            that its behavior can be overridden. The behavior of the default
 *            implementation depends on MICROLIBRARY_TARGET. If MICROLIBRARY_TARGET is
 *            DEVELOPMENT_ENVIRONMENT, the default implementation writes all available
 *            information about an assertion failure to std::cerr and calls std::abort().
 *            If MICROLIBRARY_TARGET is not DEVELOPMENT_ENVIRONMENT, the default
 *            implementation simply calls std::abort().
 *
 * \param[in] error The error that the assertion detected.
 */
[[noreturn]] void handle_assertion_failure( Error_Code const & error ) noexcept;
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

} // namespace microlibrary

#endif // MICROLIBRARY_ASSERTION_FAILURE_H
