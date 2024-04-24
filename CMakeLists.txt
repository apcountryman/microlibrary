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

set( MICROLIBRARY_HIL
    "" CACHE STRING
    "microlibrary: HIL."
    )

set( MICROLIBRARY_TARGET
    "" CACHE STRING
    "microlibrary: Target environment."
    )

option( MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION
    "microlibrary: Suppress human readable error information."
    OFF
    )

option( MICROLIBRARY_BUILD_AUTOMATED_TESTS
    "microlibrary: Build automated tests."
    OFF
    )

option( MICROLIBRARY_BUILD_INTERACTIVE_TESTS
    "microlibrary: Build interactive tests."
    OFF
    )

# general configuration validation

set( MICROLIBRARY_HIL_LIST
    "ARM_CORTEX_M0PLUS"
    "MICROCHIP_MEGAAVR"
    "MICROCHIP_MEGAAVR0"
    "MICROCHIP_SAM_D21DA1"
    "ALL"
    "CUSTOM"
    )
if( NOT MICROLIBRARY_HIL IN_LIST MICROLIBRARY_HIL_LIST )
    message( FATAL_ERROR
        "'${MICROLIBRARY_HIL}' is not a valid value for MICROLIBRARY_HIL.\n"
        "Please set it to a value from the first column of the following list:\n"
        "    ARM_CORTEX_M0PLUS      Generic Arm Cortex-M0+ HIL.\n"
        "    MICROCHIP_MEGAAVR      Microchip megaAVR HIL.\n"
        "    MICROCHIP_MEGAAVR      Microchip megaAVR 0-series HIL.\n"
        "    MICROCHIP_SAM_D21DA1   Microchip SAM D21/DA1 HIL.\n"
        "    ALL                    All officially supported HILs.\n"
        "    CUSTOM                 A HIL that is not officially supported.\n"
        )
endif( NOT MICROLIBRARY_HIL IN_LIST MICROLIBRARY_HIL_LIST )

set( MICROLIBRARY_TARGET_LIST
    "DEVELOPMENT_ENVIRONMENT"
    "HARDWARE"
    "NONE"
    )
if( NOT MICROLIBRARY_TARGET IN_LIST MICROLIBRARY_TARGET_LIST )
    message( FATAL_ERROR
        "'${MICROLIBRARY_TARGET}' is not a valid value for MICROLIBRARY_TARGET.\n"
        "Please set it to a value from the first column of the following list:\n"
        "    DEVELOPMENT_ENVIRONMENT    Development environment.\n"
        "    HARDWARE                   Hardware.\n"
        "    NONE                       None (used to exclude target specific code from static analysis).\n"
        )
endif( NOT MICROLIBRARY_TARGET IN_LIST MICROLIBRARY_TARGET_LIST )

