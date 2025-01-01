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
 * \brief microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL implementation.
 */

#include "microlibrary/microchip/megaavr0/peripheral/clkctrl.h"

namespace microlibrary::Microchip::megaAVR0::Peripheral {

#if MICROLIBRARY_TARGET_IS_HARDWARE
static_assert( sizeof( CLKCTRL ) == 0x1C + 1 );
#endif // MICROLIBRARY_TARGET_IS_HARDWARE

} // namespace microlibrary::Microchip::megaAVR0::Peripheral