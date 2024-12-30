# Clock Facilities

Microchip megaAVR 0-series clock facilities are defined in the `microlibrary` static
library's
[`microlibrary/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/include/microlibrary/microchip/megaavr0/clock.h)/[`microlibrary/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/source/microlibrary/microchip/megaavr0/clock.cc)
header/source file pair.

## Table of Contents

1. [Clock Source Identification](#clock-source-identification)
1. [Clock Prescaler Configuration Identification](#clock-prescaler-configuration-identification)
1. [Clock Prescaler Value Identification](#clock-prescaler-value-identification)
1. [Internal 16/20 MHz Oscillator Mode Identification](#internal-1620-mhz-oscillator-mode-identification)
1. [Internal 32.768 kHz Ultra Low-Power Oscillator Mode Identification](#internal-32768-khz-ultra-low-power-oscillator-mode-identification)
1. [External 32.768 kHz Crystal Oscillator Source Identification](#external-32768-khz-crystal-oscillator-source-identification)
1. [External 32.768 kHz Crystal Oscillator Start-Up Time Identification](#external-32768-khz-crystal-oscillator-start-up-time-identification)
1. [External 32.768 kHz Crystal Oscillator Mode Identification](#external-32768-khz-crystal-oscillator-mode-identification)
1. [Clock Controller](#clock-controller)

## Clock Source Identification

The `::microlibrary::Microchip::megaAVR0::Clock_Source` enum class is used to identify
Microchip megaAVR 0-series clock sources.

A `std::ostream` insertion operator is defined for
`::microlibrary::Microchip::megaAVR0::Clock_Source` if `MICROLIBRARY_TARGET` is
`DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.

## Clock Prescaler Configuration Identification

The `::microlibrary::Microchip::megaAVR0::Clock_Prescaler` enum class is used to identify
Microchip megaAVR 0-series clock prescaler configurations.

A `std::ostream` insertion operator is defined for
`::microlibrary::Microchip::megaAVR0::Clock_Prescaler` if `MICROLIBRARY_TARGET` is
`DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.

## Clock Prescaler Value Identification

The `::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value` enum class is used to
identify Microchip megaAVR 0-series clock prescaler values.

A `std::ostream` insertion operator is defined for
`::microlibrary::Microchip::megaAVR0::Clock_Prescaler_Value` if `MICROLIBRARY_TARGET` is
`DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.

## Internal 16/20 MHz Oscillator Mode Identification

The `::microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode` enum class
is used to identify Microchip megaAVR 0-series internal 16/20 MHz oscillator modes.

A `std::ostream` insertion operator is defined for
`::microlibrary::Microchip::megaAVR0::Internal_16_20_MHz_Oscillator_Mode` if
`MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.

## Internal 32.768 kHz Ultra Low-Power Oscillator Mode Identification

The
`::microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode`
enum class is used to identify Microchip megaAVR 0-series internal 32.768 kHz ultra
low-power oscillator modes.

A `std::ostream` insertion operator is defined for
`::microlibrary::Microchip::megaAVR0::Internal_32_768_kHz_Ultra_Low_Power_Oscillator_Mode`
if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.

## External 32.768 kHz Crystal Oscillator Source Identification

The `::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source`
enum class is used to identify Microchip megaAVR 0-series external 32.768 kHz crystal
oscillator sources.

A `std::ostream` insertion operator is defined for
`::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Source` if
`MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.

## External 32.768 kHz Crystal Oscillator Start-Up Time Identification

The
`::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time`
enum class is used to identify Microchip megaAVR 0-series external 32.768 kHz crystal
oscillator start-up times.

A `std::ostream` insertion operator is defined for
`::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Start_Up_Time`
if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.

## External 32.768 kHz Crystal Oscillator Mode Identification

The `::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode`
enum class is used to identify Microchip megaAVR 0-series external 32.768 kHz crystal
oscillator modes.

A `std::ostream` insertion operator is defined for
`::microlibrary::Microchip::megaAVR0::External_32_768_kHz_Crystal_Oscillator_Mode` if
`MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.

## Clock Controller

The `::microlibrary::Microchip::megaAVR0::Clock_Controller` clock controller class is used
to interact with a Microchip megaAVR 0-series microcontroller's CLKCTRL peripheral.
- To check if the clock source is changing, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source_is_changing()`
  member function.
- To get the clock source, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::clock_source()` member function.
- To set the clock source, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::set_clock_source()` member
  function.
- To check if clock output is enabled, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::clock_output_is_enabled()`
  member function.
- To enable clock output, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::enable_clock_output()` member
  function.
- To disable clock output, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::disable_clock_output()` member
  function.
- To check if the clock prescaler is enabled, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_is_enabled()`
  member function.
- To get the clock prescaler configuration, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_configuration()`
  member function.
- To get the clock prescaler value, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::clock_prescaler_value()` member
  function.
- To configure the clock prescaler, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::configure_clock_prescaler()`
  member function.
- To enable the clock prescaler, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::enable_clock_prescaler()` member
  function.
- To disable the clock prescaler, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::disable_clock_prescaler()`
  member function.
- To check if the clock configuration is locked, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::clock_configuration_is_locked()`
  member function.
- To lock the clock configuration, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::lock_clock_configuration()`
  member function.
- To check if the internal 16/20 MHz oscillator is stable, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_is_stable()`
  member function.
- To get the internal 16/20 MHz oscillator mode, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_mode()`
  member function.
- To set the internal 16/20 MHz oscillator mode, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_16_20_MHz_oscillator_mode()`
  member function.
- To check if the internal 16/20 MHz oscillator calibration settings are locked, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::internal_16_20_MHz_oscillator_calibration_settings_are_locked()`
  member function.
- To configure the internal 16/20 MHz oscillator calibration settings, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::configure_internal_16_20_MHz_oscillator_calibration_settings()`
  member function.
- To check if the internal 32.768 kHz ultra low-power oscillator is stable, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_is_stable()`
  member function.
- To get the internal 32.768 kHz ultra low-power oscillator mode, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::internal_32_768_kHz_ultra_low_power_oscillator_mode()`
  member function.
- To set the internal 32.768 kHz ultra low-power oscillator mode, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::set_internal_32_768_kHz_ultra_low_power_oscillator_mode()`
  member function.
- To check if the external 32.768 kHz crystal oscillator is stable, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_is_stable()`
  member function.
- To get the external 32.768 kHz crystal oscillator source, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_source()`
  member function.
- To get the external 32.768 kHz crystal oscillator start-up time, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_start_up_time()`
  member function.
- To get the external 32.768 kHz crystal oscillator mode, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_mode()`
  member function.
- To configure the external 32.768 kHz crystal oscillator, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::configure_external_32_768_kHz_crystal_oscillator()`
  member function.
- To set the external 32.768 kHz crystal oscillator mode, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::set_external_32_768_kHz_crystal_oscillator_mode()`
  member function.
- To check if the external 32.768 kHz crystal oscillator is enabled, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::external_32_768_kHz_crystal_oscillator_is_enabled()`
  member function.
- To enable the external 32.768 kHz crystal oscillator, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::enable_external_32_768_kHz_crystal_oscillator()`
  member function.
- To disable the external 32.768 kHz crystal oscillator, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::disable_external_32_768_kHz_crystal_oscillator()`
  member function.
- To check if the external clock is stable, use the
  `::microlibrary::Microchip::megaAVR0::Clock_Controller::external_clock_is_stable()`
  member function.

`::microlibrary::Microchip::megaAVR0::Clock_Controller` automated tests are defined in the
`test-automated-microlibrary-microchip-megaavr0-clock_controller` automated test
executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/microchip/megaavr0/clock_controller/main.cc)
source file.

The `::microlibrary::Testing::Automated::Microchip::megaAVR0::Mock_Clock_Controller` mock
clock controller class is available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mock is defined in the
[`microlibrary/testing/automated/microchip/megaavr0/clock.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/microchip/megaavr0/clock.h)/[`microlibrary/testing/automated/microchip/megaavr0/clock.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/microchip/megaavr0/clock.cc)
header/source file pair.
