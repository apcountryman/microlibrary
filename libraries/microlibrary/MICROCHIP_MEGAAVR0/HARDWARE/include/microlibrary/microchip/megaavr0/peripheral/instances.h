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
 * \brief microlibrary Microchip megaAVR 0-series peripheral instances interface.
 */

#ifndef MICROLIBRARY_MICROCHIP_MEGAAVR0_PERIPHERAL_INSTANCES_H
#define MICROLIBRARY_MICROCHIP_MEGAAVR0_PERIPHERAL_INSTANCES_H

#include "microlibrary/microchip/megaavr0/peripheral/clkctrl.h"
#include "microlibrary/microchip/megaavr0/peripheral/rstctrl.h"
#include "microlibrary/peripheral.h"

namespace microlibrary::Microchip::megaAVR0::Peripheral {

/**
 * \brief RSTCTRL0.
 */
using RSTCTRL0 = ::microlibrary::Peripheral::Instance<RSTCTRL, 0x0040>;

/**
 * \brief CLKCTRL0.
 */
using CLKCTRL0 = ::microlibrary::Peripheral::Instance<CLKCTRL, 0x0060>;

} // namespace microlibrary::Microchip::megaAVR0::Peripheral

#endif // MICROLIBRARY_MICROCHIP_MEGAAVR0_PERIPHERAL_INSTANCES_H
