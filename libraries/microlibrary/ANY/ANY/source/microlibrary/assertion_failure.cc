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

namespace {

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Default assertion failure logger.
 *
 * \param[in] data The data (none) associated with this assertion failure logger.
 * \param[in] file The file in which the assertion failure occurred.
 * \param[in] line The line on which the assertion failure occurred.
 * \param[in] error The error that the assertion detected.
 */
void log_assertion_failure_default( void * data, ::microlibrary::ROM::String file, int line, ::microlibrary::Error_Code const & error ) noexcept
{
#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
    static_cast<void>( data );

    std::cerr << file << ':' << line << ": " << error << '\n';
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

#if MICROLIBRARY_TARGET_IS_HARDWARE
    static_cast<void>( data );
    static_cast<void>( file );
    static_cast<void>( line );
    static_cast<void>( error );
#endif // MICROLIBRARY_TARGET_IS_HARDWARE
}
#else // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Default assertion failure logger.
 *
 * \param[in] data The data (none) associated with this assertion failure logger.
 * \param[in] file The file in which the assertion failure occurred.
 * \param[in] line The line on which the assertion failure occurred.
 * \param[in] error The error that the assertion detected.
 */
void log_assertion_failure_default( void * data, ::microlibrary::Error_Code const & error ) noexcept
{
#if MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT
    static_cast<void>( data );

    std::cerr << error << '\n';
#endif // MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT

#if MICROLIBRARY_TARGET_IS_HARDWARE
    static_cast<void>( data );
    static_cast<void>( error );
#endif // MICROLIBRARY_TARGET_IS_HARDWARE
}
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

/**
 * \brief The active assertion failure logger.
 */
auto ASSERTION_FAILURE_LOGGER = log_assertion_failure_default;

/**
 * \brief The data associated with the active assertion failure logger.
 */
auto ASSERTION_FAILURE_LOGGER_DATA = static_cast<void *>( nullptr );

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Log an assertion failure.
 *
 * \param[in] file The file in which the assertion failure occurred.
 * \param[in] line The line on which the assertion failure occurred.
 * \param[in] error The error that the assertion detected.
 */
void log_assertion_failure( ::microlibrary::ROM::String file, int line, ::microlibrary::Error_Code const & error ) noexcept
{
    ( *ASSERTION_FAILURE_LOGGER )( ASSERTION_FAILURE_LOGGER_DATA, file, line, error );
}
#else  // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Log an assertion failure.
 *
 * \param[in] error The error that the assertion detected.
 */
void log_assertion_failure( ::microlibrary::Error_Code const & error ) noexcept
{
    ( *ASSERTION_FAILURE_LOGGER )( ASSERTION_FAILURE_LOGGER_DATA, error );
}
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

} // namespace

/**
 * \brief Handle an assertion failure.
 */
extern "C" [[noreturn]] void microlibrary_handle_assertion_failure() noexcept
{
    std::abort();
}

namespace microlibrary {

void replace_assertion_failure_logger( Assertion_Failure_Logger_Pointer assertion_failure_logger, void * assertion_failure_logger_data ) noexcept
{
    if ( assertion_failure_logger == nullptr ) {
        ASSERTION_FAILURE_LOGGER      = log_assertion_failure_default;
        ASSERTION_FAILURE_LOGGER_DATA = nullptr;
    } else {
        ASSERTION_FAILURE_LOGGER      = assertion_failure_logger;
        ASSERTION_FAILURE_LOGGER_DATA = assertion_failure_logger_data;
    } // else
}

[[noreturn]] void handle_assertion_failure() noexcept
    __attribute__( ( weak, alias( "microlibrary_handle_assertion_failure" ) ) );

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
[[noreturn]] void trap_assertion_failure( ROM::String file, int line, Error_Code const & error ) noexcept
{
    log_assertion_failure( file, line, error );

    handle_assertion_failure();
}
#else  // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
[[noreturn]] void trap_assertion_failure( Error_Code const & error ) noexcept
{
    log_assertion_failure( error );

    handle_assertion_failure();
}
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

} // namespace microlibrary
