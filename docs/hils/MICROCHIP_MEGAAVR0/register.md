# Register Facilities

Microchip megaAVR 0-series register facilities are defined in the `microlibrary` static
library's
[`microlibrary/microchip/megaavr0/register.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/include/microlibrary/microchip/megaavr0/register.h)/[`microlibrary/microchip/megaavr0/register.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/ANY/source/microlibrary/microchip/megaavr0/register.cc)
header/source file pair.

## Table of Contents

1. [Protected Register](#protected-register)

## Protected Register

The `::microlibrary::Microchip::megaAVR0::Protected_Register` class is used to declare a
memory-mapped protected register.
`::microlibrary::Microchip::megaAVR0::Protected_Register` is an alias for
`::microlibrary::Testing::Automated::Mock_Register` when `MICROLIBRARY_TARGET` is
`DEVELOPMENT_ENVIRONMENT`.
Register access is restricted to the following operations:
- Conversion to the register's underlying integer type (reading the register)
- Assignment
- Bitwise AND assignment
- Bitwise OR assignment
- Bitwise XOR assignment
