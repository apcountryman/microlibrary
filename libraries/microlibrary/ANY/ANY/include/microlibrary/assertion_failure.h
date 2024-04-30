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

#include <type_traits>

#include "microlibrary/error.h"
#include "microlibrary/rom.h"

namespace microlibrary {

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Assertion failure logger.
 *
 * \param[in] data The data (if any) associated with the assertion failure logger.
 * \param[in] file The file in which the assertion failure occurred.
 * \param[in] line The line on which the assertion failure occurred.
 * \param[in] error The error that the assertion detected.
 */
using Assertion_Failure_Logger = void( void * data, ROM::String file, int line, Error_Code const & error ) noexcept;
#else  // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Assertion failure logger.
 *
 * \param[in] data The data (if any) associated with the assertion failure logger.
 * \param[in] error The error that the assertion detected.
 */
using Assertion_Failure_Logger = void( void * data, Error_Code const & error ) noexcept;
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

/**
 * \brief Assertion failure logger pointer.
 */
using Assertion_Failure_Logger_Pointer = std::add_pointer_t<Assertion_Failure_Logger>;

/**
 * \brief Specify the assertion failure logger that microlibrary::trap_assertion_failure()
 *        will call if an assertion failure occurs.
 *
 * \param[in] assertion_failure_logger The assertion failure logger to be called by
 *            microlibrary::trap_assertion_failure() if an assertion failure occurs. If
 *            assertion_failure_logger is nullptr, the default assertion failure logger
 *            will be called by microlibrary::trap_assertion_failure() if an assertion
 *            failure occurs. The behavior of the default assertion failure logger depends
 *            on MICROLIBRARY_TARGET. If MICROLIBRARY_TARGET is DEVELOPMENT_ENVIRONMENT,
 *            the default assertion failure logger writes all available information about
 *            an assertion failure to std::cerr. If MICROLIBRARY_TARGET is HARDWARE, the
 *            default assertion failure logger does nothing.
 * \param[in] assertion_failure_logger_data The data (if any) associated with the
 *            assertion failure logger.
 */
void replace_assertion_failure_logger(
    Assertion_Failure_Logger_Pointer assertion_failure_logger,
    void *                           assertion_failure_logger_data ) noexcept;

/**
 * \brief Handle an assertion failure.
 *
 * \attention This function is defined as a weak alias for its default implementation
 *            (which simply calls std::abort()) so that its behavior can be overridden.
 */
[[noreturn]] void handle_assertion_failure() noexcept;

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Trap an assertion failure.
 *
 * \param[in] file The file in which the assertion failure occurred.
 * \param[in] line The line on which the assertion failure occurred.
 * \param[in] error The error that the assertion detected.
 */
[[noreturn]] void trap_assertion_failure( ROM::String file, int line, Error_Code const & error ) noexcept;
#else  // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Trap an assertion failure.
 *
 * \param[in] file The file in which the assertion failure occurred.
 * \param[in] line The line on which the assertion failure occurred.
 * \param[in] error The error that the assertion detected.
 */
[[noreturn]] void trap_assertion_failure( Error_Code const & error ) noexcept;
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

} // namespace microlibrary

#endif // MICROLIBRARY_ASSERTION_FAILURE_H
