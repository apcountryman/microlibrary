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
1. [`for_each()`](#for_each)

## Algorithm Functor Policies

The following algorithm functor policy types are used to select algorithm implementations
that check for functor reported errors and report functor errors to the caller:
- `::microlibrary::Functor_Reports_Errors`
- `::microlibrary::Functor_Reports_Errors_Return_Functor`
- `::microlibrary::Functor_Reports_Errors_Discard_Functor`

## `for_each()`

To apply a functor to a range, use the `::microlibrary::for_each()` algorithm.
To report functor errors to the caller, use the
`::microlibrary::Functor_Reports_Errors_Return_Functor` or
`::microlibrary::Functor_Reports_Errors_Discard_Functor` algorithm functor policy.
```c++
#include <cstdint>

#include "microlibrary/algorithm.h"
#include "microlibrary/result.h"

void foo( std::uint_fast8_t value ) noexcept;

auto bar( std::uint_fast8_t value ) noexcept -> Result<void>;

auto wibble( std::uint_fast8_t const * begin, std::uint_fast8_t const * end ) noexcept
{
    return ::microlibrary::for_each( begin, end, foo );
}

auto wobble( std::uint_fast8_t const * begin, std::uint_fast8_t const * end ) noexcept
{
    auto result = ::microlibrary::for_each<::microlibrary::Functor_Reports_Errors_Return_Functor>(
        begin, end, bar );
    if ( result.is_error() ) {
        // handle error
    } // if

    return result.value();
}

void wobble( std::uint_fast8_t const * begin, std::uint_fast8_t const * end ) noexcept
{
    auto result = ::microlibrary::for_each<::microlibrary::Functor_Reports_Errors_Discard_Functor>(
        begin, end, bar );
    if ( result.is_error() ) {
        // handle error
    } // if
}
```
