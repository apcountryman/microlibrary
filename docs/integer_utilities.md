# Integer Utilities

Integer utilities are defined in the `microlibrary` static library's
[`microlibrary/integer.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/integer.h)/[`microlibrary/integer.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/integer.cc)
header/source file pair.
Integer utilities automated tests are defined in the `test-automated-microlibrary-integer`
automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/integer/main.cc)
source file.

## Table of Contents

1. [`to_unsigned()`](#to_unsigned)
1. [`highest_bit_set()`](#highest_bit_set)
1. [`mask()`](#mask)
1. [`reflect()`](#reflect)
1. [`is_power_of_two()`](#is_power_of_two)

## `to_unsigned()`

To convert a potentially signed integer to its bitwise unsigned integer equivalent, use
the `::microlibrary::to_unsigned()` utility.

## `highest_bit_set()`

To lookup an unsigned integer value's highest bit set, use the
`::microlibrary::highest_bit_set()` utility.

## `mask()`

To create a bit mask, use the `::microlibrary::mask()` utility.

## `reflect()`

To reflect an unsigned integer's bits, use the `::microlibrary::reflect()` utility.

## `is_power_of_two()`

To check if an unsigned integer is a power of two, use the
`::microlibrary::is_power_of_two()` utility.
