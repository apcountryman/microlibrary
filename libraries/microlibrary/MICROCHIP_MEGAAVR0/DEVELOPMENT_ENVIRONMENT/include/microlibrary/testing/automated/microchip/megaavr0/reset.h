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
 * \brief microlibrary Microchip megaAVR 0-series reset automated testing facilities
 *        interface.
 */

#ifndef MICROLIBRARY_TESTING_AUTOMATED_MICROCHIP_MEGAAVR0_RESET_H
#define MICROLIBRARY_TESTING_AUTOMATED_MICROCHIP_MEGAAVR0_RESET_H

#include <cstdlib>

#include "gmock/gmock.h"
#include "microlibrary/microchip/megaavr0/reset.h"

namespace microlibrary::Testing::Automated::Microchip::megaAVR0 {

/**
 * \brief Mock reset controller.
 */
class Mock_Reset_Controller {
  public:
    Mock_Reset_Controller() = default;

    Mock_Reset_Controller( Mock_Reset_Controller && ) = delete;

    Mock_Reset_Controller( Mock_Reset_Controller const & ) = delete;

    ~Mock_Reset_Controller() noexcept = default;

    auto operator=( Mock_Reset_Controller && ) = delete;

    auto operator=( Mock_Reset_Controller const & ) = delete;

    MOCK_METHOD( ::microlibrary::Microchip::megaAVR0::Reset_Source, reset_source, (), ( const ) );
    MOCK_METHOD( void, clear_reset_source, () );

    [[noreturn]] void initiate_software_reset()
    {
        std::exit( 0 );
    }
};

} // namespace microlibrary::Testing::Automated::Microchip::megaAVR0

#endif // MICROLIBRARY_TESTING_AUTOMATED_MICROCHIP_MEGAAVR0_RESET_H
