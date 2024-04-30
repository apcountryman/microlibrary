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
 * \brief microlibrary postcondition assertion facilities interface.
 */

#ifndef MICROLIBRARY_POSTCONDITION_H
#define MICROLIBRARY_POSTCONDITION_H

#include "microlibrary/assertion_failure.h"
#include "microlibrary/rom.h"

namespace microlibrary {

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Check a postcondition's guarantee.
 *
 * \param[in] guarantee The guarantee to check.
 * \param[in] error The error that has occurred if the guarantee is not met.
 */
#define MICROLIBRARY_ENSURE( guarantee, error )                 \
    ( ( guarantee ) ? static_cast<void>( 0 )                    \
                      : ::microlibrary::handle_assertion_failure( \
                          MICROLIBRARY_ROM_STRING( __FILE__ ), __LINE__, error ) )
#else // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Check a postcondition's guarantee.
 *
 * \param[in] guarantee The guarantee to check.
 * \param[in] error The error that has occurred if the guarantee is not met.
 */
#define MICROLIBRARY_ENSURE( guarantee, error ) \
    ( ( guarantee ) ? static_cast<void>( 0 ) : ::microlibrary::handle_assertion_failure( error ) )
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

#if !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Report that a postcondition's guarantee has not been met.
 *
 * \param[in] error The error that has occurred.
 */
#define MICROLIBRARY_GUARANTEE_NOT_MET( error ) \
    ::microlibrary::handle_assertion_failure( MICROLIBRARY_ROM_STRING( __FILE__ ), __LINE__, error )
#else // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION
/**
 * \brief Report that a postcondition's guarantee has not been met.
 *
 * \param[in] error The error that has occurred.
 */
#define MICROLIBRARY_GUARANTEE_NOT_MET( error ) \
    ::microlibrary::handle_assertion_failure( error )
#endif // !MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION

} // namespace microlibrary

#endif // MICROLIBRARY_POSTCONDITION_H
