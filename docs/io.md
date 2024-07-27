# I/O Facilities

I/O facilities are defined in the `microlibrary` static library's
[`microlibrary/stream.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/stream.h)/[`microlibrary/stream.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/stream.cc)
header/source file pair.

## Table of Contents

1. [Device Error Handling](#device-error-handling)
1. [Stream I/O Driver](#stream-io-driver)
1. [Stream Core](#stream-core)
1. [Output Stream](#output-stream)
    1. [Output Formatters](#output-formatters)

## Device Error Handling

Two different types of streams (normal and fault reporting) are supported that are
differentiated by how device errors are handled.
Normal streams (`::microlibrary::Stream_IO_Driver`, `::microlibrary::Stream`,
`::microlibrary::Output_Stream`, and derived classes) cannot experience device errors,
handle device errors internally, or call `::microlibrary::handle_assertion_failure()` (via
a precondition or postcondition check) if a device error occurs.
Fault reporting streams (`::microlibrary::Fault_Reporting_Stream_IO_Driver`,
`::microlibrary::Fault_Reporting_Stream`, `::microlibrary::Fault_Reporting_Output_Stream`,
and derived classes) enter an error state when a device error occurs and report the device
error to the caller.

## Stream I/O Driver

The `::microlibrary::Stream_IO_Driver` and
`::microlibrary::Fault_Reporting_Stream_IO_Driver` stream I/O driver classes define the
standard interfaces that streams use to interact with devices.
`::microlibrary::Stream_IO_Driver` automated tests are defined in the
`test-automated-microlibrary-stream_io_driver` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/stream_io_driver/main.cc)
source file.
`::microlibrary::Fault_Reporting_Stream_IO_Driver` automated tests are defined in the
`test-automated-microlibrary-fault_reporting_stream_io_driver` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/fault_reporting_stream_io_driver/main.cc)
source file.

The `::microlibrary::Testing::Automated::Mock_Stream_IO_Driver` and
`::microlibrary::Testing::Automated::Mock_Fault_Reporting_Stream_IO_Driver` mock stream
I/O driver classes are available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mocks are defined in the
[`microlibrary/testing/automated/stream.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/stream.h)/[`microlibrary/testing/automated/stream.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/stream.cc)
header/source file pair.

## Stream Core

The `::microlibrary::Stream` and `::microlibrary::Fault_Reporting_Stream` stream core
classes store a stream's state information and associate a stream with a stream I/O
driver.
Stream state includes the following:
- End-of-file reached
- I/O error reported
- Fatal error (fault) reported (fault reporting streams only)

`::microlibrary::Stream` and `::microlibrary::Fault_Reporting_Stream` support the
following operations:
- To check if a stream is nominal (no errors reported and end-of-file has not been
  reached), use the `::microlibrary::Stream::is_nominal()` and
  `::microlibrary::Fault_Reporting_Stream::is_nominal()` member functions.
- To check if errors (I/O error and/or fatal error (fault)) have been reported, use the
  `::microlibrary::Stream::error_reported()` and
  `::microlibrary::Fault_Reporting_Stream::error_reported()` member functions.
- To check if end-of-file has been reached, use the
  `::microlibrary::Stream::end_of_file_reached()` and
  `::microlibrary::Fault_Reporting_Stream::end_of_file_reached()` member functions.
- To report that end-of-file has been reached from a derived class, use the
  `::microlibrary::Stream::report_end_of_file_reached()` and
  `::microlibrary::Fault_Reporting_Stream::report_end_of_file_reached()` member functions.
- To clear an end-of-file reached report from a derived class, use the
  `::microlibrary::Stream::clear_end_of_file_reached_report()` and
  `::microlibrary::Fault_Reporting_Stream::clear_end_of_file_reached_report()` member
  functions.
- To check if an I/O error has been reported, use the
  `::microlibrary::Stream::io_error_reported()` and
  `::microlibrary::Fault_Reporting_Stream::io_error_reported()` member functions.
- To report an I/O error, use the `::microlibrary::Stream::report_io_error()` and
  `::microlibrary::Fault_Reporting_Stream::report_io_error()` member functions.
- To clear an I/O error report, use the `::microlibrary::Stream::clear_io_error_report()`
  and `::microlibrary::Fault_Reporting_Stream::clear_io_error_report()` member functions.
- To check if a fatal error (fault) has been reported, use the
  `::microlibrary::Fault_Reporting_Stream::fatal_error_reported()` member function.
- To report a fatal error (fault) from a derived class, use the
  `::microlibrary::Fault_Reporting_Stream::report_fatal_error()` member function.
- To clear a fatal error (fault) report from a derived class, use the
  `::microlibrary::Fault_Reporting_Stream::clear_fatal_error_report()` member functions.
- To check if a stream is associated with a stream I/O driver, use the
  `::microlibrary::Stream::driver_is_set()` and
  `::microlibrary::Fault_Reporting_Stream::driver_is_set()` member functions.
- To get the stream I/O driver associated with a stream from a derived class, use the
  `::microlibrary::Stream::driver()` and
  `::microlibrary::Fault_Reporting_Stream::driver()` member functions.
- To associate a stream with a stream I/O driver from a derived class, use the
  `::microlibrary::Stream::set_driver()` and
  `::microlibrary::Fault_Reporting_Stream::set_driver()` member functions.

`::microlibrary::Stream` automated tests are defined in the
`test-automated-microlibrary-stream` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/stream/main.cc)
source file.
`::microlibrary::Fault_Reporting_Stream` automated tests are defined in the
`test-automated-microlibrary-fault_reporting_stream` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/fault_reporting_stream/main.cc)
source file.

## Output Stream

The `::microlibrary::Output_Stream` and `::microlibrary::Fault_Reporting_Output_Stream`
output stream classes define stream unformatted and formatted output operations.
The stream being nominal is a precondition for all output operations.
`::microlibrary::Stream` and `::microlibrary::Fault_Reporting_Stream` support the
following operations:
- To write any data that has been buffered to the data sink associated with a stream, use
  the `::microlibrary::Stream::flush()` and
  `::microlibrary::Fault_Reporting_Stream::flush()` member functions.
- To write unformatted data to the data sink associated with a stream, use the
  `::microlibrary::Stream::put()` and `::microlibrary::Fault_Reporting_Stream::put()`
  member functions.
- To write formatted data to the data sink associated with a stream, use the
  `::microlibrary::Stream::print()` and `::microlibrary::Fault_Reporting_Stream::print()`
  member functions.
  Formatting is controlled by the `::microlibrary::Output_Formatter` following each
  argument or a default constructed `::microlibrary::Output_Formatter` if one isn't
  provided.
```c++
#include "microlibrary/stream.h"

void foo( ::microlibrary::Output_Stream & stream, char const * string ) noexcept
{
    // default constructed ::microlibrary::Output_Formatter<char const *> used
    stream.print( string );

    // provided ::microlibrary::Output_Formatter<char const *> used
    stream.print( string, ::microlibrary::Output_Formatter<char const *>{} );
}
```

`::microlibrary::Output_Stream` automated tests are defined in the
`test-automated-microlibrary-output_stream` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/output_stream/main.cc)
source file.
`::microlibrary::Fault_Reporting_Output_Stream` automated tests are defined in the
`test-automated-microlibrary-fault_reporting_output_stream` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/fault_reporting_output_stream/main.cc)
source file.

