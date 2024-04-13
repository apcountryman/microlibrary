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

# Description: microlibrary static library Arm Cortex-M0+ HIL CMake rules.

set( MICROLIBRARY_ARM_CORTEX_M0PLUS_HIL_LIST
    "ARM_CORTEX_M0PLUS"
    "MICROCHIP_SAM_D21DA1"
    )
if( NOT MICROLIBRARY_HIL STREQUAL "ALL" AND NOT MICROLIBRARY_HIL IN_LIST MICROLIBRARY_ARM_CORTEX_M0PLUS_HIL_LIST )
    return()
endif( NOT MICROLIBRARY_HIL STREQUAL "ALL" AND NOT MICROLIBRARY_HIL IN_LIST MICROLIBRARY_ARM_CORTEX_M0PLUS_HIL_LIST )

add_subdirectory( ANY )
add_subdirectory( DEVELOPMENT_ENVIRONMENT )
add_subdirectory( HARDWARE )
