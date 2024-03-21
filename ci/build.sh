#!/usr/bin/env bash

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

# Description: CI build script.

function error()
{
    local -r message="$1"

    ( >&2 echo "$mnemonic: $message" )
}

function abort()
{
    if [[ "$#" -gt 0 ]]; then
        local -r message="$1"

        error "$message, aborting"
    fi

    exit 1
}

function validate_script()
{
    if ! shellcheck "$script"; then
        abort
    fi
}

function display_help_text()
{
    local configuration

    printf "%b" \
        "NAME\n" \
        "    $mnemonic - Ensure no build errors are present.\n" \
        "SYNOPSIS\n" \
        "    $mnemonic --help\n" \
        "    $mnemonic --version\n" \
        "    $mnemonic --configuration <configuration>\n" \
        "OPTIONS\n" \
        "    --configuration <configuration>\n" \
        "        Specify the configuration to build. The following configurations are\n" \
        "        supported:\n" \
        ""

    for configuration in "${configurations[@]}"; do
        printf "%b" \
            "            $configuration\n" \
            ""
    done

    printf "%b" \
        "    --help\n" \
        "        Display this help text.\n" \
        "    --version\n" \
        "        Display the version of this script.\n" \
        "EXAMPLES\n" \
        "    $mnemonic --help\n" \
        "    $mnemonic --version\n" \
        ""

    for configuration in "${configurations[@]}"; do
        printf "%b" \
            "    $mnemonic --configuration $configuration\n" \
            ""
    done
}

function display_version()
{
    echo "$mnemonic, version $version"
}

function value_is_in_array()
{
    local -r target_value="$1"; shift
    local -r array=( "$@" )

    for value in "${array[@]}"; do
        if [[ "$target_value" == "$value" ]]; then
            return 0
        fi
    done

    return 1
}

function ensure_no_build_errors_are_present()
{
    local -r build_directory="$repository/build/$configuration"
    local -r build_configuration="$repository/configuration/$configuration/CMakeLists.txt"

    if ! cmake -C "$build_configuration" -S "$repository" -B "$build_directory"; then
        abort
    fi

    if ! cmake --build "$build_directory" -j "$( nproc )"; then
        abort
    fi
}

function main()
{
    local -r script=$( readlink -f "$0" )
    local -r mnemonic=$( basename "$script" )

    validate_script

    local -r repository=$( readlink -f "$( dirname "$script" )/.." )
    local -r version=$( git -C "$repository" describe --match=none --always --dirty --broken )

    local configurations; mapfile -t configurations < <( git -C "$repository" ls-files 'configuration/' | cut -f 2 -d / | sort -u | grep '^build-' ); readonly configurations

    while [[ "$#" -gt 0 ]]; do
        local argument="$1"; shift

        case "$argument" in
            --configuration)
                if [[ -n "$configuration" ]]; then
                    abort "build configuration already specified"
                fi

                if [[ "$#" -le 0 ]]; then
                    abort "build configuration not specified"
                fi

                local -r configuration="$1"; shift

                if ! value_is_in_array "$configuration" "${configurations[@]}"; then
                    abort "'$configuration' is not a supported build configuration"
                fi
                ;;
            --help)
                display_help_text
                exit
                ;;
            --version)
                display_version
                exit
                ;;
            --*)
                ;&
            -*)
                abort "'$argument' is not a supported option"
                ;;
            *)
                abort "'$argument' is not a valid argument"
                ;;
        esac
    done

    if [[ -z "$configuration" ]]; then
        abort "'--configuration' must be specified"
    fi

    ensure_no_build_errors_are_present
}

main "$@"