The `::microlibrary::Testing::Automated::Mock_Output_Stream` and
`::microlibrary::Testing::Automated::Mock_Fault_Reporting_Output_Stream` mock output
stream classes are available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The mocks are defined in the
[`microlibrary/testing/automated/stream.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/stream.h)/[`microlibrary/testing/automated/stream.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/stream.cc)
header/source file pair.
- To access a stream's mock stream I/O driver, use the
  `::microlibrary::Testing::Automated::Mock_Output_Stream::driver()` and
  `::microlibrary::Testing::Automated::Mock_Fault_Reporting_Output_Stream::driver()`
  member functions.

The `::microlibrary::Testing::Automated::Output_String_Stream` and
`::microlibrary::Testing::Automated::Fault_Reporting_Output_String_Stream` output string
stream classes are available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The string streams are defined in the
[`microlibrary/testing/automated/stream.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/stream.h)/[`microlibrary/testing/automated/stream.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/stream.cc)
header/source file pair.
- To get the `std::string` that is written to by a stream, use the
  `::microlibrary::Testing::Automated::Mock_Output_Stream::string()` and
  `::microlibrary::Testing::Automated::Mock_Fault_Reporting_Output_Stream::string()`
  member functions.

The `::microlibrary::Testing::Automated::Output_Vector_Stream` and
`::microlibrary::Testing::Automated::Fault_Reporting_Output_Vector_Stream` output vector
stream classes are available if `MICROLIBRARY_TARGET` is `DEVELOPMENT_ENVIRONMENT`.
The vector streams are defined in the
[`microlibrary/testing/automated/stream.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/include/microlibrary/testing/automated/stream.h)/[`microlibrary/testing/automated/stream.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/DEVELOPMENT_ENVIRONMENT/source/microlibrary/testing/automated/stream.cc)
header/source file pair.
- To get the `std::vector` that is written to by a stream, use the
  `::microlibrary::Testing::Automated::Mock_Output_Stream::vector()` and
  `::microlibrary::Testing::Automated::Mock_Fault_Reporting_Output_Stream::vector()`
  member functions.

