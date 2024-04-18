# Dependencies

## Table of Contents

1. [avr-libcpp](#avr-libcpp)
1. [GoogleTest](#googletest)

## avr-libcpp
avr-libcpp is a microlibrary dependency if `MICROLIBRARY_HIL` is `MICROCHIP_MEGAAVR`, and
`MICROLIBRARY_TARGET` is `HARDWARE`.
A parent project supplied copy of avr-libcpp can be used instead of the microlibrary
supplied copy by using CMake's FetchContent module to add the parent project supplied copy
to a CMake build before miicrolibrary is added to the CMake build.
```cmake
include( FetchContent )
FetchContent_Declare( avrlibcpp
    ...
    )
```

If a parent project supplied copy of avr-libcpp is used, avr-libcpp must be configured as
follows:
- `AVRLIBCPP_SUPPRESS_SFR_MACROS` must be `ON`

## GoogleTest

GoogleTest is a microlibrary dependency if `MICROLIBRARY_TARGET` is
`DEVELOPMENT_ENVIRONMENT`.
A parent project supplied copy of GoogleTest can be used instead of the microlibrary
supplied copy by using CMake's FetchContent module to add the parent project supplied copy
to a CMake build before miicrolibrary is added to the CMake build.
```cmake
include( FetchContent )
FetchContent_Declare( googletest
    ...
    )
```
