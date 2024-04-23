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

# Description: microlibrary static library CMake rules.

add_library( microlibrary STATIC )

target_compile_definitions( microlibrary
    PUBLIC MICROLIBRARY_TARGET_IS_DEVELOPMENT_ENVIRONMENT=$<IF:$<STREQUAL:"${MICROLIBRARY_TARGET}","DEVELOPMENT_ENVIRONMENT">,1,0>
    PUBLIC MICROLIBRARY_TARGET_IS_HARDWARE=$<IF:$<STREQUAL:"${MICROLIBRARY_TARGET}","HARDWARE">,1,0>
    PUBLIC MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION=$<BOOL:${MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION}>
    )

add_subdirectory( ANY )
add_subdirectory( ARM_CORTEX_M0PLUS )
add_subdirectory( MICROCHIP_MEGAAVR )
add_subdirectory( MICROCHIP_MEGAAVR0 )
add_subdirectory( MICROCHIP_SAM_D21DA1 )
add_subdirectory( CUSTOM )
