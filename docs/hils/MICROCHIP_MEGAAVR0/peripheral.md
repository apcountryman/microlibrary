# Peripheral Facilities

## Table of Contents

1. [Peripherals](#peripherals)
    1. [CLKCTRL](#clkctrl)
    1. [RSTCTRL](#rstctrl)
1. [Peripheral Instances](#peripheral-instances)

## Peripherals

The layout of each Microchip megaAVR 0-series peripheral's registers is defined by the
structure named after the peripheral (e.g. the layout of the CLKCTRL peripheral's
registers is defined by the `::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL`
structure).
Peripheral registers are accessed via the member variables named after the registers (e.g.
the CLKCTRL peripheral's MCLKCTRLA register is accessed via the
`::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL::mclkctrla` member variable).
Peripheral register information is defined in member structures named after the registers
(e.g. CLKCTRL peripheral MCLKCTRLA register information is defined in the
`::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL::MCLKCTRLA` member structure).
Peripheral register field constants are defined in the following member structures:
- `Size`: field sizes (e.g. the size of the CLKSEL field of the CLKCTRL peripheral's
  MCLKCTRLA register is defined by the
  `::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL::MCLKCTRLA::Size::CLKSEL`
  constant).
- `Bit`: field bit positions (e.g. the position of the CLKSEL field of the CLKCTRL
  peripheral's MCLKCTRLA register is defined by the
  `::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL::MCLKCTRLA::Bit::CLKSEL`
  constant).
- `Mask`: field bit masks (e.g. the mask for the CLKSEL field of the CLKCTRL peripheral's
  MCLKCTRLA register is defined by the
  `::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL::MCLKCTRLA::Mask::CLKSEL`
  constant).

### CLKCTRL

The `::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL` structure defines the
layout of the Microchip megaAVR 0-series CLKCTRL peripheral and information about its
registers.
The `::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL` structure is defined in the
`microlibrary` static library's
[`microlibrary/microchip/megaavr0/peripheral/clkctrl.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/include/microlibrary/microchip/megaavr0/peripheral/clkctrl.h)/[`microlibrary/microchip/megaavr0/peripheral/clkctrl.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/source/microlibrary/microchip/megaavr0/peripheral/clkctrl.cc)
header/source file pair.

### RSTCTRL

The `::microlibrary::Microchip::megaAVR0::Peripheral::RSTCTRL` structure defines the
layout of the Microchip megaAVR 0-series RSTCTRL peripheral and information about its
registers.
The `::microlibrary::Microchip::megaAVR0::Peripheral::RSTCTRL` structure is defined in the
`microlibrary` static library's
[`microlibrary/microchip/megaavr0/peripheral/rstctrl.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/include/microlibrary/microchip/megaavr0/peripheral/rstctrl.h)/[`microlibrary/microchip/megaavr0/peripheral/rstctrl.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/source/microlibrary/microchip/megaavr0/peripheral/rstctrl.cc)
header/source file pair.

## Peripheral Instances

Microchip megaAVR 0-series peripheral instances are defined in the `microlibrary` static
library's
[`microlibrary/microchip/megaavr0/peripheral/instances.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/HARDWARE/include/microlibrary/microchip/megaavr0/peripheral/instances.h)/[`microlibrary/microchip/megaavr0/peripheral/instances.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/HARDWARE/source/microlibrary/microchip/megaavr0/peripheral/instances.cc)
header/source file pair which is available if `MICROLIBRARY_TARGET` is `HARDWARE`.
Peripheral instance names are based on the names used in the "Peripheral Module Address
Map" table of the datasheets with the following change: a `0` is added to the end of the
name of peripherals that only have a single instance to differentiate the peripheral name
and the instance name.
The following peripheral instances are defined (listed alphabetically):
- `::microlibrary::Microchip::megaAVR0::Peripheral::CLKCTRL0`
- `::microlibrary::Microchip::megaAVR0::Peripheral::RSTCTRL0`

The availability of these peripheral instance definitions depends on the specific
Microchip megaAVR 0-series microcontroller that is used.
