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

# Description: microlibrary static library Arm Cortex-M0+ HIL, hardware target CMake
#       rules.

if( NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
    return()
endif( NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )

if( MICROLIBRARY_HIL STREQUAL "ARM_CORTEX_M0PLUS" )
    if( TARGET microlibrary-arm-cortex-m0plus )
        target_link_libraries( microlibrary
            PUBLIC microlibrary-arm-cortex-m0plus
            )
    else( TARGET microlibrary-arm-cortex-m0plus )
        message(
            STATUS
            "microlibrary-arm-cortex-m0plus target not found, using default configuration"
            )
    endif( TARGET microlibrary-arm-cortex-m0plus )
endif( MICROLIBRARY_HIL STREQUAL "ARM_CORTEX_M0PLUS" )
