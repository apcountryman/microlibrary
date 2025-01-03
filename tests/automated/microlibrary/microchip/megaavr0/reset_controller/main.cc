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
 * \brief microlibrary::Microchip::megaAVR0::Reset_Controller automated tests.
 */

#include <cstdint>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "microlibrary/microchip/megaavr0/peripheral/rstctrl.h"
#include "microlibrary/microchip/megaavr0/reset.h"
#include "microlibrary/pointer.h"

namespace {

using ::microlibrary::Not_Null;
using ::microlibrary::Microchip::megaAVR0::Reset_Controller;
using ::microlibrary::Microchip::megaAVR0::Peripheral::RSTCTRL;
using ::testing::Return;

} // namespace

/**
 * \brief Verify microlibrary::Microchip::megaAVR0::Clock_Controller::reset_source() works
 *        properly.
 */
TEST( resetSource, worksProperly )
{
    auto const rstfr = std::uint8_t{ 0b01'0'1'0'0'1'1 };

    auto rstctrl = RSTCTRL{};

    auto const reset_controller = Reset_Controller{ Not_Null{ &rstctrl } };

    EXPECT_CALL( rstctrl.rstfr, read() ).WillOnce( Return( rstfr ) );

    EXPECT_EQ( reset_controller.reset_source().rstctrl_rstfr(), rstfr );
}

/**
 * \brief Verify microlibrary::Microchip::megaAVR0::Clock_Controller::clear_reset_source()
 *        works properly.
 */
TEST( clearResetSource, worksProperly )
{
    auto rstctrl = RSTCTRL{};

    auto reset_controller = Reset_Controller{ Not_Null{ &rstctrl } };

    EXPECT_CALL( rstctrl.rstfr, write( 0b00'1'1'1'1'1'1 ) );

    reset_controller.clear_reset_source();
}
