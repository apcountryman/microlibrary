# Register Facilities

Register facilities are defined in the `microlibrary` static library's
[`microlibrary/register.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/register.h)/[`microlibrary/register.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/register.cc)
header/source file pair.

## Table of Contents

1. [Register](#register)
1. [Reserved Register](#reserved-register)
1. [Read-Only Register](#read-only-register)
1. [Write-Only Register](#write-only-register)

## Register

The `::microlibrary::Register` class is used to declare a memory-mapped register.
`::microlibrary::Register` is an alias for the
`::microlibrary::Testing::Automated::Mock_Register` when `MICROLIBRARY_TARGET` is
`DEVELOPMENT_ENVIRONMENT`.
Register access is restricted to the following operations:
- Conversion to the register's underlying integer type (reading the register)
- Assignment
- Bitwise AND assignment
- Bitwise OR assignment
- Bitwise XOR assignment

The `::microlibrary::Testing::Automated::Mock_Register` mock register class is available
if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mock is defined in the
[`microlibrary/testing/automated/register.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/register.h)/[`microlibrary/testing/automated/register.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/register.cc)
header/source file pair.

## Reserved Register

The `::microlibrary::Reserved_Register` class is used to declare a memory-mapped reserved
register.
Reserved registers cannot be accessed.

## Read-Only Register

The `::microlibrary::Read_Only_Register` class is used to declare a memory-mapped
read-only register.
`::microlibrary::Read_Only_Register` is an alias for the
`::microlibrary::Testing::Automated::Mock_Read_Only_Register` when `MICROLIBRARY_TARGET`
is `DEVELOPMENT_ENVIRONMENT`.
Register access is restricted to the following operations:
- Conversion to the register's underlying integer type (reading the register)

The `::microlibrary::Testing::Automated::Mock_Read_Only_Register` mock register class is
available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mock is defined in the
[`microlibrary/testing/automated/register.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/register.h)/[`microlibrary/testing/automated/register.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/register.cc)
header/source file pair.

## Write-Only Register

The `::microlibrary::Write_Only_Register` class is used to declare a memory-mapped
write-only register.
`::microlibrary::Write_Only_Register` is an alias for the
`::microlibrary::Testing::Automated::Mock_Write_Only_Register` when `MICROLIBRARY_TARGET`
is `DEVELOPMENT_ENVIRONMENT`.
Register access is restricted to the following operations:
- Assignment

The `::microlibrary::Testing::Automated::Mock_Write_Only_Register` mock register class is
available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mock is defined in the
[`microlibrary/testing/automated/register.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/register.h)/[`microlibrary/testing/automated/register.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/register.cc)
header/source file pair.
