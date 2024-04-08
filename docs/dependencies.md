# Dependencies

## Table of Contents

1. [avr-libcpp](#avr-libcpp)
1. [GoogleTest](#googletest)

## avr-libcpp
avr-libcpp is a microlibrary dependency if `MICROLIBRARY_HIL` is `MICROCHIP_MEGAAVR`, and
`MICROLIBRARY_TARGET` is `HARDWARE`.
A parent project supplied copy of avr-libcpp can be used instead of microlibrary's
avr-libcpp submodule by setting the `MICROLIBRARY_USE_PARENT_PROJECT_AVRLIBCPP` option to
`ON`.

## GoogleTest

GoogleTest is a microlibrary dependency if `MICROLIBRARY_TARGET` is
`DEVELOPMENT_ENVIRONMENT`.
A parent project supplied copy of GoogleTest can be used instead of microlibrary's
GoogleTest submodule by setting the `MICROLIBRARY_USE_PARENT_PROJECT_GOOGLETEST` option to
`ON`.
