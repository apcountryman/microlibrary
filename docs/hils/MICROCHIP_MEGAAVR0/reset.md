# Reset Facilities

Microchip megaAVR 0-series reset facilities are defined in the `microlibrary` static
library's
[`microlibrary/microchip/megaavr0/reset.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/include/microlibrary/microchip/megaavr0/reset.h)/[`microlibrary/microchip/megaavr0/reset.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/source/microlibrary/microchip/megaavr0/reset.cc)
header/source file pair.

## Table of Contents

1. [Reset Source](#reset-source)
1. [Reset Controller](#reset-controller)

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

## Reset Controller

The `::microlibrary::Microchip::megaAVR0::Reset_Controller` reset controller class is used
to interact with a Microchip megaAVR 0-series microcontroller's RSTCTRL peripheral.
- To get the reset source(s), use the
  `::microlibrary::Microchip::megaAVR0::Reset_Controller::reset_source()` member function.
- To clear the reset source(s), use the
  `::microlibrary::Microchip::megaAVR0::Reset_Controller::clear_reset_source()` member
  function.
- To initiate a software reset, use the
  `::microlibrary::Microchip::megaAVR0::Reset_Controller::initiate_software_reset()`
  member function.

`::microlibrary::Microchip::megaAVR0::Reset_Controller` automated tests are defined in the
`test-automated-microlibrary-microchip-megaavr0-reset_controller` automated test
executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/microchip/megaavr0/reset_controller/main.cc)
source file.

The `::microlibrary::Testing::Automated::Microchip::megaAVR0::Mock_Reset_Controller` mock
reset controller class is available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mock is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/reset.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/reset.h)/[`microlibrary/testing/automated/microchip/megaavr0/reset.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/reset.cc)
header/source file pair.
