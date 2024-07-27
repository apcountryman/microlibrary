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

# Description: Build (Microchip megaAVR HIL, hardware target, ATmega2560 MCU)
#       configuration.

set( CMAKE_BUILD_TYPE              "RelWithDebInfo" CACHE INTERNAL "" )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON               CACHE INTERNAL "" )

set( MICROLIBRARY_HIL                                             "MICROCHIP_MEGAAVR" CACHE INTERNAL "" )
set( MICROLIBRARY_TARGET                                          "HARDWARE"          CACHE INTERNAL "" )
set( MICROLIBRARY_SUPPRESS_ASSERTION_FAILURE_LOCATION_INFORMATION ON                  CACHE INTERNAL "" )
set( MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION       OFF                 CACHE INTERNAL "" )
set( MICROLIBRARY_BUILD_AUTOMATED_TESTS                           OFF                 CACHE INTERNAL "" )
set( MICROLIBRARY_BUILD_INTERACTIVE_TESTS                         OFF                 CACHE INTERNAL "" )

set( MICROLIBRARY_MICROCHIP_MEGAAVR_MCU   "atmega2560" CACHE INTERNAL "" )
set( MICROLIBRARY_MICROCHIP_MEGAAVR_F_CPU "16000000UL" CACHE INTERNAL "" )
