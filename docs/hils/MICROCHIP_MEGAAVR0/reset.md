# Reset Facilities

Microchip megaAVR 0-series reset facilities are defined in the `microlibrary` static
library's
[`microlibrary/microchip/megaavr0/reset.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/include/microlibrary/microchip/megaavr0/reset.h)/[`microlibrary/microchip/megaavr0/reset.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/source/microlibrary/microchip/megaavr0/reset.cc)
header/source file pair.

## Table of Contents

1. [Reset Source](#reset-source)

## Reset Source

The `::microlibrary::Microchip::megaAVR0::Reset_Source` class holds a Microchip megaAVR
0-series microcontroller's reset source(s).
- To get the RSTCTRL peripheral RSTFR value, use the
  `::microlibrary::Microchip::megaAVR0::Reset_Source::rstctrl_rstfr()` member function.
- To check if a power-on reset has occurred, use the
  `::microlibrary::Microchip::megaAVR0::Reset_Source::is_power_on_reset()` member
  function.
- To check if a brown-out reset has occurred, use the
  `::microlibrary::Microchip::megaAVR0::Reset_Source::is_brown_out_reset()` member
  function.
- To check if an external reset has occurred, use the
  `::microlibrary::Microchip::megaAVR0::Reset_Source::is_external_reset()` member
  function.
- To check if a watchdog reset has occurred, use the
  `::microlibrary::Microchip::megaAVR0::Reset_Source::is_watchdog_reset()` member
  function.
- To check if a software reset has occurred, use the
  `::microlibrary::Microchip::megaAVR0::Reset_Source::is_software_reset()` member
  function.
- To check if a UPDI reset has occurred, use the
  `::microlibrary::Microchip::megaAVR0::Reset_Source::is_updi_reset()` member function.
