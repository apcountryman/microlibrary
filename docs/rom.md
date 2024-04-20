# ROM Facilities

ROM facilities are defined in the `microlibrary` static library's
[`microlibrary/rom.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/rom.h)/[`microlibrary/rom.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/rom.cc)
header/source file pair.

## Table of Contents

1. [Null-Terminated Strings](#null-terminated-strings)

## Null-Terminated Strings

The `::microlibrary::ROM::String` type is used for handles to null-terminated strings that
may be stored in ROM.
This type defaults to `char const *`.
A custom HIL can replace this type with a HIL specific version by doing the following:
- Provide a `microlibrary-custom` library that provides `microlibrary/hil/rom.h`
- Define `MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED` to be a value that will be evaluated as
  true by the preprocessor (e.g. `1`) in `microlibrary/hil/rom.h`
- Define the HIL specific version of `::microlibrary::ROM::String` in
  `microlibrary/hil/rom.h`

If a function is being overloaded to work with null-terminated strings stored in RAM and
null-terminated strings that may be stored in ROM, the `::microlibrary::ROM::String`
overload(s) must only be defined if `MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED` is true since
`::microlibrary::ROM::String` defaults to `char const *`.
```c++
void foo( char const * string ) noexcept;

#if MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
void foo( ::microlibrary::ROM::String string ) noexcept;
#endif // MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED
```

To create a string literal that can be stored in ROM, use the `MICROLIBRARY_ROM_STRING()`
macro:
```c++
auto foo() noexcept -> ::microlibrary::ROM::String
{
    return MICROLIBRARY_ROM_STRING( "foo" );
}
```

A custom HIL can replace `MICROLIBRARY_ROM_STRING()` with a HIL specific version by doing
the following:
- Provide a `microlibrary-custom` library that provides `microlibrary/hil/rom.h`
- Define `MICROLIBRARY_ROM_STRING_IS_HIL_DEFINED` to be a value that will be evaluated as
  true by the preprocessor (e.g. `1`) `in microlibrary/hil/rom.h`
- Define the HIL specific version of `MICROLIBRARY_ROM_STRING()` in
  `microlibrary/hil/rom.h`
