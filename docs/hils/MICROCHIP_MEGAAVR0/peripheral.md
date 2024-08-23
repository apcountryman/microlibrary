# Peripheral Facilities

## Table of Contents

1. [Peripherals](#peripherals)

## Peripherals

Microchip megaAVR 0-series peripheral instances are defined in the `microlibrary` static
library's
[`microlibrary/microchip/megaavr0/peripheral/instances.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/HARDWARE/include/microlibrary/microchip/megaavr0/peripheral/instances.h)/[`microlibrary/microchip/megaavr0/peripheral/instances.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/MICROCHIP_MEGAAVR0/HARDWARE/source/microlibrary/microchip/megaavr0/peripheral/instances.cc)
header/source file pair which is available if `MICROLIBRARY_TARGET` is `HARDWARE`.
Peripheral instance names are based on the names used in the "Peripheral Module Address
Map" table of the datasheets with the following change: a `0` is added to the end of the
name of peripherals that only have a single instance to differentiate the peripheral name
and the instance name.
The following peripheral instances are defined (listed alphabetically):

The availability of these peripheral instance definitions depends on the specific
Microchip megaAVR 0-series microcontroller that is used.
