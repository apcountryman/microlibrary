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
 * \brief microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL interface.
 */

#ifndef MICROLIBRARY_MICROCHIP_MEGAAVR0_PERIPHERAL_CLKCTRL_H
#define MICROLIBRARY_MICROCHIP_MEGAAVR0_PERIPHERAL_CLKCTRL_H

#include <cstdint>

#include "microlibrary/integer.h"
#include "microlibrary/microchip/megaavr0/register.h"
#include "microlibrary/register.h"

namespace microlibrary::Microchip::megaAVR0::Peripheral {

/**
 * \brief Microchip megaAVR 0-series Clock Controller (CLKCTRL) peripheral.
 */
struct CLKCTRL {
    /**
     * \brief Main Clock Control A (MCLKCTRLA) register information.
     *
     * This register has the following fields:
     * - Clock Select (CLKSEL)
     * - System Clock Out (CLKOUT)
     */
    struct MCLKCTRLA {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto CLKSEL    = std::uint_fast8_t{ 2 }; ///< CLKSEL.
            static constexpr auto RESERVED2 = std::uint_fast8_t{ 5 }; ///< RESERVED2.
            static constexpr auto CLKOUT    = std::uint_fast8_t{ 1 }; ///< CLKOUT.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto CLKSEL = std::uint_fast8_t{ 0 }; ///< CLKSEL.
            static constexpr auto RESERVED2 = std::uint_fast8_t{ CLKSEL + Size::CLKSEL }; ///< RESERVED2.
            static constexpr auto CLKOUT = std::uint_fast8_t{ RESERVED2 + Size::RESERVED2 }; ///< CLKOUT.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto CLKSEL = mask<std::uint8_t>( Size::CLKSEL, Bit::CLKSEL ); ///< CLKSEL.
            static constexpr auto RESERVED2 = mask<std::uint8_t>( Size::RESERVED2, Bit::RESERVED2 ); ///< RESERVED2.
            static constexpr auto CLKOUT = mask<std::uint8_t>( Size::CLKOUT, Bit::CLKOUT ); ///< CLKOUT.
        };

        /**
         * \brief CLKSEL.
         */
        enum CLKSEL : std::uint8_t {
            CLKSEL_OSC20M    = 0x0 << Bit::CLKSEL, ///< 16/20 MHz internal oscillator.
            CLKSEL_OSCULP32K = 0x1 << Bit::CLKSEL, ///< 32.768 kHz internal ultra low-power oscillator.
            CLKSEL_XOSC32K = 0x2 << Bit::CLKSEL, ///< 32.768 kHz external crystal oscillator.
            CLKSEL_EXTCLK = 0x3 << Bit::CLKSEL, ///< External clock.
        };
    };

    /**
     * \brief Main Clock Control B (MCLKCTRLB) register information.
     *
     * This register has the following fields:
     * - Prescaler Enable (PEN)
     * - Prescaler Division (PDIV)
     */
    struct MCLKCTRLB {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto PEN       = std::uint_fast8_t{ 1 }; ///< PEN.
            static constexpr auto PDIV      = std::uint_fast8_t{ 4 }; ///< PDIV.
            static constexpr auto RESERVED5 = std::uint_fast8_t{ 3 }; ///< RESERVED5.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto PEN  = std::uint_fast8_t{ 0 };               ///< PEN.
            static constexpr auto PDIV = std::uint_fast8_t{ PEN + Size::PEN }; ///< PDIV.
            static constexpr auto RESERVED5 = std::uint_fast8_t{ PDIV + Size::PDIV }; ///< RESERVED5.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto PEN = mask<std::uint8_t>( Size::PEN, Bit::PEN ); ///< PEN.
            static constexpr auto PDIV = mask<std::uint8_t>( Size::PDIV, Bit::PDIV ); ///< PDIV.
            static constexpr auto RESERVED5 = mask<std::uint8_t>( Size::RESERVED5, Bit::RESERVED5 ); ///< RESERVED5.
        };

