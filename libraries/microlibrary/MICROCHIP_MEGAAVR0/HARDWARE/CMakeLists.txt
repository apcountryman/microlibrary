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

# Description: microlibrary static library Microchip megaAVR 0-series HIL, hardware target
#       CMake rules.

if( NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
    return()
endif( NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )

target_include_directories( microlibrary
    PUBLIC include
    )

target_sources( microlibrary
    PRIVATE source/microlibrary/microchip/megaavr0/peripheral/instances.cc
    )

target_link_libraries( microlibrary
    PUBLIC avr-libcpp
    )
