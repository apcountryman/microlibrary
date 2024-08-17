# Pointer Utilities

Pointer utilities are defined in the `microlibrary` static library's
[`microlibrary/pointer.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/pointer.h)/[`microlibrary/pointer.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/pointer.cc)
header/source file pair.

## Table of Contents

1. [`Not_Null`](#not_null)

## `Not_Null`

To verify a pointer is not null and propagate the pointer without needing further not null
checks, use the `::microlibrary::Not_Null` utility.
- Pointer operations (operators `*` and `->`) are supported.
- To get the wrapped pointer, use the `::microlibrary::Not_Null::get()` member functions.
