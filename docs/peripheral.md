# Peripheral Facilities

Peripheral facilities are defined in the `microlibrary` static library's
[`microlibrary/peripheral.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/peripheral.h)/[`microlibrary/peripheral.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/peripheral.cc)
header/source file pair.

## Table of Contents

1. [Peripheral Instance](#peripheral-instance)

## Peripheral Instance

The `::microlibrary::Peripheral::Instance` template class is used to define memory-mapped
peripheral instances.
- To get a pointer to a peripheral instance, use the
  `::microlibrary::Peripheral::Instance::pointer()` static member function.
