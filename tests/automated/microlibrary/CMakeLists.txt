# microlibrary
#
# Copyright 2024, Andrew Countryman <apcountryman@gmail.com> and the microlibrary
# contributors
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
# file except in compliance with the License. You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under
# the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the specific language governing
# permissions and limitations under the License.

# Description: microlibrary static library automated tests CMake rules.

# microlibrary algorithms automated tests
add_subdirectory( algorithm )

# microlibrary::Error_Code automated tests
add_subdirectory( error_code )

# microlibrary::Fault_Reporting_Stream_IO_Driver automated tests
add_subdirectory( fault_reporting_stream_io_driver )

# microlibrary::Generic_Error automated tests
add_subdirectory( generic_error )

# microlibrary::Generic_Error_Category automated tests
add_subdirectory( generic_error_category )

# microlibrary integer utilities automated tests
add_subdirectory( integer )

# microlibrary::Stream automated tests
add_subdirectory( stream )

# microlibrary::Stream_IO_Driver automated tests
add_subdirectory( stream_io_driver )
