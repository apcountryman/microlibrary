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

# Description: Core CMake rules.

cmake_minimum_required( VERSION 3.16.3 )
project( microlibrary
    LANGUAGES CXX
    )

# general configuration

set(
    MICROLIBRARY_HIL
    "" CACHE STRING
    "microlibrary: HIL."
    )

set(
    MICROLIBRARY_TARGET
    "" CACHE STRING
    "microlibrary: Target environment."
    )

option(
    MICROLIBRARY_BUILD_AUTOMATED_TESTS
    "microlibrary: Build automated tests."
    OFF
    )

option(
    MICROLIBRARY_BUILD_INTERACTIVE_TESTS
    "microlibrary: Build interactive tests."
    OFF
    )

# general configuration validation

set(
    MICROLIBRARY_HIL_LIST
    "ARM_CORTEX_M0PLUS"
    "ALL"
    "CUSTOM"
    )
if( NOT MICROLIBRARY_HIL IN_LIST MICROLIBRARY_HIL_LIST )
    message(
        FATAL_ERROR
        "'${MICROLIBRARY_HIL}' is not a valid value for MICROLIBRARY_HIL.\n"
        "Please set it to a value from the first column of the following list:\n"
        "    ARM_CORTEX_M0PLUS      Generic Arm Cortex-M0+ HIL.\n"
        "    ALL                    All officially supported HILs.\n"
        "    CUSTOM                 A HIL that is not officially supported.\n"
        )
endif( NOT MICROLIBRARY_HIL IN_LIST MICROLIBRARY_HIL_LIST )

set(
    MICROLIBRARY_TARGET_LIST
    "DEVELOPMENT_ENVIRONMENT"
    "HARDWARE"
    "NONE"
    )
if( NOT MICROLIBRARY_TARGET IN_LIST MICROLIBRARY_TARGET_LIST )
    message(
        FATAL_ERROR
        "'${MICROLIBRARY_TARGET}' is not a valid value for MICROLIBRARY_TARGET.\n"
        "Please set it to a value from the first column of the following list:\n"
        "    DEVELOPMENT_ENVIRONMENT    Development environment.\n"
        "    HARDWARE                   Hardware.\n"
        "    NONE                       None (used to exclude target specific code from static analysis).\n"
        )
endif( NOT MICROLIBRARY_TARGET IN_LIST MICROLIBRARY_TARGET_LIST )

if( MICROLIBRARY_HIL STREQUAL "ALL" AND NOT ( MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" OR MICROLIBRARY_TARGET STREQUAL "NONE" ) )
    message(
        FATAL_ERROR
        "MICROLIBRARY_TARGET must be 'DEVELOPMENT_ENVIRONMENT' or 'NONE' if MICROLIBRARY_HIL is 'ALL'"
        )
endif( MICROLIBRARY_HIL STREQUAL "ALL" AND NOT ( MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" OR MICROLIBRARY_TARGET STREQUAL "NONE" ) )

if( MICROLIBRARY_HIL STREQUAL "CUSTOM" AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR )
    message(
        FATAL_ERROR
        "Standalone builds are not supported if MICROLIBRARY_HIL is 'CUSTOM'"
        )
endif( MICROLIBRARY_HIL STREQUAL "CUSTOM" AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR )

if( MICROLIBRARY_BUILD_AUTOMATED_TESTS AND NOT MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" )
    message(
        FATAL_ERROR
        "automated tests can only be built if MICROLIBRARY_TARGET is 'DEVELOPMENT_ENVIRONMENT'"
        )
endif( MICROLIBRARY_BUILD_AUTOMATED_TESTS AND NOT MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" )

if( MICROLIBRARY_BUILD_INTERACTIVE_TESTS AND NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
    message(
        FATAL_ERROR
        "interactive tests can only be built if MICROLIBRARY_TARGET is 'HARDWARE'"
        )
endif( MICROLIBRARY_BUILD_INTERACTIVE_TESTS AND NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )

# compilation and linking configuration
if( PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR )
    set( CMAKE_CXX_STANDARD 17 )

    if( MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" )
        add_compile_options(
            -Werror -Wall -Wextra
            -Wcast-align=strict
            -Wcast-qual
            -Wduplicated-cond
            -Wextra-semi
            -Wfloat-equal
            -Wimplicit-fallthrough=5
            -Wlogical-op
            -Wmissing-field-initializers
            -Wmissing-include-dirs
            -Wold-style-cast
            -Wplacement-new=2
            -Wpointer-arith
            -Wshadow
            -Wunsafe-loop-optimizations
            -fno-exceptions
            -fno-threadsafe-statics
            )

        if( MICROLIBRARY_BUILD_AUTOMATED_TESTS )
            add_compile_options(
                -fsanitize=address
                -fno-sanitize-recover=all
                )

            add_link_options(
                -fsanitize=address
                -fno-sanitize-recover=all
                )
        endif( MICROLIBRARY_BUILD_AUTOMATED_TESTS )
    endif( MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" )

    if( MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
        add_compile_options(
            -Werror -Wall -Wextra
            -Wcast-align=strict
            -Wcast-qual
            -Wduplicated-cond
            -Wextra-semi
            -Wfloat-equal
            -Wimplicit-fallthrough=5
            -Wlogical-op
            -Wmissing-field-initializers
            -Wmissing-include-dirs
            -Wold-style-cast
            -Wplacement-new=2
            -Wpointer-arith
            -Wshadow
            -Wunsafe-loop-optimizations
            -fno-exceptions
            -fno-threadsafe-statics
            )

        if( MICROLIBRARY_HIL STREQUAL "ARM_CORTEX_M0PLUS" )
            add_compile_options(
                -mcpu=cortex-m0plus
                -mthumb
                )
        endif( MICROLIBRARY_HIL STREQUAL "ARM_CORTEX_M0PLUS" )
    endif( MICROLIBRARY_TARGET STREQUAL "HARDWARE" )

    if( MICROLIBRARY_TARGET STREQUAL "NONE" )
        add_compile_options(
            -Werror -Wall -Wextra
            -Wcast-align
            -Wcast-qual
            -Wextra-semi
            -Wfloat-equal
            -Wimplicit-fallthrough
            -Wmissing-field-initializers
            -Wmissing-include-dirs
            -Wold-style-cast
            -Wpointer-arith
            -Wshadow
            -fno-exceptions
            -fno-threadsafe-statics
            )
    endif( MICROLIBRARY_TARGET STREQUAL "NONE" )
endif( PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR )

# automated testing configuration
if( MICROLIBRARY_BUILD_AUTOMATED_TESTS )
    enable_testing()
endif( MICROLIBRARY_BUILD_AUTOMATED_TESTS )

# library dependencies
add_subdirectory( dependencies )

# libraries
add_subdirectory( libraries )

# library tests
add_subdirectory( tests )