if( MICROLIBRARY_HIL STREQUAL "ALL" AND NOT ( MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" OR MICROLIBRARY_TARGET STREQUAL "NONE" ) )
    message( FATAL_ERROR
        "MICROLIBRARY_TARGET must be 'DEVELOPMENT_ENVIRONMENT' or 'NONE' if MICROLIBRARY_HIL is 'ALL'"
        )
endif( MICROLIBRARY_HIL STREQUAL "ALL" AND NOT ( MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" OR MICROLIBRARY_TARGET STREQUAL "NONE" ) )

if( MICROLIBRARY_HIL STREQUAL "CUSTOM" AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR )
    message( FATAL_ERROR
        "Standalone builds are not supported if MICROLIBRARY_HIL is 'CUSTOM'"
        )
endif( MICROLIBRARY_HIL STREQUAL "CUSTOM" AND CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR )

if( MICROLIBRARY_BUILD_AUTOMATED_TESTS AND NOT MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" )
    message( FATAL_ERROR
        "automated tests can only be built if MICROLIBRARY_TARGET is 'DEVELOPMENT_ENVIRONMENT'"
        )
endif( MICROLIBRARY_BUILD_AUTOMATED_TESTS AND NOT MICROLIBRARY_TARGET STREQUAL "DEVELOPMENT_ENVIRONMENT" )

if( MICROLIBRARY_BUILD_AUTOMATED_TESTS AND MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION )
    message( FATAL_ERROR
        "microlibrary automated tests require human readable error information"
        )
endif( MICROLIBRARY_BUILD_AUTOMATED_TESTS AND MICROLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION )

if( MICROLIBRARY_BUILD_INTERACTIVE_TESTS AND NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
    message( FATAL_ERROR
        "interactive tests can only be built if MICROLIBRARY_TARGET is 'HARDWARE'"
        )
endif( MICROLIBRARY_BUILD_INTERACTIVE_TESTS AND NOT MICROLIBRARY_TARGET STREQUAL "HARDWARE" )

# Microchip SAM D21/DA1 HIL configuration
if( MICROLIBRARY_HIL STREQUAL "MICROCHIP_SAM_D21DA1" )
    if( MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
        set( MICROLIBRARY_MICROCHIP_SAM_D21DA1_MCU
            "" CACHE STRING
            "microlibrary: Microchip SAM D21/DA1 MCU type."
            )
    endif( MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
endif( MICROLIBRARY_HIL STREQUAL "MICROCHIP_SAM_D21DA1" )

# Microchip SAM D21/DA1 HIL configuration validation
if( MICROLIBRARY_HIL STREQUAL "MICROCHIP_SAM_D21DA1" )
    if( MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
        set( MICROLIBRARY_MICROCHIP_SAM_D21DA1_MCU_LIST
            "ATSAMD21E15A"
            "ATSAMD21E15B"
            "ATSAMD21E15C"
            "ATSAMD21E15L"
            "ATSAMD21E16A"
            "ATSAMD21E16B"
            "ATSAMD21E16C"
            "ATSAMD21E16L"
            "ATSAMD21E17A"
            "ATSAMD21E17D"
            "ATSAMD21E17L"
            "ATSAMD21E18A"
            "ATSAMD21G15A"
            "ATSAMD21G15B"
            "ATSAMD21G16A"
            "ATSAMD21G16B"
            "ATSAMD21G16L"
            "ATSAMD21G17A"
            "ATSAMD21G17D"
            "ATSAMD21G17L"
            "ATSAMD21G18A"
            "ATSAMD21J15A"
            "ATSAMD21J15B"
            "ATSAMD21J16A"
            "ATSAMD21J16B"
            "ATSAMD21J17A"
            "ATSAMD21J17D"
            "ATSAMD21J18A"
            "ATSAMDA1E14B"
            "ATSAMDA1E15B"
            "ATSAMDA1E16B"
            "ATSAMDA1G14B"
            "ATSAMDA1G15B"
            "ATSAMDA1G16B"
            "ATSAMDA1J14B"
            "ATSAMDA1J15B"
            "ATSAMDA1J16B"
            )
        if( NOT MICROLIBRARY_MICROCHIP_SAM_D21DA1_MCU IN_LIST MICROLIBRARY_MICROCHIP_SAM_D21DA1_MCU_LIST )
            message( FATAL_ERROR
                "'${MICROLIBRARY_MICROCHIP_SAM_D21DA1_MCU}' is not a valid Microchip SAM D21/DA1 MCU type"
                )
        endif( NOT MICROLIBRARY_MICROCHIP_SAM_D21DA1_MCU IN_LIST MICROLIBRARY_MICROCHIP_SAM_D21DA1_MCU_LIST )
    endif( MICROLIBRARY_TARGET STREQUAL "HARDWARE" )
endif( MICROLIBRARY_HIL STREQUAL "MICROCHIP_SAM_D21DA1" )

# CMake modules configuration
list( APPEND CMAKE_MODULE_PATH
    "${PROJECT_SOURCE_DIR}/cmake/modules/cmake-utilities"
    )

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
                -fprofile-arcs
                -ftest-coverage
                )

            add_link_options(
                -fsanitize=address
                -fno-sanitize-recover=all
                -fprofile-arcs
                -ftest-coverage
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

        if( MICROLIBRARY_HIL STREQUAL "MICROCHIP_MEGAAVR" )
            set( MICROLIBRARY_MICROCHIP_MEGAAVR_MCU
                "" CACHE STRING
                "microlibrary: Microchip megaAVR MCU type."
                )

            set( MICROLIBRARY_MICROCHIP_MEGAAVR_F_CPU
                "" CACHE STRING
                "microlibrary: Microchip megaAVR CPU frequency, in Hz."
                )

            add_compile_options(
                -mmcu=${MICROLIBRARY_MICROCHIP_MEGAAVR_MCU}
                -B "${PROJECT_SOURCE_DIR}/dfps/dfp-microchip-atmega/dfp/gcc/dev/${MICROLIBRARY_MICROCHIP_MEGAAVR_MCU}"
                )

            add_compile_definitions(
                F_CPU=${MICROLIBRARY_MICROCHIP_MEGAAVR_F_CPU}
                )

            add_link_options(
                -mmcu=${MICROLIBRARY_MICROCHIP_MEGAAVR_MCU}
                )

            include_directories( SYSTEM
                "${PROJECT_SOURCE_DIR}/dfps/dfp-microchip-atmega/dfp/include"
                )
        endif( MICROLIBRARY_HIL STREQUAL "MICROCHIP_MEGAAVR" )

        if( MICROLIBRARY_HIL STREQUAL "MICROCHIP_MEGAAVR0" )
            set( MICROLIBRARY_MICROCHIP_MEGAAVR0_MCU
                "" CACHE STRING
                "microlibrary: Microchip megaAVR 0-series MCU type."
                )

            set( MICROLIBRARY_MICROCHIP_MEGAAVR0_F_CPU
                "" CACHE STRING
                "microlibrary: Microchip megaAVR 0-series CPU frequency, in Hz."
                )

            add_compile_options(
                -mmcu=${MICROLIBRARY_MICROCHIP_MEGAAVR0_MCU}
                -B "${PROJECT_SOURCE_DIR}/dfps/dfp-microchip-atmega/dfp/gcc/dev/${MICROLIBRARY_MICROCHIP_MEGAAVR0_MCU}"
                )

            add_compile_definitions(
                F_CPU=${MICROLIBRARY_MICROCHIP_MEGAAVR0_F_CPU}
                )

            add_link_options(
                -mmcu=${MICROLIBRARY_MICROCHIP_MEGAAVR0_MCU}
                )

            include_directories( SYSTEM
                "${PROJECT_SOURCE_DIR}/dfps/dfp-microchip-atmega/dfp/include"
                )
        endif( MICROLIBRARY_HIL STREQUAL "MICROCHIP_MEGAAVR0" )

        if( MICROLIBRARY_HIL STREQUAL "MICROCHIP_SAM_D21DA1" )
            add_compile_options(
                -mcpu=cortex-m0plus
                -mthumb
                )
        endif( MICROLIBRARY_HIL STREQUAL "MICROCHIP_SAM_D21DA1" )
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
    set( MICROLIBRARY_AUTOMATED_TESTS_OPTIONS
        --gtest_color=yes
        )

    include( lcov-utilities )
    add_lcov_coverage_target( microlibrary-automated-tests-coverage
        ctest
        EXECUTABLE_ARGUMENTS --tests-regex test-automated-microlibrary*
        INCLUDE_BRANCH_COVERAGE
        EXCLUDE_EXTERNAL_SOURCE_FILES
        REMOVE
            */dependencies/*
            */include/microlibrary/testing.h
            */include/microlibrary/testing/*
            */source/microlibrary/testing.h
            */source/microlibrary/testing/*
            */tests/*
        )

    enable_testing()
endif( MICROLIBRARY_BUILD_AUTOMATED_TESTS )

# library dependencies
add_subdirectory( dependencies )

# libraries
add_subdirectory( libraries )

# library tests
add_subdirectory( tests )
