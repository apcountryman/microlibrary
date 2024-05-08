# Algorithms

Algorithms are defined in the `microlibrary` static library's
[`microlibrary/algorithm.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/algorithm.h)/[`microlibrary/algorithm.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/algorithm.cc)
header/source file pair.
Algorithms automated tests are defined in the `test-automated-microlibrary-algorithm`
automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/algorithm/main.cc)
source file.

## Table of Contents

1. [Algorithm Functor Policies](#algorithm-functor-policies)

## Algorithm Functor Policies

The following algorithm functor policy types are used to select algorithm implementations
that check for functor reported errors and report functor errors to the caller:
- `::microlibrary::Functor_Reports_Errors`
- `::microlibrary::Functor_Reports_Errors_Return_Functor`
- `::microlibrary::Functor_Reports_Errors_Discard_Functor`
