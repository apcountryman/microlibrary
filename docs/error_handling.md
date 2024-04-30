# Error Handling Facilities

## Table of Contents

1. [Error Identification](#error-identification)
    1. [Library Defined Errors](#library-defined-errors)
    1. [Defining Additional Errors](#defining-additional-errors)
1. [Assertions](#assertions)
    1. [Precondition Assertions](#precondition-assertions)
    1. [Assertion Failure Handling](#assertion-failure-handling)

## Error Identification

Error identification facilities are defined in the `microlibrary` static library's
[`microlibrary/error.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/error.h)/[`microlibrary/error.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/error.cc)
header/source file pair.

The `::microlibrary::Error_Code` class is used to identify errors.
An error can be identified using the combination of the address of the error's error
category (`::microlibrary::Error_Category`) and the error's error ID
(`::microlibrary::Error_ID`).
- To get a reference to an error's error category, use the
  `::microlibrary::Error_Code::category()` member function.
- To get an error's error ID, use the `::microlibrary::Error_Code::id()` member function.
- Implicit conversion from an enum class to a `::microlibrary::Error_Code` is enabled if
  `::microlibrary::is_error_code_enum` has been appropriately specialized for the enum
  class.
- Direct comparison for equality and inequality is supported.

`::microlibrary::Error_Code` automated tests are defined in the
`test-automated-microlibrary-error_code` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/error_code/main.cc)
source file.

A `std::ostream` insertion operator is defined for `::microlibrary::Error_Code` if
`MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/error.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/error.h)/[`microlibrary/testing/automated/error.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/error.cc)
header/source file pair.

The `::microlibrary::Error_Category` class is used to get human readable error
information.
- To get an error category's name, use the `::microlibrary::Error_Category::name()` member
  function.
- To get an error ID's description, use the
  `::microlibrary::Error_Category::error_description()` member function.

If the `MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION` project configuration
option is `ON`, these functions will return empty strings.

### Library Defined Errors
microlibrary defines the following errors sets:
- Generic errors
- Mock errors

The generic error set is defined in the
[`microlibrary/error.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/error.h)/[`microlibrary/error.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/error.cc)
header/source file pair.

The `::microlibrary::Generic_Error` enum class's enumerators identify the specific errors
in the set.
Implicit conversion from `::microlibrary::Generic_Error` to `::microlibrary::Error_Code`
is enabled.

The `::microlibrary::Generic_Error_Category` class is the error category for the set.
- To get a reference to the `::microlibrary::Generic_Error_Category` instance, use the
  `::microlibrary::Generic_Error_Category::instance()` static member function.

Generic error set automated tests are defined in the
`test-automated-microlibrary-generic_error` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/generic_error/main.cc)
source file and the `test-automated-microlibrary-generic_error_category` automated test
executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/generic_error_category/main.cc)
source file

A `std::ostream` insertion operator is defined for `::microlibrary::Generic_Error` if
`MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The insertion operator is defined in the
[`microlibrary/testing/automated/error.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/error.h)/[`microlibrary/testing/automated/error.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/error.cc)
header/source file pair.

The mock error set is available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mock error set is defined in the
[`microlibrary/testing/automated/error.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/error.h)/[`microlibrary/testing/automated/error.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/error.cc)
header/source file pair.

The `::microlibrary::Testing::Automated::Mock_Error` enum class is used to identify
"specific" errors in the set.
A `std::ostream` insertion operator is defined for
`::microlibrary::Testing::Automated::Mock_Error`.

The `::microlibrary::Testing::Automated::Mock_Error_Category` class is the error category
for the set.
- To get a reference to a common `::microlibrary::Testing::Automated::Mock_Error_Category`
  instance, use the `::microlibrary::Testing::Automated::Mock_Error_Category::instance()`
  static member function.
  Additional `::microlibrary::Testing::Automated::Mock_Error_Category` instances can be
  constructed as needed to support automated testing.

### Defining Additional Errors
To create an additional error set, do the following:
1. Define an enum class whose enumerators identify the specific errors in the set.
   The underlying type for the enum class must be `::microlibrary::Error_ID`.
2. Create an error category class for the error set.
   `::microlibrary::Error_Category` must be a public base of this class.
   This class should be a singleton.
3. Define a `make_error_code()` function in the same namespace as the enum class that
   takes the enum class and returns a `::microlibrary::Error_Code`.
4. Register the enum class as an error code enum by specializing
   `::microlibrary::is_error_code_enum` for the enum class.

## Assertions

### Precondition Assertions

Precondition assertion facilities are defined in the `microlibrary` static library's
[`microlibrary/precondition.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/precondition.h)/[`microlibrary/precondition.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/precondition.cc)
header/source file pair.

To check a precondition expectation, use the `MICROLIBRARY_EXPECT()` macro.
If the `expectation` macro argument evaluates to `false`,
`::microlibrary::handle_assertion_failure()` will be called.
If code is structured in a way that an execution path being taken indicates a precondition
expectation has not been met, use the `MICROLIBRARY_EXPECTATION_NOT_MET()` macro to
unconditionally call `::microlibrary::handle_assertion_failure()`.

To create a function overload that lets the user bypass precondition expectation checks,
use the `::microlibrary::Bypass_Precondition_Expectation_Checks` type.
Users can then use the `::microlibrary::BYPASS_PRECONDITION_EXPECTATION_CHECKS` constant
to select the function overload that bypasses the precondition expectation checks.

To create a function overload that lets the user run the function's precondition
expectation checks while bypassing a called function's precondition expectation checks,
use the `::microlibrary::Run_Precondition_Expectation_Checks` type.
Users can then use the `::microlibrary::RUN_PRECONDITION_EXPECTATION_CHECKS` constant to
select the function overload that runs the function's precondition expectation checks
while bypassing the called function's precondition expectation checks.

### Assertion Failure Handling

Assertion failure handling facilities are defined in the `microlibrary` static library's
[`microlibrary/assertion_failure.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/assertion_failure.h)/[`microlibrary/assertion_failure.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/assertion_failure.cc)
header/source file pair.

The `::microlibrary::handle_assertion_failure()` function is called if an assertion
failure occurs.
This function is defined as a weak alias for its default implementation so that its
behavior can be overridden.
The behavior of the default implementation depends on `MICROLIBRARY_TARGET`.
If `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`, the default implementation writes
all available information about an assertion failure to `std::cerr` and calls
`std::abort()`.
If `MICROLIBRARY_TARGET` is not `DEVELOPMENT_ENVIRONMENT`, the default implementation
simply calls `std::abort()`.