### Output Formatters

The `::microlibrary::Output_Formatter` template class must be fully or partially
specialized for each type that will support formatted output.
Specialization constructor parameters can be used to let the user configure formatting.

The following `::microlibrary::Output_Formatter` specializations are defined in the
[`microlibrary/stream.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/stream.h)/[`microlibrary/stream.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/stream.cc)
header/source file pair:
- `::microlibrary::Output_Formatter<char>`
- `::microlibrary::Output_Formatter<char const *>`
- `::microlibrary::Output_Formatter<::microlibrary::ROM::String>`
- `::microlibrary::Output_Formatter<::microlibrary::Error_Code>`
- `::microlibrary::Output_Formatter<Enum,
  std::enable_if_t<::microlibrary::is_error_code_enum_v<Enum>>>`

The `::microlibrary::Output_Formatter<char>` specialization does not support user
formatting configuration.
`::microlibrary::Output_Formatter<char>` automated tests are defined in the
`test-automated-microlibrary-output_stream` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/output_stream/main.cc)
source file and the `test-automated-microlibrary-fault_reporting_output_stream` automated
test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/fault_reporting_output_stream/main.cc)
source file.

The `::microlibrary::Output_Formatter<char const *>` specialization does not support user
formatting configuration.
`::microlibrary::Output_Formatter<char const *>` automated tests are defined in the
`test-automated-microlibrary-output_stream` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/output_stream/main.cc)
source file and the `test-automated-microlibrary-fault_reporting_output_stream` automated
test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/fault_reporting_output_stream/main.cc)
source file.

The `::microlibrary::Output_Formatter<::microlibrary::ROM::String>` specialization does
not support user formatting configuration.

The `::microlibrary::Output_Formatter<::microlibrary::Error_Code>` specialization does not
support user formatting configuration.
`::microlibrary::Output_Formatter<::microlibrary::Error_Code>` automated tests are defined
in the `test-automated-microlibrary-output_stream` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/output_stream/main.cc)
source file and the `test-automated-microlibrary-fault_reporting_output_stream` automated
test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/fault_reporting_output_stream/main.cc)
source file.
```c++
#include "microlibrary/error.h"
#include "microlibrary/stream.h"

void foo( ::microlibrary::Output_Stream & stream ) noexcept
{
    // output will be "::microlibrary::Generic_Error::LOGIC_ERROR"
    stream.print( ::microlibrary::Error_Code{ ::microlibrary::Generic_Error::LOGIC_ERROR } );
}
```

The `::microlibrary::Output_Formatter<Enum,
std::enable_if_t<::microlibrary::is_error_code_enum_v<Enum>>>` specialization does not
support user formatting configuration.
`::microlibrary::Output_Formatter<Enum,
std::enable_if_t<::microlibrary::is_error_code_enum_v<Enum>>>` automated tests are defined
in the `test-automated-microlibrary-output_stream` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/output_stream/main.cc)
source file and the `test-automated-microlibrary-fault_reporting_output_stream` automated
test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/fault_reporting_output_stream/main.cc)
source file.
```c++
#include "microlibrary/error.h"
#include "microlibrary/stream.h"

void foo( ::microlibrary::Output_Stream & stream ) noexcept
{
    // output will be "::microlibrary::Generic_Error::LOGIC_ERROR"
    stream.print( ::microlibrary::Generic_Error::LOGIC_ERROR );
}
```

The following formatting helper types and `::microlibrary::Output_Formatter`
specializations are defined in the
[`microlibrary/format.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/format.h)/[`microlibrary/format.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/format.cc)
header/source file pair:
- `::microlibrary::Format::Bin`
- `::microlibrary::Output_Formatter<::microlibrary::Format::Bin<Integer>>`

The `::microlibrary::Format::Bin` class is used to print an integer type in binary.
The `::microlibrary::Output::Formatter<::microlibrary::Format::Bin<Integer>>`
specialization does not support user formatting configuration.
`::microlibrary::Output_Formatter<::microlibrary::Format::Bin<Integer>>` automated tests
are defined in the `test-automated-microlibrary-format-bin` automated test executable's
[`main.cc`](https://github.com/apcountryman/microlibrary/blob/main/tests/automated/microlibrary/format/bin/main.cc)
source file.
```c++
#include <cstdint>

#include "microlibrary/format.h"
#include "microlibrary/stream.h"

void foo( ::microlibrary::Output_Stream & stream ) noexcept
{
    // output will be "0b01010101"
    stream.print( ::microlibrary::Format::Bin{ std::uint8_t{ 0b01010101 } } );
}
```
