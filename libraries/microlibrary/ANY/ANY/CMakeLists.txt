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

# Description: microlibrary static library any HIL, any target CMake rules.

target_include_directories( microlibrary
    PUBLIC include
    )

target_compile_definitions( microlibrary
    PUBLIC MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT=$<STREQUAL:"${MICROLIBRARY_TARGET}","DEVELOPMENT_ENVIRONMENT">
    PUBLIC MICROLIBRARY_TARGET_IS_HARDWARE=$<STREQUAL:"${MICROLIBRARY_TARGET}","HARDWARE">
    PUBLIC MICROLIBRARY_TARGET_IS_NONE=$<STREQUAL:"${MICROLIBRARY_TARGET}","NONE">
    PUBLIC MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION=$<BOOL:${MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION}>
    PUBLIC MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION=$<BOOL:${MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION}>
    )

target_sources( microlibrary
    PRIVATE source/microlibrary.cc
    PRIVATE source/microlibrary/algorithm.cc
    PRIVATE source/microlibrary/arm.cc
    PRIVATE source/microlibrary/arm/cortex.cc
    PRIVATE source/microlibrary/assertion_failure.cc
    PRIVATE source/microlibrary/enum.cc
    PRIVATE source/microlibrary/error.cc
    PRIVATE source/microlibrary/integer.cc
    PRIVATE source/microlibrary/microchip.cc
    PRIVATE source/microlibrary/microchip/sam.cc
    PRIVATE source/microlibrary/postcondition.cc
    PRIVATE source/microlibrary/precondition.cc
    PRIVATE source/microlibrary/result.cc
    PRIVATE source/microlibrary/rom.cc
    PRIVATE source/microlibrary/stream.cc
    PRIVATE source/microlibrary/testing.cc
    )
