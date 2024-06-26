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

# Description: avr-libcpp dependency CMake rules.

if( NOT MICROLIBRARY_HIL STREQUAL "MICROCHIP_MEGAAVR" AND NOT MICROLIBRARY_HIL STREQUAL "MICROCHIP_MEGAAVR0" )
    return()
endif( NOT MICROLIBRARY_HIL STREQUAL "MICROCHIP_MEGAAVR" AND NOT MICROLIBRARY_HIL STREQUAL "MICROCHIP_MEGAAVR0" )

if( NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
    return()
endif( NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )

FetchContent_GetProperties( avrlibcpp )
if( NOT avrlibcpp_POPULATED )
    set( AVRLIBCPP_SUPPRESS_SFR_MACROS ON CACHE INTERNAL "" )
endif( NOT avrlibcpp_POPULATED )

if( NOT AVRLIBCPP_SUPPRESS_SFR_MACROS )
    message( FATAL_ERROR
        "AVRLIBCPP_SUPPRESS_SFR_MACROS must be 'ON'."
        )
endif( NOT AVRLIBCPP_SUPPRESS_SFR_MACROS )

FetchContent_Declare( avrlibcpp
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/avr-libcpp"
    )
FetchContent_MakeAvailable( avrlibcpp )