        /**
         * \brief PDIV.
         */
        enum PDIV : std::uint8_t {
            PDIV_DIV2  = 0x0 << Bit::PDIV, ///< CLK_MAIN divided by 2.
            PDIV_DIV4  = 0x1 << Bit::PDIV, ///< CLK_MAIN divided by 4.
            PDIV_DIV8  = 0x2 << Bit::PDIV, ///< CLK_MAIN divided by 8.
            PDIV_DIV16 = 0x3 << Bit::PDIV, ///< CLK_MAIN divided by 16.
            PDIV_DIV32 = 0x4 << Bit::PDIV, ///< CLK_MAIN divided by 32.
            PDIV_DIV64 = 0x5 << Bit::PDIV, ///< CLK_MAIN divided by 64.
            PDIV_DIV6  = 0x8 << Bit::PDIV, ///< CLK_MAIN divided by 6.
            PDIV_DIV10 = 0x9 << Bit::PDIV, ///< CLK_MAIN divided by 10.
            PDIV_DIV12 = 0xA << Bit::PDIV, ///< CLK_MAIN divided by 12.
            PDIV_DIV24 = 0xB << Bit::PDIV, ///< CLK_MAIN divided by 24.
            PDIV_DIV48 = 0xC << Bit::PDIV, ///< CLK_MAIN divided by 48.
        };
    };

    /**
     * \brief Main Clock Lock (MCLKLOCK) register information.
     *
     * This register has the following fields:
     * - Lock Enable (LOCKEN)
     */
    struct MCLKLOCK {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto LOCKEN    = std::uint_fast8_t{ 1 }; ///< LOCKEN.
            static constexpr auto RESERVED1 = std::uint_fast8_t{ 7 }; ///< RESERVED1.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto LOCKEN = std::uint_fast8_t{ 0 }; ///< LOCKEN.
            static constexpr auto RESERVED1 = std::uint_fast8_t{ LOCKEN + Size::LOCKEN }; ///< RESERVED1.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto LOCKEN = mask<std::uint8_t>( Size::LOCKEN, Bit::LOCKEN ); ///< LOCKEN.
            static constexpr auto RESERVED1 = mask<std::uint8_t>( Size::RESERVED1, Bit::RESERVED1 ); ///< RESERVED1.
        };
    };

    /**
     * \brief Main Clock Status (MCLKSTATUS) register information.
     *
     * This register has the following fields:
     * - Main Clock Oscillator Changing (SOSC)
     * - OSC20M Status (OSC20MS)
     * - OSCULP32K Status (OSC32KS)
     * - XOSC32K Status (XOSC32KS)
     * - External Clock Status (EXTS)
     */
    struct MCLKSTATUS {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto SOSC      = std::uint_fast8_t{ 1 }; ///< SOSC.
            static constexpr auto RESERVED1 = std::uint_fast8_t{ 3 }; ///< RESERVED1.
            static constexpr auto OSC20MS   = std::uint_fast8_t{ 1 }; ///< OSC20MS.
            static constexpr auto OSC32KS   = std::uint_fast8_t{ 1 }; ///< OSC32KS.
            static constexpr auto XOSC32KS  = std::uint_fast8_t{ 1 }; ///< XOSC32KS.
            static constexpr auto EXTS      = std::uint_fast8_t{ 1 }; ///< EXTS.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto SOSC = std::uint_fast8_t{ 0 }; ///< SOSC.
            static constexpr auto RESERVED1 = std::uint_fast8_t{ SOSC + Size::SOSC }; ///< RESERVED1.
            static constexpr auto OSC20MS = std::uint_fast8_t{ RESERVED1 + Size::RESERVED1 }; ///< OSC20MS.
            static constexpr auto OSC32KS = std::uint_fast8_t{ OSC20MS + Size::OSC20MS }; ///< OSC32KS.
            static constexpr auto XOSC32KS = std::uint_fast8_t{ OSC32KS + Size::OSC32KS }; ///< XOSC32KS.
            static constexpr auto EXTS = std::uint_fast8_t{ XOSC32KS + Size::XOSC32KS }; ///< EXTS.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto SOSC = mask<std::uint8_t>( Size::SOSC, Bit::SOSC ); ///< SOSC.
            static constexpr auto RESERVED1 = mask<std::uint8_t>( Size::RESERVED1, Bit::RESERVED1 ); ///< RESERVED1.
            static constexpr auto OSC20MS = mask<std::uint8_t>( Size::OSC20MS, Bit::OSC20MS ); ///< OSC20MS.
            static constexpr auto OSC32KS = mask<std::uint8_t>( Size::OSC32KS, Bit::OSC32KS ); ///< OSC32KS.
            static constexpr auto XOSC32KS = mask<std::uint8_t>( Size::XOSC32KS, Bit::XOSC32KS ); ///< XOSC32KS.
            static constexpr auto EXTS = mask<std::uint8_t>( Size::EXTS, Bit::EXTS ); ///< EXTS.
        };
    };

    /**
     * \brief 16/20 MHz Oscillator Control A (OSC20MCTRLA) register information.
     *
     * This register has the following fields:
     * - Run Standby (RUNSTDBY)
     */
    struct OSC20MCTRLA {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto RESERVED0 = std::uint_fast8_t{ 1 }; ///< RESERVED0.
            static constexpr auto RUNSTDBY  = std::uint_fast8_t{ 1 }; ///< RUNSTDBY.
            static constexpr auto RESERVED2 = std::uint_fast8_t{ 6 }; ///< RESERVED2.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto RESERVED0 = std::uint_fast8_t{ 0 }; ///< RESERVED0.
            static constexpr auto RUNSTDBY = std::uint_fast8_t{ RESERVED0 + Size::RESERVED0 }; ///< RUNSTDBY.
            static constexpr auto RESERVED2 = std::uint_fast8_t{ RUNSTDBY + Size::RUNSTDBY }; ///< RESERVED2.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto RESERVED0 = mask<std::uint8_t>( Size::RESERVED0, Bit::RESERVED0 ); ///< RESERVED0.
            static constexpr auto RUNSTDBY = mask<std::uint8_t>( Size::RUNSTDBY, Bit::RUNSTDBY ); ///< RUNSTDBY.
            static constexpr auto RESERVED2 = mask<std::uint8_t>( Size::RESERVED2, Bit::RESERVED2 ); ///< RESERVED2.
        };
    };

    /**
     * \brief 16/20 MHz Oscillator Calibration A (OSC20MCALIBA) register information.
     *
     * This register has the following fields:
     * - Calibration (CAL20M)
     */
    struct OSC20MCALIBA {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto CAL20M    = std::uint_fast8_t{ 7 }; ///< CAL20M.
            static constexpr auto RESERVED7 = std::uint_fast8_t{ 1 }; ///< RESERVED7.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto CAL20M = std::uint_fast8_t{ 0 }; ///< CAL20M.
            static constexpr auto RESERVED7 = std::uint_fast8_t{ CAL20M + Size::CAL20M }; ///< RESERVED7.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto CAL20M = mask<std::uint8_t>( Size::CAL20M, Bit::CAL20M ); ///< CAL20M.
            static constexpr auto RESERVED7 = mask<std::uint8_t>( Size::RESERVED7, Bit::RESERVED7 ); ///< RESERVED7.
        };
    };

    /**
     * \brief 16/20 MHz Oscillator Calibration B (OSC20MCALIBB) register information.
     *
     * This register has the following fields:
     * - Oscillator Temperature Coefficient Calibration (TEMPCAL20M)
     * - Oscillator Calibration Locked by Fuse (LOCK)
     */
    struct OSC20MCALIBB {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto TEMPCAL20M = std::uint_fast8_t{ 4 }; ///< TEMPCAL20M.
            static constexpr auto RESERVED4  = std::uint_fast8_t{ 3 }; ///< RESERVED4.
            static constexpr auto LOCK       = std::uint_fast8_t{ 1 }; ///< LOCK.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto TEMPCAL20M = std::uint_fast8_t{ 0 }; ///< TEMPCAL20M.
            static constexpr auto RESERVED4 = std::uint_fast8_t{ TEMPCAL20M + Size::TEMPCAL20M }; ///< RESERVED4.
            static constexpr auto LOCK = std::uint_fast8_t{ RESERVED4 + Size::RESERVED4 }; ///< LOCK.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto TEMPCAL20M = mask<std::uint8_t>( Size::TEMPCAL20M, Bit::TEMPCAL20M ); ///< TEMPCAL20M.
            static constexpr auto RESERVED4 = mask<std::uint8_t>( Size::RESERVED4, Bit::RESERVED4 ); ///< RESERVED4.
            static constexpr auto LOCK = mask<std::uint8_t>( Size::LOCK, Bit::LOCK ); ///< LOCK.
        };
    };

    /**
     * \brief 32.768 kHz Oscillator Control A (OSC32KCTRLA) register information.
     *
     * This register has the following fields:
     * - Run Standby (RUNSTDBY)
     */
    struct OSC32KCTRLA {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto RESERVED0 = std::uint_fast8_t{ 1 }; ///< RESERVED0.
            static constexpr auto RUNSTDBY  = std::uint_fast8_t{ 1 }; ///< RUNSTDBY.
            static constexpr auto RESERVED2 = std::uint_fast8_t{ 6 }; ///< RESERVED2.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto RESERVED0 = std::uint_fast8_t{ 0 }; ///< RESERVED0.
            static constexpr auto RUNSTDBY = std::uint_fast8_t{ RESERVED0 + Size::RESERVED0 }; ///< RUNSTDBY.
            static constexpr auto RESERVED2 = std::uint_fast8_t{ RUNSTDBY + Size::RUNSTDBY }; ///< RESERVED2.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto RESERVED0 = mask<std::uint8_t>( Size::RESERVED0, Bit::RESERVED0 ); ///< RESERVED0.
            static constexpr auto RUNSTDBY = mask<std::uint8_t>( Size::RUNSTDBY, Bit::RUNSTDBY ); ///< RUNSTDBY.
            static constexpr auto RESERVED2 = mask<std::uint8_t>( Size::RESERVED2, Bit::RESERVED2 ); ///< RESERVED2.
        };
    };

    /**
     * \brief 32.768 kHz Crystal Oscillator Control A (XOSC32KCTRLA) register information.
     *
     * This register has the following fields:
     * - Enable (ENABLE)
     * - Run Standby (RUNSTDBY)
     * - Source Select (SEL)
     * - Crystal Start-Up Time (CSUT)
     */
    struct XOSC32KCTRLA {
        /**
         * \brief Field sizes.
         */
        struct Size {
            static constexpr auto ENABLE    = std::uint_fast8_t{ 1 }; ///< ENABLE.
            static constexpr auto RUNSTDBY  = std::uint_fast8_t{ 1 }; ///< RUNSTDBY.
            static constexpr auto SEL       = std::uint_fast8_t{ 1 }; ///< SEL.
            static constexpr auto RESERVED3 = std::uint_fast8_t{ 1 }; ///< RESERVED3.
            static constexpr auto CSUT      = std::uint_fast8_t{ 2 }; ///< CSUT.
            static constexpr auto RESERVED6 = std::uint_fast8_t{ 2 }; ///< RESERVED6.
        };

        /**
         * \brief Field bit positions.
         */
        struct Bit {
            static constexpr auto ENABLE = std::uint_fast8_t{ 0 }; ///< ENABLE.
            static constexpr auto RUNSTDBY = std::uint_fast8_t{ ENABLE + Size::ENABLE }; ///< RUNSTDBY.
            static constexpr auto SEL = std::uint_fast8_t{ RUNSTDBY + Size::RUNSTDBY }; ///< SEL.
            static constexpr auto RESERVED3 = std::uint_fast8_t{ SEL + Size::SEL }; ///< RESERVED3.
            static constexpr auto CSUT = std::uint_fast8_t{ RESERVED3 + Size::RESERVED3 }; ///< CSUT.
            static constexpr auto RESERVED6 = std::uint_fast8_t{ CSUT + Size::CSUT }; ///< RESERVED6.
        };

        /**
         * \brief Field bit masks.
         */
        struct Mask {
            static constexpr auto ENABLE = mask<std::uint8_t>( Size::ENABLE, Bit::ENABLE ); ///< ENABLE.
            static constexpr auto RUNSTDBY = mask<std::uint8_t>( Size::RUNSTDBY, Bit::RUNSTDBY ); ///< RUNSTDBY.
            static constexpr auto SEL = mask<std::uint8_t>( Size::SEL, Bit::SEL ); ///< SEL.
            static constexpr auto RESERVED3 = mask<std::uint8_t>( Size::RESERVED3, Bit::RESERVED3 ); ///< RESERVED3.
            static constexpr auto CSUT = mask<std::uint8_t>( Size::CSUT, Bit::CSUT ); ///< CSUT.
            static constexpr auto RESERVED6 = mask<std::uint8_t>( Size::RESERVED6, Bit::RESERVED6 ); ///< RESERVED6.
        };

        /**
         * \brief CSUT.
         */
        enum CSUT : std::uint8_t {
            CSUT_1K  = 0x0 << Bit::CSUT, ///< 1k cycles.
            CSUT_16K = 0x1 << Bit::CSUT, ///< 16k cycles.
            CSUT_32K = 0x2 << Bit::CSUT, ///< 32k cycles.
            CSUT_64K = 0x3 << Bit::CSUT, ///< 64k cycles.
        };
    };

    /**
     * \brief Main Clock Control A (MCLKCTRLA) register.
     */
    Protected_Register<std::uint8_t, CPU_CCP_Key::IOREG> mclkctrla;

    /**
     * \brief Main Clock Control B (MCLKCTRLB) register.
     */
    Protected_Register<std::uint8_t, CPU_CCP_Key::IOREG> mclkctrlb;

    /**
     * \brief Main Clock Lock (MCLKLOCK) register.
     */
    Protected_Register<std::uint8_t, CPU_CCP_Key::IOREG> mclklock;

    /**
     * \brief Main Clock Status (MCLKSTATUS) register.
     */
    Read_Only_Register<std::uint8_t> const mclkstatus;

    /**
     * \brief Reserved registers (offset 0x04-0x0F).
     */
    Reserved_Register<std::uint8_t> const reserved_register_0x04_0x0F[ ( 0x0F - 0x04 ) + 1 ];

    /**
     * \brief 16/20 MHz Oscillator Control A (OSC20MCTRLA) register.
     */
    Protected_Register<std::uint8_t, CPU_CCP_Key::IOREG> osc20mctrla;

    /**
     * \brief 16/20 MHz Oscillator Calibration A (OSC20MCALIBA) register.
     */
    Protected_Register<std::uint8_t, CPU_CCP_Key::IOREG> osc20mcaliba;

    /**
     * \brief 16/20 MHz Oscillator Calibration B (OSC20MCALIBB) register.
     */
    Protected_Register<std::uint8_t, CPU_CCP_Key::IOREG> osc20mcalibb;

    /**
     * \brief Reserved registers (offset 0x13-0x17).
     */
    Reserved_Register<std::uint8_t> const reserved_register_0x13_0x17[ ( 0x17 - 0x13 ) + 1 ];

    /**
     * \brief 32.768 kHz Oscillator Control A (OSC32KCTRLA) register.
     */
    Protected_Register<std::uint8_t, CPU_CCP_Key::IOREG> osc32kctrla;

    /**
     * \brief Reserved registers (offset 0x19-0x1B).
     */
    Reserved_Register<std::uint8_t> const reserved_register_0x19_0x1B[ ( 0x1B - 0x19 ) + 1 ];

    /**
     * \brief 32.768 kHz Crystal Oscillator Control A (XOSC32KCTRLA) register.
     */
    Protected_Register<std::uint8_t, CPU_CCP_Key::IOREG> xosc32kctrla;
};

} // namespace microlibrary::Microchip::megaAVR0::Peripheral

#endif // MICROLIBRARY_MICROCHIP_MEGAAVR0_PERIPHERAL_CLKCTRL_H
