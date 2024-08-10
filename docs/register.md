# Register Facilities

Register facilities are defined in the `microlibrary` static library's
[`microlibrary/register.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/register.h)/[`microlibrary/register.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/register.cc)
header/source file pair.

## Table of Contents

1. [Register](#register)

## Register

The `::microlibrary::Register` class is used to declare a microcontroller register.
Register access is restricted to the following operations:
- Conversion to the register's underlying integer type (reading the register)
- Assignment
- Bitwise AND assignment
- Bitwise OR assignment
- Bitwise XOR assignment

`::microlibrary::Register` is an alias for the
`::microlibrary::Testing::Automated::Mock_Register` mock register class when
`MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mock is defined in the
[`microlibrary/testing/automated/register.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/register.h)/[`microlibrary/testing/automated/register.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/register.cc)
header/source file pair.
